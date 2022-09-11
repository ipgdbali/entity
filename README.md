![Language](https://img.shields.io/badge/language-c++-red.svg)
![Platform](https://img.shields.io/badge/platform-gnu%20%7C%20linux%20%7C%20unix-lightgrey.svg)

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
    CField::alloc<unsigned int>("id"),  // index - 0
    CField::alloc<void*>("fullname"),   // index - 1
    CField::alloc<void*>("nickname"),   // index - 2
    CField::alloc<char>("sex")          // index - 3
});
```
### 2. Create Entity from Fields

- #### Create an Unique Entity
```
CEntityUnique eCustomer;
eCustomer.createFrom(fCustomer)
```

- #### Create an Array of Entity 
```
constexprt size_t ROW_COUNT = 10;
CEntities eCustomers;
eCustomers.createFrom(fCustomer,ROW_COUNT)

for(size_t li = 0;li < ROW_COUNT;li++)
    eCustomers.assignFrom(li,new char[fCustomers.size()]);  // initialize memory
```

- #### Create Shared Entity
     - ##### From Unique Entity
     ```
     CEntityShared eSharedCustomer;
     eCustomers.shareTo(eSharedCustomer);
     ```
     - ##### From Array of Entity
     ```
     CEntityShared eSharedCustomer;
     eCustomers.shareTo(eSharedCustomer,index);
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
eCustomer.copyAttrTo(0,"&id);
assert(id == 30);

```
- #### Using as method 
```
eCustomer.as<unsigned int>(0) = 10;                 
assert(eCustomer.as<unsigned int>("id") == 10);     

eCustomer.as<unsigned int>("id") = 20;                 
assert(eCustomer.as<unsigned int>(0) == 20);

```
- #### Using Custom Type
```
CCTPrimitive<unsigned int> ctID;

eCustomer.toCustomType(0,ctID);
ctID = 20
assert(ctID == 20);
assert(eCustomer.as<unsigned int>("id") == 20);

eCustomer.toCustomType("id",ctID);
ctID = 30
assert(ctID == 30);
assert(eCustomer.as<unsigned int>(0) == 30);
```
