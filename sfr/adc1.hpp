#ifndef XC32LIB_SFR_ADC1_INC
#define XC32LIB_SFR_ADC1_INC 100
#
#include"device_include.h"
#include<XCBase/type.hpp>
#include"sfr_register_mixin.hpp"
#include"exclusive_mixin.hpp"
#include"adc_base.hpp"
namespace xc32 {
	using namespace xc;
	namespace sfr {
		struct adc1 :public sfr_register_mixin<adc1>, public exclusive_mixin<adc1> {
		public:
			//ADCモシュールON
			void enable(bool val_) { AD1CON1bits.ADCEN = static_cast<unsigned char>(val_); }
			bool enable()const { return static_cast<bool>(AD1CON1bits.ADCEN); }
			//ADCモジュールの使用準備ができたか(モジュールの自動calibration待ち)
			bool module_ready()const volatile { return static_cast<bool>(AD1CON2bits.ADCRDY); }
			//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,…
			void scan_trigger_select(unsigned char val_) { AD1CON1bits.STRGSRC = val_; }
			unsigned char scan_trigger_select()const { return AD1CON1bits.STRGSRC; }
			//グローバルソフトウェアトリガビット
			void global_software_trigger() { AD1CON3bits.GSWTRG = 1; }
			//ADCクロック源(T_Q)ビット，1:Tcy,2:REFCLK3,3:FRCオシレータ出力,0:予約済み
			void clock_select(unsigned char val_) { AD1CON2bits.ADCSEL = val_; }
			unsigned char clock_select()const { return AD1CON2bits.ADCSEL; }
			//ADCクロック分周比ビット(0～127)：clock_div==0ならT_AD = T_Q ,T_AD = 2 * T_Q * clock_div
			void clock_div(unsigned char val_) { AD1CON2bits.ADCDIV = val_; }
			unsigned char clock_div()const { return AD1CON2bits.ADCDIV; }
			//単独ADC変換要求ビット
			void individual_convert(bool val_) { AD1CON3bits.RQCONVRT = static_cast<unsigned char>(val_); }
			bool individual_convert()const { return static_cast<bool>(AD1CON3bits.RQCONVRT); }
			//単独ADC入力選択ビット
			void individual_convert_input_select(unsigned char val_) { AD1CON3bits.ADINSEL = val_; }
			unsigned char individual_convert_input_select()const { return AD1CON3bits.ADINSEL; }
			//Vref選択ビット.0:VrefH=AVdd VrefL=AVss,1:VrefH=Vref+ VrefL=AVss,2:VrefH=AVdd VrefL=Vref-,3:VrefH=Vref+ VrefL=Vref-
			void reference_voltage(unsigned char val_) { AD1CON3bits.VREFSEL = val_; }
			unsigned char reference_voltage()const { return AD1CON3bits.VREFSEL; }
			//ADC入力スキャン選択ビット(AN0～AN31まで)
			void scan_select1(uint32 val_) { AD1CSS1 = val_; }
			uint32 scan_select1()const { return AD1CSS1; }
			//ADC入力スキャン選択ビット(AN32～AN44まで)
			void scan_select2(uint16 val_) { AD1CSS2 = val_; }
			uint16 scan_select2()const { return static_cast<uint16>(AD1CSS2); }
			//ADCデータレディビット(AN0～AN31まで,データを読み出すとクリアされる)
			uint32 data_ready1()const { return AD1DSTAT1; }
			//ADCデータレディビット(AN32～AN44まで,データを読み出すとクリアされる)
			uint32 data_ready2()const { return AD1DSTAT2; }
		};
	}
}
#
#endif
