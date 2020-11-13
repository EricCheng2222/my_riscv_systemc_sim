

#include "systemc.h"
#include "hello_world.c"
#include "core.c"
int sc_main(int argc, char* argv[]) {
    hello_world hello("HELLO");
    hello.say_hello();

	CORE core("my_core");
	sc_start();
    return(0);
 }

