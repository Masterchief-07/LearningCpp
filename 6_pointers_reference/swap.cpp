#include <iostream>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapRef(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a{10}, b{30};
    std::cout<<"a: "<<a<<"\nb: "<<b<<"\n";
    swap(&a, &b);
    std::cout<<"a: "<<a<<"\nb: "<<b<<"\n";
    swapRef(a, b);
    std::cout<<"a: "<<a<<"\nb: "<<b<<"\n";
}