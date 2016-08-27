#include<device_include.h>
#include<hmLib_config.h>
#include<homuraLib_v2/type.hpp>

#include<device.hpp>
#include<interrupt.hpp>
#include<clock.hpp>
#include<uart.hpp>
#include<sfr/uart_base.hpp>
#include<sfr/uart1.hpp>
#include<sfr/uart3.hpp>
#include<timer.hpp>
#include<longtimer.hpp>
#include<sfr/timer1.hpp>
#include<sfr/timer2.hpp>
#include<sfr/timer3.hpp>
#include<sfr/timer4.hpp>
#include<sfr/adc1.hpp>
#include<sfr/interrupt.hpp>
#include<pin.hpp>
#include<sfr/port/portA.hpp>
#include<sfr/port/portB.hpp>
#include<sfr/port/portC.hpp>
#include<sfr/port/portD.hpp>
#include<sfr/port/portE.hpp>
#include<sfr/port/portF.hpp>
#include<sfr/port/portG.hpp>
#include<homuraLib_v2/machine/device/kk10.hpp>

typedef xc32::output_pin<xc32::sfr::portC::pin12,true> red_led;
typedef xc32::output_pin<xc32::sfr::portC::pin15,true> green_led;
typedef xc32::output_pin<xc32::sfr::portC::pin4> pin5VDVDC;
typedef xc32::output_pin<xc32::sfr::portE::pin3> pinMainPower;
typedef xc32::output_pin<xc32::sfr::portE::pin2> pinRF1Power;
typedef xc32::output_pin<xc32::sfr::portG::pin12> pinRF3Power;
typedef xc32::output_pin<xc32::sfr::portE::pin2> pinRF3Pw;
typedef xc32::output_pin<xc32::sfr::portD::pin11> pinMagAxcelPower;
typedef xc32::input_pin<xc32::sfr::portA::pin10> Vref;
typedef xc32::output_pin<xc32::sfr::portB::pin2> pinPowerAD1to4;
typedef xc32::output_pin<xc32::sfr::portB::pin4> pinPowerAD0;
typedef xc32::output_pin<xc32::sfr::portF::pin12> pinPowerCamera0;
typedef xc32::output_pin<xc32::sfr::portF::pin13> pinPowerCamera1;
typedef xc32::output_pin<xc32::sfr::portA::pin0> pinPowerGPS0;
typedef xc32::output_pin<xc32::sfr::portB::pin5> pinPowerGPS1;
typedef xc32::sfr::portB::pin3 pinAD0;
typedef xc32::sfr::portB::pin1 pinAD1;
typedef xc32::sfr::portA::pin9 pinAD2;
typedef xc32::sfr::portB::pin8 pinAD3;
typedef xc32::sfr::portC::pin1 pinBattAD;
typedef xc32::input_pin<xc32::sfr::portE::pin0> pinDip1;
typedef xc32::input_pin<xc32::sfr::portB::pin11> PathVdd1;
typedef xc32::input_pin<xc32::sfr::portB::pin15> PathVdd2;

class sync_uart1 {
private:
	xc32::sfr::uart1 Register;
	xc32::synchronous_uart<xc32::sfr::uart1> Module;
private:
	typedef xc32::output_pin<xc32::sfr::portC::pin13> pinU1TX;
	typedef xc32::input_pin<xc32::sfr::portC::pin14> pinU1RX;
	pinU1TX transmit_pin;
	pinU1RX recieve_pin;
public:
	inline void putc(unsigned char data_) { Module.putc(data_); }
	inline bool can_putc() const { return Module.can_putc(); }
	inline unsigned char getc() { return Module.getc(); }
	inline bool can_getc()const { return Module.can_getc(); }
public:
	sync_uart1() {
		transmit_pin.lock();
		recieve_pin.lock();
		{
			xc32::oscillator::lock_guard Lock(xc32::oscillator::Mutex);
			CFGCONbits.IOLOCK = 0;
			__asm("nop");
			RPC13R = 1;		//TXをC13pinに設定
			__asm("nop");
			U1RXR = 7;		//RXをC14pinに設定
			__asm("nop");
			CFGCONbits.IOLOCK = 1;
		}
		Module.initialize(Register);
		Module.config(9600,xc32::sfr::uart::flowcontrol::no_control);
		Module.lock();
	}
};

