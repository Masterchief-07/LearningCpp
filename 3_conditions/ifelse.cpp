#include <iostream>

int main()
{
    int age;
    std::cout<<"quel est ton age? : ";
    std::cin >> age;
    if (age > 18)
        std::cout<<"tu es majeur toi!\n";
    else if(age > 15)
        std::cout<<"tu es un ado toi \n";
    else if (age < 0)
        std::cout<<"error age ne peut pas etre negatif\n";
    else
        std::cout<<"tu es mineur toi \n";

    return 0;
}