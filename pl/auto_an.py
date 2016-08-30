No=0
f = open("an.hpp","w")
while No<48:
	f.write("#ifdef BLCK_ANALOG_"+str(No)+"\n")
	f.write("template<>\n")
	f.write("struct an<constexpr_no<"+str(No)+">> {\n")
	f.write("typedef costexpr_no<BLCK_ANALOG_"+str(No)+"> converter_no;\n")
	f.write("public:\n")
	f.write("uint16 data()const volatile { return ADCDATA"+str(No)+"; }\n")
	f.write("bool data_ready()const { return ADCDSTAT1bits.ARDY"+str(No)+"; }\n")
	f.write("};\n")
	f.write("#endif\n\n")
	No += 1

f.close()
