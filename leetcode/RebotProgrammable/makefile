cc=gcc
cflag=-g

src=./src/main.c \
	./src/robot.c \
	../com/com.c 

inc=-I ./inc/ \
	-I ../com/ 

obj=$(src:.o=.c)

tar=robot

${tar}:${obj}
	${cc} ${cflag} ${inc} -o $@ $^

%.o:%.c
	${cc} ${cflag} ${inc} -o $@ -c $<

clean:
	rm ${tar}


