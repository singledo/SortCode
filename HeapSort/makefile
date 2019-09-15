cc=gcc
cflag=-g
inc=-I ../com \
	-I inc/

src=./src/heapsort.c \
	./src/main.c

obj=$(src:.o=.c)

tar=heapsrot

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	-rm src/*.o $(tar)
