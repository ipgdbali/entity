![Language](https://img.shields.io/badge/language-c++-red.svg)
![Platform](https://img.shields.io/badge/compiler-g++-lightgrey.svg)
![Platform](https://img.shields.io/badge/build-make-yellow.svg)

# Entity Library
A C++ header only Entity library.

## Description
It creates a data structure at runtime.\
This structure contains one to many attributes that can be accessed by index or name.
Each attribute may have its value to be be copied from or to another memory.
There is also a method to cast attribute into a custom type for ease of use.
Attribute size is defined earlier before entity is created among its name.

## Get started
### 1. Create a Fields from Field
```
CFields fCustomer({
    CField::alloc<unsigned int>("id"),              // index - 0
    CField::alloc<sizeof(char*)>("name"),           // index - 1
    CField::alloc<char>("sex")                      // index - 2
    CField::alloc<sizeof(unsigned char)>("age"),    // index - 3
});
```
### 2. Create Entity from Fields

- #### Create an Unique Entity
```
CEntityUnique eCustomer(&fCustomer);
```

- #### Create Shared Entity
```
CEntityShared eSharedCustomer(fCustomer);
```

### 3. Access attribute
- #### Using copy memory
```
unsigned int id;

id = 20;
eCustomer.copyAttrFrom(0,&id);

id = 0;
eCustomer.copyAttrTo("id",&id);
assert(id == 20);

id = 30;
eCustomer.copyAttrFrom("id",&id);

id = 0;
eCustomer.copyAttrTo(0,&id);
assert(id == 30);
```
- #### Using as method 
```
eCustomer.as<char>(2) = 'F';
assert(eCustomer.as<char>("sex") == 'F');

eCustomer.as<char>("sex") = 'M';
assert(eCustomer.as<char>(2) == 'M');

```
- #### Using Custom Type
```
CCTPrimitive<unsigned char> ctAge;

eCustomer.toCustomType(3,ctAge);
ctAge = 20;
assert((ctAge == 20));
assert((eCustomer.as<unsigned char>("age") == 20));

eCustomer.toCustomType("age",ctAge);
ctAge = 30;
assert((ctAge == 30));
assert((eCustomer.as<unsigned char>(3) == 30));
```


You can see source code above [here](https://github.com/ipgdbali/entity/blob/master/test/start.cpp)