class interrupt_uart1 {
private:
	xc32::sfr::uart1 Register;
	xc32::interrupt_uart<xc32::sfr::uart1> Module;
private:
	class transmit_interrupt_func:public xc32::interrupt::function {
	private:
		xc32::interrupt_uart<xc32::sfr::uart1>& Module;
		unsigned char data;
	private:
		void operator()(void) {
			Module.send_data(data);
			//			while(!Module.recv_in_data());
			//			data = Module.recv_data();
			Module.send_disable();
			Module.recv_enable();
			return;
		}
	public:
		transmit_interrupt_func(xc32::interrupt_uart<xc32::sfr::uart1>& Module_)
			:Module(Module_),data(0xAA) {
		}
	public:
		void set_data(unsigned char data_) { data = data_; }
	};
	class recieve_interrupt_func:public xc32::interrupt::function {
	private:
		xc32::interrupt_uart<xc32::sfr::uart1>& Module;
		transmit_interrupt_func& tx_func;
		unsigned char data;
	private:
		void operator()(void) {
			data = Module.recv_data();
			tx_func.set_data(data);
			//			while(Module.send_in_data());
			//			Module.send_data(data);
			Module.recv_disable();
			Module.send_enable();
			return;
		}
	public:
		recieve_interrupt_func(xc32::interrupt_uart<xc32::sfr::uart1>& Module_,transmit_interrupt_func& tx_func_)
			:Module(Module_),data(0),tx_func(tx_func_) {
		}
	};
	transmit_interrupt_func tx_func;
	recieve_interrupt_func rx_func;
private:
	typedef xc32::output_pin<xc32::sfr::portC::pin13> pinU1TX;
	typedef xc32::input_pin<xc32::sfr::portC::pin14> pinU1RX;
	pinU1TX transmit_pin;
	pinU1RX recieve_pin;
public:
	inline void send_enable() { Module.send_enable(); }
	inline void send_disable() { Module.send_disable(); }
	inline bool send_is_enable()const { return Module.send_is_enable(); }
	inline void recv_enable() { Module.recv_enable(); }
	inline void recv_disable() { Module.recv_disable(); }
	inline bool recv_is_enable()const { return Module.recv_is_enable(); }
public:
	interrupt_uart1():tx_func(Module),rx_func(Module,tx_func) {
		transmit_pin.lock();
		recieve_pin.lock();
		Module.initialize(Register);
		{
			xc32::oscillator::lock_guard Lock(xc32::oscillator::Mutex);
			CFGCONbits.IOLOCK = 0;
			__asm("nop");
			RPC13R = 1;		//TXをC13pinに設定
			__asm("nop");
			U1RXR = 7;		//RXをC14pinに設定
			__asm("nop");
			CFGCONbits.IOLOCK = 1;
		}
		Module.config(9600,xc32::uart::flowcontrol::no_control,tx_func,rx_func);
		Module.recv_disable();
		Module.send_disable();
		Module.lock();
	}
};

class sync_uart3 {
private:
	xc32::sfr::uart3 Register;
	xc32::synchronous_uart<xc32::sfr::uart3> Module;
private:
	typedef xc32::output_pin<xc32::sfr::portD::pin2> pinU3TX;
	typedef xc32::input_pin<xc32::sfr::portD::pin3> pinU3RX;
	pinU3TX transmit_pin;
	pinU3RX recieve_pin;
public:
	inline void putc(unsigned char data_) { Module.putc(data_); }
	inline bool can_putc() const { return Module.can_putc(); }
	inline unsigned char getc() { return Module.getc(); }
	inline bool can_getc()const { return Module.can_getc(); }
public:
	sync_uart3() {
		transmit_pin.lock();
		recieve_pin.lock();
		{
			xc32::oscillator::lock_guard Lock(xc32::oscillator::Mutex);
			CFGCONbits.IOLOCK = 0;
			__asm("nop");
			RPD2R = 1;		//TXをD2pinに設定
			__asm("nop");
			U3RXR = 0;		//RXをD3pinに設定
			__asm("nop");
			CFGCONbits.IOLOCK = 1;
		}
		Module.initialize(Register);
		Module.config(9600,xc32::sfr::uart::flowcontrol::no_control);
		Module.lock();
	}
};

