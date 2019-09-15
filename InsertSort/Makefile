CC=gcc

cflag= -g

src=./src/InsertApi.c \
	./src/main.c

inc=-I ../com \
	-I inc/ 

obj=$(src:.o=.c)

target=insert

$(target):$(obj)
	$(CC) $(cflag) $(inc) -o $@ $^

%.o:%c
	$(CC) $(cflag) $(inc) -o $@ -c $<

clean:
	-rm src/*.o insert

