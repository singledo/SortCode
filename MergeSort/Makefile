cc=gcc
cflag=-g
inc=-I ../com/ \
	-I inc/

src=./src/main.c \
	./src/MergeSort.c 

obj=$(src:.o=.c)

tar=merge

$(tar): $(obj)
	$(cc) $(cflag) $(inc) -o $@ $^

%.o:%.c
	$(cc) $(inc) $(cflag) -o $@ -c $<

clean:
	rm src/*.o $(tar)
