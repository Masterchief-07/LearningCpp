#include <vector>
#include <iostream>

std::vector<int> addition(std::vector<int>& myvect1, std::vector<int>& myvect2)
{
    if(myvect1.size() != myvect2.size())
    {
        std::cout<<"need vector of same size\n";
        return std::vector<int>{};
    }
    std::vector<int> result{};
    for(int i=0; i<myvect1.size(); i++)
    {
        result.push_back(myvect1[i] + myvect2[i]);
    }
    return result;
}
std::vector<int> soustraction(std::vector<int>& myvect1, std::vector<int>& myvect2)
{
    if(myvect1.size() != myvect2.size())
    {
        std::cout<<"need vector of same size\n";
        return std::vector<int>{};
    }
    std::vector<int> result{};
    for(int i=0; i<myvect1.size(); i++)
    {
        result.push_back(myvect1[i] - myvect2[i]);
    }
    return result;
}

void printVect(const std::vector<int>& vect)
{
    for(int i=0; i<vect.size(); i++)
    {
        std::cout<<vect[i]<<" ";
    }
    std::cout<<"\n";
}

int main()
{
    std::vector<int> vect1{1, 2, 3}, vect2{4, 5, 6};
    std::vector<int> vect3 = addition(vect1, vect2);
    std::vector<int> vect4 = soustraction(vect2, vect1);
    printVect(vect3);
    printVect(vect4);
}
