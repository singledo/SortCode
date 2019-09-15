cc=gcc
c_f=-g

root=../..
inc = -I${root}/DataStruct/diagrams/inc \
      -I${root}/com

src= ./src/diagram.c \
     ./src/main.c

obj=${src:.o=.c}

tar=diagram

${tar}:${obj}
	${cc} ${inc} ${c_f} -o $@ $^


%.o:%.c
	${cc} ${inc} ${c_f} -o $@ $<

clean:
	rm src/*.o ${tar}

