cc=gcc
cflag= -g
inc= -I ../com \
	 -I inc/

src=./src/main.c \
	./src/fastsort.c

obj=$(src:.o=.c)

tar=fastsort

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	-rm src/*.o $(tar)

