exec = gismo
sources = $(wildcard src/*.c)
obj = $(sources:.c=.o)

CFLAGS_DEBUG = -g -Wall -Wextra -O0
CFLAGS_RELEASE = -O2

CFLAGS = $(CFLAGS_DEBUG)

debug: CFLAGS = $(CFLAGS_DEBUG)
release: CFLAGS = $(CFLAGS_RELEASE)

$(exec): $(obj)
	gcc $(CFLAGS) $(obj) -o $(exec)

src/%.o: src/%.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(obj) $(exec)

debug: $(exec)
release: $(exec)

