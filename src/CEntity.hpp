#ifndef CENTITY_HPP
#define CENTITY_HPP

namespace ipgdlib::entity
{

template <typename FieldsT>
class CEntity
{
    protected:
        class Base;

    public:
        using TFields           = FieldsT;

        class Unique;
        class Shared;

        template <
            typename CountT,
            typename SharedT = Shared
        >
        class Array
        {
            public:

                using TCount            = CountT;
                using TShared           = SharedT;
                
                using TRowIndex         = TCount;

                ~Array();
                Array(const TFields &fields,TRowIndex entityCount);
                const TFields &getFields() const;
                TCount count() const noexcept;

                class Cursor
                {
                    public:
                        Cursor(const Array &array,TRowIndex iStart);
                        TRowIndex getRowPos() const noexcept;
                        Cursor& setRowPos(TRowIndex rowPos);
                        const TShared& getEntity() const;
                        TShared &getEntity();

                        const TShared& operator[](TRowIndex rowPos) const;
                        TShared& operator[](TRowIndex rowPos);

                    private:
                        const Array*    m_EntityArray;
                        TRowIndex       m_RowPos;
                        TShared         m_EntityShared;
                };
                Cursor createCursor(TRowIndex iStart = 0) const;

            private:
                const TFields*      m_Fields;
                TCount              m_EntityCount;
                char**              m_arrPEntityData;
        };
        
};

};

#endif
