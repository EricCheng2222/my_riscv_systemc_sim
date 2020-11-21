





#include "systemc.h"

SC_MODULE(adder){

	sc_in<sc_uint<32> >		oprnd1;
	sc_in<sc_uint<32> >		oprnd2;

	sc_out<sc_uint<32> >	result;

	void update(){
		cout << "Adder: "<< this->name()<<endl;
		cout << "oprnd1: "<<oprnd1 << " oprnd2:"<<oprnd2<<endl;
		cout << "Adder Updating Value\n";
		result.write( oprnd1.read() + oprnd2.read() );
		cout << endl;
	}


	SC_CTOR(adder){
		cout << "Constructing Adder\n";
		SC_METHOD(update);
		sensitive << oprnd1;
		sensitive << oprnd2;
	}


};
