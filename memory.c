



#include "systemc.h"

SC_MODULE(memory){
	sc_in<sc_uint<32> > 	data_result;
	sc_in<sc_uint<32> > 	addr;
	sc_in<bool>				wr_en;
	
	sc_out<sc_uint<32> >	out;

	sc_uint<32> 			internal_mem[4096];

	void update(){
		if(wr_en.read()==1){
			internal_mem[addr<<2].write( data_result.read() );
		}
		else{
			out.write( internal_mem[addr<<2].read() );
		}
	}

	SC_CTOR(memory){
		SC_METHOD(update);
		sensitive<<data_result;
		sensitive<<addr;
		sensitive<<wr_en;
	}
};
