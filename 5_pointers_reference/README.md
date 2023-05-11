# pointer/reference
des concepts tres important en c++ il permettent de manipuler la memoire directement

## pointer
c'est une variable qui stocke l'address memoire d'une autre variable, et qui permet ainsi de faire des modifications directement sur la variable
```cpp
    int a = 10;
    int *a_p = &a; //creation d'un pointeur qui point sur la variable a
    std::cout<<*a_p<<"\n"; //avoir access a la valeur de la variable a
    std::cout<<a_p<<"\n"; //affiche l'address memoire de la variable a
    std::cout<<&a_p<<"\n"; //affiche l'address memoire du pointer a_p
```
- exemple
```cpp
    int x=20, y=30;
    int *p = &x;
    std::cout<<"x: "<<*p<<"\n";
    p = &y;
    std::cout<<"y: "<<*p<<"\n";
```

## reference
similaire a un pointeur, mais ici une reference ne peut pas changer de reference durant son execution
```cpp
    int x=20;
    int &ref_x = x;
    std::cout<<"x" << ref_x<<"\n"; //affiche la valeur de x contenue dans la ref_x
```