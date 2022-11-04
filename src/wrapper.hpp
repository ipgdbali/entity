#ifndef IPGDLIB_WRAPPER_HPP
#define IPGDLIB_WRAPPER_HPP

#include <type_traits>
#include <memory>

namespace ipgdlib
{

class EWrapper {};

class EWrapperNone              : EWrapper {};
class EWrapperReference         : EWrapper {};
class EWrapperPointer           : EWrapper {};
class EWrapperSharedPtr         : EWrapper {};
class EWrapperUniquePtr         : EWrapper {};

template <typename T,typename EWrapperT>
struct wrapper
{
    static_assert(std::is_base_of<EWrapperT,EWrapper>::value);
};

template <typename T>
struct wrapper<T,EWrapperNone>
{
    public:
        using param_type        = T;
        using param_ewrapper    = EWrapperNone;

        using type          = T;
        using type_const    = T const;
};


template <typename T>
struct wrapper<T,EWrapperReference>
{
    public:
        using param_type        = T;
        using param_ewrapper    = EWrapperReference;

        using type = T&;
        using type_const = T const&;
};

template <typename T>
struct wrapper<T,EWrapperPointer>
{
    public:
        using param_type        = T;
        using param_ewrapper    = EWrapperPointer;

        using type = T*;
        using type_const = T const*;

};

template <typename T>
struct wrapper<T,EWrapperSharedPtr>
{
    public:
        using param_type        = T;
        using param_ewrapper    = EWrapperSharedPtr;

        using type              = std::shared_ptr<T>;
        using type_const        = std::shared_ptr<T const>;
        
        using const_type        = type const;
        using const_type_const  = type_const const;

};

template <typename T>
struct wrapper<T,EWrapperUniquePtr>
{
    public:
        using param_type        = T;
        using param_ewrapper    = EWrapperUniquePtr;

        using type = std::unique_ptr<T>;
        using type_const = std::unique_ptr<T const>;
        
        using const_type        = type const;
        using const_type_const  = type_const const;


};

};

#endif