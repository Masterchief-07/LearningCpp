# conditions

ils permettent de creer differentes operation en fonction d'une condition ou de plusieurs conditions
chaque condition renvoie:
- true: si la condition est satisfaite
- false: si elle ne l'est pas

## list condition
- a > b     superieur
- a >= b    superieur ou egale
- a < b     inferieur
- a <= b    inferieur ou egale
- a == b    egale
- a != b    different

## ensemble de condition
- cond1 && cond2    and (les 2 condition doivent true pour qu'il renvoie true)
- cond1 || cond2    or (suffit qu'une condition soit true pour qu'il renvoie true)
- !cond             not (renvie l'inverse de la condition si true renvoie false)

## if/else if/ else
permet de faire des test de conditions et en fonction du resultat executer un bout de code precis
```cpp
    int age = 18;
    if(age >= 18)
    {
        std::cout<<"Majeur\n";
    }
    else if(age >= 15)
    {
        std::cout<<"ado\n";
    }
    else if (age < 0)
    {
        std::cout<<"error age ne peut pas etre negatif\n";
    }
    else{
        std::cout<<"mineur\n";
    }
```

## switch

fonction comme if mais necessite une selection beaucoup plus precise

```cpp
    char selection='y';
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
```