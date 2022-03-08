cc = clang++
params= -Wall -Wpedantic -std=c++17 -pthread
code = $(cc)  $(params) $^ -o $@
file = server client

all: $(file)

server: server.cpp
	$(code)

client: client.cpp
	$(code)

