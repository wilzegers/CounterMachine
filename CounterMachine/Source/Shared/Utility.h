#pragma once

#include <type_traits>
#include <memory>

#include "BoostIncludes.h"

/// Iterátor elé lépés.
/**
* \param iter a megelőzendő iterátor.
* \param n a lépésmennyiség.
* \return a lépéses után kapott iterátor.
*/
template <typename IterT>
IterT Forward(IterT iter, size_t n)
{
    return std::next(iter, static_cast<typename IterT::difference_type>(n));
}

/// Regiszterérték-típus
using RegisterValue = uint64_t;

/// Regisztercím-típus
using RegisterName = size_t;

/// Regisztercímek halmazát leíró osztály.
using RegisterNameSet = boost::container::flat_set<RegisterName>;

/// Regisztercímekhez regiszter-értékeket rendelő hozzárendelés.
using RegisterValueMap = boost::container::flat_map<RegisterName, RegisterValue>;

/* Segédet pointerek birtoklásához. */

/// Típusalias annak a jelzésére, hogy ez az objektum már birtokolva van.
template <typename T>
using ViewPtr = T*;

/// Birtokolt pointer view-vé konvertálása.
/**
* \param t_ptr a birtokolt pointer.
* \return view a birtokolt pointerre.
*/
template <typename T>
ViewPtr<T> MakeView(const std::unique_ptr<T>& t_ptr)
{
    return t_ptr.get();
}

/* Klónozható osztályok létreozásához, használatához eszközök */

/// Klónozható leszármazott osztályba írandó macro.
#define CLONEABLE(Super, Base) std::unique_ptr<Base> Clone() const override \
{ \
    return std::unique_ptr<Base>( new Super{ *this } ); \
} \

/// Klónozható ősosztályba írandó macro.
#define CLONEABLE_BASE(Base) virtual std::unique_ptr<Base> Clone() const = 0;

/// Klónozható objektumokat tartalmazó konténer klónozása.
/**
* \tparam Container a konténer típusa.
* \tparam Type a konténer által tartalmazott típus.
* \tparam Args a konténer többi template-paramétere.
* \param container a klónozandó konténer.
* \return a klónozás eredménye.
*/
template<template<typename, typename...> class Container, typename Type, typename... Args>
Container<std::unique_ptr<Type>, Args...> CloneContainer(const Container<std::unique_ptr<Type>, Args...>& container)
{
    Container<std::unique_ptr<Type>, Args...> result;
    boost::transform(container, std::inserter(result, result.end()), [](const std::unique_ptr<Type>& elem) {
        return elem->Clone();
    });
    return result;
};