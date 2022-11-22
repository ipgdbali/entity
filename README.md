![Language](https://img.shields.io/badge/language-c++-red.svg)
![Platform](https://img.shields.io/badge/compiler-g++-lightgrey.svg)
![Platform](https://img.shields.io/badge/build-make-yellow.svg)

# Entity Library
A C++ header only Entity library.

## Description
A library to creates a structure (C\C++ struct) on runtime.\

This structure (called entity) has data member which is called by attribute (attr for short) and defined by class CField. Every CField has name and size which gives attributes its corresponding value. CFields class takes one or more CField as argument for its construction. 
This CFields is a template argument to construct Entity. Entity constructed by specific CFields
has attributes defined in CFields.
An entity may have its attribute value to be copied from or to another variable or memory.

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
        eCustomer.copyAttrTo(li,0,&id);
        assert(id == (li + 1) * 10)
    }

    // Using attrAs method
    for(int li = 0; li < num;li++)
        eCustomer.attrAs(li,"id") = (li + 1) * 10;

    for(int li = 0; li < num;li++)
        assert(eCustomer.attrAs(li,0) == (li + 1) * 10);
```

##### Create cursor to access entities individually
```
CEntities::Cursor cursor(entities);
CEntity::Shared &eSharedCustomer = cursor.setRowPos(rowNum).getEntity(); // return reference to internal object
```

### 3. Access attribute
Array of Entities (CEntities) must be transfered to CEntity::Shared to access entities individually.

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
