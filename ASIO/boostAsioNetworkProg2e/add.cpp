#include<iostream>
#include<boost/lexical_cast.hpp>
#include <string>
using namespace std;
using namespace boost;

auto main() -> int
{
	try
	{
		string str;
		cout<<"input first number: ";
		cin>>str;
		int n1 = lexical_cast<int>(str);
		cout<<"input second number: ";
		cin>>str;
		int n2 = lexical_cast<int>(str);
		cout<<"the sum of tow number is: ";
		cout<< n1 + n2 <<"\n";
		return 0;
	}
	catch(const bad_lexical_cast &e)
	{
		cerr<<e.what()<<"\n";
		return 1;
	}
}

