CC = clang++
params = -std=c++2a -Wall -Wpedantic -pthreads

target = daytimeclientsync daytimeserversync daytimeserverasync
code = $(CC) $(params) $^ -o $@

all: $(target)


daytimeclientsync: daytimeclientsync.cpp
	$(code)
daytimeserversync: daytimeserversync.cpp
	$(code)
daytimeserverasync: daytimeserverasync.cpp
	$(code)


clean:
	rm -rf $(target)
