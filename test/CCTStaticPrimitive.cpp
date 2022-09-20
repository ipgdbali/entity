#include <iostream>
#include <cassert>

#include "CustomType/CCTPrimitive.hpp"

using namespace ipgdlib::entity;

int main(int argc,char * argv[])
{
    float f;
    CCTPrimitive<float,size_t> fPointer;
    fPointer.setPtr(&f);

    fPointer = 100.0f;
    assert(fPointer == 100.0f);
    assert(f == 100.0f);
    return 0;
}
