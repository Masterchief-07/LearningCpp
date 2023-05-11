#include <iostream>

int main()
{
    char selection;
    std::cout<<"do you agree to sell your soul?\n";
    std::cout<<"answere y/n: ";
    std::cin >> selection;
    switch(selection)
    {
        case 'y':
            std::cout<<"accepted\n";
        break;
        case 'n':
            std::cout<<"refused\n";
        break;
        default:
            std::cout<<"invalid\n";
        break;
    }

    return 0;
}