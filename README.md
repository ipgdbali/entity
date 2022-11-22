![Language](https://img.shields.io/badge/language-c++-red.svg)
![Platform](https://img.shields.io/badge/compiler-g++-lightgrey.svg)
![Platform](https://img.shields.io/badge/build-make-yellow.svg)

# Entity Library
A C++ header only Entity library.

## Description
A library to creates C\C++ struct runtime.

This structure (called entity) has data member which is called by attribute and is defined earlier before a corresponding entity is created. 
Each attribute has a name and a size. A name may be used to access its attribute value from an entitiy. While its size is size of an allocated space in memory to store its value. CField is a class to represent definition of an attribute.
Attributes is collected in a specific class named CFields (note the 's' suffix). The order they are supplied to CFields class is also the order of their index. The first supplied CField class become attribute of index 0 when accessed from corresponding entity class. CFields class also contains other information derived from supplied attributes from constructor. Please see IFields interface for list of method that CFields class needs to have.
After CFields class is instanced, supply it instance into an entity class like CEntitiy::Unique or CEntitiy::Array to create instance of an entity class. An entity class will then make attributes (C\C++ struct data member) based information on CFields class.
Every attributes in an entitiy may have its value to be copied from or into another variable/memory.

## Get started
### 1. Create a Fields from Field
```
CFields fCustomer({
    {"id",sizeof(int)},     // index - 0, size = sizeof(int)
    {"name"},               // index - 1, size = sizeof(void*)
    {"addr"},               // index - 2, size = sizeof(void*)
    {"sex",sizeof(char)}    // index - 3, size = sizeof(char)
});
```
### 2. Create Entity
#### a. Single Entity
```
CEntity::Unique eCustomer(fCustomer);       // create 1 entity from fCustomer
```
#### b. Array of Entity
```
constexpr num = 10;                     
CEntities entities(fCustomer,num);          // create 10 entity from fCustomer
```

### 3. Use Entity
#### a. Single Entity
```
    // Using copyAttrXXX method
    int id = 10;

    eCustomer.copyAttrFrom(0,&id);          // copy eCustomer attr index - 0 from variable id
    id = 30;                                // change id
    eCustomer.copyAttrTo("id",&id);         // copy eCustomer attr "id" to variable id
    assert(id == 10);                       // assert value

    // Using attrAs method
    eCustomer.attrAs<int>("sex") = 'M';     
    assert(eCustomer.attrAs<int>(3) == 'M');
```
#### b. Array of Entity
```
    // Using copyAttrXXX method
    for(int li = 0; li < num;li++)
    {
        id = (li + 1) * 10;
        eCustomer.copyAttrFrom(li,0,&id);
    }
    for(int li = 0; li < num;li++)
    {
        id = 0;
        eCustomer.copyAttrTo(li,"id",&id);
        assert(id == (li + 1) * 10)
    }

    // Using attrAs method
    for(int li = 0; li < num;li++)
        eCustomer.attrAs(li,"id") = (li + 1) * 10;

    for(int li = 0; li < num;li++)
        assert(eCustomer.attrAs(li,0) == (li + 1) * 10);
```

You can see example source code [here](https://github.com/ipgdbali/entity/blob/master/test/start.cpp)

## Feature
