SRC=test.cpp
CPPFLAGS=-Wall -Wpedantic -Werror -O3 -std=c++14 -I../include
LDFLAGS=
OFNAME=test

build:
	@g++ ${CPPFLAGS} ${SRC} -o ${OFNAME} ${LDFLAGS}

run: build
	@./${OFNAME}

clean:
	@rm -f ${OFNAME} *.o
