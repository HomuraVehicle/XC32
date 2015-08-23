#ifndef XC32LIB_TEST_VIRTUALADCREGISTER_INC
#define XC32LIB_TEST_VIRTUALADCREGISTER_INC 100
#
#include<XCBase/type.hpp>
#include<XC32Lib/sfr/exclusive_mixin.hpp>
#include<XC32Lib/sfr/sfr_register_mixin.hpp>
#include<XC32Lib/sfr/adc_base.hpp>
namespace xc32 {
	using namespace xc;
	namespace test {
		using namespace sfr;
		template<unsigned int no_>
		struct virtual_adc_register :public sfr_register_mixin<virtual_adc_register<no_>>, public exclusive_mixin<virtual_adc_register<no_>> {
			static bool IsEnable;
			static bool IsReady;
			static unsigned char ScanTriger;
			static unsigned char ClockSelect;
			static unsigned char ClockDiv;
			static bool IsIndividualConvert;
			static unsigned char IndividualConvertCh;
			static unsigned char ReferenceVoltage;
			static uint32 ScanSelect1;
			static uint16 ScanSelect2;
			static uint32 DataReady1;
			static uint32 DataReady2;
		public:
			//ADCモシュールON
			void enable(bool val_) { IsEnable = static_cast<unsigned char>(val_); }
			bool enable()const { return static_cast<bool>(IsEnable); }
			//ADCモジュールの使用準備ができたか(モジュールの自動calibration待ち)
			bool module_ready()const volatile { return IsReady; }
			//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,…
			void scan_trigger_select(unsigned char val_) { ScanTriger = val_; }
			unsigned char scan_trigger_select()const { return ScanTriger; }
			//グローバルソフトウェアトリガビット
			void global_software_trigger() { }
			//ADCクロック源(T_Q)ビット，1:Tcy,2:REFCLK3,3:FRCオシレータ出力,0:予約済み
			void clock_select(unsigned char val_) { ClockSelect = val_; }
			unsigned char clock_select()const { return ClockSelect; }
			//ADCクロック分周比ビット(0～127)：clock_div==0ならT_AD = T_Q ,T_AD = 2 * T_Q * clock_div
			void clock_div(unsigned char val_) { ClockDiv = val_; }
			unsigned char clock_div()const { return ClockDiv; }
			//単独ADC変換要求ビット
			void individual_convert(bool val_) { IsIndividualConvert = static_cast<unsigned char>(val_); }
			bool individual_convert()const { return static_cast<bool>(IsIndividualConvert); }
			//単独ADC入力選択ビット
			void individual_convert_input_select(unsigned char val_) { IndividualConvertCh = val_; }
			unsigned char individual_convert_input_select()const { return IndividualConvertCh; }
			//Vref選択ビット.0:VrefH=AVdd VrefL=AVss,1:VrefH=Vref+ VrefL=AVss,2:VrefH=AVdd VrefL=Vref-,3:VrefH=Vref+ VrefL=Vref-
			void reference_voltage(unsigned char val_) { ReferenceVoltage = val_; }
			unsigned char reference_voltage()const { return ReferenceVoltage; }
			//ADC入力スキャン選択ビット(AN0～AN31まで)
			void scan_select1(uint32 val_) { ScanSelect1 = val_; }
			uint32 scan_select1()const { return ScanSelect1; }
			//ADC入力スキャン選択ビット(AN32～AN44まで)
			void scan_select2(uint16 val_) { ScanSelect2 = val_; }
			uint16 scan_select2()const { return static_cast<uint16>(ScanSelect2); }
			//ADCデータレディビット(AN0～AN31まで,データを読み出すとクリアされる)
			uint32 data_ready1()const { return DataReady1; }
			//ADCデータレディビット(AN32～AN44まで,データを読み出すとクリアされる)
			uint32 data_ready2()const { return DataReady2; }
		};

		template<unsigned int no_>
		bool virtual_adc_register<no_>::IsEnable;
		template<unsigned int no_>
		bool virtual_adc_register<no_>::IsReady;
		template<unsigned int no_>
		unsigned char virtual_adc_register<no_>::ScanTriger;
		template<unsigned int no_>
		unsigned char virtual_adc_register<no_>::ClockSelect;
		template<unsigned int no_>
		unsigned char virtual_adc_register<no_>::ClockDiv;
		template<unsigned int no_>
		bool virtual_adc_register<no_>::IsIndividualConvert;
		template<unsigned int no_>
		unsigned char virtual_adc_register<no_>::IndividualConvertCh;
		template<unsigned int no_>
		unsigned char virtual_adc_register<no_>::ReferenceVoltage;
		template<unsigned int no_>
		uint32 virtual_adc_register<no_>::ScanSelect1;
		template<unsigned int no_>
		uint16 virtual_adc_register<no_>::ScanSelect2;
		template<unsigned int no_>
		uint32 virtual_adc_register<no_>::DataReady1;
		template<unsigned int no_>
		uint32 virtual_adc_register<no_>::DataReady2;
	}
}
#
#endif
