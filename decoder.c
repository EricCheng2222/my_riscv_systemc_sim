

#include "systemc.h"

SC_MODULE(decoder){
	sc_in<sc_uint<32> > 	inst;
	sc_out<sc_uint<5> > 	rs1;
	sc_out<sc_uint<5> > 	rs2;
	sc_out<sc_uint<5> > 	rd;
	sc_out<sc_uint<20> >	imm;
	sc_out<sc_uint<2>  >	imm_used;//
	sc_out<bool>			is_branch;

	void update(){
		;
	}

	SC_CTOR(decoder){
		SC_METHOD(update);
		sensitive << inst;
	}

	
};
