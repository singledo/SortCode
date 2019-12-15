cc = gcc 
cflag = -g
inc = -I ./inc \
	  -I ../com \
	  -I ../tree 

src = ./src/main.c \
	  ./src/rangeSum.c \
	  ../com/com.c \
	  ../tree/tree.c

obj=$(src:.o=.c)

tar=rangeSum

${tar}:${obj}
	${cc} ${cflag} ${inc} -o $@ $^

%.o: %.c
	${cc} ${cflag} ${inc} -o $@ -c $<

clean:
	rm ${tar}
