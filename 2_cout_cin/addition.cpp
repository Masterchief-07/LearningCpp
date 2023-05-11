#include <iostream>

int main()
{
    //project addidition
    int a{0}, b{0}, result{0};
    std::cout<<"welcome to addition software\n";
    std::cout<<"Input a:";
    std::cin>>a;
    std::cout<<"Input b:";
    std::cin>>b;
    result = a + b;
    std::cout<<"result: "<<result<<"\n";
    //version 2
    std::cout<<"welcome to addition software\n";
    std::cout<<"Input a et b:";
    std::cin>>a>>b;
    result = a + b;
    std::cout<<"result: "<<result<<"\n";
}