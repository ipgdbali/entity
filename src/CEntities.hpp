#ifndef CENTITIES_HPP
#define CENTITIES_HPP

#include "IEntities.hpp"
#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <typename TRowIndex, typename TFields>
class CEntities : 
    virtual public IEntities<TRowIndex, TFields, ewConstReference>
{

    public:
        using iface             = IEntities<TRowIndex, TFields, ewConstReference>;
        using TWFields          = typename iface::TWFields;
        using TFieldIndex       = typename TFields::type_field_index;
        using TFieldName        = typename TFields::TFieldName;

        virtual ~CEntities()
        {
            if (this->m_arrPEntityData != nullptr)
            {
                for(TRowIndex li = 0;li < this->m_EntityCount;li++)
                {
                    delete this->m_arrPEntityData[li];
                    this->m_arrPEntityData[li] = nullptr;
                }
                delete[] m_arrPEntityData;
                this->m_arrPEntityData = nullptr;
            }
        }

        CEntities(TWFields fields, TRowIndex entityCount)
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

        typename CEntity<TFields>::Shared getEntity(TRowIndex rowPos) override
        {
            return {this->m_Fields,this->m_arrPEntityData[rowPos]};
        }

        class Cursor;

    protected:
        char *getPEntityData(TRowIndex rowPos)
        {
            return this->m_arrPEntityData[rowPos];
        }
    private:
        TWFields m_Fields;
        TRowIndex m_EntityCount;
        char **m_arrPEntityData;
    };

template <typename TRowIndex, typename TFields>
class CEntities<TRowIndex,TFields>::Cursor :
    virtual public IEntities<TRowIndex,TFields,CEntities<TRowIndex,TFields>::iface::enum_wrapper_fields>::ICursor
{
    public:
        Cursor(CEntities & entities)
            : m_Entities(entities),m_RowPos(0),m_EntityShared(entities.m_Fields,entities.m_arrPEntityData[0])
        {
        }

        Cursor &setRowPos(TRowIndex rowPos) override
        {
            this->m_RowPos = rowPos;
            this->m_EntityShared.set(this->m_Entities.m_arrPEntityData[rowPos]);
            return *this;
        }

        TRowIndex getRowPos() const noexcept override
        {
            return this->m_RowPos;
        }

        typename CEntity<TFields>::Shared &getEntity() override
        {
            return this->m_EntityShared;
        }

    protected:
    private:
        CEntities &m_Entities;
        TRowIndex m_RowPos;
        typename CEntity<TFields>::Shared m_EntityShared;
};

};


#endif
