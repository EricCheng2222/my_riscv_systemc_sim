

#include "systemc.h"

SC_MODULE(decoder){
	sc_in<sc_uint<32> > 	inst;
	sc_out<sc_uint<5> > 	rs1;
	sc_out<sc_uint<5> > 	rs2;
	sc_out<sc_uint<5> > 	rd;
	sc_out<sc_uint<20> >	imm;
	sc_out<sc_uint<2>  >	imm_used;//
	sc_out<bool>			is_branch;

	void update(){
		rs1.write( (inst.read()>>15)%32 );	//32 for 5 bits
		rs2.write( (inst.read()>>20)%32 );
		rd.write ( (inst.read()>>7) %32 );

		//the following decides the value of imm, imm_used, is_branch 
		if(inst.read()%32==0x17){
			//LUI, AUIPC
		}
		else if(inst.read()%128==0x6f){
			//JAL
		}
		else if(inst.read()%128==0x63){
			//BRANCH
		}
		else if(inst.read()%128==0x3){
			//LOAD
		}
		else if(inst.read()%128==0x23){
			//STORE
		}
		else if(inst.read()%128==0x13){
			//ADDI --> ANDI
		}
		

	}

	SC_CTOR(decoder){
		SC_METHOD(update);
		sensitive << inst;
	}

	
};
