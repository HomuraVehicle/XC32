#include<XCBase/type.hpp>
#include<XC32Lib/interrupt.hpp>
#include<XC32Lib/sfr/exclusive_mixin.hpp>
#include<XC32Lib/sfr/sfr_register_mixin.hpp>
namespace xc32{
	namespace test{
		union virtualI2CCONbits_t{
			struct {
				unsigned SEN : 1;
				unsigned RSEN : 1;
				unsigned PEN : 1;
				unsigned RCEN : 1;
				unsigned ACKEN : 1;
				unsigned ACKDT : 1;
				unsigned STREN : 1;
				unsigned GCEN : 1;
				unsigned SMEN : 1;
				unsigned DISSLW : 1;
				unsigned A10M : 1;
				unsigned STRICT : 1;
				unsigned SCLREL : 1;
				unsigned SIDL : 1;
				unsigned : 1;
				unsigned ON : 1;
				unsigned DHEN : 1;
				unsigned AHEN : 1;
				unsigned SBCDE : 1;
				unsigned SDAHT : 1;
				unsigned BOEN : 1;
				unsigned SCIE : 1;
				unsigned PCIE : 1;
			};
			struct {
				unsigned : 11;
				unsigned IPMIEN : 1;
				unsigned : 1;
				unsigned I2CSIDL : 1;
				unsigned : 1;
				unsigned I2CEN : 1;
			};
			xc::uint16 val;
		}Test;
		using namespace sfr;
		template<unsigned int no_>
		struct virtual_i2c_register :public sfr_register_mixin<virtual_i2c_register<no_>>, public exclusive_mixin<virtual_i2c_register<no_>>{
			static unsigned int i2c_no(){ return 100+no_; }
			static virtualI2CCONbits_t I2CCONbits;
			static bool IE;
			static bool IF;
			static unsigned char IP;
			static unsigned char IS;
			static unsigned char Rcv;
			static unsigned char Trn;
		public:
			//Start Condition Enable bit : I2CxCONbits.SEN
			void start_enable(bool val_){ I2CCONbits.SEN = static_cast<unsigned char>(val_); }
			bool start_enable()const{ return static_cast<bool>(I2CCONbits.SEN); }
			//Restart Condition Enable bit : I2CxCONbits.RSEN
			void restart_enable(bool val_){ I2CCONbits.RSEN = static_cast<unsigned char>(val_); }
			bool restart_enable()const{ return static_cast<bool>(I2CCONbits.RSEN); }
			//Stop Condition bit : I2CxCONbits.PEN
			void stop_enable(bool val_){ I2CCONbits.PEN = static_cast<unsigned char>(val_); }
			bool stop_enable()const{ return static_cast<bool>(I2CCONbits.PEN); }
			//Receive Enable bit : I2CxCONbits.RCEN
			void receive_enable(bool val_){ I2CCONbits.RCEN = static_cast<unsigned char>(val_); }
			bool receive_enable()const{ return static_cast<bool>(I2CCONbits.RCEN); }
			//ACK Sequence Enable bit : I2CxCONbits.ACKEN
			void ack_enable(bool val_){ I2CCONbits.ACKEN = static_cast<unsigned char>(val_); }
			bool ack_enable()const{ return static_cast<bool>(I2CCONbits.ACKEN); }
			//ACK Data bit : I2CxCONbits.ACKDT
			void ack_data(bool val_){ I2CCONbits.ACKDT = static_cast<unsigned char>(val_); }
			//Master Interrupt Flag : IFSxbits.I2CxMIF
			void interrupt_flag(bool val_){ IF = static_cast<unsigned char>(val_); }
			bool interrupt_flag()const { return static_cast<bool>(IF); }
			//interrupt enable bit : IECxbits.I2CxMIE
			void interrupt_enable(bool val_){ IE= static_cast<unsigned char>(val_); }
			bool interrupt_enable()const{ return static_cast<bool>(IE); }
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_priority_level(unsigned char val_){ IP= val_; }
			unsigned char interrupt_priority_level(){ return IP; }
			//Interrupt priority level : IPCxbits.I2CxIP
			void interrupt_sub_priority_level(unsigned char val_){ IS= val_; }
			unsigned char interrupt_sub_priority_level(){ return IS; }
			//Receive Data Register : I2CxRCV
			unsigned char receive_data(){ return static_cast<unsigned char>(Rcv); }
			//Transmit Data Register : I2CxTRN
			void transmit_data(unsigned char val_){ Trn = val_; }
			//ACK Status bti : I2CxSTATbits.ACKSTAT(0:ACK was received,1:ACK was not received)
			bool ack_status()const { return false; }
			//Receive Buffer Full Status bit : I2CxSTATbits.RBF
			bool receive_buf_full()const { return false; }
			//Transmit Buffer Full Status bit : I2CxSTATbits.TBF
			bool transmit_buf_full()const{ return false; }

			//Boud Rate Generator bits : I2CxBRG (ボーレートからI2Cクロックを生成するための何か設定)
			/*
			BRG= ( 1/(2*FSCL) - PGD ) * PBCLK -2
			FSCL：I2C側のクロックスピード 100k,400k,1Mの3種類が主流らしい
			100k:1.0e-5s=10000ns
			400k:2.5e-6s= 2500ns
			1M:1.0e-6s= 1000ns
			PGD : Pulse_Gobbler_Delay デバイス固有　データシート参照
			Pic4EP512GU810:1.30e-7
			FCY : システム側のクロック PLL後　ただし，DOZE利用の場合はCPUクロックと一致しない
			*/
			void baud_rate_register(unsigned long val_){}
			//I2C Enable bit : I2CxCONbits.ON
			void enable(bool val_){ I2CCONbits.ON = static_cast<unsigned char>(val_); }
			bool enable()const{ return static_cast<bool>(I2CCONbits.ON); }
			//I2C Control Register : I2CxCON
			void reset_all_config(){
				I2CCONbits.val = 0;
				enable(false);
				interrupt_enable(false);
				interrupt_flag(false);

				interrupt_function(0);
			}
		private:
			static typename xc32::interrupt::function* interrupt_ptr;
		public:
			const typename xc32::interrupt::function* interrupt_function()const{ return interrupt_ptr; }
			void interrupt_function(typename xc32::interrupt::function* ptr_) { interrupt_ptr = ptr_; }
		public:
			static const unsigned char ipl;
		};
		template<unsigned int no_>
		virtualI2CCONbits_t virtual_i2c_register<no_>::I2CCONbits;
		template<unsigned int no_>
		bool virtual_i2c_register<no_>::IE=false;
		template<unsigned int no_>
		bool virtual_i2c_register<no_>::IF = false;
		template<unsigned int no_>
		unsigned char virtual_i2c_register<no_>::IP=0;
		template<unsigned int no_>
		unsigned char virtual_i2c_register<no_>::IS = 0;
		template<unsigned int no_>
		unsigned char virtual_i2c_register<no_>::Rcv = 0;
		template<unsigned int no_>
		unsigned char virtual_i2c_register<no_>::Trn = 0;
		template<unsigned int no_>
		typename xc32::interrupt::function* virtual_i2c_register<no_>::interrupt_ptr = 0;
		template<unsigned int no_>
		const unsigned char virtual_i2c_register<no_>::ipl = 0;
	}
}

