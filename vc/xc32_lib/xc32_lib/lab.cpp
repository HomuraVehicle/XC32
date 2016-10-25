#include<adc.hpp>
#include<sfr/adc1.hpp>
#include<sfr/port.hpp>
int main(){
	using my_adc = xc32::exclusive_adc<xc32::sfr::adc_block>;
	
	my_adc ADC;
	ADC.lock();

	my_adc::converter<xc::constexpr_no<4>> Cvt1(ADC);

	my_adc::analog_pin<xc32::sfr::portB::pin4> APin(ADC,Cvt1);
	APin.lock();
	APin(5);
	APin.unlock();

	return 0;
}