





#include "systemc.h"

SC_MODULE(is_larger){

	sc_in<sc_uint<32> >		oprnd1;
	sc_in<sc_uint<32> >		oprnd2;

	sc_out<bool>			result;

	void update(){
		result.write( oprnd1.read() > oprnd2.read() );
	}

	SC_CTOR(is_larger){
		SC_METHOD(update);
		sensitive << oprnd1;
		sensitive << oprnd2;
	}


};
