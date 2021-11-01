cc=gcc
cflag= -g
lib= -lrt
inc= -I ../../../../com \
	 -I inc/

src=./src/main.c \
	./src/ipc.c

obj=$(src:.o=.c)

tar=name-pipe-server

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^ $(lib)

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $< $(lib)

clean:
	-rm src/*.o 
	-rm $(tar)

