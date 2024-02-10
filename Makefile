CC   = cc
OBJS = ArrayList.o my_string.o tokenizer.o
S_OBJS = ./o/ArrayList.o ./o/my_string.o ./o/tokenizer.o

CFLAGS = -I./h -O3 -g3 -Wall -Wextra -Werror=format-security -Werror=implicit-function-declaration \
         -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wconversion

all: compile

%.o: %.c
	${CC} $(CFLAGS) -c -o $@ $<

compile: $(OBJS)

test: $(OBJS) ./o/tokenizer.o test.o
	${CC} -o $@ $^

clean:
	(cd student && make clean)
	rm -rf ./h
	rm -rf ./o
	rm -f *.o test

ArrayList.o: ArrayList.c ArrayList.h
my_string.o: my_string.c my_string.h
tokenizer.o: tokenizer.c tokenizer.h my_string.h
	${CC} $(CFLAGS) -c -Dtokenize=my_tokenize -o $@ $<
test.o: test.c my_string.h tokenizer.h ArrayList.h ./h/my_string.h ./h/tokenizer.h ./h/ArrayList.h

$(S_OBJS):
	mkdir ./h
	mkdir ./o
	(cd student && make)
	(cd student && cp *.h ../h)
	(cd student && mv *.o ../o)

