cc=gcc
cflag= -g
lib= -lrt
inc= -I ../../../../com \
	 -I inc/

src=./src/main.c \
	./src/msgClient.c

obj=$(src:.o=.c)

tar=MsgQueue_client

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^ $(lib)

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $< $(lib)

clean:
	-rm src/*.o 
	-rm $(tar)

