#ifndef XC32_SFR_ADC1_INC
#define XC32_SFR_ADC1_INC 100
#
#include"device_include.h"
#include<XCBase/type.hpp>
#include<XCBase/constexpr_no.hpp>
#include"sfr_register_mixin.hpp"
#include"exclusive_mixin.hpp"
#include"interrupt.hpp"
#include"adc_base.hpp"


#if defined(XC32_PIC32MX)
#elif defined(XC32_PIC32MZ)
#	ifndef XC32_SFR_ADC1_EXPLICITINTERRUPT
#		ifndef XC32_DEBUGMODE
#			define x_xc32_sfr_adc1_global_convert_end_interrupt(void) __ISR(_ADC_EOS_VECTOR,IPL7AUTO) ADC_EOS_Interrupt(void)
#		else
extern "C"{void x_xc32_sfr_adc1_global_convert_end_interrupt(void);}
#		endif
#	else
#		ifndef XC32_DEBUGMODE
#			define xc32_sfr_adc1_global_convert_end_interrupt(void) __ISR(_ADC_EOS_VECTOR,IPL7AUTO) ADC_EOS_Interrupt(void)
#		else
extern "C"{void xc32_sfr_adc1_global_convert_end_interrupt(void);}
#		endif
#	endif
#else
#	error Unknown device!
#endif

namespace xc32 {
	using namespace xc;
	namespace sfr {
		struct adc_block :public sfr_register_mixin<adc_block>, public exclusive_mixin<adc_block> {
		public:
			//ADCモシュールON
			void enable(bool val_) { ADCCON1bits.ON = static_cast<unsigned char>(val_); }
			bool enable()const { return static_cast<bool>(ADCCON1bits.ON); }
			//ADCモジュールの使用準備ができたか(モジュールの自動calibration待ち)
			bool module_ready()const volatile { return static_cast<bool>(ADCCON2bits.BGVRRDY); }
			//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,…
			void scan_trigger_select(unsigned char val_) { ADCCON1bits.STRGSRC = val_; }
			unsigned char scan_trigger_select()const { return ADCCON1bits.STRGSRC; }
			//一斉スキャン設定をリセット
			void reset_request_global_convert(){
				ADCCSS1 = 0;
				ADCCSS2 = 0;
			}
			//グローバルソフトウェアトリガビット
			void global_convert_trigger(){ ADCCON3bits.GSWTRG = 1; }
			//一斉スキャン（Global Scan）が終了したか　読みだすと自動的に落ちる
			bool is_end_global_convert()const volatile{ return static_cast<bool>(ADCCON2bits.EOSRDY); }
			//一斉スキャン終了割り込み有効
			void global_convert_end_interrupt_enable(bool val){
				ADCCON2bits.EOSIEN = val;
				IEC6bits.ADCEOSIE = val;
			}
			bool  global_convert_end_interrupt_enable(void)const volatile{
				return ADCCON2bits.EOSIEN;
			}
			//一斉スキャン終了割り込みフラグ
			void global_convert_end_interrupt_flag(bool val){IFS6bits.ADCEOSIF = val;}
			bool  global_convert_end_interrupt_flag(void)const volatile{return IFS6bits.ADCEOSIF;}
			//一斉スキャン終了割り込み priority level
			void global_convert_end_interrupt_priority_level(unsigned char val_){ IPC48bits.ADCEOSIP = val_; }
			unsigned char global_convert_end_interrupt_priority_level(){ return IPC48bits.ADCEOSIP; }
			//ADCマスタークロック源(T_Q)ビット，1:Tcy,2:REFCLK3,3:FRCオシレータ出力,0:予約済み
			void clock_select(unsigned char val_) { ADCCON3bits.ADCSEL = val_; }
			unsigned char clock_select()const { return ADCCON3bits.ADCSEL; }
			//ADCマスタークロック分周比ビット(0～12XXX)：clock_div==0ならT_AD = T_Q ,T_AD = 2 * T_Q * clock_div
			void clock_div(unsigned char val_) { ADCCON3bits.CONCLKDIV = val_; }
			unsigned char clock_div()const { return ADCCON3bits.CONCLKDIV; }
			//単独ADC変換要求ビット
			void individual_convert_trigger(bool val_) { ADCCON3bits.RQCNVRT = static_cast<unsigned char>(val_); }
			bool individual_convert_trigger()const { return static_cast<bool>(ADCCON3bits.RQCNVRT); }
			//単独ADC入力選択ビット
			void individual_convert_select(unsigned char val_) { ADCCON3bits.ADINSEL = val_; }
			unsigned char individual_convert_select()const { return ADCCON3bits.ADINSEL; }
			//Vref選択ビット.0:VrefH=AVdd VrefL=AVss,1:VrefH=Vref+ VrefL=AVss,2:VrefH=AVdd VrefL=Vref-,3:VrefH=Vref+ VrefL=Vref-
			void reference_voltage(unsigned char val_) { ADCCON3bits.VREFSEL = val_; }
			unsigned char reference_voltage()const { return ADCCON3bits.VREFSEL; }

