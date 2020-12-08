;CPU interrupt vectors

 .title		"vectors.asm"
 .ref		_c_int0; 
 .ref		_nothing;
 .ref		_int1_server;
 .ref		_int2_server;
 .ref		_int5_server;
 .sect		".vectors"

reset	  	B	  _c_int0;
int1		B	  _int1_server;
int2        B 	  _int2_server;
int3		B	  _nothing;
int4		B	  _nothing;
int5	    B  	  _int5_server;
int6		B	  _nothing;
