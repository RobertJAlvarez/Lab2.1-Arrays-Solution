CC   = cc
OBJS = my_string.o

CFLAGS = -I./h -O3 -g3 -Wall -Wextra -Werror=format-security -Werror=implicit-function-declaration \
         -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wconversion

all: $(OBJS)

test: $(OBJS) ArrayList.o test.o
	${CC} -o $@ $^

test_tokenize: $(OBJS) tokenizer.o test_tokenize.o
	${CC} -o $@ $^

clean:
	rm -f *.o test test_tokenize

ArrayList.o: ArrayList.c ArrayList.h
my_string.o: my_string.c my_string.h
tokenizer.o: tokenizer.c tokenizer.h my_string.h
test.o: test.c my_string.h ArrayList.h
test_tokenize.o: test_tokenize.c my_string.h tokenizer.h

