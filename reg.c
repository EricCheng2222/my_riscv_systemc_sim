





#include "systemc.h"

SC_MODULE(reg){

	sc_in_clk				clock;
	sc_in<sc_uint<32> > 	in;

	sc_out<sc_uint<32> >	out;
	sc_uint<32>				internal_mem;

	void update(){
		cout << "updating reg:"<<this->name()<<endl;
		cout << "reg updated to:" << in.read()<<endl;
		internal_mem = in.read();
		out.write(internal_mem);
		cout<<endl;
	}

	SC_CTOR(reg){
		cout << "constructing reg\n";
		SC_METHOD(update);
		sensitive<<clock.pos();
	}

};
