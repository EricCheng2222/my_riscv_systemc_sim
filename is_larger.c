





#include "systemc.h"

SC_MODULE(is_larger){

	sc_in<sc_uint<32> >		rs1;
	sc_in<sc_uint<32> >		rs2;

	sc_out<bool>			result;

	void update(){
		cout << "updating is_larger\n";
		result.write( rs1.read()>rs2.read() );
	}

	SC_CTOR(is_larger){
		cout << "Constructing is_larger\n";
		SC_METHOD(update);
		sensitive << rs1;
		sensitive << rs2;
	}


};
