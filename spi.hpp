#ifndef XC32LIB_SPI_INC
#define XC32LIB_SPI_INC 101
#
#include"exceptions.hpp"
#include"sfr/interrupt.hpp"
//*********** SPI関連関数 ***********************
//SPIの初期設定を行った後、書き込んで、読み取って関数を使う
// 選択していないPINは highで保持しておく必要がある 
//

namespace xc32{
	namespace spi {
		struct exception :public xc32::exception{};		
		struct not_lock_exception :public exception{};
	}
	//同期関数型SPI
	template<typename spi_register_>
	class synchronous_spi{
	private:
		spi_register_ Register;
		bool IsMaster;
		bool ClockPolarity;
		unsigned int ClockDiv;
	public:
		synchronous_spi()
			: Register()
			, IsMaster(true)
			, ClockPolarity(false)
			, ClockDiv(0){
		}
	public:
		void config(bool IsMaster_,bool ClockPolarity_,unsigned int ClockDiv_){
			IsMaster=IsMaster_;
			ClockPolarity=ClockPolarity_;
			ClockDiv=ClockDiv_;
		}
		bool lock(bool IsMaster_,bool ClockPolarity_,unsigned int ClockDiv_){
			config(IsMaster_,ClockPolarity_,ClockDiv_);
			return lock();
		}
		bool lock(){
			if(is_lock())return false;

			if(ClockDiv==0 || ClockDiv>1024)return true;

			//ロック
			if(Register.lock())return true;
			
			//設定全クリア
			Register.reset_all_config();
			//バッファクリア
			Register.buffer(0);
			//受信オーバーフローフラグクリア
			Register.receive_overflow(0);
			//High to Low かLow to Highかの設定
			Register.clock_polarity(ClockPolarity);
			//Master or Slave
			Register.master_mode(IsMaster);
			//SS pinを使うか？(slaveのときだけ使う，Masterのときは自分で上げ下げする)
			Register.slave_select_enable(!IsMaster);

			//Masterの場合はSPIのクロック速度の設定
			if(IsMaster){
				//一応，奇数を指定されたときのための処理
				//F_SCK = systemclock_ / clockdiv_		clockdiv_は2の倍数で1024まで，2の倍数でない時は勝手に+1します
				if(ClockDiv % 2)Register.baud_rate_register((ClockDiv + 1) / 2 - 1);
				else Register.baud_rate_register(ClockDiv/2 -1);
			}

			//電源ON
			Register.enable(true);

			return false;
		}
		bool is_lock()const{
			return Register.is_lock();
		}
		void unlock(){
			//ロック例外
			if(!is_lock())return;

			//電源OFF
			Register.enable(false);
			//設定全クリア
			Register.reset_all_config();

			//ロック解除
			Register.unlock();

			return;
		}
	public:
		bool in_data()const volatile{
			xc32_assert(is_lock(), spi::not_lock_exception());

			return Register.receive_overflow();
		}
		unsigned char read(unsigned char data_){
			xc32_assert(is_lock(), spi::not_lock_exception());

			Register.receive_overflow(false);
			Register.buffer(data_);
			while(!Register.receive_buf_full());
			return Register.buffer();
		}
		void write(unsigned char data_) {
			xc32_assert(is_lock(), spi::not_lock_exception());

			read(data_);
		}
	};

	//同期関数型SPI
	template<typename spi_register_, typename identifier_>
	class shared_spi{
	private:
		typedef shared_spi<spi_register_, identifier_> my_type;
	private:
		static bool IsUsed;
		static spi_register_ Register;
		static bool IsMaster;
		static bool ClockPolarity;
		static unsigned int ClockDiv;
	public:
		static void config(bool IsMaster_, bool ClockPolarity_, unsigned int ClockDiv_){
			IsMaster = IsMaster_;
			ClockPolarity = ClockPolarity_;
			ClockDiv = ClockDiv_;
		}
		static bool lock(bool IsMaster_, bool ClockPolarity_, unsigned int ClockDiv_){
			config(IsMaster_, ClockPolarity_, ClockDiv_);
			return lock();
		}
		static bool lock(){
			if(is_lock())return false;

			if(ClockDiv == 0 || ClockDiv>1024)return true;

			//ロック
			if(Register.lock())return true;

			//設定全クリア
			Register.reset_all_config();
			//バッファクリア
			Register.buffer(0);
			//受信オーバーフローフラグクリア
			Register.receive_overflow(0);
			//High to Low かLow to Highかの設定
			Register.clock_polarity(ClockPolarity);
			//Master or Slave
			Register.master_mode(IsMaster);
			//SS pinを使うか？(slaveのときだけ使う，Masterのときは自分で上げ下げする)
			Register.slave_select_enable(!IsMaster);

			//Masterの場合はSPIのクロック速度の設定
			if(IsMaster){
				//一応，奇数を指定されたときのための処理
				//F_SCK = systemclock_ / clockdiv_		clockdiv_は2の倍数で1024まで，2の倍数でない時は勝手に+1します
				if(ClockDiv % 2)Register.baud_rate_register((ClockDiv + 1) / 2 - 1);
				else Register.baud_rate_register(ClockDiv / 2 - 1);
			}

			//電源ON
			Register.enable(true);

			return false;
		}
		static bool is_lock(){
			return Register.is_lock();
		}
		static void unlock(){
			//ロック例外
			if(!is_lock())return;

			//電源OFF
			Register.enable(false);
			//設定全クリア
			Register.reset_all_config();

			//ロック解除
			Register.unlock();

			return;
		}
	public:
		class client{
		private:
			bool IsLock;
		public:
			client() : IsLock(false){}
		public:
			bool lock(){
				if(is_lock())return false;
				if(!my_type::is_lock())return true;

				//ロック
				if(IsUsed)return true;
				IsUsed = true;
				IsLock = true;

				return false;
			}
			bool is_lock()const{
				return IsLock;
			}
			void unlock(){
				//ロック例外
				if(!is_lock())return;

				IsUsed = false;
				IsLock = false;

				return;
			}
		public:
			bool in_data()const volatile{
				xc32_assert(is_lock(), spi::not_lock_exception());
				return Register.receive_overflow();
			}
			unsigned char read(unsigned char data_){
				xc32_assert(is_lock(), spi::not_lock_exception());
				Register.receive_overflow(false);
				Register.buffer(data_);
				while(!Register.receive_buf_full());
				return Register.buffer();
			}
			void write(unsigned char data_) {
				xc32_assert(is_lock(), spi::not_lock_exception());

				read(data_);
			}
		};
	};
	template<typename spi_register_, typename identifier_>
	bool shared_spi<spi_register_, identifier_>::IsUsed = false;
	template<typename spi_register_, typename identifier_>
	spi_register_ shared_spi<spi_register_, identifier_>::Register;
	template<typename spi_register_, typename identifier_>
	bool shared_spi<spi_register_, identifier_>::IsMaster = false;
	template<typename spi_register_, typename identifier_>
	bool shared_spi<spi_register_, identifier_>::ClockPolarity = false;
	template<typename spi_register_, typename identifier_>
	unsigned int shared_spi<spi_register_, identifier_>::ClockDiv = 0;

