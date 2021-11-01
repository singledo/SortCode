cc=gcc
cflag= -g
lib= -lrt
inc= -I ../com \
	 -I inc/

src=./src/main.c \
    ../com/com.c \
	./src/dirOpe.c

obj=$(src:.o=.c)

tar=dirOpe

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^ $(lib)

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $< $(lib)

clean:
	-rm src/*.o $(tar)

