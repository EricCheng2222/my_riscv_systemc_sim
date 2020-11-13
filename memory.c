



#include "systemc.h"

SC_MODULE(memory){
	sc_in<sc_uint<32> > 	data_result;
	sc_in<sc_uint<32> > 	addr;
	sc_in<bool>				wr_en;
	
	sc_out<sc_uint<32> >	out;

	void update(){;}

	SC_CTOR(memory){
		SC_METHOD(update);
		sensitive<<data_result;
		sensitive<<addr;
		sensitive<<wr_en;
	}
};
