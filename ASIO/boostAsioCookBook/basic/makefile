CC = clang++

params = -Wall -Wpedantic -std=c++2a

compile = $(CC) $(params) $^ -o $@

file = clientendpoint serverendpoint simpleClient acceptorsocket resolver socketendpoint connectsocket acceptconnection

all: $(file)


clientendpoint: clientendpoint.cpp
	$(compile)

serverendpoint: serverendpoint.cpp
	$(compile)
simpleClient: simpleClient.cpp
	$(compile)
acceptorsocket: acceptorsocket.cpp
	$(compile)
resolver: resolver.cpp
	$(compile)
socketendpoint: socketendpoint.cpp
	$(compile)
connectsocket: connectsocket.cpp
	$(compile)
acceptconnection:acceptconnection.cpp
	$(compile)

