CC   = cc
OBJS = ArrayList.o my_string.o tokenizer.o

CFLAGS = -O3 -g3 -Wall -Wextra -Werror=format-security -Werror=implicit-function-declaration \
         -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wconversion

all: $(OBJS)

test_tokenize: my_string.o tokenizer.o test_tokenize.o
	${CC} -o $@ $^

clean:
	rm -f *.o test_tokenize

ArrayList.o: ArrayList.c ArrayList.h
my_string.o: my_string.c my_string.h
tokenizer.o: tokenizer.c tokenizer.h my_string.h
test_tokenize.o: test_tokenize.c tokenizer.h my_string.h

