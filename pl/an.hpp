#ifdef BLCK_ANALOG_0
template<>
struct an<constexpr_no<0>> {
typedef costexpr_no<BLCK_ANALOG_0> converter_no;
public:
uint16 data()const volatile { return ADCDATA0; }
bool data_ready()const { return ADCDSTAT1bits.ARDY0; }
};
#endif

#ifdef BLCK_ANALOG_1
template<>
struct an<constexpr_no<1>> {
typedef costexpr_no<BLCK_ANALOG_1> converter_no;
public:
uint16 data()const volatile { return ADCDATA1; }
bool data_ready()const { return ADCDSTAT1bits.ARDY1; }
};
#endif

#ifdef BLCK_ANALOG_2
template<>
struct an<constexpr_no<2>> {
typedef costexpr_no<BLCK_ANALOG_2> converter_no;
public:
uint16 data()const volatile { return ADCDATA2; }
bool data_ready()const { return ADCDSTAT1bits.ARDY2; }
};
#endif

#ifdef BLCK_ANALOG_3
template<>
struct an<constexpr_no<3>> {
typedef costexpr_no<BLCK_ANALOG_3> converter_no;
public:
uint16 data()const volatile { return ADCDATA3; }
bool data_ready()const { return ADCDSTAT1bits.ARDY3; }
};
#endif

#ifdef BLCK_ANALOG_4
template<>
struct an<constexpr_no<4>> {
typedef costexpr_no<BLCK_ANALOG_4> converter_no;
public:
uint16 data()const volatile { return ADCDATA4; }
bool data_ready()const { return ADCDSTAT1bits.ARDY4; }
};
#endif

#ifdef BLCK_ANALOG_5
template<>
struct an<constexpr_no<5>> {
typedef costexpr_no<BLCK_ANALOG_5> converter_no;
public:
uint16 data()const volatile { return ADCDATA5; }
bool data_ready()const { return ADCDSTAT1bits.ARDY5; }
};
#endif

#ifdef BLCK_ANALOG_6
template<>
struct an<constexpr_no<6>> {
typedef costexpr_no<BLCK_ANALOG_6> converter_no;
public:
uint16 data()const volatile { return ADCDATA6; }
bool data_ready()const { return ADCDSTAT1bits.ARDY6; }
};
#endif

#ifdef BLCK_ANALOG_7
template<>
struct an<constexpr_no<7>> {
typedef costexpr_no<BLCK_ANALOG_7> converter_no;
public:
uint16 data()const volatile { return ADCDATA7; }
bool data_ready()const { return ADCDSTAT1bits.ARDY7; }
};
#endif

#ifdef BLCK_ANALOG_8
template<>
struct an<constexpr_no<8>> {
typedef costexpr_no<BLCK_ANALOG_8> converter_no;
public:
uint16 data()const volatile { return ADCDATA8; }
bool data_ready()const { return ADCDSTAT1bits.ARDY8; }
};
#endif

#ifdef BLCK_ANALOG_9
template<>
struct an<constexpr_no<9>> {
typedef costexpr_no<BLCK_ANALOG_9> converter_no;
public:
uint16 data()const volatile { return ADCDATA9; }
bool data_ready()const { return ADCDSTAT1bits.ARDY9; }
};
#endif

#ifdef BLCK_ANALOG_10
template<>
struct an<constexpr_no<10>> {
typedef costexpr_no<BLCK_ANALOG_10> converter_no;
public:
uint16 data()const volatile { return ADCDATA10; }
bool data_ready()const { return ADCDSTAT1bits.ARDY10; }
};
#endif

#ifdef BLCK_ANALOG_11
template<>
struct an<constexpr_no<11>> {
typedef costexpr_no<BLCK_ANALOG_11> converter_no;
public:
uint16 data()const volatile { return ADCDATA11; }
bool data_ready()const { return ADCDSTAT1bits.ARDY11; }
};
#endif

