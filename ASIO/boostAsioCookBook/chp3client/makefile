cc= clang++
params = -std=c++2a -Wall -Wpedantic -pthreads
code = $(cc) $(params) $^ -o $@

file = syncudpclient asynctcpclient synctcpclient

all: $(file)

synctcpclient : synctcpclient.cpp
	$(code)
syncudpclient : syncudpclient.cpp
	$(code)
asynctcpclient : asynctcpclient.cpp
	$(code)


