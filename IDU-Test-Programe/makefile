cc=gcc
cflag= -g
lib= -lrt -pthread


inc= -I ../com \
	 -I serial/inc \
	 -I arinc/inc  \
	 -I log/inc

src=./main.c \
	./serial/src/error-log.c \
	./serial/src/serialport.c \
	./arinc/src/arinc.c \
	./log/src/log.c \
	../com/com.c \

obj=$(src:.o=.c)

tar=DEMO_arinc

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^ $(lib)

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $< $(lib)

clean:
	-rm $(tar)

