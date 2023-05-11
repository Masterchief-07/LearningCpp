CC= g++
FLAGS= --std=c++2a -g -Wall
INPUTS = integer floating character

all: 
	$(foreach var, $(INPUTS), $(CC) $(FLAGS) -o ./build/$(var) $(var).cpp ;)

clean:
	rm hello
