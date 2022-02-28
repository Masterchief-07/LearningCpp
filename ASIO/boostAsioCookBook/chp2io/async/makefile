cc = clang++
params = -Wall -Wpedantic -std=c++2a
code = $(cc) $(params) $^ -o $@

file = client server client2

all: $(file)

client: client.cpp
	$(code)

server: server.cpp
	$(code)
client2: client2.cpp
	$(code)
