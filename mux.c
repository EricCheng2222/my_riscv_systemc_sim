



#include "systemc.h"


SC_MODULE(mux){

	sc_in<sc_uint<32> > 	data1;
	sc_in<sc_uint<32> > 	data2;
	sc_in<bool > 			sel;
	
	sc_out<sc_uint<32> >	out;

	void update(){;}

	SC_CTOR(mux){
		SC_METHOD(update);
		sensitive<<data1;
		sensitive<<data2;
		sensitive<<sel;
	}

};
