#include <iostream>
#include "CustomType/CCTStaticCString.hpp"
#include <cstring>
#include <cassert>

using namespace ipgdlib::entity;

int main(int argc,char * argv[])
{
    char str[11];
    CCTStaticCString<char,size_t,size_t,10> s;
    s.setPtr(str);
    s.copyFrom("Ini Dia");

    assert(s.getTypeSize() == 11);
    assert(s.max_length == 10);
    assert(s.getLength() == 7);
    assert(std::strcmp(str,"Ini Dia") == 0);

    return 0;
}
