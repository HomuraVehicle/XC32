#ifndef XC32_I2CBASE_INC
#define XC32_I2CBASE_INC 100
#
#include"exceptions.hpp"
#include"sfr/interrupt.hpp"
#include"clock.hpp"

namespace xc32{
	namespace i2c {
		namespace clockmode{
			enum type{
				_1MHz = 500,//clock_1MHz=1000,
				_400kHz = 1250,//clock_400kHz=2500
				_100kHz = 5000
			};
		}
		struct exception :public xc32::exception{};
		struct not_lock_exception :public exception{};
	}
	template<typename i2c_register_>
	class synchronous_i2c{
/*
//I2C�̎g����
	i2c.start(slave_adress,0);
	i2c.write('A');
	i2c.write('B');
	i2c.write('C');
	i2c.restart(slave_adress,1);
	Buf[1]=i2c.read(0);
	Buf[2]=i2c.read(0);
	Buf[3]=i2c.read(0);
	Buf[4]=i2c.read(1);
	i2c.stop();
*/
	private:
		i2c_register_ Register;
		i2c::clockmode::type ClockMode;
		unsigned int nsPGD;
	public:
		synchronous_i2c() 
			: ClockMode(i2c::clockmode::_400kHz)
			, nsPGD(0){
		}
	public:
		void config(i2c::clockmode::type ClockMode_, unsigned int nsPGD_){
			ClockMode=ClockMode_;
			nsPGD=nsPGD_;
		}
		bool lock(i2c::clockmode::type ClockMode_, unsigned int nsPGD_){
			config(ClockMode_,nsPGD_);
			return lock();
		}
		bool lock(){
			if(is_lock())return false;

			if(Register.lock())return true;

			//�R���g���[�����W�X�^���N���A
			Register.reset_all_config();
			//�{�[���[�g����I2C�N���b�N�𐶐����邽�߂̉����ݒ�
			Register.baud_rate_register((static_cast<unsigned long>(static_cast<unsigned long>(ClockMode-nsPGD)*(clock::get_bus_clock()/100000))-20000)/10000);
			//I2C�L����
			Register.enable(true);
			Register.interrupt_flag(false);

			return false;
		}
		bool is_lock()const{
			return Register.is_lock();
		}
		void unlock(){
			if(!is_lock())return;

			//�R���g���[�����W�X�^���N���A
			Register.reset_all_config();
			//I2C��~
			Register.enable(false);

			Register.unlock();
		}
	private:
		//ACK���M
		void sendACK(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//ACK���M���[�h�ɐݒ�
			Register.ack_data(false);
			//ACK���M
			Register.ack_enable(true);
			//ACK���M�I���ҋ@
			while(Register.ack_enable()==1);
		}
		//NACK���M
		void sendNACK(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//NACK���M���[�h�ɐݒ�
			Register.ack_data(true);
			//NACK���M
			Register.ack_enable(true);
			//NACK���M�I���ҋ@
			while(Register.ack_enable()==1);
		}
		//NACK��M�m�F
		bool checkNACK(){//const volatile{
			xc32_assert(is_lock(), i2c::not_lock_exception());

			return Register.ack_status();
		}
	public:
		bool start(unsigned char address_,bool IO_){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//�ʐM�J�n
			Register.start_enable(true);
			//�ʐM�J�n�����I���ҋ@
			while(Register.start_enable()==1);

			//slave address��IO(write or read)�𑗐M
			Register.transmit_data((0x01&static_cast<unsigned char>(IO_))|(address_<<1));
			//�f�[�^���M�����I���ҋ@
			while(Register.transmit_buf_full()==1);

			return checkNACK();
		}
		bool restart(unsigned char address_,bool IO_){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//�ʐM�ĊJ
			Register.restart_enable(true);
			//�ʐM�ĊJ�����I���ҋ@
			while(Register.restart_enable()==1);

			//slave address��IO(write or read)�𑗐M
			Register.transmit_data((0x01&static_cast<unsigned char>(IO_))|(address_<<1));
			//�f�[�^���M�����I���ҋ@
			while(Register.transmit_buf_full()==1);

			return checkNACK();
		}
		void stop(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//�ʐM�I�������J�n
			Register.stop_enable(true);	
			//�ʐM�I�������I���ҋ@
			while(Register.stop_enable()==1);

			//PIC32MZ�n�̃o�O�H�̂����ōċN�����Ȃ��Ƃ���ȍ~�̏��������܂����삵�Ȃ��C�ڂ�����evernote�Q��
			Register.enable(false);
			__asm("nop");
			Register.enable(true);
			__asm("nop");
		}
		bool write(unsigned char data_){
			xc32_assert(is_lock(), i2c::not_lock_exception());
			//�o�b�t�@�ɏ�������
			Register.transmit_data(data_);
			//�f�[�^���M�����I���ҋ@
			while(Register.transmit_buf_full()==1);

			return checkNACK();
		}
		unsigned char read(bool EndFlag_){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//��Menable
			Register.receive_enable(true);
			//�f�[�^��M�����I���ҋ@
			while(Register.receive_enable()==1);

			//slave��ACK/NACK���M
			if(EndFlag_)sendNACK();	//NACK���M�i��M�����I���j
			else sendACK();			//ACK���M�i��M���������j

			//��M���W�X�^��Ԃ�
			return Register.receive_data();
		}
	};

