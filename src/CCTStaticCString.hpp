#ifndef CCT_STATIC_CSTRING
#define CCT_STATIC_CSTRING

#include "ICustomTypeStatic.hpp"
#include <cstring>

namespace ipgdlib::entity
{

/**
 *
 * len -> maximum length without null
 *
 **/
template <typename T,typename TSize,typename TIndex,TIndex len>
class CCTStaticCString :
    public ICustomTypeStatic<TSize>
{
public:
    constexpr static TIndex max_length = len;
    constexpr static TSize size = sizeof(T) * (len+1);

    TSize getTypeSize() const noexcept override
    {
	return size;
    }

    TIndex getLength() const noexcept
    {
	return this->m_Length;
    }

    void copyTo(void *pDest) const override
    {
	T* dst = static_cast<T*>(pDest);
	for(TIndex li = 0;li <= this->m_Length;li++)
	    dst[li] = this->m_pData[li];
    }

    void copyFrom(const void *pSrc) override
    {
	const T* src = static_cast<const T*>(pSrc);
	TIndex li = 0;
	do
	{
	    this->m_pData[li] = src[li];
	    if(m_pData[li] == 0)
	    {
		this->m_Length = li;
		break;
	    }
	    else
	    if(li == max_length)
	    {
		this->m_pData[li] = 0;
		this->m_Length = max_length;
		break;
	    }
	    li++;
	}while(true);
    }

    void setPtr(void *pSrc)
    {
	this->m_pData = static_cast<T*>(pSrc);
    }

    CCTStaticCString<T,TSize,TIndex,len> &operator = (const T* ref)
    {
	copyFrom(ref);
	return *this;
    }

    const T &get(TIndex index) const
    {
	return m_pData[index];
    }

private:
    T *m_pData;
    TIndex m_Length;
};

};

#endif
