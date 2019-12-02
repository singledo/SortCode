cc=gcc
cflag=-g

inc = -I ../com \
	 -I ./inc

src = ./src/main.c \
	  ./src/TreeMirror.c \
	  ../com/com.c \
	  ./src/Tree.c

tar = TreeMirror

obj=$(src:.o=.c)

${tar}: ${obj}
	${cc} ${cflag} ${inc} -o $@ $^

%.o: %.c
	${cc} ${cflag} ${inc} -o $@ -c $<

clean:
	rm  ${tar}

