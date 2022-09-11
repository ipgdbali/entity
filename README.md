![Language](https://img.shields.io/badge/language-c++-red.svg)
![Platform](https://img.shields.io/badge/platform-gnu%20%7C%20linux%20%7C%20unix-lightgrey.svg)

# Entity Library
A C++ header only Entity library.

## What it does
It creates a data structure at runtime.\
This structure contains one to many attributes that can be accessed by index or name.
Each attribute may have its value to be be copied from or to another memory.
There is also a method to cast attribute into a custom type for ease of use.
Attribute size is defined earlier before entity is created among its name.

## Get started
1. Create a Fields Info from Field Info
```
CFields fCustomer({
    CField::alloc<unsigned int>("id"),  // index - 0
    CField::alloc<void*>("fullname"),   // index - 1
    CField::alloc<void*>("nickname"),   // index - 2
    CField::alloc<char>("sex")          // index - 3
});
```
2. Create Entity from Fields Info
 ```
 // Create Unique Entity
 CEntityUnique eCustomer;
 eCustomer.createFrom(fCustomer)

// Create Array of Entity
CEntities eCustomers;
eCustomers.createfrom(fCustomer)

// Create Shared Entity


 ```
3. Access attribute
```
eCustomer.as<unsigned int>(0) = 10;                 // access by index
assert(eCustomer.as<unsigned int>("id") == 10);     // access by name
```
