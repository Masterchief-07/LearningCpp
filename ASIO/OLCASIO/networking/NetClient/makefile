cc = clang++
params = -Wall -Wpedantic -pthreads -std=c++2a
code = $(cc) $(params) -I../NetCommon $^ -o $@
file = SimpleClient SimpleServer

all: $(file)

SimpleClient: SimpleClient.cpp
	$(code)
SimpleServer: SimpleServer.cpp
	$(code)