			//ADCごとの固有のクロック分周比(1-12XXX) この値の2倍の周期になる
			template<typename converter_no_>
			void converter_clock_div(unsigned char val_);
			template<typename converter_no_>
			unsigned char converter_clock_div();
			//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
			template<typename converter_no_>
			void converter_sampling_time(unsigned char val_);
			template<typename converter_no_>
			unsigned char converter_sampling_time();
			//ADCのbit精度　resolution_modeから選択
			template<typename converter_no_>
			void converter_resolution_bits(unsigned char val_);
			template<typename converter_no_>
			unsigned char converter_resolution_bits();
			//excluded ADC専用　割り当ての別のpinwを使うか
			template<typename converter_no_>
			void converter_use_alternative_pin(bool val_);
			template<typename converter_no_>
			bool converter_use_alternative_pin();
			//ADCごとのclockスタート
			template<typename converter_no_>
			void converter_enable(bool val_);
			template<typename converter_no_>
			bool converter_enable();
			//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
			template<typename converter_no_>
			bool converter_work_ready();
			//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
			template<typename converter_no_>
			void converter_work_enable(bool val_);
			template<typename converter_no_>
			bool converter_work_enable();
			//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
			template<typename converter_no_>
			void converter_scan_trigger_select(unsigned char val_);

			//Reset all confige about ADC
			void reset_all_config(){
				ADCCON1 &= 0x00008000;			//ON以外を0でフィル
				ADCCON2 = 0;
				ADCCON3 = 0;

				ADCANCON = 0;
				ADCIMCON1 = 0;
				ADCIMCON2 = 0;
				ADCIMCON3 = 0;
				//割り込みの設定をクリア
				ADCGIRQEN1 = 0;
				ADCGIRQEN2 = 0;

				global_convert_end_interrupt_enable(false);
				global_convert_end_interrupt_function(0);
			}
		private:
			static interrupt::function* global_convert_end_interrupt_ptr;
		public:
			const interrupt::function* global_convert_end_interrupt_function()const{ return global_convert_end_interrupt_ptr; }
			void global_convert_end_interrupt_function(interrupt::function* ptr_){ global_convert_end_interrupt_ptr = ptr_; }
		public:
			static const unsigned char global_convert_end_ipl;
		};

