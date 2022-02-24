#include<iostream>
#include<boost/random/random_device.hpp>
#include<boost/random/uniform_int_distribution.hpp>

using namespace std;
using namespace boost;

auto main() -> int
{
	int guessNumber;
	cout<<"select number[0,10] : ";
	cin>>guessNumber;
	if(guessNumber < 0 || guessNumber > 10)
		return 1;
	random::random_device rng;
	random::uniform_int_distribution<> ten(0,10);
	int random_num = ten(rng);
	if(guessNumber == random_num)
		cout<<"CONGRATULATIONS, "<<guessNumber<<" guessed correctly!!!\n";
	else
		cout<<"Sorry, i'm thinking about number: "<<random_num<<"\n";
	return 0;

}