#ifdef BLCK_ANALOG_12
template<>
struct an<constexpr_no<12>> {
typedef costexpr_no<BLCK_ANALOG_12> converter_no;
public:
uint16 data()const volatile { return ADCDATA12; }
bool data_ready()const { return ADCDSTAT1bits.ARDY12; }
};
#endif

#ifdef BLCK_ANALOG_13
template<>
struct an<constexpr_no<13>> {
typedef costexpr_no<BLCK_ANALOG_13> converter_no;
public:
uint16 data()const volatile { return ADCDATA13; }
bool data_ready()const { return ADCDSTAT1bits.ARDY13; }
};
#endif

#ifdef BLCK_ANALOG_14
template<>
struct an<constexpr_no<14>> {
typedef costexpr_no<BLCK_ANALOG_14> converter_no;
public:
uint16 data()const volatile { return ADCDATA14; }
bool data_ready()const { return ADCDSTAT1bits.ARDY14; }
};
#endif

#ifdef BLCK_ANALOG_15
template<>
struct an<constexpr_no<15>> {
typedef costexpr_no<BLCK_ANALOG_15> converter_no;
public:
uint16 data()const volatile { return ADCDATA15; }
bool data_ready()const { return ADCDSTAT1bits.ARDY15; }
};
#endif

#ifdef BLCK_ANALOG_16
template<>
struct an<constexpr_no<16>> {
typedef costexpr_no<BLCK_ANALOG_16> converter_no;
public:
uint16 data()const volatile { return ADCDATA16; }
bool data_ready()const { return ADCDSTAT1bits.ARDY16; }
};
#endif

#ifdef BLCK_ANALOG_17
template<>
struct an<constexpr_no<17>> {
typedef costexpr_no<BLCK_ANALOG_17> converter_no;
public:
uint16 data()const volatile { return ADCDATA17; }
bool data_ready()const { return ADCDSTAT1bits.ARDY17; }
};
#endif

#ifdef BLCK_ANALOG_18
template<>
struct an<constexpr_no<18>> {
typedef costexpr_no<BLCK_ANALOG_18> converter_no;
public:
uint16 data()const volatile { return ADCDATA18; }
bool data_ready()const { return ADCDSTAT1bits.ARDY18; }
};
#endif

#ifdef BLCK_ANALOG_19
template<>
struct an<constexpr_no<19>> {
typedef costexpr_no<BLCK_ANALOG_19> converter_no;
public:
uint16 data()const volatile { return ADCDATA19; }
bool data_ready()const { return ADCDSTAT1bits.ARDY19; }
};
#endif

#ifdef BLCK_ANALOG_20
template<>
struct an<constexpr_no<20>> {
typedef costexpr_no<BLCK_ANALOG_20> converter_no;
public:
uint16 data()const volatile { return ADCDATA20; }
bool data_ready()const { return ADCDSTAT1bits.ARDY20; }
};
#endif

#ifdef BLCK_ANALOG_21
template<>
struct an<constexpr_no<21>> {
typedef costexpr_no<BLCK_ANALOG_21> converter_no;
public:
uint16 data()const volatile { return ADCDATA21; }
bool data_ready()const { return ADCDSTAT1bits.ARDY21; }
};
#endif

#ifdef BLCK_ANALOG_22
template<>
struct an<constexpr_no<22>> {
typedef costexpr_no<BLCK_ANALOG_22> converter_no;
public:
uint16 data()const volatile { return ADCDATA22; }
bool data_ready()const { return ADCDSTAT1bits.ARDY22; }
};
#endif

#ifdef BLCK_ANALOG_23
template<>
struct an<constexpr_no<23>> {
typedef costexpr_no<BLCK_ANALOG_23> converter_no;
public:
uint16 data()const volatile { return ADCDATA23; }
bool data_ready()const { return ADCDSTAT1bits.ARDY23; }
};
#endif

