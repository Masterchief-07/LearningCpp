#include <iostream>

void printCarre(int cote)
{
    for(int i=0; i<=cote; i++)
    {
        for(int j=0; j<=cote; j++)
        {
            std::cout<<"*";
        }
        std::cout<<"\n";
    }
}

void printRectangle(int largeur, int longueur)
{
    for(int i=0; i<=largeur; i++)
    {
        for(int j=0; j<=longueur; j++)
        {
            std::cout<<"*";
        }
        std::cout<<"\n";
    }
}

int main()
{
    printCarre(10);
    printRectangle(10, 20);

    return 0;
}