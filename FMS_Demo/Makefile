cc=gcc
cflag= -g
lib= -lc
inc= -I ../com \
	 -I inc/

src=./src/main.c \
    ../com/com.c \
	./src/_fsm.c \
	./src/node_func.c

obj=$(src:.o=.c)

tar=fsm_demo

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^ $(lib)

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $< $(lib)

clean:
	-rm src/*.o $(tar)

