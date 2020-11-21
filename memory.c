



#include "systemc.h"
#include <stdio.h>

SC_MODULE(memory){
	sc_in<sc_uint<32> > 	data_result;
	sc_in<sc_uint<32> > 	addr;
	sc_in<bool>				wr_en;
	
	sc_out<sc_uint<32> >	out;

	unsigned int 			internal_mem[4096];

	void update(){
		cout << "updating memory: "<<this->name()<<endl;
		cout << "addr: " << addr.read()<<endl;
		cout << "wr_en: "<<wr_en.read()<<endl;
		cout << "internal_mem: "<<std::hex<<internal_mem[addr.read()>>2]<<endl;
		if(wr_en.read()==1){
			internal_mem[addr.read()>>2] = data_result.read() ;
		}
		else{
			cout << "writing out: " << std::hex<<internal_mem[addr.read()>>2]<<endl; 
			out.write( internal_mem[addr.read()>>2] );
		}
		cout << endl;
	}

	void load_mem(char* loc){
		FILE *fp;
		fp = fopen(loc, "r");
		int ite = 0;
		while(fscanf(fp, "%x", &internal_mem[ite])!=EOF){
			printf("%d: %x\n", ite, internal_mem[ite]);
			ite++;
		}
		fclose(fp);
	}

	SC_CTOR(memory){
		cout << "CONSTRUCTING memory\n";
		SC_METHOD(update);
		sensitive<<data_result;
		sensitive<<addr;
		sensitive<<wr_en;
	}
};