	//割り込み関数型SPI
	template<typename spi_register_>
	class interrupt_spi{
	private:
		spi_register_ Register;
		sfr::interrupt::function* pInterrupt;
		unsigned char InterruptPriorityLv;
		bool IsMaster;
		bool ClockPolarity;
		unsigned int ClockDiv;
	public:
		interrupt_spi()
			:pInterrupt(0)
			,InterruptPriorityLv(spi_register_::rx_ipl)
			,IsMaster(false)
			,ClockPolarity(false)
			,ClockDiv(0){
		}
	public:
		void config(bool IsMaster_, bool ClockPolarity_, unsigned int ClockDiv_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=spi_register_::rx_ipl) {
			pInterrupt=&Interrupt_;
			InterruptPriorityLv=InterruptPriorityLv_;
			IsMaster=IsMaster_;
			ClockPolarity=ClockPolarity_;
			ClockDiv=ClockDiv_;
		}
		bool lock(bool IsMaster_, bool ClockPolarity_, unsigned int ClockDiv_, sfr::interrupt::function& Interrupt_, unsigned char InterruptPriorityLv_=spi_register_::rx_ipl) {
			config(IsMaster_, ClockPolarity_, ClockDiv_, Interrupt_, InterruptPriorityLv_);
			return lock();
		}
		bool lock(){
			if(is_lock())return false;

			if(ClockDiv==0 || ClockDiv>1024)return true;

			if(pInterrupt==0)return true;

			if(lock(Register))return true;

			Register.interrupt_function(*pInterrupt);

			//High to Low かLow to Highかの設定
			Register.clock_polarity(ClockPolarity);
			//Master or Slave
			Register.master_mode(IsMaster);
			//SS pinを使うか？(slaveのときだけ使う，Masterのときは自分で上げ下げする)
			Register.slave_select(!IsMaster);
			//Masterの場合はSPIのクロック速度の設定
			if(IsMaster) {
				//一応，奇数を指定されたときのための処理
				if(ClockDiv%2)Register.baud_rate_generator((ClockDiv+1)/2 -1);
				else Register.baud_rate_generator(ClockDiv/2 -1);
			}//slaveのときはバッファクリア 
			else {
				Register.buffer(0);
			}
			Register.interrupt_priority_level(InterruptPriorityLv);
			Register.receive_overflow(false);
			Register.enable(true);

			return false;
		}
		bool is_lock()const{
			return Register.is_lock();
		}
		void unlock(){
			if(!is_lock())return;

			Register.enable(false);
			Register.reset_all_config();

			Register.unlock();
		}
	public:
		//割り込み関数内で必ず行う処理に必要なものはlock確認しない
		bool is_enable()const {
			xc32_assert(is_lock(), spi::not_lock_exception());

			return Register.interrupt_enable(); 
		}
		void enable(){
			xc32_assert(is_lock(), spi::not_lock_exception());

			Register.interrupt_enable(true);
		}
		void disable(){
			xc32_assert(is_lock(), spi::not_lock_exception());

			Register.interrupt_enable(false);
		}
		bool is_flag()const volatile{
			xc32_assert(is_lock(), spi::not_lock_exception());

			return Register.interrupt_flag(); 
		}
		void clear_flag() {
			xc32_assert(is_lock(), spi::not_lock_exception());

			return Register.interrupt_flag(false); 
		}
		void set_flag() {
			xc32_assert(is_lock(), spi::not_lock_exception());

			return Register.interrupt_flag(true); 
		}
		bool in_data()const volatile {
			xc32_assert(is_lock(), spi::not_lock_exception());
			return Register.receive_overflow();
		}
		unsigned char data(unsigned char data_){
			xc32_assert(is_lock(), spi::not_lock_exception());

			//SPI割り込み時に必ず送られてきたデータを読んであげないと正常に割り込みが生成されないので読みこみだけは必ずやってあげる
			unsigned char tmp=Register.buffer();
			Register.buffer(data_);
			return tmp;
		}
	};
}

#
#endif
