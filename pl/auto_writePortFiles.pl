use strict;
foreach my $Port ("A","B","C","D","E","F","G","H","I","J","K"){
	open(FILE,">port$Port.hpp");
	
	print FILE ("#ifndef XC32LIB_SFR_PORT",$Port,"_INC\n");
	print FILE ("#define XC32LIB_SFR_PORT",$Port,"_INC 100\n");
	print FILE ("#\n");
	print FILE ('#include"device_include.h"');
	print FILE ("\n");
	print FILE ('#include"../constexpr_no.hpp"');
	print FILE ("\n");
#	print FILE ("#ifdef PORT_",$Port,"\n");#for PORT_X
	print FILE ("namespace xc32{\n");
	print FILE ("\tnamespace sfr{\n");
	print FILE ("\t\tstruct port",$Port,"{\n");
	foreach my $Pin (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15){
		print FILE ("\t\t\t#ifdef PORT_",$Port,$Pin,"\n"); #for PORT_NO_Xnn
		print FILE ("\t\t\tstruct pin",$Pin,"{\n");
		print FILE ("\t\t\t\tbool port()const volatile {return PORT",$Port,"bits.R",$Port,$Pin,"; }\n");
		print FILE ("\t\t\t\t#ifndef PORT_IN_",$Port,$Pin,"\n"); #for PORT_IN_Xnn
		print FILE ("\t\t\t\tvoid lat(bool val) {LAT",$Port,"bits.LAT",$Port,$Pin,"=val; }\n");
		print FILE ("\t\t\t\t#endif //for PORT_IN\n"); #for PORT_IN_Xnn
		print FILE ("\t\t\t\tvoid tris(bool val) {TRIS",$Port,"bits.TRIS",$Port,$Pin,"=val; }\n");
		print FILE ("\t\t\t\tvoid opendrain(bool val) {ODC",$Port,"bits.ODC",$Port,$Pin,"=val; }\n");
		print FILE ("\t\t\t\t#ifdef PORT_ANALOG_",$Port,$Pin,"\n"); #for PORT_ANALOG_Xnn
		print FILE ("\t\t\t\tvoid analog(bool val) {ANSEL",$Port,"bits.ANS",$Port,$Pin,"=val; }\n");
		print FILE ("\t\t\t\ttypedef constexpr_no<PORT_ANALOG_",$Port,$Pin,"> analog_no;\n");
		print FILE ("\t\t\t\t#endif //for PORT_ANALOG_Xnn\n"); 			#for PORT_ANALOG_Xnn
		print FILE ("\t\t\t};\n");
		print FILE ("\t\t\t#endif //for PORT_NO\n"); 			#for PORT_NO_Xnn
	}
	print FILE ("\t\t};\n");
	print FILE ("\t}\n");
	print FILE ("}\n");
#	print FILE ("#endif//for PORT\n");#for PORT_X
	print FILE ("#\n");
	print FILE ("#endif\n");
	close(FILE);
}
