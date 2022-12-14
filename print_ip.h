#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>

#include "generator.h"

/// \brief  Print integers, separated by dots.
/// \author Igor Dedkovskiy
namespace print_ip_ns
{

using ip_field_t = unsigned char;

/// \warning print ip helpers are not ment to be a part of an interface.
///          Anyway, use it if you find it usefull.
/// \note    It's possible to hide helpers, but this way helpers will become untestable.
namespace print_ip_helpers
{

template<typename T> concept Integer = std::is_integral_v<T>;

/// \brief   Returns elements of \a addr like it's an ip address.
/// \details If \a T is an integer, returns addr's bytes in reverse order, starting from
///          higher byte.
///          If \a T is std::vector<ip_field_t> or std::list<ip_field_t>, where \a t is
///          an integer, returns elements of \a T one by one.
template<Integer T> generator<ip_field_t> process(const T& addr)
{
    for(std::size_t cntr = 0; cntr < sizeof(T); ++cntr)
        co_yield ((addr >> (sizeof(T) - cntr - 1)*8) & 0xFF);
}

template<typename T> concept Container = std::is_same_v<T, std::vector<ip_field_t>>
                                      || std::is_same_v<T, std::list<ip_field_t>>;

template<Container T> generator<ip_field_t> process(const T& addr)
{
    for(const auto it:addr)
        co_yield it;
}

template<typename T> void print(const T& var, std::size_t size)
{
    using std::cout;
    std::size_t cntr = 0;
    for(const auto it:print_ip_helpers::process(var))
    {
        cout << (int)it;
        if(cntr++ < size - 1)
            cout << '.';
    }
    cout << '\n';
}

}

/// \brief Prints \a addr as is
void print_ip(const std::string& addr)
{
    std::cout << addr << '\n';
}

/// \brief   Prints \a addr like it's an ip address
/// \details If \a T is an integer, prints addr's bytes in reverse order, e.g. starting from
///          higher byte, separated by dots.
template<print_ip_helpers::Integer T> void print_ip(const T& addr)
{
    print_ip_helpers::print(addr, sizeof(T));
}

/// \brief   Prints \a addr like it's an ip address
/// \details If \a T is std::vector<ip_field_t> or std::list<ip_field_t>, where \a t is an integer,
///          prints elements of \a T one by one, separated by dots.
template<print_ip_helpers::Container T> void print_ip(const T& addr)
{
    print_ip_helpers::print(addr, addr.size());
}

}
