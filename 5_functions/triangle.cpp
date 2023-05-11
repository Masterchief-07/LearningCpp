#include <iostream>

void printTriangleRectangle(int taille)
{
    for (int i = 1; i <= taille; i++) {
        for (int j = 1; j <= i; j++) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

int main()
{

    printTriangleRectangle(10);

    return 0;
}