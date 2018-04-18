SRC=tests.cpp
CPPFLAGS=-Wall -Wpedantic -Werror -g -O3 -std=c++14
LDFLAGS=
OFNAME=main

build:
	@g++ ${CPPFLAGS} ${SRC} -o ${OFNAME} ${LDFLAGS}

run: build
	@./${OFNAME}

clean:
	@rm -f ${OFNAME} *.o
