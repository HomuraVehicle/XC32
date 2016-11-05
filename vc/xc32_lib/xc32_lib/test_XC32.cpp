#include"device_include.h"
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
#include<adc.hpp>
#include<sfr/analog.hpp>

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
typedef xc32::sfr::portB::pin9 pinAD4;
#define AD0_RDY ADCDSTAT1bits.ARDY3
#define AD0_DATA ADCDATA3
#define AD1_RDY ADCDSTAT1bits.ARDY1
#define AD1_DATA ADCDATA1
#define AD2_RDY ADCDSTAT1bits.ARDY27
#define AD2_DATA ADCDATA27
#define AD3_RDY AD0_RDY
#define AD3_DATA AD0_DATA
#define AD4_RDY ADCDSTAT1bits.ARDY4
#define AD4_DATA ADCDATA4
typedef xc32::sfr::portC::pin1 pinBattAD;
#define AD_MAIN_BATT_RDY ADCDSTAT1bits.ARDY22
#define AD_MAIN_BATT_DATA ADCDATA22
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
			RPC13R = 1;		//TXÇC13pinÇ…ê›íË
			__asm("nop");
			U1RXR = 7;		//RXÇC14pinÇ…ê›íË
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
			RPC13R = 1;		//TXÇC13pinÇ…ê›íË
			__asm("nop");
			U1RXR = 7;		//RXÇC14pinÇ…ê›íË
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
			RPD2R = 1;		//TXÇD2pinÇ…ê›íË
			__asm("nop");
			U3RXR = 0;		//RXÇD3pinÇ…ê›íË
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
			RPD2R = 1;		//TXÇD2pinÇ…ê›íË
			__asm("nop");
			U3RXR = 0;		//RXÇD3pinÇ…ê›íË
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

class test_interrupt_timer {
private:
	typedef xc32::sfr::timer3 timer_register;
	timer_register Register;
	xc32::interrupt_timer<timer_register> Module;
	class cInterruptFunc:public xc32::sfr::interrupt::function {
	private:
		green_led Green_LED;
		unsigned char count;
		xc32::interrupt_timer<timer_register>& Module;
	private:
		virtual void operator()(void) {
			Module.clear_flag();
			Module.clear_count();
			++count;
			if(count%2)Green_LED(1);
			else Green_LED(0);
		}
	public:
		cInterruptFunc(xc32::interrupt_timer<timer_register>& Module_):
			Module(Module_) {
			Green_LED.lock();
			Green_LED(0);
		}
	};
	cInterruptFunc interrupt_func;
public:
	test_interrupt_timer():interrupt_func(Module) {
		Module.initialize(Register);
		Module.config(500,interrupt_func);
		Module.lock();
	}
	void start() { Module.start(); }
	void stop() { Module.stop(); }
};

using MyADC=xc32::exclusive_adc<xc32::sfr::adc_block>;

struct shared_adc_identifer{};
using MySharedADC=xc32::shared_adc<xc32::sfr::adc_block,shared_adc_identifer>;

struct functional_adc_identifer{};
using MyFuncADC=xc32::async_functional_adc<xc32::sfr::adc_block,functional_adc_identifer>;

int main() {
	hmr::machine::device::kk10 KK10;

	TRISA=0xFFC0;
	TRISB=0x8BCB;
	TRISC=0x4FE7;
	TRISD=0x73EA;
	TRISE=0xFE53;
	TRISF=0xCED4;
	TRISG=0x4CBD;

	sync_uart1 Sync_uart1;
	delay_ms1 delay_ms;
	test_interrupt_timer interrupt_timer3;
	//interrupt_timer3.start();
	//xc32::sfr::adc1 ADC;

	pinDip1 Dip1;
	Dip1.lock();

	pinMainPower MainPower;
	MainPower.lock();
	MainPower(1);

	pin5VDVDC Pin5VDCDC;
	Pin5VDCDC.lock();
	Pin5VDCDC(1);

	//green_led Green_LED;
	//Green_LED.lock();
	//Green_LED(1);

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

	MyFuncADC FunctionalADC;
	MyFuncADC::analog_pin<xc32::sfr::portB::pin1> fAN1;
	MyFuncADC::analog_pin<xc32::sfr::portB::pin3> fAN0_1;
	MyFuncADC::analog_pin<xc32::sfr::portB::pin3> fAN0;

	xc32::adc::block_setting BlockSetting;
	BlockSetting.ClockDiv=2;
	BlockSetting.VrefMode=xc32::adc::vref_mode::vref_Vref_Gnd;

	xc32::adc::converter_setting ConverterSetting;
	ConverterSetting.ClockDiv=1;
	ConverterSetting.ResolutionMode=xc32::sfr::adc::resolution_mode::resolution_12bits;
	ConverterSetting.SamplingTime=5;
	
	fAN1.lock(&BlockSetting,&ConverterSetting);
	fAN0.lock(&BlockSetting,&ConverterSetting);
	fAN0_1.lock(&BlockSetting,&ConverterSetting);

/*	xc32::input_pin<pinAD2> PinAD2;
	PinAD2.lock();

	xc32::input_pin<pinAD1> PinAD1;
	PinAD1.lock();

	xc32::input_pin<pinAD0> PinAD0;
	PinAD0.lock();

	xc32::input_pin<pinAD3> PinAD3;
	PinAD3.lock();

	xc32::input_pin<pinAD4> PinAD4;
	PinAD4.lock();*/

	auto ans1=fAN1();
	auto ans0=fAN0();
	auto ans0_1=fAN0_1();

	while(1){
		if(ans1.can_get()){
			int ans=ans1.get();
			Sync_uart1.putc(0x01);
			Sync_uart1.putc(ans>>8);
			Sync_uart1.putc(ans);
			Sync_uart1.putc(0x0D);
			Sync_uart1.putc(0x0A);

			ans1=fAN1(100);
			delay_ms(200);
		}
		if(ans0.can_get()){
			int ans=ans0.get();
			Sync_uart1.putc(0x00);
			Sync_uart1.putc(ans>>8);
			Sync_uart1.putc(ans);
			Sync_uart1.putc(0x0D);
			Sync_uart1.putc(0x0A);

			ans0=fAN0(100);
			delay_ms(200);
		}
		if(ans0_1.can_get()){
			int ans=ans0_1.get();
			Sync_uart1.putc(0x10);
			Sync_uart1.putc(ans>>8);
			Sync_uart1.putc(ans);
			Sync_uart1.putc(0x0D);
			Sync_uart1.putc(0x0A);

			ans0_1=fAN0_1(10);
			delay_ms(200);
		}
		

		FunctionalADC();
		
		//Red_LED(1);
		//delay_ms(100);
		//Red_LED(0);
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