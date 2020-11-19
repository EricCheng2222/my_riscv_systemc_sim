



#include "systemc.h"


SC_MODULE(is_branch_mux){

	sc_in<bool> 			is_branch;
	sc_in<bool> 			is_equal;
	sc_in<bool> 			is_larger;
	
	sc_out<bool>			out;

	void update(){
		cout << "Updating is_branch_mux\n";
		out.write(is_branch&&(is_equal||is_larger));	
	}

	SC_CTOR(is_branch_mux){
		cout << "Constructing is_branch_mux\n";
		SC_METHOD(update);
		sensitive<<is_branch;
		sensitive<<is_equal;
		sensitive<<is_larger;
	}

};
