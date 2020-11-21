

#include "systemc.h"
#include "operation_definition.h"
SC_MODULE(alu){
	sc_in<sc_uint<32> > 	rs1;
	sc_in<sc_uint<32> > 	rs2;
	sc_in<sc_uint<32> >		op;//this should not be 32 bits

	sc_out<sc_uint<32> >	result;

	void update(){
		//According to inst, change 
		cout << "ALU updating\n";
		if(op.read()==ADD){
			//ADD, ADDI
			cout << "ALU: ADD"<<endl;
			result = rs1.read() + rs2.read();
		}
		else if(op.read()==DONT_CARE){
			result = rs1.read();
		}
		else if(op.read()==SUB){
			//SUB
			result = rs1.read() - rs2.read();
		}
		else if(op.read()==SLTI){
			//SLTI
			result = (rs1.read()<rs2.read())?1 : 0;
		}
		else if(op.read()==SLTIU){
			//SLTIU
			result = (rs1.read()<rs2.read())?1 : 0;
		}
		else if(op.read()==XOR){
			//XOR
			result = (rs1.read() ^ rs2.read());
		}
		else if(op.read()==OR){
			//OR
			result = (rs1.read() | rs2.read());
		}
		else if(op.read()==AND){
			//AND, ANDI
			result = (rs1.read() & rs2.read());
		}
		else if(op.read()==SLL){
			//SLL, SLLI(Logical Left Shift)
			result = (rs1.read() << rs2.read());
		}
		else if(op.read()==SRL){
			//SRL, SRLI(Logical Right Shift)
			result = (rs1.read() >> rs2.read());
		}
		else if(op.read()==SRA){
			//SRA, SRAI(Arithmetic Right Shift)
			result = (rs1.read() >> rs2.read());//should sign ext 
		}
		cout << endl;
	}

	SC_CTOR(alu){
		cout << "Constructing ALU\n";
		SC_METHOD(update);
		sensitive <<rs1;
		sensitive <<rs2;
		sensitive <<op;
	}

	
};
