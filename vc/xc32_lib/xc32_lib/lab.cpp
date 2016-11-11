#include<adc.hpp>
#include<sfr/adc1.hpp>
#include<sfr/port.hpp>
int main(){
	{
		using my_adc = xc32::exclusive_adc<xc32::sfr::adc_block>;

		//ADCBlock
		my_adc ADC;

		//Port B pin4��Converter4�ɏ������Ă���̂ŁA������e��
		my_adc::converter<xc::constexpr_no<4>> Cvt1(ADC);

		//�s�����m��
		my_adc::analog_pin<xc32::sfr::portB::pin4> APin(ADC, Cvt1);

		//�s���̃��b�N�@ADC��Converter�̃��b�N�Ƃ́A�ǂ��炪��ł��ǂ��B
		APin.lock();

		//ADC��Converter�̃��b�N�@�\����AADC���b�N����łȂ���Converter���b�N�����܂������Ȃ��ꍇ�����邩���B
		ADC.lock();
		Cvt1.lock();

		//�ǂݏo���B
		xc::uint16 Data = APin(5);

		//�A�����b�N
		APin.unlock();
		Cvt1.unlock();
		ADC.unlock();
	}

	{
		//�Ȃ�ł������̂ŁAshared_adc�����ʂ��邽�߂̃^�O���`
		struct adc_id{};
		using my_adc = xc32::shared_adc<xc32::sfr::adc_block, adc_id>;

		//ADCBlock�AConverter�͐ÓI�N���X�����o�Ƃ��Ē�`����Ă���̂ŁA���ׂ����Ƃ�AnalogPin����邾��
		my_adc::analog_pin<xc32::sfr::portB::pin4> APin;

		//���b�N�@���̎������I�ɁAADCBlock��Converter��lock���s����B����āA�ŏ�����������ƃ��b�N�Ɏ��Ԃ�������B
		APin.lock();

		//�ǂݏo���B
		xc::uint16 Data = APin(5);

		//�A�����b�N ���b�N���Ɠ������AADCBlock��Converter���i�N�����p�҂����Ȃ��Ȃ�΁junlock�����B
		APin.unlock();
	}





	return 0;
}