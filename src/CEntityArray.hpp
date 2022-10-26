#ifndef CENTITY_ARRAY_HPP
#define CENTITY_ARRAY_HPP

#include "IEntities.hpp"
#include "CEntityFacade.hpp"
#include "CEntityShared.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
template <typename TRowIndex>
class CEntityFacade<TFields>::Array :
    virtual public IEntities<TRowIndex, TFields, ewConstReference>
{

    public:
        using iface             = IEntities<TRowIndex, TFields, ewConstReference>;
        using TWFields          = typename iface::TWFields;
        using TFieldIndex       = typename TFields::type_field_index;
        using TFieldName        = typename TFields::TFieldName;

        class Cursor;

        virtual ~Array()
        {
            if (this->m_arrPEntityData != nullptr)
            {
                for(TRowIndex li = 0;li < this->m_EntityCount;li++)
                    delete this->m_arrPEntityData[li];
                delete[] m_arrPEntityData;
            }
        }

        Array(TWFields fields, TRowIndex entityCount)
            : m_Fields(fields), m_EntityCount(entityCount)
        {
            this->m_arrPEntityData = new char *[m_EntityCount];
            for (TRowIndex li = 0; li < m_EntityCount; li++)
                m_arrPEntityData[li] = new char[m_Fields.size()];
        }

        TWFields getFields() const override
        {
            return this->m_Fields;
        }

        TRowIndex count() const noexcept override
        {
            return this->m_EntityCount;
        }

        typename CEntityFacade<TFields>::Shared createEntity(TRowIndex rowPos) override
        {
            return {this->m_Fields,this->m_arrPEntityData[rowPos]};
        }

    protected:

        char *getPEntityData(TRowIndex rowPos)
        {
            return this->m_arrPEntityData[rowPos];
        }

    private:
        TWFields    m_Fields;
        TRowIndex   m_EntityCount;
        char**      m_arrPEntityData;

};



};

#endif