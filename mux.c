



#include "systemc.h"


SC_MODULE(mux){

	sc_in<sc_uint<32> > 	data1;
	sc_in<sc_uint<32> > 	data2;
	sc_in<bool> 			sel;
	
	sc_out<sc_uint<32> >	out;

	void update(){
		cout << "updating mux: "<<this->name()<<endl;
		if(sel.read()==1){
			out.write( data1.read() );
		}
		else{
			out.write( data2.read() );
		}
		cout<<endl;
	}

	SC_CTOR(mux){
		cout << "CONSTRUCTING mux\n";
		SC_METHOD(update);
		sensitive<<data1;
		sensitive<<data2;
		sensitive<<sel;
	}

};
