




#include "systemc.h"

SC_MODULE(register_file){

	sc_in<sc_uint<5> > 		rs1;
	sc_in<sc_uint<5> > 		rs2;
	sc_in<sc_uint<5> > 		rd;
	sc_in<sc_uint<32> > 	write_back_val;
	sc_in<bool> 			wr_en;

	sc_out<sc_uint<32> >	rs1_data;
	sc_out<sc_uint<32> >	rs2_data;

	void update(){;}

	SC_CTOR(register_file){
		SC_METHOD(update);
		sensitive<<rs1;
		sensitive<<rs2;
		sensitive<<rd;
		sensitive<<write_back_val;
		sensitive<<wr_en;

	}

};
