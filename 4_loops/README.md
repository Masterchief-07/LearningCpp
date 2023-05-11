# boucle

permettent d'executer plusieur fois un meme bout de code  

## for
permet de repeter un bout de code un certains nombre de fois
- la structure
```cpp
    for(initialization; condition; update)
    {
        //code   
    }
```
- example
```cpp
    for(int i=0; i < 10; i++)
    {
        std::cout<<i<<std::endl;
    }
```

## while (tanque)

- la structure
```cpp
    while(condition)
    {

    }
```
repete le bout de code tanque la condition est correct
- example
```cpp
    int i = 10;
    while(i > 0)
    {
        std::cout<<i<<std::endl;
        i--;    // il faut se rappeler d'update la variable pour eviter une bouche infinie
    }
```


## do while
fonction de la meme facons que while mais ici il execute le code au moince une fois que le condition soit vrai ou pas
- structure
```cpp
    do{
        //code
    }while(condition);
```

- example
```cpp
    int i=0;
    do{
        std::cout<<"taper un nombre inferieur a 10: ";
        std::cin>>i;
    }while(i>=10);
```