

#include "systemc.h"
#include "hello_world.c"
#include "core.c"
int sc_main(int argc, char* argv[]) {
	sc_clock clock;
	sc_signal<bool> reset;

    hello_world hello("HELLO");
    hello.say_hello();

	CORE core("my_core");
	core(clock, reset);
	sc_start();
    return(0);
 }

