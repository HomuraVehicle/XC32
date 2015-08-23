use strict;
my $No=0;
open(FILE,">an.hpp");
while($No<48){
	print FILE ("template<>\n");
	print FILE ("struct an<constexpr_no<",$No,">>: public converter {\n");
	print FILE ("public:\n");
	print FILE ("\tuint16 data()const volatile { return AD1DATA",$No,"; }\n");
	print FILE ("\tbool data_ready()const { return static_cast<bool>(AD1DSTAT&",2**$No,"); }\n");
	print FILE ("};\n");
	$No=$No+1;
}
close(FILE);
