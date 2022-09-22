![Language](https://img.shields.io/badge/language-c++-red.svg)
![Platform](https://img.shields.io/badge/compiler-g++-lightgrey.svg)
![Platform](https://img.shields.io/badge/build-make-yellow.svg)

# Entity Library
A C++ header only Entity library.

## Description
It creates a data structure at runtime.\
This structure contains one to many attributes that can be accessed by index or name.
Name of an Attribute, is a Field. Attribute is a value of a field.
For examples :
red and color, red is and attribute and color is field. 

Each attribute of an entity may have its value to be be copied from or to another memory using methods.
To be able to store a value into an attribute, an attribute size must be defined along its name.
Attribute definition (CFields class) is made before an entity can be made.

## Get started
### 1. Create a Fields from Field
```
CFields fCustomer({
    CFieldFactory::alloc<int>("id"),
    CFieldFactory::alloc<sizeof(char*)>("name"),
    CFieldFactory::alloc<char>("sex"),
    CFieldFactory::alloc<sizeof(unsigned char)>("age")
});
```
### 2. Create Entity

- #### Create an Unique Entity
```
CEntityUnique eCustomer(fCustomer);
```

- #### Create Shared Entity from another entity
```
CEntityShared eSharedCustomer(eCustomer);
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

## Feature
### Create CFields from collection
```
std::vector<CFields::TWField> fields;
fields.push_back(CFieldFactory::alloc<unsigned int>("id"));
fields.push_back(CFieldFactory::alloc<sizeof(char*)>("name"));
fields.push_back(CFieldFactory::alloc<char>("sex"));
fields.push_back(CFieldFactory::alloc<sizeof(unsigned char)>("age"));

CFields fCustomer(fields);
assert(fCustomer.count() == 4);
```
