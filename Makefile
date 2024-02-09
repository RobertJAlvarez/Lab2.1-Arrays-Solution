CC   = cc
OBJS = ArrayList.o my_string.o tokenizer.o

CFLAGS = -O3 -g3 -Wall -Wextra -Werror=format-security -Werror=implicit-function-declaration \
         -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wconversion

all: compile

%.o: %.c
	${CC} $(CFLAGS) -c -o $@ $<

compile: $(OBJS)

test:
	${CC} $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

ArrayList.o: ArrayList.c ArrayList.h
my_string.o: my_string.c my_string.h
tokenizer.o: tokenizer.c my_string.h
test.o: test.c my_string.h tokenizer.h ArrayList.h

