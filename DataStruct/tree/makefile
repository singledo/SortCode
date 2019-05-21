cc=gcc
cflag=-g
inc=-I ../../com \
	-I inc/

src=./src/main.c \
	./src/tree.c \
	../../com/com.c \

obj=$(src:.o=.c)

tar=tree

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	-rm  $(tar)
