#include <iostream>

void print1()
{
	for(int i = 0; i < 5; i++)
		std::cout<<"[print1] "<<i<<"\n";
}
void print2()
{
	for(int i = 0; i < 5; i++)
		std::cout<<"[print2] "<<i<<"\n";
}

auto main() -> int
{
	print1();
	print2();
}
