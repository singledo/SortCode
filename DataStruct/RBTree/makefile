cc=gcc
cflag=-g -O2 -w
inc=-I ../../com \
	-I inc/

src=./src/main.c \
	./src/RBTree.c \
	../../com/com.c \

obj=$(src:.o=.c)

tar=RBTree

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	rm ${tar}