#ifdef BLCK_ANALOG_24
template<>
struct an<constexpr_no<24>> {
typedef costexpr_no<BLCK_ANALOG_24> converter_no;
public:
uint16 data()const volatile { return ADCDATA24; }
bool data_ready()const { return ADCDSTAT1bits.ARDY24; }
};
#endif

#ifdef BLCK_ANALOG_25
template<>
struct an<constexpr_no<25>> {
typedef costexpr_no<BLCK_ANALOG_25> converter_no;
public:
uint16 data()const volatile { return ADCDATA25; }
bool data_ready()const { return ADCDSTAT1bits.ARDY25; }
};
#endif

#ifdef BLCK_ANALOG_26
template<>
struct an<constexpr_no<26>> {
typedef costexpr_no<BLCK_ANALOG_26> converter_no;
public:
uint16 data()const volatile { return ADCDATA26; }
bool data_ready()const { return ADCDSTAT1bits.ARDY26; }
};
#endif

#ifdef BLCK_ANALOG_27
template<>
struct an<constexpr_no<27>> {
typedef costexpr_no<BLCK_ANALOG_27> converter_no;
public:
uint16 data()const volatile { return ADCDATA27; }
bool data_ready()const { return ADCDSTAT1bits.ARDY27; }
};
#endif

#ifdef BLCK_ANALOG_28
template<>
struct an<constexpr_no<28>> {
typedef costexpr_no<BLCK_ANALOG_28> converter_no;
public:
uint16 data()const volatile { return ADCDATA28; }
bool data_ready()const { return ADCDSTAT1bits.ARDY28; }
};
#endif

#ifdef BLCK_ANALOG_29
template<>
struct an<constexpr_no<29>> {
typedef costexpr_no<BLCK_ANALOG_29> converter_no;
public:
uint16 data()const volatile { return ADCDATA29; }
bool data_ready()const { return ADCDSTAT1bits.ARDY29; }
};
#endif

#ifdef BLCK_ANALOG_30
template<>
struct an<constexpr_no<30>> {
typedef costexpr_no<BLCK_ANALOG_30> converter_no;
public:
uint16 data()const volatile { return ADCDATA30; }
bool data_ready()const { return ADCDSTAT1bits.ARDY30; }
};
#endif

#ifdef BLCK_ANALOG_31
template<>
struct an<constexpr_no<31>> {
typedef costexpr_no<BLCK_ANALOG_31> converter_no;
public:
uint16 data()const volatile { return ADCDATA31; }
bool data_ready()const { return ADCDSTAT1bits.ARDY31; }
};
#endif

#ifdef BLCK_ANALOG_32
template<>
struct an<constexpr_no<32>> {
typedef costexpr_no<BLCK_ANALOG_32> converter_no;
public:
uint16 data()const volatile { return ADCDATA32; }
bool data_ready()const { return ADCDSTAT1bits.ARDY32; }
};
#endif

#ifdef BLCK_ANALOG_33
template<>
struct an<constexpr_no<33>> {
typedef costexpr_no<BLCK_ANALOG_33> converter_no;
public:
uint16 data()const volatile { return ADCDATA33; }
bool data_ready()const { return ADCDSTAT1bits.ARDY33; }
};
#endif

#ifdef BLCK_ANALOG_34
template<>
struct an<constexpr_no<34>> {
typedef costexpr_no<BLCK_ANALOG_34> converter_no;
public:
uint16 data()const volatile { return ADCDATA34; }
bool data_ready()const { return ADCDSTAT1bits.ARDY34; }
};
#endif

#ifdef BLCK_ANALOG_35
template<>
struct an<constexpr_no<35>> {
typedef costexpr_no<BLCK_ANALOG_35> converter_no;
public:
uint16 data()const volatile { return ADCDATA35; }
bool data_ready()const { return ADCDSTAT1bits.ARDY35; }
};
#endif