	#ifdef ADCXXX_SPESIALIZED
		//ADCごとの固有のクロック分周比(1-12XXX) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<XXX>>(unsigned char val_){
			ADCXXXTIMEbits.ADCDIV = val_;
		}
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<XXX>>(){
			return ADCXXXTIMEbits.ADCDIV;
		}
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<XXX>>(unsigned char val_){
			ADCXXXTIMEbits.SAMC = val_;
		}
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<XXX>>(){
			return ADCXXXTIMEbits.SAMC;
		}
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<XXX>>(unsigned char val_){
			ADCXXXTIMEbits.SELRES = val_;
		}
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<XXX>>(){
			return ADCXXXTIMEbits.SELRES;
		}
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<XXX>>(bool val_){
			ADCTRGMODEbits.SHXXXALT = val_;
		}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<XXX>>(){
			return ADCTRGMODEbits.SHXXXALT;
		}
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<XXX>>(bool val_){
			ADCANCONbits.ANENXXX = val_;
		}
		template<>
		inline bool adc_block::converter_enable<constexpr_no<XXX>>(){
			return ADCANCONbits.ANENXXX;
		}
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<XXX>>(){
			return ADCANCONbits.WKRDYXXX;
		}
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable(bool val_){
			ADCCON3bits.DIGENXXX = val_;
		}
		template<>
		inline bool adc_block::converter_work_enable(){
			return ADCCON3bits.DIGENXXX;
		}
	#endif
	#ifdef ADCXXX_GENERALIZED
		//ADCごとの固有のクロック分周比(1-12XXX) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<XXX>>(unsigned char val_){ ADCCON2bits.ADCDIV = val_; }
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<XXX>>(){ return ADCCON2bits.ADCDIV; }
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<XXX>>(unsigned char val_){ ADCCON2bits.SAMC = val_; }
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<XXX>>(){ return ADCCON2bits.SAMC; }
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<XXX>>(unsigned char val_){ { ADCCON1bits.SELRES = val_; }
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<XXX>>(){ return ADCCON1bits.SELRES; }
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<XXX>>(bool val_){}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<XXX>>(){ return false; }
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<XXX>>(bool val_){ ADCANCONbits.ANENXXX = val_; }
		template<>
		inline bool adc_block::converter_enable<constexpr_no<XXX>>(){ return ADCANCONbits.ANENXXX; }
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<XXX>>(){ return ADCANCONbits.WKRDYXXX; }
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable(bool val_){ ADCCON3bits.DIGENXXX = val_; }
		template<>
		inline bool adc_block::converter_work_enable(){ return ADCCON3bits.DIGENXXX; }
	#endif

	#ifdef ADC0_SPESIALIZED
		//ADCごとの固有のクロック分周比(1-120) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<0>>(unsigned char val_){
			ADC0TIMEbits.ADCDIV = val_;
		}
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<0>>(){
			return ADC0TIMEbits.ADCDIV;
		}
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<0>>(unsigned char val_){
			ADC0TIMEbits.SAMC = val_;
		}
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<0>>(){
			return ADC0TIMEbits.SAMC;
		}
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<0>>(unsigned char val_){
			ADC0TIMEbits.SELRES = val_;
		}
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<0>>(){
			return ADC0TIMEbits.SELRES;
		}
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<0>>(bool val_){
			ADCTRGMODEbits.SH0ALT = val_;
		}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<0>>(){
			return ADCTRGMODEbits.SH0ALT!=0;
		}
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<0>>(bool val_){
			ADCANCONbits.ANEN0 = val_;
		}
		template<>
		inline bool adc_block::converter_enable<constexpr_no<0>>(){
			return ADCANCONbits.ANEN0;
		}
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<0>>(){
			return ADCANCONbits.WKRDY0;
		}
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable<constexpr_no<0>>(bool val_){
			ADCCON3bits.DIGEN0 = val_;
		}
		template<>
		inline bool adc_block::converter_work_enable<constexpr_no<0>>(){
			return ADCCON3bits.DIGEN0;
		}
		//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
		template<>
		inline void adc_block::converter_scan_trigger_select<constexpr_no<0>>(unsigned char val_){
			ADCTRG1bits.TRGSRC0 = val_;
		}
	#endif

