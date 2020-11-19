





#include "systemc.h"

SC_MODULE(is_equal){

	sc_in<sc_uint<32> >		rs1;
	sc_in<sc_uint<32> >		rs2;

	sc_out<bool>			result;

	void update(){
		cout << "IS_EQ updating\n";
		result.write( rs1.read()==rs2.read() );
	}

	SC_CTOR(is_equal){
		cout << "Constructing is_equal\n";
		SC_METHOD(update);
		sensitive << rs1;
		sensitive << rs2;
	}


};
