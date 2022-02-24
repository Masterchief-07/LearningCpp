CC = clang++

params = -Wall -Wpedantic -std=c++2a

compile = $(CC) $(params) $^ -o $@

file = iobuffer 

all: $(file)


iobuffer: iobuffer.cpp
	$(compile)

clean: $(file)
	rm -rf $^
