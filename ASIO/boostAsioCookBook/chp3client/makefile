cc= clang++
params = -std=c++2a -Wall -Wpedantic -pthreads
code = $(cc) $(params) $^ -o $@

file = syncudpclient synctcpclient

all: $(file)

synctcpclient : synctcpclient.cpp
	$(code)
syncudpclient : syncudpclient.cpp
	$(code)


