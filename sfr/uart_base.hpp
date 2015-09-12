#ifndef XC32_SFR_UARTBASE_INC
#define XC32_SFR_UARTBASE_INC 100
#
#include<XC32/clock.hpp>
namespace xc32 {
	namespace sfr {
		namespace uart {
			namespace tx_interrupt_mode {
				//割り込みタイミングを決める
				enum mode {
					//少なくとも1文字がバッファから送信レジスタに移動したタイミング
					move_each=0,
					//全ての文字がバッファから送信レジスタに移動し、かつすべて送信されたタイミング
					send_all=1,
					//全ての文字がバッファから送信レジスタに移動したタイミング
					move_register_all=2
				};
			}
			namespace rx_interrupt_mode {
				//割り込みタイミングを決める
				enum mode {
					//少なくとも1文字が受信レジスタからバッファに移動したタイミング
					move_each=0,
					//受信レジスタから移動された文字がバッファの3分の4を超えたタイミング
					move_three_quarter=2,
					//受信レジスタから移動された文字がバッファ一杯になったタイミング
					move_full=3
				};
			}
			namespace flowcontrol {
				/*
					0b11 = UxTX, UxRX and UxBCLK pins are enabled and used; UxCTS pin is controlled by corresponding bits in the PORTx register
					0b10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
					0b01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin is controlled by corresponding bits in the PORTx register
					0b00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS /UxBCLK pins are controlled by corresponding bits in the PORTx register
				*/
				//フロー制御ピンの使用有無を設定する
				enum mode {
					no_control=0,
					rts_control=1,
					rts_cts_control=2
				};
			}

			//BRGvalue = bus_clock/(16 * baudrate)-1
			inline unsigned int baud_rate(unsigned int bps) {
				return static_cast<unsigned int>(clock::get_bus_clock()/(16.0*bps) -1);
			}
		}
	}
}
#
#endif
