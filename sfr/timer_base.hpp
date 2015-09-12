#ifndef XC32_SFR_TIMERBASE_INC
#define XC32_SFR_TIMERBASE_INC 100
#
#include<XCBase/type_traits.hpp>
#include<XCBase/type.hpp>
#include<XCBase/exceptions.hpp>
namespace xc32 {
	using namespace xc;
	namespace sfr {
		namespace timer {
//			struct exception :public xc32::exception{};
//			struct over_div_exception : public exception {};
//			struct invalid_timer_type_exception :public exception {};
			struct normal_prescaler{
				enum div {
					div1=0,
					div2=1,
					div4=2,
					div8=3,
					div16=4,
					div32=5,
					div64=6,
					div256=7,
					diverr=-1
				};
				static unsigned int div_to_value(div Div_) {
					if(Div_==div256)return 256;
					else return 1<<static_cast<unsigned int>(Div_);
				}
				/*
				max(uint16) > clock * (msec/1000) / 2^(1+N)
				2^16 > [clockKHz *10^3 * msec * 10^-3 ] / 2^(1+N)
				2^16 > [clockKHz * msec ] / 2^(1+N)
				2^(N+17) > [clockKHz * msec]

				msec > 2^(N+17)/clockKHz								*/
				static div auto_div(xc32::uint64 BusClock, unsigned int MSec) {
					unsigned long long Val=static_cast<unsigned long long>(BusClock/1000)*MSec;
					if((Val>>18)==0) {
						if((Val>>16)==0)return div::div1;
						else if((Val>>17)==0)return div::div2;
						else return div::div4;
					} else if((Val>>21)==0) {
						if((Val>>19)==0)return div::div8;
						else if((Val>>20)==0)return div::div16;
						else return div::div32;
					} else if((Val>>22)==0) {
						return div::div64;
					} else if((Val>>24)==0) {
						return div::div256;
					}
					return div::diverr;
/*					if((Val>>19)==0) {
						if((Val>>17)==0)return div::div1;
						else if((Val>>18)==0)return div::div2;
						else return div::div4;
					} else if((Val>>22)==0) {
						if((Val>>20)==0)return div::div8;
						else if((Val>>21)==0)return div::div16;
						else return div::div32;
					} else if((Val>>23)==0) {
						return div::div64;
					} else if((Val>>25)==0) {
						return div::div256;
					}
					return div::diverr;
*/				
				}
				static uint16 period(xc32::uint64 BusClock, unsigned int MSec, div Div) {
					return static_cast<uint16>(
						(static_cast<uint64>((BusClock/1000)*MSec) + div_to_value(Div)) /  div_to_value(Div)
					);
				}
				/*
				max(uint32) > clock * (msec/1000) / 2^(1+N)
				2^32 > [clockKHz *10^3 * msec * 10^-3 ] / 2^(1+N)
				2^32 > [clockKHz * msec ] / 2^(1+N)
				2^(N+33) > [clockKHz * msec]

				msec > 2^(N+17)/clockKHz
				*/
				static div long_auto_div(xc32::uint64 BusClock, unsigned int MSec) {
					unsigned long long Val=static_cast<unsigned long long>(BusClock)*MSec;
					if((Val>>35)==0) {
						if((Val>>33)==0)return div::div1;
						else if((Val>>34)==0)return div::div2;
						else return div::div4;
					} else if((Val>>38)==0) {
						if((Val>>36)==0)return div::div8;
						else if((Val>>37)==0)return div::div16;
						else return div::div32;
					} else if((Val>>39)==0) {
						return div::div64;
					} else if((Val>>41)==0) {
						return div::div256;
					}
					return div::diverr;
				}
				static uint32 long_period(xc32::uint64 BusClock, unsigned int MSec, div Div) {
					return static_cast<uint32>(
						static_cast<uint64>((BusClock/1000)*MSec + div_to_value(Div)) /  div_to_value(Div)
					);
				}	
			};
			struct timer1_prescaler{
				//Prescaler bits : TxCONbits.TCKPS,
				//0b11 = 1:256 prescale value
				//0b10 = 1:64  prescale value
				//0b01 = 1:8   prescale value
				//0b00 = 1:1   prescale value
				enum div {
					div1=0,
					div8=1,
					div64=2,
					div256=3,
					diverr=-1
				};
				static unsigned int div_to_value(div Div_) {
					if(Div_==div256)return 256;
					else return 1<<(3*static_cast<unsigned int>(Div_));
				}
				/*
				max(uint32) > clock * (msec/1000) / 2^(1+N)
				2^16 > [clockKHz *10^3 * msec * 10^-3 ] / 2^(1+N)
				2^16 > [clockKHz * msec ] / 2^(1+N)
				2^(17+N) > [clockKHz * msec]							*/
				static div auto_div(uint64 BusClock, unsigned int MSec) {
					unsigned long long Val=static_cast<unsigned long long>(BusClock/1000)*MSec;
					if((Val>>16)==0)return div::div1;
					 else if((Val>>19)==0)return div::div8;
					 else if((Val>>24)==0)return div::div256;
					return div::diverr;
/*					if((Val>>17)==0)return div::div1;
					 else if((Val>>20)==0)return div::div8;
					 else if((Val>>25)==0)return div::div256;
					return div::diverr;
*/
				}
				static uint16 period(uint64 BusClock, unsigned int MSec, div Div) {
					return static_cast<uint16>(
						(static_cast<uint64>((BusClock/1000)*MSec) + div_to_value(Div)) /  div_to_value(Div)
					);
				}			
			};
			//32bitóptimerÇÃëgÇ›çáÇÌÇπÇ™ë√ìñÇ©îªífÇ∑ÇÈ
			template<typename master_timer_register_, typename slave_timer_register_>
			struct is_valid_combination:public xc::false_type{
				typedef false_type type; 
			};
			template<typename master_timer_register_, typename slave_timer_register_>
			bool is_valid_combination_dynamic(master_timer_register_& Master_Register_, slave_timer_register_& Slave_Register_) {
				if(Master_Register_.timer_no()==2 && Slave_Register_.timer_no()==3)return true;
				if(Master_Register_.timer_no()==4 && Slave_Register_.timer_no()==5)return true;
				if(Master_Register_.timer_no()==6 && Slave_Register_.timer_no()==7)return true;
				if(Master_Register_.timer_no()==8 && Slave_Register_.timer_no()==9)return true;
				return false;
			}
		}
	}
}
#
#endif
