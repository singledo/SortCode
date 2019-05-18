cc=gcc
cflag=-g
inc=-I ../../com \
	-I inc/

src=./src/main.c \
	./src/list.c \
	../../com/com.c \

obj=$(src:.o=.c)

tar=list

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	-rm  $(tar)
