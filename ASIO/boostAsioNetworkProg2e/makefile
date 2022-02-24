CC = clang++
params = -Wall -std=c++2a -Wpedantic
exec = add rangen_boost nonconcurrent concurrent blocked poll removework multithreads ioservicebind mutexbind post dispatch nonstrand strand strandwrap exception exception2 errorcode errorcode2 timer timer2 timer3 connectsync connectasync serverasync readwritesocket
code = $(CC) $(params) -lboost_system -lboost_thread-mt $^ -o $@

all: $(exec) 

add: add.cpp
	$(CC) $(params) $^ -o $@
nonconcurrent: nonconcurrent.cpp
	$(CC) $(params) $^ -o $@
concurrent: concurrent.cpp
	$(CC) $(params) -lboost_system -lboost_thread-mt -lboost_chrono $^ -o $@
blocked: blocked.cpp
	$(CC) $(params) $^ -o $@
poll:poll.cpp
	$(CC) $(params) $^ -o $@
removework:removework.cpp
	$(CC) $(params) $^ -o $@
multithreads:multithreads.cpp
	$(code)
ioservicebind:ioservicebind.cpp
	$(code)
mutexbind:mutexbind.cpp
	$(code)
post:post.cpp
	$(code)
dispatch:dispatch.cpp
	$(code)
nonstrand:nonstrand.cpp
	$(code)
strand:strand.cpp
	$(code)
strandwrap:strandwrap.cpp
	$(code)
exception:exception.cpp
	$(code)
exception2:exception2.cpp
	$(code)
errorcode:errorcode.cpp
	$(code)
errorcode2:errorcode2.cpp
	$(code)
timer:timer.cpp
	$(code)
timer2:timer2.cpp
	$(code)
timer3:timer3.cpp
	$(code)
connectsync:connectsync.cpp
	$(code)
connectasync:connectasync.cpp
	$(code)
serverasync:serverasync.cpp
	$(code)
readwritesocket:readwritesocket.cpp
	$(code)

rangen_boost: rangen_boost.cpp
	$(CC) $(params) -lboost_system -lboost_random $^ -o $@

clean:
	rm -rf $(exec)
