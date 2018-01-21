#pragma once

#include <type_traits>
#include <memory>

template <typename T>
constexpr typename std::underlying_type<T>::type ToUnderlying(T t)
{
    return static_cast<typename std::underlying_type<T>::type>(t);
}

template <typename IterT>
IterT Forward(IterT iter, size_t n)
{
    return std::next(iter, static_cast<IterT::difference_type>(n));
}

using RegisterValue = size_t;

using RegisterName = size_t;

struct InternalError : public std::exception
{
    InternalError(const std::string message) : message{ "Internal Error: " + message }
    {
    }
private:
    std::string message;
};

/* ViewPtr */

template <typename T>
using ViewPtr = T*;

template <typename T>
ViewPtr<T> MakeView(const std::unique_ptr<T>& t_ptr)
{
    return t_ptr.get();
}

/* Cloneable */

#define CLONEABLE(Super, Base) std::unique_ptr<Base> Clone() const override \
{ \
    return std::unique_ptr<Base>( new Super{ *this } ); \
} \

#define CLONEABLE_BASE(Base) virtual std::unique_ptr<Base> Clone() const = 0;

template<template<typename, typename...> class Container, typename Type, typename... Args>
Container<std::unique_ptr<Type>, Args...> CloneContainer(const Container<std::unique_ptr<Type>, Args...>& container)
{
    Container<std::unique_ptr<Type>, Args...> result;
    boost::transform(container, std::inserter(result, result.end()), [](const std::unique_ptr<Type>& elem) {
        return elem->Clone();
    });
    return result;
};