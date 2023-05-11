<!-- include <iostream> -->
# lib iostream

# cout

permet d'afficher du text dans la console

```Cpp
std::cout<<"hello world"<<std::endl;
std::cout<<"hello "<<"world"<<std::endl;
std::string hello{"hello world"};
std::cout<<hello<<std::endl;
```

# cin

permet de recuperer du text de la console et de le stocker dans une ou plusieurs variables

```Cpp
std::string info
std::cin>>info;
float input;
std::cin>>input;
float a, b;
std::cin>>a>>b;
```