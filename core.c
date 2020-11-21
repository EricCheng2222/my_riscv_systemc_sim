




#include "systemc.h"
#include "adder.c"
#include "alu.c"
#include "decoder.c"
#include "is_branch_mux.c"
#include "is_equal.c"
#include "is_larger.c"
#include "memory.c"
#include "mux.c"
#include "reg.c"
#include "register_files.c"
#include "sign_ext.c"

SC_MODULE(CORE){

	sc_in<bool>	clock;
	sc_in<bool>	reset;
	
	
	sc_signal<sc_uint<32> > PC_IN;
	sc_signal<sc_uint<32> > PC_OUT;
	sc_signal<sc_uint<32> > IM_OUT;
	sc_signal<sc_uint<5>  > RS1_ADDR;
	sc_signal<sc_uint<5>  > RS2_ADDR;
	sc_signal<sc_uint<5>  > RD_ADDR;
	sc_signal<sc_uint<32> > WB_VAL;
	sc_signal<bool>			RF_WR_EN;
	sc_signal<bool>			ALU_SEL;
	sc_signal<bool>			IS_BRANCH;
	sc_signal<bool>			MEM_WR;
	sc_signal<bool>			WB_MX_SEL;
	sc_signal<sc_uint<32> > ALU_OP;
	sc_signal<sc_uint<32> > RS1_DATA;
	sc_signal<sc_uint<32> > RS2_DATA;
	sc_signal<sc_uint<20> > IMM;
	sc_signal<sc_uint<2>  > IMM_KIND;
	sc_signal<sc_uint<32> > EXT_IMM;
	sc_signal<sc_uint<32> > ALU_RESULT;
	sc_signal<sc_uint<32> > ALU_IN2;
	sc_signal<sc_uint<32> > FILE_MEM_OUT;
	sc_signal<bool>			IS_EQUAL;	
	sc_signal<bool>			IS_LARGER;	
	sc_signal<bool>			B_MX_OUT;	
	sc_signal<bool>			IS_JUMP;
	sc_signal<bool>			REG_WB;
	sc_signal<bool>			ALU_MUX;
	sc_signal<sc_uint<32> >	PC_PLUS_4;	
	sc_signal<sc_uint<32> >	PC_IF_BRANCH;	

	sc_signal<sc_uint<32> > ZERO;
	sc_signal<sc_uint<32> > FOUR;
	sc_signal<bool>			FALSE;

	SC_CTOR(CORE)
		:PC("PC_REG"),
		 IM("INSTRUCTION_MEMORY"),
		 DC("DECODER"),
		 RF("REGISTER_FILES"),
		 SE("SIGN_EXTENDER"),
		 ALU_MX("ALU_MUX"),
		 ALU("ALU"),
		 FM("FILE_MEMORY"),
		 IE("IS_EQUAL"),
		 IL("IS_LARGER"),
		 PC_BRANCH_ADDER("PC_BRANCH_ADDER"),
		 PC_4("PC_ADD_4"),
		 WB_MX("WRITE_BACK_MUX"),
		 PC_MX("NEXT_PC_MUX"),
		 B_MX("IS_BRANCH_SEL")
		
	{
		cout<<"CONSTRUCTING CORE\n";
		IM.load_mem("/Users/eric/Desktop/my_RISCV_sim/my_testing_c_program/test.bin");
		ZERO.write(0);
		FOUR.write(4);
		FALSE.write(false);
	
		PC(clock, PC_IN, PC_OUT);
		IM(ZERO, PC_OUT, FALSE, IM_OUT);
		DC(IM_OUT, RS1_ADDR, RS2_ADDR, RD_ADDR, IMM, IMM_KIND, ALU_OP, IS_JUMP, IS_BRANCH, ALU_MUX, MEM_WR, WB_MX_SEL, REG_WB);
		RF(RS1_ADDR, RS2_ADDR, RD_ADDR, WB_VAL, RF_WR_EN, RS1_DATA, RS2_DATA);
		SE(IMM, EXT_IMM);
		ALU_MX(RS2_DATA, EXT_IMM, ALU_SEL, ALU_IN2);
		ALU(RS1_DATA, ALU_IN2, ALU_OP, ALU_RESULT);
		FM(ALU_RESULT, ALU_IN2, MEM_WR, FILE_MEM_OUT);
		IE(RS1_DATA, RS2_DATA, IS_EQUAL);
		IL(RS1_DATA, RS2_DATA, IS_LARGER);
		PC_BRANCH_ADDER(PC_OUT, EXT_IMM, PC_IF_BRANCH);
		PC_4(FOUR, PC_OUT, PC_PLUS_4);
		WB_MX(ALU_RESULT, FILE_MEM_OUT, WB_MX_SEL, WB_VAL);
		B_MX(IS_BRANCH, IS_EQUAL, IS_LARGER, B_MX_OUT);
		PC_MX(PC_PLUS_4, PC_IF_BRANCH, B_MX_OUT, PC_IN);

	}
	private:
		reg               PC;
		memory            IM;
		decoder			  DC;
		register_file     RF;
		sign_ext      	  SE;
		mux               ALU_MX;
		alu               ALU;
		memory            FM;
		is_equal      	  IE;
		is_larger         IL;
		adder             PC_BRANCH_ADDER;
		adder         	  PC_4;
		mux               WB_MX;
		mux           	  PC_MX;
		is_branch_mux	  B_MX;
};
