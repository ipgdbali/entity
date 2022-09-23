#ifndef CEntity_HPP
#define CEntity_HPP

#include "IEntity.hpp"
#include "CField.hpp"
#include "CFields.hpp"
#include "ICustomType.hpp"
#include <cstring>

namespace ipgdlib::entity
{

template <typename TFields>
class CEntity : 
    public virtual IEntity<TFields, ewConstReference>
{

    public:
        using iface                                     = IEntity<TFields, ewConstReference>;
        using type_fields                               = TFields;
        static constexpr eWrapper enum_wrapper_fields   = ewConstReference;
        
        using TFieldIndex       = typename TFields::type_field_index;
        using TFieldName        = typename TFields::TFieldName;
        using TFieldSize        = typename TFields::TFieldSize;
        using TWFields          = typename ipgdlib::wrap<TFields, ewConstReference>::value;
        
        CEntity() = delete;
        CEntity(const CEntity &ref) = delete;
        CEntity &operator = (const CEntity &ref) = delete;
        CEntity(CEntity &&ref) = delete;
        CEntity &operator = (CEntity &&ref) = delete;

        TWFields getFields() const noexcept override
        {
            return this->m_Fields;
        }

        bool copyAttrTo(TFieldIndex const &fieldIndex, void *pDst) const override
        {
            return 
                std::memcpy(
                    pDst,
                    &this->m_pEntityData[this->m_Fields.offset(fieldIndex)],
                    this->m_Fields.getField(fieldIndex)->size()) != nullptr;
        }

        bool copyAttrTo(TFieldName const &fieldName, void *pDst) const override
        {
            return copyAttrTo(
                this->m_Fields.indexOf(fieldName),
                pDst);
        }

        bool copyAttrFrom(TFieldIndex const &fieldIndex, const void *pSrc) override
        {
            std::memcpy(
                &this->m_pEntityData[this->m_Fields.offset(fieldIndex)],
                pSrc,
                this->m_Fields.getField(fieldIndex)->size());
            return true;
        }

        bool copyAttrFrom(TFieldName const &fieldName, const void *pSrc) override
        {
            return copyAttrFrom(
                this->m_Fields.indexOf(fieldName),
                pSrc);
        }

        template <typename T>
        T &as(TFieldIndex const &fieldIndex)
        {
            return *reinterpret_cast<T *>(&this->m_pEntityData[this->m_Fields.offset(fieldIndex)]);
        }

        template <typename T>
        T const &as(TFieldIndex const &fieldIndex) const
        {
            return *reinterpret_cast<T *>(&this->m_pEntityData[this->m_Fields.offset(fieldIndex)]);
        }

        template <typename T>
        T &as(TFieldName const &fieldName)
        {
            return as<T>(this->m_Fields.indexOf(fieldName));
        }

        template <typename T>
        T const &as(TFieldName const &fieldName) const
        {
            return as<T>(this->m_Fields.indexOf(fieldName));
        }

        
        bool toCustomType(TFieldIndex const &fieldIndex, ICustomType<TFieldSize> &ref) override
        {
            if (ref.getTypeSize() == this->m_Fields.getField(fieldIndex)->size())
            {
                ref.setPtr(&this->m_pEntityData[this->m_Fields.offset(fieldIndex)]);
                return true;
            }
            else
                return false;
        }
        
        bool toCustomType(TFieldName const &fieldName, ICustomType<TFieldSize> &ref) override
        {
            return toCustomType(
                this->m_Fields.indexOf(fieldName),
                ref);
        }

        class Unique;
        class Shared;
        
    protected:

        CEntity(TWFields fields) :
            m_Fields(fields),m_pEntityData(nullptr)
        {
        }

        // Unique Entity & CShared Entity
        CEntity(TWFields fields,char *pData) : 
            m_Fields(fields), m_pEntityData(pData)
        {
            if(m_pEntityData == nullptr)
                throw "pData cannot be null";
        }

        // Shared Entity
        CEntity(CEntity &ref) :
            CEntity(ref.m_Fields,ref.m_pEntityData)
        {
        }

        char *getEntityPtr() const
        {
            return this->m_pEntityData;
        }

        void setEntityPtr(char *pData)
        {
            this->m_pEntityData = pData;
        }

    private:
        TWFields    m_Fields;
        char*       m_pEntityData;
};

template <typename TFields>
class CEntity<TFields>::Unique :
    public CEntity<TFields>,
    virtual public IEntity<TFields,CEntity<TFields>::enum_wrapper_fields>::IUnique
{
    public:
        using parent    = CEntity<TFields>;
        using TWFields  = typename parent::TWFields;

        virtual ~Unique()
        {
            if(this->getEntityPtr() != nullptr)
                delete []this->getEntityPtr();
        }

        Unique() = delete;
        Unique(const Unique &ref) = delete;
        Unique &operator = (const Unique &ref) = delete;
        Unique(Unique &&ref) = delete;
        Unique &operator = (Unique &&ref) = delete;


        Unique(TWFields fields) 
            : CEntity<TFields>(fields,new char[fields.size()])
        {
        }

};

template <typename TFields>
class CEntity<TFields>::Shared :
    public CEntity<TFields>,
    virtual public IEntity<TFields,CEntity<TFields>::enum_wrapper_fields>::IShared
{

    public:

        using parent = CEntity<TFields>;
        using TWFields = typename parent::TWFields;
        
        Shared() = delete;
        Shared(const Shared &ref) = delete;
        Shared &operator = (const Shared &ref) = delete;
        Shared(Shared &&ref) = delete;
        Shared &operator = (Shared &&ref) = delete;

        Shared(CEntity<TFields> &ref) :
            CEntity<TFields>(ref)
        {
        }

        Shared(TWFields fields,char *pData) :
            CEntity<TFields>(fields,pData)
        {
        }

        Shared(TWFields fields) :
            CEntity<TFields>(fields)
        {
        }

        void set(void *pSrc) override
        {
            this->setEntityPtr(static_cast<char*>(pSrc));
        }

        bool isNull() const noexcept override
        {
            return this->getEntityPtr() == nullptr;
        }

        void clear() noexcept override
        {
            this->setEntityPtr(nullptr);
        }

};

};

#endif
