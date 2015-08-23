#ifndef XC32LIB_SFR_SPI1_CPP_INC
#define XC32LIB_SFR_SPI1_CPP_INC 100
#
#include"spi1.hpp"

#ifndef XC32LIB_SFR_SPI1_EXPLICITINTERRUPT
extern "C"{
	void x_xc32_sfr_spi1_interrupt(void) {
		static xc32::sfr::spi1 SPI1;
		//private�����o�̊֐��|�C���^�����s���邽�߂ɁA������const���O���Ă���
		if(SPI1.rx_interrupt_function()) {
			(*const_cast<xc32::sfr::interrupt::function*>(SPI1.rx_interrupt_function()))();
		}
		SPI1.rx_interrupt_flag(false);
	/*
		if(SPI1.tx_interrupt_flag()) {
			//private�����o�̊֐��|�C���^�����s���邽�߂ɁA������const���O���Ă���
			if(SPI1.tx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI1.tx_interrupt_function()))();
			}
			SPI1.tx_interrupt_flag(false);
		} else if(SPI1.rx_interrupt_flag()) {
			//private�����o�̊֐��|�C���^�����s���邽�߂ɁA������const���O���Ă���
			if(SPI1.rx_interrupt_function()) {
				(*const_cast<xc32::sfr::interrupt::function*>(SPI1.rx_interrupt_function()))();
			}
			SPI1.rx_interrupt_flag(false);
		} else return;*/
	}
}
#endif

namespace xc32{
	namespace sfr{
		interrupt::function* spi1::tx_interrupt_ptr;
		interrupt::function* spi1::rx_interrupt_ptr;
		const unsigned char spi1::rx_ipl = XC32LIB_SPI1_RX_IPL;
	}
}

#
#endif
