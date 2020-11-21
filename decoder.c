

#include "systemc.h"
#include "operation_definition.h"

SC_MODULE(decoder){
	sc_in<sc_uint<32> > 	inst;

	sc_out<sc_uint<5> > 	rs1;
	sc_out<sc_uint<5> > 	rs2;
	sc_out<sc_uint<5> > 	rd;

	sc_out<sc_uint<20> >	imm;
	sc_out<sc_uint<2>  >	imm_used;//
	sc_out<sc_uint<32> >	alu_op; //should not be 32
	sc_out<bool>			is_jump;
	sc_out<bool>			is_branch;
	sc_out<bool>			alu_mux;
	sc_out<bool>			memory_write;
	sc_out<bool>			wb_mux;
	sc_out<bool>			reg_wb;

	void update(){
		cout << "Decoder Updating\n";
		cout << this->name()<<endl;
		cout << "Inst: " << inst.read()<<endl;
		cout << "rs1: " << rs1.read()<<endl;
		cout << "rs2: " << rs2.read()<<endl;
		cout << "rd: "  << rd.read()<<endl;

		rs1.write( (inst.read()>>15)%32 );	//32 for 5 bits
		rs2.write( (inst.read()>>20)%32 );
		rd.write ( (inst.read()>>7) %32 );

		//the following decides the value of imm, imm_used, is_branch 
		if(inst.read()%32==0x17){
			//LUI, AUIPC
			cout << "LUI/AUIPC decoded" <<endl;
			is_jump.write(false);
			imm.write(inst.read()>>12);
			imm_used.write(0); 			//0 for 20 bits
			alu_op.write(ADD);
			is_branch.write(false);
			alu_mux.write(false);
			memory_write.write(false);
			wb_mux.write(true);
			reg_wb.write(true);
		}
		else if(inst.read()%128==0x6f){
			//JAL
			is_jump.write(true);
			imm.write(inst.read()>>12);
			imm_used.write(0);
			alu_op.write(ADD);
			is_branch.write(true);
			alu_mux.write(false); //don't care
			memory_write.write(false); 
			wb_mux.write(false);
			reg_wb.write(false);
		}
		else if(inst.read()%128==0x63){
			//BRANCH
			is_jump.write(false);
			imm.write(inst.read()>>12);
			imm_used.write(1);			//1 for 12bits
			alu_op.write(DONT_CARE);
			is_branch.write(true);
			alu_mux.write(true);		//don;t care
			memory_write.write(false);	//don't care
			wb_mux.write(false);		//don't care
			reg_wb.write(false);
		}
		else if(inst.read()%128==0x3){
			//LOAD
			is_jump.write(false);
			reg_wb.write(true);
			imm.write(inst.read()>>20);
			imm_used.write(1);		//1 for 12bit imm
			alu_op.write(DONT_CARE);
			is_branch.write(false);
			alu_mux.write(false);
			memory_write.write(false);
			wb_mux.write(false);
		}
		else if(inst.read()%128==0x23){
			//STORE
			is_jump.write(false);
			reg_wb.write(true);
			imm.write((inst.read()>>7)%32 + (inst.read()>>25));
			imm_used.write(2);		//2 for 11 bits
			alu_op.write(ADD);
			is_branch.write(false);
			alu_mux.write(false);		//might be incorrect
			memory_write.write(true);
			wb_mux.write(false);
		}
		else if(inst.read()%128==0x13){
			//ADDI --> SRAI
			cout << "ADDI --> SRAI decoded\n";
			is_jump.write(false);
			reg_wb.write(true);
			imm.write(inst.read()>>12);
			imm_used.write(inst.read()>>20); 
			is_branch.write(false);
			alu_mux.write(false);
			memory_write.write(false);
			wb_mux.write(false);
		}
		else if(inst.read()%128==0x33){
			//ADD --> AND
			is_jump.write(false);
			reg_wb.write(true);
			imm.write(0);
			imm_used.write(3);		//not used
			is_branch.write(false);
			alu_mux.write(true);
			memory_write.write(false);
			wb_mux.write(true);
		}		
		if(inst.read()%128==0x33 || inst.read()%128==0x13){
			int hi_op = (inst.read()>>12)%8;
			if(hi_op==0){
				if(inst.read()>>25 == 0)
					alu_op.write(ADD);
				else 
					alu_op.write(SUB);
			}
			else if(hi_op==1)
				alu_op.write(SLL);
			else if(hi_op==2)
				alu_op.write(SLT);
			else if(hi_op==3)
				alu_op.write(SLTU);
			else if(hi_op==4)
				alu_op.write(XOR);
			else if(hi_op==5){
				if(inst.read()>>25==0)
					alu_op.write(SRL);
				else 
					alu_op.write(SRA);
			}
			else if(hi_op==6)
				alu_op.write(OR);
			else if(hi_op==7)
				alu_op.write(AND);
				
		}
		cout << endl;
	}

	SC_CTOR(decoder){
		cout << "Constructing Decoder\n";
		SC_METHOD(update);
		sensitive << inst;
	}

	
};
