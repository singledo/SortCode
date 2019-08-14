cc=gcc
cflag=-g 
src=./src/DyncPro.c \
    ./src/main.c \
    ../com/com.c

inc=-I ./inc \
    -I ../com

obj=$(src:.o=.c)

tar=DyncProg

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o: %.c
	$(cc) $(cflag) $(inc) -o $@ -c $<

clean:
	rm $(tar)
