





#include "systemc.h"

SC_MODULE(sign_ext){

	sc_in<sc_uint<20>  > 	in;
	sc_out<sc_uint<32> >	out;

	void update(){
		cout << "updating sign ext\n";
		out.write(in.read());
	}

	SC_CTOR(sign_ext){
		cout << "Constructing sign ext\n";
		SC_METHOD(update);
		sensitive<<in;
	}

};
