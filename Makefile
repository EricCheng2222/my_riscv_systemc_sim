

OBJS = hello_world.o sim_main.o core.o decoder.o memory.o register_files.o mux.o
SRC  = $(wildcard *.c) 

all: sim

sim: $(OBJS)
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux $(OBJS) -o sim -lsystemc -lm

$(OBJS): $(SRC)
	echo $(SRC)
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux -c $(SRC) -lsystemc -lm

clean:
	rm -rf ./sim $(OBJS)