class interrupt_uart3 {
private:
	xc32::sfr::uart3 Register;
	xc32::interrupt_uart<xc32::sfr::uart3> Module;
private:
	class transmit_interrupt_func:public xc32::interrupt::function {
	private:
		xc32::interrupt_uart<xc32::sfr::uart3>& Module;
		unsigned char data;
	private:
		void operator()(void) {
			Module.send_data(data);
			while(!Module.recv_in_data());
			data = Module.recv_data();
			//			Module.send_disable();
			//			Module.recv_enable();
			return;
		}
	public:
		transmit_interrupt_func(xc32::interrupt_uart<xc32::sfr::uart3>& Module_)
			:Module(Module_),data(0xAA) {
		}
	};
	class recieve_interrupt_func:public xc32::interrupt::function {
	private:
		xc32::interrupt_uart<xc32::sfr::uart3>& Module;
		unsigned char data;
	private:
		void operator()(void) {
			data = Module.recv_data();
			Module.recv_disable();
			Module.send_enable();
			return;
		}
	public:
		recieve_interrupt_func(xc32::interrupt_uart<xc32::sfr::uart3>& Module_)
			:Module(Module_),data(0) {
		}
	};
	transmit_interrupt_func tx_func;
	recieve_interrupt_func rx_func;
private:
	typedef xc32::output_pin<xc32::sfr::portD::pin2> pinU3TX;
	typedef xc32::input_pin<xc32::sfr::portD::pin3> pinU3RX;
	pinU3TX transmit_pin;
	pinU3RX recieve_pin;
public:
	inline void send_enable() { Module.send_enable(); }
	inline void send_disable() { Module.send_disable(); }
	inline bool send_is_enable()const { return Module.send_is_enable(); }
	inline void recv_enable() { Module.recv_enable(); }
	inline void recv_disable() { Module.recv_disable(); }
	inline bool recv_is_enable()const { return Module.recv_is_enable(); }
public:
	interrupt_uart3():tx_func(Module),rx_func(Module) {
		transmit_pin.lock();
		recieve_pin.lock();
		Module.initialize(Register);
		{
			xc32::oscillator::lock_guard Lock(xc32::oscillator::Mutex);
			CFGCONbits.IOLOCK = 0;
			__asm("nop");
			RPD2R = 1;		//TXをD2pinに設定
			__asm("nop");
			U3RXR = 0;		//RXをD3pinに設定
			__asm("nop");
			CFGCONbits.IOLOCK = 1;
		}
		Module.config(9600,xc32::uart::flowcontrol::no_control,tx_func,rx_func);
		Module.recv_disable();
		Module.send_disable();
		Module.lock();
	}
};

class delay_ms1 {
private:
	xc32::sfr::timer1 Register;
	xc32::delay_ms_timer<xc32::sfr::timer1> Module;
public:
	delay_ms1() {
		Module.initialize(Register);
		Module.lock();
	}
	~delay_ms1() { Module.unlock(); }
public:
	void operator()(unsigned int miliseconds_) { Module(miliseconds_); }
};

class delay_ms2 {
private:
	xc32::sfr::timer2 Register;
	xc32::delay_ms_timer<xc32::sfr::timer2> Module;
public:
	delay_ms2() {
		Module.initialize(Register);
		Module.lock();
	}
	~delay_ms2() { Module.unlock(); }
public:
	void operator()(unsigned int miliseconds_) { Module(miliseconds_); }
	void operator()(unsigned int period_,xc32::timer::normal_prescaler::div div_) { Module(period_,div_); }
};