	template<typename i2c_register_,typename identifier_>
	class shared_i2c{
		/*
		//I2C�̎g����
		i2c.start(slave_adress,0);
		i2c.write('A');
		i2c.write('B');
		i2c.write('C');
		i2c.restart(slave_adress,1);
		Buf[1]=i2c.read(0);
		Buf[2]=i2c.read(0);
		Buf[3]=i2c.read(0);
		Buf[4]=i2c.read(1);
		i2c.stop();
		*/
	private:
		typedef shared_i2c<i2c_register_, identifier_> my_type;
	private:
		static bool IsUsed;
		static i2c_register_ Register;
		static i2c::clockmode::type ClockMode;
		static unsigned int nsPGD;
	public:
		static void config(i2c::clockmode::type ClockMode_, unsigned int nsPGD_){
			ClockMode = ClockMode_;
			nsPGD = nsPGD_;
		}
		static bool lock(i2c::clockmode::type ClockMode_, unsigned int nsPGD_){
			config(ClockMode_, nsPGD_);
			return lock();
		}
		static bool lock(){
			if(is_lock())return false;

			if(Register.lock())return true;

			//�R���g���[�����W�X�^���N���A
			Register.reset_all_config();
			//�{�[���[�g����I2C�N���b�N�𐶐����邽�߂̉����ݒ�
			Register.baud_rate_register((static_cast<unsigned long>(static_cast<unsigned long>(ClockMode - nsPGD)*(clock::get_bus_clock() / 100000)) - 20000) / 10000);
			//I2C�L����
			Register.enable(true);
			Register.interrupt_flag(false);

			return false;
		}
		static bool is_lock(){
			return Register.is_lock();
		}
		static void unlock(){
			if(!is_lock())return;

			//�R���g���[�����W�X�^���N���A
			Register.reset_all_config();
			//I2C��~
			Register.enable(false);

			Register.unlock();
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

				//���b�N
				if(IsUsed)return true;
				IsUsed = true;
				IsLock = true;

				return false;
			}
			bool is_lock()const{
				return IsLock;
			}
			void unlock(){
				//���b�N��O
				if(!is_lock())return;

				IsUsed = false;
				IsLock = false;

				return;
			}
		private:
			//ACK���M
			void sendACK(){
				xc32_assert(is_lock(), i2c::not_lock_exception());

				//ACK���M���[�h�ɐݒ�
				Register.ack_data(false);
				//ACK���M
				Register.ack_enable(true);
				//ACK���M�I���ҋ@
				while(Register.ack_enable() == 1);
			}
			//NACK���M
			void sendNACK(){
				xc32_assert(is_lock(), i2c::not_lock_exception());

				//NACK���M���[�h�ɐݒ�
				Register.ack_data(true);
				//NACK���M
				Register.ack_enable(true);
				//NACK���M�I���ҋ@
				while(Register.ack_enable() == 1);
			}
			//NACK��M�m�F
			bool checkNACK(){//const volatile{
				xc32_assert(is_lock(), i2c::not_lock_exception());

				return Register.ack_status();
			}
		public:
			bool start(unsigned char address_, bool IO_){
				xc32_assert(is_lock(), i2c::not_lock_exception());

				//�ʐM�J�n
				Register.start_enable(true);
				//�ʐM�J�n�����I���ҋ@
				while(Register.start_enable() == 1);

				//slave address��IO(write or read)�𑗐M
				Register.transmit_data((0x01 & static_cast<unsigned char>(IO_)) | (address_ << 1));
				//�f�[�^���M�����I���ҋ@
				while(Register.transmit_buf_full() == 1);

				return checkNACK();
			}
			bool restart(unsigned char address_, bool IO_){
				xc32_assert(is_lock(), i2c::not_lock_exception());

				//�ʐM�ĊJ
				Register.restart_enable(true);
				//�ʐM�ĊJ�����I���ҋ@
				while(Register.restart_enable() == 1);

				//slave address��IO(write or read)�𑗐M
				Register.transmit_data((0x01 & static_cast<unsigned char>(IO_)) | (address_ << 1));
				//�f�[�^���M�����I���ҋ@
				while(Register.transmit_buf_full() == 1);

				return checkNACK();
			}
			void stop(){
				xc32_assert(is_lock(), i2c::not_lock_exception());

				//�ʐM�I�������J�n
				Register.stop_enable(true);
				//�ʐM�I�������I���ҋ@
				while(Register.stop_enable() == 1);

				//PIC32MZ�n�̃o�O�H�̂����ōċN�����Ȃ��Ƃ���ȍ~�̏��������܂����삵�Ȃ��C�ڂ�����evernote�Q��
				Register.enable(false);
				__asm("nop");
				Register.enable(true);
				__asm("nop");
			}
			bool write(unsigned char data_){
				xc32_assert(is_lock(), i2c::not_lock_exception());
				//�o�b�t�@�ɏ�������
				Register.transmit_data(data_);
				//�f�[�^���M�����I���ҋ@
				while(Register.transmit_buf_full() == 1);

				return checkNACK();
			}
			unsigned char read(bool EndFlag_){
				xc32_assert(is_lock(), i2c::not_lock_exception());

				//��Menable
				Register.receive_enable(true);
				//�f�[�^��M�����I���ҋ@
				while(Register.receive_enable() == 1);

				//slave��ACK/NACK���M
				if(EndFlag_)sendNACK();	//NACK���M�i��M�����I���j
				else sendACK();			//ACK���M�i��M���������j

				//��M���W�X�^��Ԃ�
				return Register.receive_data();
			}
		};
	};
	template<typename i2c_register_, typename identifier_>
	bool shared_i2c<i2c_register_,identifier_>::IsUsed=false;
	template<typename i2c_register_, typename identifier_>
	i2c_register_  shared_i2c<i2c_register_,identifier_>::Register;
	template<typename i2c_register_, typename identifier_>
	i2c::clockmode::type  shared_i2c<i2c_register_,identifier_>::ClockMode = i2c::clockmode::_400kHz;
	template<typename i2c_register_, typename identifier_>
	unsigned int  shared_i2c<i2c_register_,identifier_>::nsPGD=0;

	template<typename i2c_register_>
	class interrupt_i2c{
/*
//I2C���荞�ݎg����
void __attribute__((interrupt, no_auto_psv)) _MI2C2Interrupt(void){
	static bool ACKFlag=0;
	static uint8 status=0;
	static uint8 SendCnt=0;
	static uint8 RecvCnt=0;

	interrupt_i2c.clear_interrupt_flag();		//Clear the DMA0 Interrupt Flag;
	
	if(ACKFlag){
		if(interrupt_i2c.checkNACK())status=0;
	}
	ACKFlag=0;

	switch (status){
		case 1:
			interrupt_i2c.setup_start();
			++status;
			ACKFlag=1;
			break;
		case 2:
			interrupt_i2c.do_start(slave_address,0);
			++status;
			ACKFlag=1;
			break;
		case 3:
			interrupt_i2c.write(Buf[SendCnt++]);
			if(SendCnt>X)++status;
			ACKFlag=1;
			break;
		case 4:
			interrupt_i2c.setup_restart();
			++status;
			ACKFlag=1;
			break;
		case 5:
			interrupt_i2c.do_restart(slave_address,1);
			++status;
			ACKFlag=1;
			break;
		case 6:
			if(RecvCnt%2==0)interrupt_i2c.settup_read();
			else Buf[RecvCnt]=interrupt_i2c.do_read;
			++RecvCnt;
			if(RecvCnt>Y)++status;
			break;
		case 7:
			interrupt_i2c.stop();
			status=0;
			break;
		default:
			break;
	}
}
*/
	private:
		i2c_register_ Register;
		sfr::interrupt::function* pInterrupt;
		unsigned char InterruptPriorityLv;
		i2c::clockmode::type ClockMode;
		unsigned int nsPGD;
	public:
		interrupt_i2c() 
			: pInterrupt(0)
			, InterruptPriorityLv(i2c_register_::ipl)
			, ClockMode(i2c::clockmode::_400kHz)
			, nsPGD(0){
		}
	public:
		void config(sfr::interrupt::function& Interrupt_, i2c::clockmode::type ClockMode_, unsigned int nsPGD_ = 0, unsigned char InterruptPriorityLv_ = i2c_register_::ipl) {
			pInterrupt=&Interrupt_;
			InterruptPriorityLv=InterruptPriorityLv_;
			ClockMode=ClockMode_;
			nsPGD=nsPGD_;
		}
		bool lock(sfr::interrupt::function& Interrupt_, i2c::clockmode::type ClockMode_, unsigned int nsPGD_ = 0, unsigned char InterruptPriorityLv_ = i2c_register_::ipl) {
			config(Interrupt_, ClockMode_, nsPGD_, InterruptPriorityLv_);
			return lock();
		}
		bool lock(){
			if(is_lock())return false;

			if(pInterrupt==0)return true;
			if(lock(Register))return true;

			Register.interrupt_function(*pInterrupt);

			//�R���g���[�����W�X�^���N���A
			Register.control_register(0);
			//�{�[���[�g����I2C�N���b�N�𐶐����邽�߂̉����ݒ�
			Register.boud_rate_generator((static_cast<unsigned long>(ClockMode+nsPGD)*(clock::get_bus_clock()/100000)-10000)/10000);
			//interrupt priority level�ݒ�
			Register.interrupt_priority_level(InterruptPriorityLv);
			//I2C�L����
			Register.enable(true);

			return false;
		}
		bool is_lock()const{
			return Register.is_lock();
		}
		void unlock(){
			if(!is_lock())return;

			//�R���g���[�����W�X�^���N���A
			Register.reset_all_config();
			//I2C��~
			Register.enable(false);

			Register.unlock();
		}
	private:
		//ACK���M
		inline void sendACK(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//ACK���M���[�h�ɐݒ�
			Register.ack_data(false);
			//ACK���M
			Register.ack_enable(true);
		}
		//NACK���M
		inline void sendNACK(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			//NACK���M���[�h�ɐݒ�
			Register.ack_data(true);
			//NACK���M
			Register.ack_enable(true);
		}
	public:
		//���荞�݊֐����ŕK���s�������ɕK�v�Ȃ��̂�lock�m�F���Ȃ�
		void enable(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.interrupt_enable(true);
		}
		void diable(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.interrupt_enable(false);
		}
		void clear_flag(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.interrupt_flag(false);
		}
		bool is_enable(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			return Register.interrupt_enable();
		}
		void setup_start(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.start_enable(true);
		}
		void do_start(unsigned char address_,bool IO_){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.transmit_data((0x01&static_cast<unsigned char>(IO_))|(address_<<1));
		}
		void setup_restart(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.restart_enable(true);
		}
		void do_restart(unsigned char address_,bool IO_){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			do_start(address_,IO_);
		}
		void stop(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.stop_enable(true);
		}
		void write(unsigned char data_){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.transmit_data(data_);
		}
		void setup_read(){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			Register.receive_enable(true);
		}
		unsigned char do_read(bool EndFlag){
			xc32_assert(is_lock(), i2c::not_lock_exception());

			if(Register.is_lock())return 0;
			Register.lock();
			//slave��ACK/NACK���M
			if(EndFlag)sendNACK();		//NACK���M�i��M�����I���j
			else sendACK();			//ACK���M

			//��M���W�X�^��Ԃ�
			unsigned char tmp=Register.receive_data();
			Register.unlock();
			return tmp;
		}
		//NACK��M�m�F
		bool checkNACK()const volatile{return Register.ack_status();}
	};
}

#
#endif
