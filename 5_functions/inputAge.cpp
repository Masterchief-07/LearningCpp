#include <iostream>

int getAge()
{
    int age{0};
    do
    {
        std::cout<<"tape ton age: ";
        std::cin>>age;
        if (age<=0 || age >=200)
        {
            std::cout<<"hum.... pourquoi tu mens\n";
        }
    }while(age <= 0 || age >= 200);

    return age; //retourn la valeur de l'age
}

int main()
{
    int age = getAge();
    std::cout<<"tu as "<<age<<"ans\n";
    return 0;
}