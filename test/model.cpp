#include "CField.hpp"
#include "CFields.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include <string>
#include <cassert>

using CField = ipgdlib::entity::CField<std::string, unsigned char>;
using CFields = ipgdlib::entity::CFields<size_t, size_t, CField>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CFields>;
using CEntityShared = ipgdlib::entity::CEntityShared<CFields>;

class CProduct
{
public:
    static CFields eInfo;

    CProduct(
        unsigned int id,
        const char *fullname,
        unsigned int price_sell_unit,
        unsigned int price_buy_pcs,
        unsigned char pcs_per_unit) : m_Entity(eInfo)
    {
        this->id() = id;
        this->fullname() = fullname;
        this->price_sell_unit() = price_sell_unit;
        this->price_buy_pcs() = price_buy_pcs;
        this->pcs_per_unit() = pcs_per_unit;
    }

    unsigned int &id()
    {
        return this->m_Entity.as<unsigned int>("id");
    }

    const char *&fullname()
    {
        return this->m_Entity.as<const char *>("fullname");
    }

    const char *&shortname()
    {
        return this->m_Entity.as<const char *>("shortname");
    }

    unsigned int &price_sell_unit()
    {
        return this->m_Entity.as<unsigned int>("price_sell_unit");
    }

    unsigned int price_sell_unit() const
    {
        return this->m_Entity.as<unsigned int>("price_sell_unit");
    }

    unsigned int &price_buy_pcs()
    {
        return this->m_Entity.as<unsigned int>("price_buy_pcs");
    }

    unsigned int const &price_buy_pcs() const
    {
        return this->m_Entity.as<unsigned int>("price_buy_pcs");
    }

    unsigned char &pcs_per_unit()
    {
        return this->m_Entity.as<unsigned char>("pcs_per_unit");
    }

    unsigned char const &pcs_per_unit() const
    {
        return this->m_Entity.as<unsigned char>("pcs_per_unit");
    }

    unsigned char &min_sale_unit()
    {
        return this->m_Entity.as<unsigned char>("min_sale_unit");
    }

    unsigned short &stock_outlet()
    {
        return this->m_Entity.as<unsigned short>("stock_outlet");
    }

    unsigned short const &stock_outlet() const
    {
        return this->m_Entity.as<unsigned short>("stock_outlet");
    }

    unsigned short &stock_warehouse()
    {
        return this->m_Entity.as<unsigned short>("stock_warehouse");
    }

    unsigned short const &stock_warehouse() const
    {
        return this->m_Entity.as<unsigned short>("stock_warehouse");
    }

    unsigned int profit_per_unit() const
    {
        return this->price_sell_unit() - this->price_buy_pcs() * this->pcs_per_unit();
    }

    unsigned int stock_total() const
    {
        return this->stock_outlet() + this->stock_warehouse();
    }

private:
    CEntityUnique m_Entity;
};

CFields CProduct::eInfo({
    CField::alloc<unsigned int>("id"),
    CField::alloc<void *>("fullname"),
    CField::alloc<unsigned int>("price_sell_unit"),
    CField::alloc<unsigned int>("price_buy_pcs"),
    CField::alloc<unsigned char>("pcs_per_unit"),
});

int main(int argc, char *argv[])
{
    CProduct product(12, "Resistor 10K", 3000, 250, 10);
    assert(product.profit_per_unit() == 500);

    return 0;
}
