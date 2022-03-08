cc = clang++
params = -Wall -Wpedantic -std=c++2a
code = $(cc) $(params) $^ -o $@
file = requestSync requestAsync

all : $(file)

requestSync : requestSync.cpp
	$(code)
requestAsync : requestAsync.cpp
	$(code)

clean:
	rm -rf $(file)