#ifdef BLCK_ANALOG_36
template<>
struct an<constexpr_no<36>> {
typedef costexpr_no<BLCK_ANALOG_36> converter_no;
public:
uint16 data()const volatile { return ADCDATA36; }
bool data_ready()const { return ADCDSTAT1bits.ARDY36; }
};
#endif

#ifdef BLCK_ANALOG_37
template<>
struct an<constexpr_no<37>> {
typedef costexpr_no<BLCK_ANALOG_37> converter_no;
public:
uint16 data()const volatile { return ADCDATA37; }
bool data_ready()const { return ADCDSTAT1bits.ARDY37; }
};
#endif

#ifdef BLCK_ANALOG_38
template<>
struct an<constexpr_no<38>> {
typedef costexpr_no<BLCK_ANALOG_38> converter_no;
public:
uint16 data()const volatile { return ADCDATA38; }
bool data_ready()const { return ADCDSTAT1bits.ARDY38; }
};
#endif

#ifdef BLCK_ANALOG_39
template<>
struct an<constexpr_no<39>> {
typedef costexpr_no<BLCK_ANALOG_39> converter_no;
public:
uint16 data()const volatile { return ADCDATA39; }
bool data_ready()const { return ADCDSTAT1bits.ARDY39; }
};
#endif

#ifdef BLCK_ANALOG_40
template<>
struct an<constexpr_no<40>> {
typedef costexpr_no<BLCK_ANALOG_40> converter_no;
public:
uint16 data()const volatile { return ADCDATA40; }
bool data_ready()const { return ADCDSTAT1bits.ARDY40; }
};
#endif

#ifdef BLCK_ANALOG_41
template<>
struct an<constexpr_no<41>> {
typedef costexpr_no<BLCK_ANALOG_41> converter_no;
public:
uint16 data()const volatile { return ADCDATA41; }
bool data_ready()const { return ADCDSTAT1bits.ARDY41; }
};
#endif

#ifdef BLCK_ANALOG_42
template<>
struct an<constexpr_no<42>> {
typedef costexpr_no<BLCK_ANALOG_42> converter_no;
public:
uint16 data()const volatile { return ADCDATA42; }
bool data_ready()const { return ADCDSTAT1bits.ARDY42; }
};
#endif

#ifdef BLCK_ANALOG_43
template<>
struct an<constexpr_no<43>> {
typedef costexpr_no<BLCK_ANALOG_43> converter_no;
public:
uint16 data()const volatile { return ADCDATA43; }
bool data_ready()const { return ADCDSTAT1bits.ARDY43; }
};
#endif

#ifdef BLCK_ANALOG_44
template<>
struct an<constexpr_no<44>> {
typedef costexpr_no<BLCK_ANALOG_44> converter_no;
public:
uint16 data()const volatile { return ADCDATA44; }
bool data_ready()const { return ADCDSTAT1bits.ARDY44; }
};
#endif

#ifdef BLCK_ANALOG_45
template<>
struct an<constexpr_no<45>> {
typedef costexpr_no<BLCK_ANALOG_45> converter_no;
public:
uint16 data()const volatile { return ADCDATA45; }
bool data_ready()const { return ADCDSTAT1bits.ARDY45; }
};
#endif

#ifdef BLCK_ANALOG_46
template<>
struct an<constexpr_no<46>> {
typedef costexpr_no<BLCK_ANALOG_46> converter_no;
public:
uint16 data()const volatile { return ADCDATA46; }
bool data_ready()const { return ADCDSTAT1bits.ARDY46; }
};
#endif

#ifdef BLCK_ANALOG_47
template<>
struct an<constexpr_no<47>> {
typedef costexpr_no<BLCK_ANALOG_47> converter_no;
public:
uint16 data()const volatile { return ADCDATA47; }
bool data_ready()const { return ADCDSTAT1bits.ARDY47; }
};
#endif

