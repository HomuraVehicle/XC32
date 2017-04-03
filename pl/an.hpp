#ifdef BLCK_ANALOG_0
template<>
struct an<constexpr_no<0>> {
typedef costexpr_no<BLCK_ANALOG_0> converter_no;
public:
uint16 data()const volatile { return ADCDATA0; }
bool data_ready()const { return ADCDSTAT1bits.ARDY0; }
void set_common_scan(bool val){ADCCSS1bits.CSS0 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_1
template<>
struct an<constexpr_no<1>> {
typedef costexpr_no<BLCK_ANALOG_1> converter_no;
public:
uint16 data()const volatile { return ADCDATA1; }
bool data_ready()const { return ADCDSTAT1bits.ARDY1; }
void set_common_scan(bool val){ADCCSS1bits.CSS1 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_2
template<>
struct an<constexpr_no<2>> {
typedef costexpr_no<BLCK_ANALOG_2> converter_no;
public:
uint16 data()const volatile { return ADCDATA2; }
bool data_ready()const { return ADCDSTAT1bits.ARDY2; }
void set_common_scan(bool val){ADCCSS1bits.CSS2 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_3
template<>
struct an<constexpr_no<3>> {
typedef costexpr_no<BLCK_ANALOG_3> converter_no;
public:
uint16 data()const volatile { return ADCDATA3; }
bool data_ready()const { return ADCDSTAT1bits.ARDY3; }
void set_common_scan(bool val){ADCCSS1bits.CSS3 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_4
template<>
struct an<constexpr_no<4>> {
typedef costexpr_no<BLCK_ANALOG_4> converter_no;
public:
uint16 data()const volatile { return ADCDATA4; }
bool data_ready()const { return ADCDSTAT1bits.ARDY4; }
void set_common_scan(bool val){ADCCSS1bits.CSS4 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_5
template<>
struct an<constexpr_no<5>> {
typedef costexpr_no<BLCK_ANALOG_5> converter_no;
public:
uint16 data()const volatile { return ADCDATA5; }
bool data_ready()const { return ADCDSTAT1bits.ARDY5; }
void set_common_scan(bool val){ADCCSS1bits.CSS5 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_6
template<>
struct an<constexpr_no<6>> {
typedef costexpr_no<BLCK_ANALOG_6> converter_no;
public:
uint16 data()const volatile { return ADCDATA6; }
bool data_ready()const { return ADCDSTAT1bits.ARDY6; }
void set_common_scan(bool val){ADCCSS1bits.CSS6 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_7
template<>
struct an<constexpr_no<7>> {
typedef costexpr_no<BLCK_ANALOG_7> converter_no;
public:
uint16 data()const volatile { return ADCDATA7; }
bool data_ready()const { return ADCDSTAT1bits.ARDY7; }
void set_common_scan(bool val){ADCCSS1bits.CSS7 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_8
template<>
struct an<constexpr_no<8>> {
typedef costexpr_no<BLCK_ANALOG_8> converter_no;
public:
uint16 data()const volatile { return ADCDATA8; }
bool data_ready()const { return ADCDSTAT1bits.ARDY8; }
void set_common_scan(bool val){ADCCSS1bits.CSS8 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_9
template<>
struct an<constexpr_no<9>> {
typedef costexpr_no<BLCK_ANALOG_9> converter_no;
public:
uint16 data()const volatile { return ADCDATA9; }
bool data_ready()const { return ADCDSTAT1bits.ARDY9; }
void set_common_scan(bool val){ADCCSS1bits.CSS9 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_10
template<>
struct an<constexpr_no<10>> {
typedef costexpr_no<BLCK_ANALOG_10> converter_no;
public:
uint16 data()const volatile { return ADCDATA10; }
bool data_ready()const { return ADCDSTAT1bits.ARDY10; }
void set_common_scan(bool val){ADCCSS1bits.CSS10 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_11
template<>
struct an<constexpr_no<11>> {
typedef costexpr_no<BLCK_ANALOG_11> converter_no;
public:
uint16 data()const volatile { return ADCDATA11; }
bool data_ready()const { return ADCDSTAT1bits.ARDY11; }
void set_common_scan(bool val){ADCCSS1bits.CSS11 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_12
template<>
struct an<constexpr_no<12>> {
typedef costexpr_no<BLCK_ANALOG_12> converter_no;
public:
uint16 data()const volatile { return ADCDATA12; }
bool data_ready()const { return ADCDSTAT1bits.ARDY12; }
void set_common_scan(bool val){ADCCSS1bits.CSS12 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_13
template<>
struct an<constexpr_no<13>> {
typedef costexpr_no<BLCK_ANALOG_13> converter_no;
public:
uint16 data()const volatile { return ADCDATA13; }
bool data_ready()const { return ADCDSTAT1bits.ARDY13; }
void set_common_scan(bool val){ADCCSS1bits.CSS13 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_14
template<>
struct an<constexpr_no<14>> {
typedef costexpr_no<BLCK_ANALOG_14> converter_no;
public:
uint16 data()const volatile { return ADCDATA14; }
bool data_ready()const { return ADCDSTAT1bits.ARDY14; }
void set_common_scan(bool val){ADCCSS1bits.CSS14 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_15
template<>
struct an<constexpr_no<15>> {
typedef costexpr_no<BLCK_ANALOG_15> converter_no;
public:
uint16 data()const volatile { return ADCDATA15; }
bool data_ready()const { return ADCDSTAT1bits.ARDY15; }
void set_common_scan(bool val){ADCCSS1bits.CSS15 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_16
template<>
struct an<constexpr_no<16>> {
typedef costexpr_no<BLCK_ANALOG_16> converter_no;
public:
uint16 data()const volatile { return ADCDATA16; }
bool data_ready()const { return ADCDSTAT1bits.ARDY16; }
void set_common_scan(bool val){ADCCSS1bits.CSS16 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_17
template<>
struct an<constexpr_no<17>> {
typedef costexpr_no<BLCK_ANALOG_17> converter_no;
public:
uint16 data()const volatile { return ADCDATA17; }
bool data_ready()const { return ADCDSTAT1bits.ARDY17; }
void set_common_scan(bool val){ADCCSS1bits.CSS17 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_18
template<>
struct an<constexpr_no<18>> {
typedef costexpr_no<BLCK_ANALOG_18> converter_no;
public:
uint16 data()const volatile { return ADCDATA18; }
bool data_ready()const { return ADCDSTAT1bits.ARDY18; }
void set_common_scan(bool val){ADCCSS1bits.CSS18 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_19
template<>
struct an<constexpr_no<19>> {
typedef costexpr_no<BLCK_ANALOG_19> converter_no;
public:
uint16 data()const volatile { return ADCDATA19; }
bool data_ready()const { return ADCDSTAT1bits.ARDY19; }
void set_common_scan(bool val){ADCCSS1bits.CSS19 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_20
template<>
struct an<constexpr_no<20>> {
typedef costexpr_no<BLCK_ANALOG_20> converter_no;
public:
uint16 data()const volatile { return ADCDATA20; }
bool data_ready()const { return ADCDSTAT1bits.ARDY20; }
void set_common_scan(bool val){ADCCSS1bits.CSS20 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_21
template<>
struct an<constexpr_no<21>> {
typedef costexpr_no<BLCK_ANALOG_21> converter_no;
public:
uint16 data()const volatile { return ADCDATA21; }
bool data_ready()const { return ADCDSTAT1bits.ARDY21; }
void set_common_scan(bool val){ADCCSS1bits.CSS21 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_22
template<>
struct an<constexpr_no<22>> {
typedef costexpr_no<BLCK_ANALOG_22> converter_no;
public:
uint16 data()const volatile { return ADCDATA22; }
bool data_ready()const { return ADCDSTAT1bits.ARDY22; }
void set_common_scan(bool val){ADCCSS1bits.CSS22 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_23
template<>
struct an<constexpr_no<23>> {
typedef costexpr_no<BLCK_ANALOG_23> converter_no;
public:
uint16 data()const volatile { return ADCDATA23; }
bool data_ready()const { return ADCDSTAT1bits.ARDY23; }
void set_common_scan(bool val){ADCCSS1bits.CSS23 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_24
template<>
struct an<constexpr_no<24>> {
typedef costexpr_no<BLCK_ANALOG_24> converter_no;
public:
uint16 data()const volatile { return ADCDATA24; }
bool data_ready()const { return ADCDSTAT1bits.ARDY24; }
void set_common_scan(bool val){ADCCSS1bits.CSS24 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_25
template<>
struct an<constexpr_no<25>> {
typedef costexpr_no<BLCK_ANALOG_25> converter_no;
public:
uint16 data()const volatile { return ADCDATA25; }
bool data_ready()const { return ADCDSTAT1bits.ARDY25; }
void set_common_scan(bool val){ADCCSS1bits.CSS25 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_26
template<>
struct an<constexpr_no<26>> {
typedef costexpr_no<BLCK_ANALOG_26> converter_no;
public:
uint16 data()const volatile { return ADCDATA26; }
bool data_ready()const { return ADCDSTAT1bits.ARDY26; }
void set_common_scan(bool val){ADCCSS1bits.CSS26 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_27
template<>
struct an<constexpr_no<27>> {
typedef costexpr_no<BLCK_ANALOG_27> converter_no;
public:
uint16 data()const volatile { return ADCDATA27; }
bool data_ready()const { return ADCDSTAT1bits.ARDY27; }
void set_common_scan(bool val){ADCCSS1bits.CSS27 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_28
template<>
struct an<constexpr_no<28>> {
typedef costexpr_no<BLCK_ANALOG_28> converter_no;
public:
uint16 data()const volatile { return ADCDATA28; }
bool data_ready()const { return ADCDSTAT1bits.ARDY28; }
void set_common_scan(bool val){ADCCSS1bits.CSS28 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_29
template<>
struct an<constexpr_no<29>> {
typedef costexpr_no<BLCK_ANALOG_29> converter_no;
public:
uint16 data()const volatile { return ADCDATA29; }
bool data_ready()const { return ADCDSTAT1bits.ARDY29; }
void set_common_scan(bool val){ADCCSS1bits.CSS29 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_30
template<>
struct an<constexpr_no<30>> {
typedef costexpr_no<BLCK_ANALOG_30> converter_no;
public:
uint16 data()const volatile { return ADCDATA30; }
bool data_ready()const { return ADCDSTAT1bits.ARDY30; }
void set_common_scan(bool val){ADCCSS1bits.CSS30 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_31
template<>
struct an<constexpr_no<31>> {
typedef costexpr_no<BLCK_ANALOG_31> converter_no;
public:
uint16 data()const volatile { return ADCDATA31; }
bool data_ready()const { return ADCDSTAT1bits.ARDY31; }
void set_common_scan(bool val){ADCCSS1bits.CSS31 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_32
template<>
struct an<constexpr_no<32>> {
typedef costexpr_no<BLCK_ANALOG_32> converter_no;
public:
uint16 data()const volatile { return ADCDATA32; }
bool data_ready()const { return ADCDSTAT2bits.ARDY32; }
void set_common_scan(bool val){ADCCSS2bits.CSS32 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_33
template<>
struct an<constexpr_no<33>> {
typedef costexpr_no<BLCK_ANALOG_33> converter_no;
public:
uint16 data()const volatile { return ADCDATA33; }
bool data_ready()const { return ADCDSTAT2bits.ARDY33; }
void set_common_scan(bool val){ADCCSS2bits.CSS33 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_34
template<>
struct an<constexpr_no<34>> {
typedef costexpr_no<BLCK_ANALOG_34> converter_no;
public:
uint16 data()const volatile { return ADCDATA34; }
bool data_ready()const { return ADCDSTAT2bits.ARDY34; }
void set_common_scan(bool val){ADCCSS2bits.CSS34 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_35
template<>
struct an<constexpr_no<35>> {
typedef costexpr_no<BLCK_ANALOG_35> converter_no;
public:
uint16 data()const volatile { return ADCDATA35; }
bool data_ready()const { return ADCDSTAT2bits.ARDY35; }
void set_common_scan(bool val){ADCCSS2bits.CSS35 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_36
template<>
struct an<constexpr_no<36>> {
typedef costexpr_no<BLCK_ANALOG_36> converter_no;
public:
uint16 data()const volatile { return ADCDATA36; }
bool data_ready()const { return ADCDSTAT2bits.ARDY36; }
void set_common_scan(bool val){ADCCSS2bits.CSS36 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_37
template<>
struct an<constexpr_no<37>> {
typedef costexpr_no<BLCK_ANALOG_37> converter_no;
public:
uint16 data()const volatile { return ADCDATA37; }
bool data_ready()const { return ADCDSTAT2bits.ARDY37; }
void set_common_scan(bool val){ADCCSS2bits.CSS37 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_38
template<>
struct an<constexpr_no<38>> {
typedef costexpr_no<BLCK_ANALOG_38> converter_no;
public:
uint16 data()const volatile { return ADCDATA38; }
bool data_ready()const { return ADCDSTAT2bits.ARDY38; }
void set_common_scan(bool val){ADCCSS2bits.CSS38 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_39
template<>
struct an<constexpr_no<39>> {
typedef costexpr_no<BLCK_ANALOG_39> converter_no;
public:
uint16 data()const volatile { return ADCDATA39; }
bool data_ready()const { return ADCDSTAT2bits.ARDY39; }
void set_common_scan(bool val){ADCCSS2bits.CSS39 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_40
template<>
struct an<constexpr_no<40>> {
typedef costexpr_no<BLCK_ANALOG_40> converter_no;
public:
uint16 data()const volatile { return ADCDATA40; }
bool data_ready()const { return ADCDSTAT2bits.ARDY40; }
void set_common_scan(bool val){ADCCSS2bits.CSS40 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_41
template<>
struct an<constexpr_no<41>> {
typedef costexpr_no<BLCK_ANALOG_41> converter_no;
public:
uint16 data()const volatile { return ADCDATA41; }
bool data_ready()const { return ADCDSTAT2bits.ARDY41; }
void set_common_scan(bool val){ADCCSS2bits.CSS41 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_42
template<>
struct an<constexpr_no<42>> {
typedef costexpr_no<BLCK_ANALOG_42> converter_no;
public:
uint16 data()const volatile { return ADCDATA42; }
bool data_ready()const { return ADCDSTAT2bits.ARDY42; }
void set_common_scan(bool val){ADCCSS2bits.CSS42 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_43
template<>
struct an<constexpr_no<43>> {
typedef costexpr_no<BLCK_ANALOG_43> converter_no;
public:
uint16 data()const volatile { return ADCDATA43; }
bool data_ready()const { return ADCDSTAT2bits.ARDY43; }
void set_common_scan(bool val){ADCCSS2bits.CSS43 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_44
template<>
struct an<constexpr_no<44>> {
typedef costexpr_no<BLCK_ANALOG_44> converter_no;
public:
uint16 data()const volatile { return ADCDATA44; }
bool data_ready()const { return ADCDSTAT2bits.ARDY44; }
void set_common_scan(bool val){ADCCSS2bits.CSS44 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_45
template<>
struct an<constexpr_no<45>> {
typedef costexpr_no<BLCK_ANALOG_45> converter_no;
public:
uint16 data()const volatile { return ADCDATA45; }
bool data_ready()const { return ADCDSTAT2bits.ARDY45; }
void set_common_scan(bool val){ADCCSS2bits.CSS45 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_46
template<>
struct an<constexpr_no<46>> {
typedef costexpr_no<BLCK_ANALOG_46> converter_no;
public:
uint16 data()const volatile { return ADCDATA46; }
bool data_ready()const { return ADCDSTAT2bits.ARDY46; }
void set_common_scan(bool val){ADCCSS2bits.CSS46 = val; }
bool is_alternative()const { return false; }
};
#endif

#ifdef BLCK_ANALOG_47
template<>
struct an<constexpr_no<47>> {
typedef costexpr_no<BLCK_ANALOG_47> converter_no;
public:
uint16 data()const volatile { return ADCDATA47; }
bool data_ready()const { return ADCDSTAT2bits.ARDY47; }
void set_common_scan(bool val){ADCCSS2bits.CSS47 = val; }
bool is_alternative()const { return false; }
};
#endif

