exec = gismo
sources = $(wildcard src/*.c)
obj = $(sources:.c=.o)
flags = -g

$(exec): $(obj)
	gcc $(obj) $(flags) -o $(exec)

clean:
	rm ./gismo
	rm ./src/gismo

