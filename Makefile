INCLUDE_DIR=$(shell echo ~)/local/include
LIBRARY_DIR=$(shell echo ~)/local/lib
DESDTIR=/
PREFIX=/usr

CXX=clang++
CXXFLAGS=-L${LIBRARY_DIR} -I${INCLUDE_DIR} -g -std=c++11 -fPIC -Wall -Wextra -O2 -march=native

all: libsafilter.so libsafilter.a filter

install: all
	mkdir -p ${DESTDIR}/${PREFIX}/include/sa/
	mkdir -p ${DESTDIR}/${PREFIX}/lib/
	mkdir -p ${DESTDIR}/${PREFIX}/bin/
	cp src/median_filter.h ${DESTDIR}/${PREFIX}/include/sa/median_filter.h
	cp filter ${DESTDIR}/${PREFIX}/bin/filter

uninstall:
	rm -r ${DESTDIR}/${PREFIX}/include/sa/
	rm -r ${DESTDIR}/${PREFIX}/lib/libsafilter.so
	rm -r ${DESTDIR}/${PREFIX}/lib/libsafilter.a
	rm ${DESTDIR}/${PREFIX}/bin/filter

filter: src/filter.cc median_filter.o
	${CXX} ${CXXFLAGS} -o filter src/filter.cc median_filter.o -lboost_program_options

median_filter.o: src/median_filter.cc src/median_filter.h
	${CXX} ${CXXFLAGS} -c src/median_filter.cc -o median_filter.o

libsafilter.so: median_filter.o
	${CXX} ${CXXFLAGS} -shared -Wl,-soname,libsafilter.so -o libsafilter.so median_filter.o

libsafilter.a: median_filter.o
	ar rcs libsafilter.a median_filter.o

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.so
	rm filter
