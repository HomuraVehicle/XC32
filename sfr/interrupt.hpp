#ifndef XC32_SFR_INTERRUPT_INC
#define XC32_SFR_INTERRUPT_INC 100
#
#include<XC32_config.hpp>
#include"device_include.h"

namespace xc32 {
	namespace sfr {
		namespace interrupt {
			struct function {
				virtual void operator()(void)=0;
			};			
			// 全ての割り込みを許可
			inline void enable_all(void) {
			#ifndef XC32_DEBUGMODE
				asm volatile("ei");
			#endif
			}
			// 全ての割り込みを禁止
			inline void disable_all(void) {
			#ifndef XC32_DEBUGMODE
				asm volatile("di");
			#endif
			}
			// CPUの割り込み優先度を取得
			inline unsigned char cpu_priority(void) {
			#ifndef XC32_DEBUGMODE
				return (_CP0_GET_STATUS()&(_CP0_STATUS_IPL_MASK))>>_CP0_STATUS_IPL_POSITION;
			#else
				return 0;
			#endif
			}
			inline void cpu_priority(unsigned char Priority_) {
			#ifndef XC32_DEBUGMODE
				_CP0_SET_STATUS((_CP0_GET_STATUS()&(~_CP0_STATUS_IPL_MASK))|(Priority_<<_CP0_STATUS_IPL_POSITION));
			#endif
			}
			// Multi Vector Modeにする
			inline void multivectormode(bool val_){
			#ifndef XC32_DEBUGMODE
				INTCONbits.MVEC = static_cast<unsigned char>(val_);
			#endif
			}
			inline bool multivectormode(void){
			#ifndef XC32_DEBUGMODE
				return static_cast<bool>(INTCONbits.MVEC);
			#else
				return false;
			#endif
			}
		}
	}
}

