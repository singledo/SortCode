cc = gcc
cflag = -g 

inc = -I ./StrCom/inc \
	  -I ./kmp/inc \
	  -I ./rabin-karp/inc \
	  -I ./simple/inc

src = ./StrCom/src/StrCom.c \
	  ./kmp/src/kmp.c \
	  ./rabin-karp/src/rabin-karp.c \
	  ./simple/src/simple.c \
	  main.c

TARDIR=./obj

obj=$(src:.o=.c)

tar=MatchString

${tar}: ${obj}
	${cc} ${cflag} ${inc} -o $@ $^

%.o: %.c
	${cc} ${cflag} ${inc} -o ${TARDIR}/$@ -C $<

clean:
	rm obj/*.o ${tar}

