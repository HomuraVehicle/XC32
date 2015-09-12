#ifndef XC32_SFR_UARTBASE_INC
#define XC32_SFR_UARTBASE_INC 100
#
#include<XC32/clock.hpp>
namespace xc32 {
	namespace sfr {
		namespace uart {
			namespace tx_interrupt_mode {
				//���荞�݃^�C�~���O�����߂�
				enum mode {
					//���Ȃ��Ƃ�1�������o�b�t�@���瑗�M���W�X�^�Ɉړ������^�C�~���O
					move_each=0,
					//�S�Ă̕������o�b�t�@���瑗�M���W�X�^�Ɉړ����A�����ׂđ��M���ꂽ�^�C�~���O
					send_all=1,
					//�S�Ă̕������o�b�t�@���瑗�M���W�X�^�Ɉړ������^�C�~���O
					move_register_all=2
				};
			}
			namespace rx_interrupt_mode {
				//���荞�݃^�C�~���O�����߂�
				enum mode {
					//���Ȃ��Ƃ�1��������M���W�X�^����o�b�t�@�Ɉړ������^�C�~���O
					move_each=0,
					//��M���W�X�^����ړ����ꂽ�������o�b�t�@��3����4�𒴂����^�C�~���O
					move_three_quarter=2,
					//��M���W�X�^����ړ����ꂽ�������o�b�t�@��t�ɂȂ����^�C�~���O
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
				//�t���[����s���̎g�p�L����ݒ肷��
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
