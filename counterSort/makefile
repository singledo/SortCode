cc=gcc
cflag=-g
inc=-I ../com \
	-I inc/

src=./src/counterSort.c \
	./src/main.c \
	../com/com.c

obj=$(src:.o=.c)

tar=counterSort

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	-rm src/*.o $(tar)
