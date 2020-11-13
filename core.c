




#include "systemc.h"
#include "decoder.c"
#include "memory.c"
#include "mux.c"

SC_MODULE(CORE){

	sc_in_clk	clock;
	sc_in<bool>	reset;
	
	SC_CTOR(CORE){
		cout<<"CONSTRUCTING CORE\n";

	}

};
