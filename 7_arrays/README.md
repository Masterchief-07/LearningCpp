# array (tableau)
c'est une collection d'un ou de plusieurs elements de meme type, qui sont stocker de facons contigus les uns a la suite des autres dans la memoire
chaque element peut etre accede a l'aide d'un index, qui represente la position de l'element dans le tableau

- structure
```cpp
    type nom_array[taille] = {valeur1, valeur2, valeur3}; //initialize array
    //ou
    type nom_array[taille]; //uninitialize array
```

- example
```cpp
    int vecteur[3] = {1, 2, 3};
    for(int i=0; i<3; i++)
    {
        std::cout<<"vecteur["<<i<<"] = "<<vecteur[i]<<"\n";
    }
```

## vector
vector est un array dynamique dont la taille n'est pas static on peut lui ajouter de nouveau elements durant l'execution du programme
- structure
```cpp
    #include <vector>
    std::vector<type> myvect{value1, value2, value3}; //creer un tableau avec des valeurs definit
    std::vector<type> myvect2{};    //creer un tableau vide
    myvect.push_back(value); //ajoute une value au tableau
```
- example
```cpp
    #include <vector>
    std::vector<int> myvect{};
    myvect.push_back(1);
    myvect.push_back(2);
    myvect.push_back(3);
    for(int i=0; i<myvect.size(); i++)
    {
        std::cout<<"vecteur["<<i<<"] = "<<myvect[i]<<"\n";
    }
```

## STRING
un string a une chaine de characteres, il a un fonctionnement similaire a vector, mais lui est static
```cpp
    #include <string>
    std::string hello{"hello world"};
    std::cout<<hello<<"\n";
    std::cout<<"nombre de charactere"<<hello.size()<<"\n";
    std::cout<<hello[2]<<"\n";
```