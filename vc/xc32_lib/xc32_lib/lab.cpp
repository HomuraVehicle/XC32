#include<adc.hpp>
#include<sfr/adc1.hpp>
#include<sfr/port.hpp>
int main(){
	{
		using my_adc = xc32::exclusive_adc<xc32::sfr::adc_block>;

		//ADCBlock
		my_adc ADC;

		//Port B pin4はConverter4に所属しているので、それも容易
		my_adc::converter<xc::constexpr_no<4>> Cvt1(ADC);

		//ピンを確保
		my_adc::analog_pin<xc32::sfr::portB::pin4> APin(ADC, Cvt1);

		//ピンのロック　ADCやConverterのロックとは、どちらが先でも良い。
		APin.lock();

		//ADCとConverterのロック　構造上、ADCロックが先でないとConverterロックがうまくいかない場合があるかも。
		ADC.lock();
		Cvt1.lock();

		//読み出し。
		xc::uint16 Data = APin(5);

		//アンロック
		APin.unlock();
		Cvt1.unlock();
		ADC.unlock();
	}

	{
		//なんでもいいので、shared_adcを識別するためのタグを定義
		struct adc_id{};
		using my_adc = xc32::shared_adc<xc32::sfr::adc_block, adc_id>;

		//ADCBlock、Converterは静的クラスメンバとして定義されているので、やるべきことはAnalogPinを作るだけ
		my_adc::analog_pin<xc32::sfr::portB::pin4> APin;

		//ロック　この時自動的に、ADCBlockとConverterのlockが行われる。よって、最初だけちょっとロックに時間がかかる。
		APin.lock();

		//読み出し。
		xc::uint16 Data = APin(5);

		//アンロック ロック時と同じく、ADCBlockとConverterも（誰も利用者がいなくなれば）unlockされる。
		APin.unlock();
	}





	return 0;
}