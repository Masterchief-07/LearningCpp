#include <iostream>

void pow(int *valeur, int puissance)
{
    if(puissance == 0)
        *valeur=1;
    int mult = *valeur;
    for(int i=0; i<puissance-1; i++)
    {
        *valeur *= mult;
    }
}

int main()
{
    int a{0}, b{0};
    std::cout<<"taper le nombre: ";
    std::cin>>a;
    std::cout<<"taper la puissance: ";
    std::cin>>b;
    std::cout<<a<<" a la puissance "<<b<<" egale: ";
    pow(&a, b);
    std::cout<<a<<"\n";
    return 0;
}