cc=gcc
cflag= -g
lib= -lc -pthread
COMDIR=../../com
inc= -I ${COMDIR} \
	 -I inc/

src=./src/test.c \
	${COMDIR}/com.c \
	./src/circularBuff.c

obj=$(src:.o=.c)

tar=circularBuff_test
send_tar=send
recv_tar=recv

${recv_tar}:$(obj)
	$(cc) $(cflag) -DCMPILE_SWITCH=RECV $(inc) -o $@ $^ $(lib) 

${send_tar}:$(obj)
	$(cc) $(cflag) -DCMPILE_SWITCH=SEND $(inc) -o $@ $^ $(lib) 


$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^ $(lib)

%.o:%.c
	$(cc) $(cflag) $(inc) -o $@ -c $< $(lib)

clean:
	-rm  $(tar) ${recv_tar} ${send_tar}

