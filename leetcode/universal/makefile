cc = gcc
cflag=-g

tar=universal

src = ./src/main.c \
	  ./src/universal.c \
	  ../com/com.c

inc = -I ./inc \
	  -I ../com

obj=$(src:.o=.c)

${tar}: ${obj}
	${cc} ${inc} ${cflag} -o $@ $^

*.o: %.c
	${cc} ${inc} ${cflag} -o $@ -c $<


clean:
	rm ${tar}
