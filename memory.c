



#include "systemc.h"

SC_MODULE(memory){
	sc_in<sc_uint<32> > 	data_result;
	sc_in<sc_uint<32> > 	addr;
	sc_in<bool>				wr_en;
	
	sc_out<sc_uint<32> >	out;

	sc_uint<32> 			internal_mem[4096];

	void update(){
		cout << "updating memory\n";
		if(wr_en.read()==1){
			internal_mem[addr.read()<<2] = data_result.read() ;
		}
		else{
			out.write( internal_mem[addr.read()<<2] );
		}
	}

	SC_CTOR(memory){
		cout << "CONSTRUCTING memory\n";
		SC_METHOD(update);
		sensitive<<data_result;
		sensitive<<addr;
		sensitive<<wr_en;
	}
};
