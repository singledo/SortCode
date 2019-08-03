cc=gcc
cflag=-g -w
inc=-I ../../com \
	-I inc/

src=./src/main.c \
	./src/rbtree.c \
	../../com/com.c \
	./src/rbtree_show.c \

obj=$(src:.o=.c)

tar=rbtree

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	rm ${tar}
