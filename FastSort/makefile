cc=gcc
cflag= -g
lib= -lrt
inc= -I ../com \
	 -I inc/

src=./src/main.c \
	./src/fastsort.c

obj=$(src:.o=.c)

tar=fastsort

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^ $(lib)

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $< $(lib)

clean:
	-rm src/*.o $(tar)