//割り込み関数用define祭り	割り込み優先度変えられる詐欺が改善されれば不要になるはず
//I2C1
#ifndef XC32_CONFIG_I2C1_IPL
#	define XC32_I2C1_IPL 7
#else
#	define XC32_I2C1_IPL XC32_CONFIG_I2C1_IPL
#endif
#ifndef XC32_CONFIG_I2C1_IPL_FOR_ISR
#	define XC32_I2C1_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_I2C1_IPL_FOR_ISR XC32_CONFIG_I2C1_IPL_FOR_ISR
#endif
//I2C2
#ifndef XC32_CONFIG_I2C2_IPL
#	define XC32_I2C2_IPL 7
#else
#	define XC32_I2C2_IPL XC32_CONFIG_I2C2_IPL
#endif
#ifndef XC32_CONFIG_I2C2_IPL_FOR_ISR
#	define XC32_I2C2_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_I2C2_IPL_FOR_ISR XC32_CONFIG_I2C2_IPL_FOR_ISR
#endif
//I2C3
#ifndef XC32_CONFIG_I2C3_IPL
#	define XC32_I2C3_IPL 7
#else
#	define XC32_I2C3_IPL XC32_CONFIG_I2C3_IPL
#endif
#ifndef XC32_CONFIG_I2C3_IPL_FOR_ISR
#	define XC32_I2C3_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_I2C3_IPL_FOR_ISR XC32_CONFIG_I2C3_IPL_FOR_ISR
#endif
//I2C4
#ifndef XC32_CONFIG_I2C4_IPL
#	define XC32_I2C4_IPL 7
#else
#	define XC32_I2C4_IPL XC32_CONFIG_I2C4_IPL
#endif
#ifndef XC32_CONFIG_I2C4_IPL_FOR_ISR
#	define XC32_I2C4_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_I2C4_IPL_FOR_ISR XC32_CONFIG_I2C4_IPL_FOR_ISR
#endif
//I2C5
#ifndef XC32_CONFIG_I2C5_IPL
#	define XC32_I2C5_IPL 7
#else
#	define XC32_I2C5_IPL XC32_CONFIG_I2C5_IPL
#endif
#ifndef XC32_CONFIG_I2C5_IPL_FOR_ISR
#	define XC32_I2C5_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_I2C5_IPL_FOR_ISR XC32_CONFIG_I2C5_IPL_FOR_ISR
#endif
//UART1 TX
#ifndef XC32_CONFIG_UART1_TX_IPL
#	define XC32_UART1_TX_IPL 7
#else
#	define XC32_UART1_TX_IPL XC32_CONFIG_UART1_TX_IPL
#endif
#ifndef XC32_CONFIG_UART1_TX_IPL_FOR_ISR
#	define XC32_UART1_TX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART1_TX_IPL_FOR_ISR XC32_CONFIG_UART1_TX_IPL_FOR_ISR
#endif
//UART1 RX
#ifndef XC32_CONFIG_UART1_RX_IPL
#	define XC32_UART1_RX_IPL 7
#else
#	define XC32_UART1_RX_IPL XC32_CONFIG_UART1_RX_IPL
#endif
#ifndef XC32_CONFIG_UART1_RX_IPL_FOR_ISR
#	define XC32_UART1_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART1_RX_IPL_FOR_ISR XC32_CONFIG_UART1_RX_IPL_FOR_ISR
#endif
//UART2 TX
#ifndef XC32_CONFIG_UART2_TX_IPL
#	define XC32_UART2_TX_IPL 7
#else
#	define XC32_UART2_TX_IPL XC32_CONFIG_UART2_TX_IPL
#endif
#ifndef XC32_CONFIG_UART2_TX_IPL_FOR_ISR
#	define XC32_UART2_TX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART2_TX_IPL_FOR_ISR XC32_CONFIG_UART2_TX_IPL_FOR_ISR
#endif
//UART2 RX
#ifndef XC32_CONFIG_UART2_RX_IPL
#	define XC32_UART2_RX_IPL 7
#else
#	define XC32_UART2_RX_IPL XC32_CONFIG_UART2_RX_IPL
#endif
#ifndef XC32_CONFIG_UART2_RX_IPL_FOR_ISR
#	define XC32_UART2_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART2_RX_IPL_FOR_ISR XC32_CONFIG_UART2_RX_IPL_FOR_ISR
#endif
//UART3 TX
#ifndef XC32_CONFIG_UART3_TX_IPL
#	define XC32_UART3_TX_IPL 7
#else
#	define XC32_UART3_TX_IPL XC32_CONFIG_UART3_TX_IPL
#endif
#ifndef XC32_CONFIG_UART3_TX_IPL_FOR_ISR
#	define XC32_UART3_TX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART3_TX_IPL_FOR_ISR XC32_CONFIG_UART3_TX_IPL_FOR_ISR
#endif
//UART3 RX
#ifndef XC32_CONFIG_UART3_RX_IPL
#	define XC32_UART3_RX_IPL 7
#else
#	define XC32_UART3_RX_IPL XC32_CONFIG_UART3_RX_IPL
#endif
#ifndef XC32_CONFIG_UART3_RX_IPL_FOR_ISR
#	define XC32_UART3_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART3_RX_IPL_FOR_ISR XC32_CONFIG_UART3_RX_IPL_FOR_ISR
#endif
//UART4 TX
#ifndef XC32_CONFIG_UART4_TX_IPL
#	define XC32_UART4_TX_IPL 7
#else
#	define XC32_UART4_TX_IPL XC32_CONFIG_UART4_TX_IPL
#endif
#ifndef XC32_CONFIG_UART4_TX_IPL_FOR_ISR
#	define XC32_UART4_TX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART4_TX_IPL_FOR_ISR XC32_CONFIG_UART4_TX_IPL_FOR_ISR
#endif
//UART4 RX
#ifndef XC32_CONFIG_UART4_RX_IPL
#	define XC32_UART4_RX_IPL 7
#else
#	define XC32_UART4_RX_IPL XC32_CONFIG_UART4_RX_IPL
#endif
#ifndef XC32_CONFIG_UART4_RX_IPL_FOR_ISR
#	define XC32_UART4_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART4_RX_IPL_FOR_ISR XC32_CONFIG_UART4_RX_IPL_FOR_ISR
#endif
//UART5 TX
#ifndef XC32_CONFIG_UART5_TX_IPL
#	define XC32_UART5_TX_IPL 7
#else
#	define XC32_UART5_TX_IPL XC32_CONFIG_UART5_TX_IPL
#endif
#ifndef XC32_CONFIG_UART5_TX_IPL_FOR_ISR
#	define XC32_UART5_TX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART5_TX_IPL_FOR_ISR XC32_CONFIG_UART5_TX_IPL_FOR_ISR
#endif
//UART5 RX
#ifndef XC32_CONFIG_UART5_RX_IPL
#	define XC32_UART5_RX_IPL 7
#else
#	define XC32_UART5_RX_IPL XC32_CONFIG_UART5_RX_IPL
#endif
#ifndef XC32_CONFIG_UART5_RX_IPL_FOR_ISR
#	define XC32_UART5_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART5_RX_IPL_FOR_ISR XC32_CONFIG_UART5_RX_IPL_FOR_ISR
#endif
//UART6 TX
#ifndef XC32_CONFIG_UART6_TX_IPL
#	define XC32_UART6_TX_IPL 7
#else
#	define XC32_UART6_TX_IPL XC32_CONFIG_UART6_TX_IPL
#endif
#ifndef XC32_CONFIG_UART6_TX_IPL_FOR_ISR
#	define XC32_UART6_TX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART6_TX_IPL_FOR_ISR XC32_CONFIG_UART6_TX_IPL_FOR_ISR
#endif
//UART6 RX
#ifndef XC32_CONFIG_UART6_RX_IPL
#	define XC32_UART6_RX_IPL 7
#else
#	define XC32_UART6_RX_IPL XC32_CONFIG_UART6_RX_IPL
#endif
#ifndef XC32_CONFIG_UART6_RX_IPL_FOR_ISR
#	define XC32_UART6_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_UART6_RX_IPL_FOR_ISR XC32_CONFIG_UART6_RX_IPL_FOR_ISR
#endif
//SPI1
#ifndef XC32_CONFIG_SPI1_RX_IPL
#	define XC32_SPI1_RX_IPL 7
#else
#	define XC32_SPI1_RX_IPL XC32_CONFIG_SPI1_RX_IPL
#endif
#ifndef XC32_CONFIG_SPI1_RX_IPL_FOR_ISR
#	define XC32_SPI1_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_SPI1_RX_IPL_FOR_ISR XC32_CONFIG_SPI1_RX_IPL_FOR_ISR
#endif
//SPI2
#ifndef XC32_CONFIG_SPI2_RX_IPL
#	define XC32_SPI2_RX_IPL 7
#else
#	define XC32_SPI2_RX_IPL XC32_CONFIG_SPI2_RX_IPL
#endif
#ifndef XC32_CONFIG_SPI2_RX_IPL_FOR_ISR
#	define XC32_SPI2_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_SPI2_RX_IPL_FOR_ISR XC32_CONFIG_SPI2_RX_IPL_FOR_ISR
#endif
//SPI3
#ifndef XC32_CONFIG_SPI3_RX_IPL
#	define XC32_SPI3_RX_IPL 7
#else
#	define XC32_SPI3_RX_IPL XC32_CONFIG_SPI3_RX_IPL
#endif
#ifndef XC32_CONFIG_SPI3_RX_IPL_FOR_ISR
#	define XC32_SPI3_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_SPI3_RX_IPL_FOR_ISR XC32_CONFIG_SPI3_RX_IPL_FOR_ISR
#endif
//SPI4
#ifndef XC32_CONFIG_SPI4_RX_IPL
#	define XC32_SPI4_RX_IPL 7
#else
#	define XC32_SPI4_RX_IPL XC32_CONFIG_SPI4_RX_IPL
#endif
#ifndef XC32_CONFIG_SPI4_RX_IPL_FOR_ISR
#	define XC32_SPI4_RX_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_SPI4_RX_IPL_FOR_ISR XC32_CONFIG_SPI4_RX_IPL_FOR_ISR
#endif
//TIMER1
#ifndef XC32_CONFIG_TIMER1_IPL
#	define XC32_TIMER1_IPL 7
#else
#	define XC32_TIMER1_IPL XC32_CONFIG_TIMER1_IPL
#endif
#ifndef XC32_CONFIG_TIMER1_IPL_FOR_ISR
#	define XC32_TIMER1_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER1_IPL_FOR_ISR XC32_CONFIG_TIMER1_IPL_FOR_ISR
#endif
//TIMER2
#ifndef XC32_CONFIG_TIMER2_IPL
#	define XC32_TIMER2_IPL 7
#else
#	define XC32_TIMER2_IPL XC32_CONFIG_TIMER2_IPL
#endif
#ifndef XC32_CONFIG_TIMER2_IPL_FOR_ISR
#	define XC32_TIMER2_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER2_IPL_FOR_ISR XC32_CONFIG_TIMER2_IPL_FOR_ISR
#endif
//TIMER3
#ifndef XC32_CONFIG_TIMER3_IPL
#	define XC32_TIMER3_IPL 7
#else
#	define XC32_TIMER3_IPL XC32_CONFIG_TIMER3_IPL
#endif
#ifndef XC32_CONFIG_TIMER3_IPL_FOR_ISR
#	define XC32_TIMER3_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER3_IPL_FOR_ISR XC32_CONFIG_TIMER3_IPL_FOR_ISR
#endif
//TIMER4
#ifndef XC32_CONFIG_TIMER4_IPL
#	define XC32_TIMER4_IPL 7
#else
#	define XC32_TIMER4_IPL XC32_CONFIG_TIMER4_IPL
#endif
#ifndef XC32_CONFIG_TIMER4_IPL_FOR_ISR
#	define XC32_TIMER4_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER4_IPL_FOR_ISR XC32_CONFIG_TIMER4_IPL_FOR_ISR
#endif
//TIMER5
#ifndef XC32_CONFIG_TIMER5_IPL
#	define XC32_TIMER5_IPL 7
#else
#	define XC32_TIMER5_IPL XC32_CONFIG_TIMER5_IPL
#endif
#ifndef XC32_CONFIG_TIMER5_IPL_FOR_ISR
#	define XC32_TIMER5_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER5_IPL_FOR_ISR XC32_CONFIG_TIMER5_IPL_FOR_ISR
#endif
//TIMER6
#ifndef XC32_CONFIG_TIMER6_IPL
#	define XC32_TIMER6_IPL 7
#else
#	define XC32_TIMER6_IPL XC32_CONFIG_TIMER6_IPL
#endif
#ifndef XC32_CONFIG_TIMER6_IPL_FOR_ISR
#	define XC32_TIMER6_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER6_IPL_FOR_ISR XC32_CONFIG_TIMER6_IPL_FOR_ISR
#endif
//TIMER7
#ifndef XC32_CONFIG_TIMER7_IPL
#	define XC32_TIMER7_IPL 7
#else
#	define XC32_TIMER7_IPL XC32_CONFIG_TIMER7_IPL
#endif
#ifndef XC32_CONFIG_TIMER7_IPL_FOR_ISR
#	define XC32_TIMER7_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER7_IPL_FOR_ISR XC32_CONFIG_TIMER7_IPL_FOR_ISR
#endif
//TIMER8
#ifndef XC32_CONFIG_TIMER8_IPL
#	define XC32_TIMER8_IPL 7
#else
#	define XC32_TIMER8_IPL XC32_CONFIG_TIMER8_IPL
#endif
#ifndef XC32_CONFIG_TIMER8_IPL_FOR_ISR
#	define XC32_TIMER8_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER8_IPL_FOR_ISR XC32_CONFIG_TIMER8_IPL_FOR_ISR
#endif
//TIMER9
#ifndef XC32_CONFIG_TIMER9_IPL
#	define XC32_TIMER9_IPL 7
#else
#	define XC32_TIMER9_IPL XC32_CONFIG_TIMER9_IPL
#endif
#ifndef XC32_CONFIG_TIMER9_IPL_FOR_ISR
#	define XC32_TIMER9_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_TIMER9_IPL_FOR_ISR XC32_CONFIG_TIMER9_IPL_FOR_ISR
#endif
//ADC1
#ifndef XC32_CONFIG_ADC1_IPL
#	define XC32_ADC1_IPL 7
#else
#	define XC32_ADC1_IPL XC32_CONFIG_ADC1_IPL
#endif
#ifndef XC32_CONFIG_ADC1_IPL_FOR_ISR
#	define XC32_ADC1_IPL_FOR_ISR IPL7AUTO
#else
#	define XC32_ADC1_IPL_FOR_ISR XC32_CONFIG_ADC1_IPL_FOR_ISR
#endif
#
#endif
