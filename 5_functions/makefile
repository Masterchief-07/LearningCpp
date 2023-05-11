CC= g++
FLAGS= --std=c++2a -g -Wall
INPUTS = triangle square inputAge

all: 
	$(foreach var, $(INPUTS), $(CC) $(FLAGS) -o ./build/$(var) $(var).cpp ;)

clean:
	rm hello
