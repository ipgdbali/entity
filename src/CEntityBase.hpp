#ifndef CENTITY_BASE_HPP
#define CENTITY_BASE_HPP

#include "IEntity.hpp"
#include "CField.hpp"
#include "CFields.hpp"
#include "CEntityFacade.hpp"
#include "CustomType\CAbsCustomType.hpp"
#include <cstring>


namespace ipgdlib::entity
{
/**
 * 
 * 
 * * Disabled *
 *   - Default Constructor
 *   - Copy Construction
 *   - Copy Operator
 *   - Move Operator
 * 
 * * Feature *
 *  - Memory Copy Operation for Entity Attribute. From / To and By Index or Name
 *  - Templated Casting Type for attribute
 *  - Move Construction
 *  - Store CField as Pointer but public interface as const reference. 
 * 
*/
template <typename TFields>
class CEntityFacade<TFields>::Base :
    virtual public IEntity<TFields, ewConstReference>
{
    public:
        using iface                                     = IEntity<TFields, ewConstReference>;
        using type_fields                               = TFields;
        static constexpr eWrapper enum_wrapper_fields   = ewConstReference;
        
        using TFieldIndex       = typename TFields::type_field_index;
        using TFieldName        = typename TFields::TFieldName;
        using TFieldSize        = typename TFields::TFieldSize;
        using TWFields          = typename ipgdlib::wrap<TFields, ewConstReference>::value;
        
        Base() = delete;
        
        TWFields getFields() const noexcept override
        {
            return *this->m_Fields;
        }

        bool copyAttrTo(TFieldIndex const &fieldIndex, void *pDst) const override
        {
            return 
                std::memcpy(
                    pDst,
                    &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
                    this->m_Fields->getField(fieldIndex).size()) != nullptr;
        }

        bool copyAttrTo(TFieldName const &fieldName, void *pDst) const override
        {
            return copyAttrTo(
                this->m_Fields->indexOf(fieldName),
                pDst);
        }

        bool copyAttrFrom(TFieldIndex const &fieldIndex, const void *pSrc) override
        {
            std::memcpy(
                &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
                pSrc,
                this->m_Fields->getField(fieldIndex).size());
            return true;
        }

        bool copyAttrFrom(TFieldName const &fieldName, const void *pSrc) override
        {
            return copyAttrFrom(
                this->m_Fields->indexOf(fieldName),
                pSrc);
        }

        template <typename T>
        T &as(TFieldIndex const &fieldIndex)
        {
            return *reinterpret_cast<T *>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
        }

        template <typename T>
        T const &as(TFieldIndex const &fieldIndex) const
        {
            return *reinterpret_cast<T *>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
        }

        template <typename T>
        T &as(TFieldName const &fieldName)
        {
            return as<T>(this->m_Fields->indexOf(fieldName));
        }

        template <typename T>
        T const &as(TFieldName const &fieldName) const
        {
            return as<T>(this->m_Fields->indexOf(fieldName));
        }

        bool toCustomType(TFieldIndex const &fieldIndex,ICustomType<TFieldSize> &ref) override
        {
            if (ref.getTypeSize() == this->m_Fields->getField(fieldIndex).size())
            {
                dynamic_cast<CAbsCustomType<TFieldSize>&>(ref).setPtr(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
                return true;
            }
            else
                return false;
        }
        
        bool toCustomType(TFieldName const &fieldName,ICustomType<TFieldSize> &ref) override
        {
            return toCustomType(
                this->m_Fields->indexOf(fieldName),
                ref);
        }

    protected:
    
        /**
         * Copy Constructor
        */
        Base(const Base &ref) :
            m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
        {
        }

        /**
         * Move Construction
        */
        Base(Base &&ref) :
            m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
        {
            ref.m_Fields        = nullptr;
            ref.m_pEntityPtr    = nullptr;
        }

        Base(TWFields fields) :
            m_Fields(&fields),m_pEntityPtr(nullptr)
        {
        }

        // Unique Entity & CShared Entity
        Base(TWFields fields,char *pData) : 
            m_Fields(&fields), m_pEntityPtr(pData)
        {
        }

        /**
         * Copy Operator
        */
        Base &operator = (const Base &ref) = delete;

        /**
         * Move Operator
        */
        Base &operator = (Base &&ref)
        {
            std::swap(this->m_Fields,ref.m_Fields);
            std::swap(this->m_pEntityPtr,ref.m_pEntityPtr);
            return *this;
        }

        const char *getEntityAttrPtr(TFieldIndex fieldIndex) const
        {
            return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
        }


        char *getEntityAttrPtr(TFieldIndex fieldIndex)
        {
            return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
        }

        const char* getConstEntityPtr() const
        {
            return this->m_pEntityPtr;
        }

        char *getEntityPtr()
        {
            return this->m_pEntityPtr;
        }

        void setEntityPtr(void *pEntityPtr)
        {
            this->m_pEntityPtr = (char*)pEntityPtr;
        }

        void set(const TFields &fields,char* pEntityPtr)
        {
            this->m_Fields      = fields;
            this->m_pEntityPtr  = pEntityPtr;
        }

    private:
        const TFields*      m_Fields;
        char*               m_pEntityPtr;

};


};



#endif