#include "entity.hpp"
#include <cassert>
#include <iostream>

using CField        = ipgdlib::entity::CField<unsigned char>;
using CFields       = ipgdlib::entity::CFields<unsigned char, size_t,CField>;
using CEntity       = ipgdlib::entity::CEntity<CFields>;

int main(int argc,char *argv[])
{
    CFields fCustomer(
        {
            {"id",sizeof(int)},
            {"name"},
            {"addr"},
            {"sex",sizeof(char)}
        }
    );

    assert(fCustomer.count() == 4);

    assert(fCustomer[0].name() == "id");
    assert(fCustomer[0].size() == sizeof(int));
    assert(fCustomer[1].name() == "name");
    assert(fCustomer[1].size() == sizeof(void*));
    assert(fCustomer[2].name() == "addr");
    assert(fCustomer[2].size() == sizeof(void*));
    assert(fCustomer[3].name() == "sex");
    assert(fCustomer[3].size() == sizeof(char));

    {
        // Creating Unique Entity
        CEntity::Unique eCustomer(fCustomer);

        int id = 10;
        eCustomer.copyAttrFrom(0,&id);          // copy eCustomer attr index - 0 from variable id
        id = 30;                                // change id
        eCustomer.copyAttrTo("id",&id);         // copy eCustomer attr "id" to variable id
        assert(id == 10);                       // assert value

        eCustomer.attrAs<char>("sex") = 'M';
        assert(eCustomer.attrAs<char>(3) == 'M');

        //Creating Shared Entity from Unique Entity
        CEntity::Shared eSharedCustomer(eCustomer);

        assert(eSharedCustomer.attrAs<int>("id") == 10);
        eSharedCustomer.attrAs<int>(0) = 30;
        assert(eSharedCustomer.attrAs<int>("id") == 30);
        assert(eCustomer.attrAs<unsigned int>("id") == 30);
    }

    {
        // Create Array of 10 Entities
        CEntity::Array<unsigned char> eArray(fCustomer,10);
        assert(eArray.reserved() == 10);
        assert(eArray.count() == 0);

        eArray.alloc(10);
        assert(eArray.count() == 10);
        auto cursor = eArray.createCursor();    // cursor pointes to index 0

        assert(cursor.isRowPosValid());

        for(unsigned int li = 0;li < 10;li ++)
            cursor.setRowPos(li).getEntity().attrAs<unsigned int>(0) = (li + 1) * 10;
        for(unsigned int li = 0;li < 10;li ++)
            assert(cursor.setRowPos(li).getEntity().attrAs<unsigned int>("id") == (li + 1) * 10);
        eArray.deAlloc(10);

        assert(!cursor.isRowPosValid());
    }


    return 0;
}