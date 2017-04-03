No=0
f = open("an.hpp","w")
while No<32:
	f.write("#ifdef BLCK_ANALOG_"+str(No)+"\n")
	f.write("template<>\n")
	f.write("struct an<constexpr_no<"+str(No)+">> {\n")
	f.write("typedef constexpr_no<BLCK_ANALOG_"+str(No)+"> converter_no;\n")
	f.write("public:\n")
	f.write("uint16 data()const volatile { return ADCDATA"+str(No)+"; }\n")
	f.write("bool data_ready()const { return ADCDSTAT1bits.ARDY"+str(No)+"; }\n")
	f.write("void request_global_convert(bool val){ADCCSS1bits.CSS"+str(No)+" = val; }\n")
	f.write("bool is_alternative()const { return false; }\n")
	f.write("};\n")
	f.write("#endif\n\n")
	No += 1

while No<48:
	f.write("#ifdef BLCK_ANALOG_"+str(No)+"\n")
	f.write("template<>\n")
	f.write("struct an<constexpr_no<"+str(No)+">> {\n")
	f.write("typedef constexpr_no<BLCK_ANALOG_"+str(No)+"> converter_no;\n")
	f.write("public:\n")
	f.write("uint16 data()const volatile { return ADCDATA"+str(No)+"; }\n")
	f.write("bool data_ready()const { return ADCDSTAT2bits.ARDY"+str(No)+"; }\n")
	f.write("void request_global_convert(bool val){ADCCSS2bits.CSS"+str(No)+" = val; }\n")
	f.write("bool is_alternative()const { return false; }\n")
	f.write("};\n")
	f.write("#endif\n\n")
	No += 1

f.close()
