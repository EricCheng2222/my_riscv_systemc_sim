




#include "systemc.h"

SC_MODULE(register_file){

	sc_in<sc_uint<5> > 		rs1;
	sc_in<sc_uint<5> > 		rs2;
	sc_in<sc_uint<5> > 		rd;
	sc_in<sc_uint<32> > 	write_back_val;
	sc_in<bool> 			wr_en;

	sc_out<sc_uint<32> >	rs1_data;
	sc_out<sc_uint<32> >	rs2_data;

	sc_uint<32>				internal_reg[32];

	void update(){
		cout << "updating register files\n";
		if(wr_en.read()==0){
			rs1_data.write( internal_reg[rs1.read()] );
			rs2_data.write( internal_reg[rs2.read()] );
		}
		else{
			internal_reg[rd.read()] =  write_back_val.read();
		}
		cout << endl;
	}

	SC_CTOR(register_file){
		cout << "Constructing register file\n";
		SC_METHOD(update);
		sensitive<<rs1;
		sensitive<<rs2;
		sensitive<<rd;
		sensitive<<write_back_val;
		sensitive<<wr_en;

	}

};
