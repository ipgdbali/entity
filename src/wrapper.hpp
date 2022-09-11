#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <memory>

namespace ipgdlib
{

enum eWrapper { ewPointer,ewConstPointer,ewReference,ewConstReference,ewSharedPtr,ewWeakPtr,ewConst,ewNoChange };

template <typename T,eWrapper e>
struct wrap { 
};

template <typename T>
struct wrap<T,ewPointer> {
    using value = T*;
};

template <typename T>
struct wrap<T,ewConstPointer> {
    using value = T const*;
};

template <typename T>
struct wrap<T,ewReference> {
    using value = T&;
};

template <typename T>
struct wrap<T,ewConstReference> {
    using value = T const&;
};

template <typename T>
struct wrap<T,ewSharedPtr> {
    using value = std::shared_ptr<T>;
};

template <typename T>
struct wrap<T,ewWeakPtr> {
    using value = std::weak_ptr<T>;
};

template <typename T>
struct wrap<T,ewConst> {
    using value = const T;
};

template <typename T>
struct wrap<T,ewNoChange> {
    using value = T;
};

};

#endif