class delay_ms3 {
private:
	xc32::sfr::timer3 Register;
	xc32::delay_ms_timer<xc32::sfr::timer3> Module;
public:
	delay_ms3() {
		Module.initialize(Register);
		Module.lock();
	}
	~delay_ms3() { Module.unlock(); }
public:
	void operator()(unsigned int miliseconds_) { Module(miliseconds_); }
	void operator()(unsigned int period_,xc32::timer::normal_prescaler::div div_) { Module(period_,div_); }
};

class delay_ms4 {
private:
	xc32::sfr::timer4 Register;
	xc32::delay_ms_timer<xc32::sfr::timer4> Module;
public:
	delay_ms4() {
		Module.initialize(Register);
		Module.lock();
	}
	~delay_ms4() { Module.unlock(); }
public:
	void operator()(unsigned int miliseconds_) { Module(miliseconds_); }
	void operator()(unsigned int period_,xc32::timer::normal_prescaler::div div_) { Module(period_,div_); }
};

class interrupt_timer {
private:
	typedef xc32::sfr::timer3 timer_register;
	timer_register Register;
	xc32::interrupt_timer<timer_register> Module;
	class cInterruptFunc:public xc32::sfr::interrupt::function {
	private:
		red_led Red_LED;
		unsigned char count;
		xc32::interrupt_timer<timer_register>& Module;
	private:
		virtual void operator()(void) {
			Module.clear_flag();
			Module.clear_count();
			++count;
			if(count%2)Red_LED(1);
			else Red_LED(0);
		}
	public:
		cInterruptFunc(xc32::interrupt_timer<timer_register>& Module_):
			Module(Module_) {
			Red_LED.lock();
			Red_LED(0);
		}
	};
	cInterruptFunc interrupt_func;
public:
	interrupt_timer():interrupt_func(Module) {
		Module.initialize(Register);
		Module.config(500,interrupt_func);
		Module.lock();
	}
	void start() { Module.start(); }
	void stop() { Module.stop(); }
};

