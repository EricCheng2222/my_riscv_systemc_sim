





#include "systemc.h"

SC_MODULE(adder){

	sc_in<sc_uint<32> >		oprnd1;
	sc_in<sc_uint<32> >		oprnd2;

	sc_out<sc_uint<32> >	result;

	void update(){
		cout << "Adder Updating Value\n";
		result.write( oprnd1.read() + oprnd2.read() );
	}


	SC_CTOR(adder){
		cout << "Constructing Adder\n";
		SC_METHOD(update);
		sensitive << oprnd1;
		sensitive << oprnd2;
	}


};
