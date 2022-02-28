cc = clang++
params = -Wall -Wpedantic -std=c++2a
code = $(cc) $(params) $^ -o $@

file = client server

all: $(file)

client: client.cpp
	$(code)

server: server.cpp
	$(code)