int main() {
	hmr::machine::device::kk10 KK10;

	TRISA=0xFFC0;
	TRISB=0x8BCB;
	TRISC=0x4FE7;
	TRISD=0x73EA;
	TRISE=0xFE53;
	TRISF=0xCED4;
	TRISG=0x4CBD;

//	ADC0CFG=DEVADC0;
//	ADC1CFG=DEVADC1;
//	ADC2CFG=DEVADC2;
//	ADC3CFG=DEVADC3;
//	ADC4CFG=DEVADC4;

	sync_uart1 Sync_uart1;
	delay_ms1 delay_ms;
	xc32::sfr::adc1 ADC;

	pinDip1 Dip1;
	Dip1.lock();

	pinMainPower MainPower;
	MainPower.lock();
	MainPower(1);

	pin5VDVDC Pin5VDCDC;
	Pin5VDCDC.lock();
	Pin5VDCDC(1);

	green_led Green_LED;
	Green_LED.lock();
	Green_LED(1);

	pinRF1Power RF1Power;
	RF1Power.lock();
	RF1Power(1);

	pinRF3Power RF3Power;
	RF3Power.lock();
	RF3Power(1);

	pinPowerAD1to4 PowerAD;
	PowerAD.lock();
	PowerAD(1);

	pinPowerAD0 PowerAD0;
	PowerAD0.lock();
	PowerAD0(1);

	xc32::input_pin<pinAD2> PinAD2;
	PinAD2.lock();

	xc32::input_pin<pinAD1> PinAD1;
	PinAD1.lock();

	xc32::input_pin<pinAD0> PinAD0;
	PinAD0.lock();

	xc32::input_pin<pinAD3> PinAD3;
	PinAD3.lock();

	red_led Red_LED;
	Red_LED.lock();
	Red_LED(0);
	delay_ms(200);
	Red_LED(1);
	delay_ms(200);
	Red_LED(0);
	delay_ms(200);
	Red_LED(1);
	delay_ms(200);
	Red_LED(0);

	int res[3];
	
	ADCCON1=0;
	
	ADCCON2=0;
	
	ADCANCON=0;
	ADCANCONbits.WKUPCLKCNT=5;

	ADCCON1bits.AICPMPEN=1;
	CFGCONbits.IOANCPN=1;

	ADCCON3=0;
	//ADCCON3bits.ADCSEL=1;
	ADC.clock_select(1);
	//ADCCON3bits.CONCLKDIV=2;
	ADC.clock_div(2);
	//ADCCON3bits.VREFSEL=1;
	ADC.reference_voltage(1);

	ADC0TIMEbits.ADCDIV=1;
	ADC0TIMEbits.SAMC=5;

	ADC0TIMEbits.SELRES=3;
	ADC1TIMEbits.ADCDIV=1;
	ADC1TIMEbits.SAMC=5;
	ADC1TIMEbits.SELRES=3;
	ADC2TIMEbits.ADCDIV=1;
	ADC2TIMEbits.SAMC=5;
	ADC2TIMEbits.SELRES=3;
	ADC3TIMEbits.ADCDIV=1;
	ADC3TIMEbits.SAMC=5;
	ADC3TIMEbits.SELRES=3;

	ADCTRGMODEbits.SH0ALT=0;
	ADCTRGMODEbits.SH1ALT=0;
	ADCTRGMODEbits.SH2ALT=0;
	ADCTRGMODEbits.SH3ALT=1;

	ADCIMCON1=0;
	ADCIMCON2=0;
	ADCIMCON3=0;
//	ADCIMCON1bits.SIGN0=0;
//	ADCIMCON1bits.DIFF0=0;
//	ADCIMCON1bits.SIGN1=0;
//	ADCIMCON1bits.DIFF1=0;
//	ADCIMCON1bits.SIGN2=0;
//	ADCIMCON1bits.DIFF2=0;

	ADCGIRQEN1=0;
	ADCGIRQEN2=0;

	ADCCMP1=0;
	ADCCMP2=0;
	ADCCMP3=0;
	ADCCMP4=0;
	ADCCMP5=0;
	ADCCMP6=0;

	ADCFLTR1=0;
	ADCFLTR2=0;
	ADCFLTR3=0;
	ADCFLTR4=0;
	ADCFLTR5=0;
	ADCFLTR6=0;

	ADCTRGSNSbits.LVL0=0;
	ADCTRGSNSbits.LVL1=0;
	ADCTRGSNSbits.LVL2=0;
	ADCTRG1bits.TRGSRC0=1;
	ADCTRG1bits.TRGSRC1=1;
	ADCTRG1bits.TRGSRC2=1;
	ADCTRG1bits.TRGSRC3=1;
	
	ADCEIEN1=0;
	ADCEIEN2=0;

	ADCCON1bits.ON=1;

	while(!ADCCON2bits.BGVRRDY);
	while(ADCCON2bits.REFFLT);

	ADCANCONbits.ANEN0=1;
	ADCANCONbits.ANEN1=1;
	ADCANCONbits.ANEN2=1;
	ADCANCONbits.ANEN3=1;
	ADCANCONbits.ANEN4=1;
	ADCANCONbits.ANEN7=1;
	while(!ADCANCONbits.WKRDY0);
	while(!ADCANCONbits.WKRDY1);
	while(!ADCANCONbits.WKRDY2);
	while(!ADCANCONbits.WKRDY3);
	while(!ADCANCONbits.WKRDY4);
	while(!ADCANCONbits.WKRDY7);

	ADCCON3bits.DIGEN0=1;
	ADCCON3bits.DIGEN1=1;
	ADCCON3bits.DIGEN2=1;
	ADCCON3bits.DIGEN3=1;
	ADCCON3bits.DIGEN4=1;
	ADCCON3bits.DIGEN7=1;

    const int n=1000;

	ADC.individual_convert_input_select(3);
	int cnt=0;
	while(1){
		ADCTRGMODEbits.SH3ALT=cnt%2;
		res[0]=0;
        res[1]=0;
        res[2]=0;
		long long tmp=0;
        Red_LED(1);
        for(int i=0;i<n;++i){
            //ADCCON3bits.GSWTRG=1;
			ADC.individual_convert(1);
            //while(ADCDSTAT1bits.ARDY1==0);
			while(ADCDSTAT1bits.ARDY3==0);
			//tmp+=ADCDATA1;
			tmp+=ADCDATA3;
        }
		tmp/=n;
		res[1]=tmp;

		
		Sync_uart1.putc(cnt%2);
		Sync_uart1.putc(res[1]>>8);
		Sync_uart1.putc(res[1]);
		Sync_uart1.putc(0x0d);
		Sync_uart1.putc(0x0a);


		delay_ms(200);
		Red_LED(0);
		delay_ms(200);
		++cnt;
	}




	ADCCON1bits.AICPMPEN=0;
	CFGCONbits.IOANCPN=0;

/*	ADCIMCON1=0;
	ADCIMCON2=0;
	ADCIMCON3=0;*/
	ADC0TIMEbits.SELRES=3;
	ADC1TIMEbits.SELRES=3;
	ADC2TIMEbits.SELRES=3;
	ADC3TIMEbits.SELRES=3;
	ADC4TIMEbits.SELRES=3;
	ADCCON1bits.SELRES=3;
/*	ADC1TIMEbits.ADCDIV=1;
	ADC1TIMEbits.SAMC=5;
	ADCIMCON1=0;
	ADCIMCON2=0;
	ADCIMCON3=0;
	ADCCMPCON1=0;
	ADCCMPCON2=0;
	ADCCMPCON3=0;
	ADCCMPCON4=0;
	ADCCMPCON5=0;
	ADCCMPCON6=0;*/

	ADCANCONbits.WKUPCLKCNT=5;
	ADC.clock_div(2);
	ADC.clock_select(0);
	ADC.reference_voltage(1);
	ADC.enable(1);
	while(ADC.module_ready());
	while(ADCCON2bits.REFFLT);
	ADCANCONbits.ANEN0=1;
	ADCANCONbits.ANEN1=1;
	ADCANCONbits.ANEN2=1;
	ADCANCONbits.ANEN3=1;
	ADCANCONbits.ANEN4=1;
	ADCANCONbits.ANEN7=1;
	while(!ADCANCONbits.WKRDY0);
	while(!ADCANCONbits.WKRDY1);
	while(!ADCANCONbits.WKRDY2);
	while(!ADCANCONbits.WKRDY3);
	while(!ADCANCONbits.WKRDY4);
	while(!ADCANCONbits.WKRDY7);
	ADCCON3bits.DIGEN0=1;
	ADCCON3bits.DIGEN1=1;
	ADCCON3bits.DIGEN2=1;
	ADCCON3bits.DIGEN3=1;
	ADCCON3bits.DIGEN4=1;
	ADCCON3bits.DIGEN7=1;
	Green_LED(0);

	//ADCCON3bits.SAMP=1;
	ADC.individual_convert_input_select(27);
	while(1){
		ADC.individual_convert(1);
		while(ADCDSTAT1bits.ARDY27==0){ __asm("nop"); }
		unsigned int data=ADCDATA27;
//		while(ADCDSTAT1bits.ARDY1==0){ __asm("nop"); }
//		unsigned int data=ADCDATA1;
//		while(ADCDSTAT1bits.ARDY22==0){ __asm("nop"); }
//		unsigned int data=ADCDATA22;
		Sync_uart1.putc(data>>8);
		Sync_uart1.putc(data);
		Sync_uart1.putc(0x0d);
		Sync_uart1.putc(0x0a);

		Red_LED(1);
		//delay_ms(100);
		Red_LED(0);
		//delay_ms(100);
	}
	return 0;
}

/*
struct print{
void operator()(int val){
std::cout<<val;
}
};

int func(){

xc::promise<int> Promise;

xc::future<int> Future=Promise.get_future();

Future.can_get(); //false

Promise.ref()=10;
Promise.end_write();

Future.can_get(); //true

print Print;
Future.delegate(xc::ref(Print));



}*/