	#ifdef ADC1_SPESIALIZED
		//ADCごとの固有のクロック分周比(1-121) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<1>>(unsigned char val_){
			ADC1TIMEbits.ADCDIV = val_;
		}
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<1>>(){
			return ADC1TIMEbits.ADCDIV;
		}
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<1>>(unsigned char val_){
			ADC1TIMEbits.SAMC = val_;
		}
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<1>>(){
			return ADC1TIMEbits.SAMC;
		}
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<1>>(unsigned char val_){
			ADC1TIMEbits.SELRES = val_;
		}
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<1>>(){
			return ADC1TIMEbits.SELRES;
		}
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<1>>(bool val_){
			ADCTRGMODEbits.SH1ALT = val_;
		}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<1>>(){
			return ADCTRGMODEbits.SH1ALT!=0;
		}
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<1>>(bool val_){
			ADCANCONbits.ANEN1 = val_;
		}
		template<>
		inline bool adc_block::converter_enable<constexpr_no<1>>(){
			return ADCANCONbits.ANEN1;
		}
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<1>>(){
			return ADCANCONbits.WKRDY1;
		}
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable<constexpr_no<1>>(bool val_){
			ADCCON3bits.DIGEN1 = val_;
		}
		template<>
		inline bool adc_block::converter_work_enable<constexpr_no<1>>(){
			return ADCCON3bits.DIGEN1;
		}
		//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
		template<>
		inline void adc_block::converter_scan_trigger_select<constexpr_no<1>>(unsigned char val_){
			ADCTRG1bits.TRGSRC1 = val_;
		}
	#endif

	#ifdef ADC2_SPESIALIZED
		//ADCごとの固有のクロック分周比(1-122) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<2>>(unsigned char val_){
			ADC2TIMEbits.ADCDIV = val_;
		}
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<2>>(){
			return ADC2TIMEbits.ADCDIV;
		}
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<2>>(unsigned char val_){
			ADC2TIMEbits.SAMC = val_;
		}
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<2>>(){
			return ADC2TIMEbits.SAMC;
		}
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<2>>(unsigned char val_){
			ADC2TIMEbits.SELRES = val_;
		}
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<2>>(){
			return ADC2TIMEbits.SELRES;
		}
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<2>>(bool val_){
			ADCTRGMODEbits.SH2ALT = val_;
		}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<2>>(){
			return ADCTRGMODEbits.SH2ALT!=0;
		}
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<2>>(bool val_){
			ADCANCONbits.ANEN2 = val_;
		}
		template<>
		inline bool adc_block::converter_enable<constexpr_no<2>>(){
			return ADCANCONbits.ANEN2;
		}
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<2>>(){
			return ADCANCONbits.WKRDY2;
		}
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable<constexpr_no<2>>(bool val_){
			ADCCON3bits.DIGEN2 = val_;
		}
		template<>
		inline bool adc_block::converter_work_enable<constexpr_no<2>>(){
			return ADCCON3bits.DIGEN2;
		}
		//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
		template<>
		inline void adc_block::converter_scan_trigger_select<constexpr_no<2>>(unsigned char val_){
			ADCTRG1bits.TRGSRC2 = val_;
		}

	#endif

	#ifdef ADC3_SPESIALIZED
		//ADCごとの固有のクロック分周比(1-123) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<3>>(unsigned char val_){
			ADC3TIMEbits.ADCDIV = val_;
		}
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<3>>(){
			return ADC3TIMEbits.ADCDIV;
		}
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<3>>(unsigned char val_){
			ADC3TIMEbits.SAMC = val_;
		}
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<3>>(){
			return ADC3TIMEbits.SAMC;
		}
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<3>>(unsigned char val_){
			ADC3TIMEbits.SELRES = val_;
		}
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<3>>(){
			return ADC3TIMEbits.SELRES;
		}
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<3>>(bool val_){
			ADCTRGMODEbits.SH3ALT = val_;
		}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<3>>(){
			return ADCTRGMODEbits.SH3ALT!=0;
		}
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<3>>(bool val_){
			ADCANCONbits.ANEN3 = val_;
		}
		template<>
		inline bool adc_block::converter_enable<constexpr_no<3>>(){
			return ADCANCONbits.ANEN3;
		}
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<3>>(){
			return ADCANCONbits.WKRDY3;
		}
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable<constexpr_no<3>>(bool val_){
			ADCCON3bits.DIGEN3 = val_;
		}
		template<>
		inline bool adc_block::converter_work_enable<constexpr_no<3>>(){
			return ADCCON3bits.DIGEN3;
		}
		//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
		template<>
		inline void adc_block::converter_scan_trigger_select<constexpr_no<3>>(unsigned char val_){
			ADCTRG1bits.TRGSRC3 = val_;
		}
	#endif

	#ifdef ADC4_SPESIALIZED
		//ADCごとの固有のクロック分周比(1-124) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<4>>(unsigned char val_){
			ADC4TIMEbits.ADCDIV = val_;
		}
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<4>>(){
			return ADC4TIMEbits.ADCDIV;
		}
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<4>>(unsigned char val_){
			ADC4TIMEbits.SAMC = val_;
		}
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<4>>(){
			return ADC4TIMEbits.SAMC;
		}
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<4>>(unsigned char val_){
			ADC4TIMEbits.SELRES = val_;
		}
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<4>>(){
			return ADC4TIMEbits.SELRES;
		}
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<4>>(bool val_){
			ADCTRGMODEbits.SH4ALT = val_;
		}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<4>>(){
			return ADCTRGMODEbits.SH4ALT!=0;
		}
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<4>>(bool val_){
			ADCANCONbits.ANEN4 = val_;
		}
		template<>
		inline bool adc_block::converter_enable<constexpr_no<4>>(){
			return ADCANCONbits.ANEN4;
		}
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<4>>(){
			return ADCANCONbits.WKRDY4;
		}
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable<constexpr_no<4>>(bool val_){
			ADCCON3bits.DIGEN4 = val_;
		}
		template<>
		inline bool adc_block::converter_work_enable<constexpr_no<4>>(){
			return ADCCON3bits.DIGEN4;
		}
		//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
		template<>
		inline void adc_block::converter_scan_trigger_select<constexpr_no<4>>(unsigned char val_){
			ADCTRG2bits.TRGSRC4 = val_;
		}
	#endif

	#ifdef ADC0_GENERALIZED
		//ADCごとの固有のクロック分周比(1-120) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<0>>(unsigned char val_){ ADCCON2bits.ADCDIV = val_; }
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<0>>(){ return ADCCON2bits.ADCDIV; }
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<0>>(unsigned char val_){ ADCCON2bits.SAMC = val_; }
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<0>>(){ return ADCCON2bits.SAMC; }
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<0>>(unsigned char val_){ { ADCCON1bits.SELRES = val_; }
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<0>>(){ return ADCCON1bits.SELRES; }
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<0>>(bool val_){}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<0>>(){ return false; }
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<0>>(bool val_){ ADCANCONbits.ANEN0 = val_; }
		template<>
		inline bool adc_block::converter_enable<constexpr_no<0>>(){ return ADCANCONbits.ANEN0; }
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<0>>(){ return ADCANCONbits.WKRDY0; }
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable<constexpr_no<0>>(bool val_){ ADCCON3bits.DIGEN0 = val_; }
		template<>
		inline bool adc_block::converter_work_enable<constexpr_no<0>>(){ return ADCCON3bits.DIGEN0; }
		//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
		template<>
		inline void adc_block::converter_scan_trigger_select<constexpr_no<0>>(unsigned char val_){
			ADCTRG1bits.TRGSRC0 = val_;
		}
	#endif

	#ifdef ADC7_GENERALIZED
		//ADCごとの固有のクロック分周比(1-127) この値の2倍の周期になる
		template<>
		inline void adc_block::converter_clock_div<constexpr_no<7>>(unsigned char val_){ ADCCON2bits.ADCDIV = val_; }
		template<>
		inline unsigned char adc_block::converter_clock_div<constexpr_no<7>>(){ return ADCCON2bits.ADCDIV; }
		//ADCごとのサンプリングタイム(0-1023)　val+2のクロック周期だけサンプリングにかかる？
		template<>
		inline void adc_block::converter_sampling_time<constexpr_no<7>>(unsigned char val_){ ADCCON2bits.SAMC = val_; }
		template<>
		inline unsigned char adc_block::converter_sampling_time<constexpr_no<7>>(){ return ADCCON2bits.SAMC; }
		//ADCのbit精度　resolution_modeから選択
		template<>
		inline void adc_block::converter_resolution_bits<constexpr_no<7>>(unsigned char val_){ ADCCON1bits.SELRES = val_; }
		template<>
		inline unsigned char adc_block::converter_resolution_bits<constexpr_no<7>>(){ return ADCCON1bits.SELRES; }
		//excluded ADC専用　割り当ての別のpinwを使うか
		template<>
		inline void adc_block::converter_use_alternative_pin<constexpr_no<7>>(bool val_){}
		template<>
		inline bool adc_block::converter_use_alternative_pin<constexpr_no<7>>(){ return false; }
		//ADCごとのclockスタート
		template<>
		inline void adc_block::converter_enable<constexpr_no<7>>(bool val_){ ADCANCONbits.ANEN7 = val_; }
		template<>
		inline bool adc_block::converter_enable<constexpr_no<7>>(){ return ADCANCONbits.ANEN7; }
		//ADCごとのクロック同調確認　clock_enable後にwork_readyを待つ
		template<>
		inline bool adc_block::converter_work_ready<constexpr_no<7>>(){ return ADCANCONbits.WKRDY7; }
		//ADCごとのごとのタスクスタート work_readyになったらwork_enableすると、利用準備が整う
		template<>
		inline void adc_block::converter_work_enable<constexpr_no<7>>(bool val_){ ADCCON3bits.DIGEN7 = val_; }
		template<>
		inline bool adc_block::converter_work_enable<constexpr_no<7>>(){ return ADCCON3bits.DIGEN7; }
		//スキャントリガ源選択ビット,0:トリガなし,1:グローバルソフトウェアトリガ,...,3:STRGを参照
		template<>
		inline void adc_block::converter_scan_trigger_select<constexpr_no<7>>(unsigned char val_){
			ADCTRG2bits.TRGSRC7 = val_;
		}
	#endif
	}
}
#
#endif
