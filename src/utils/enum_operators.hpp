#pragma once
#include "core/defines.hpp"
#include <cstdint>
#include <type_traits>
#include <utility>

BF_BEGIN_NAMESPACE

template<typename E>
struct IsEnumFlag: std::false_type {};

template<typename E>
concept EnumFlag = IsEnumFlag<E>::value;

template<EnumFlag E>
[[nodiscard]] constexpr E operator|(E lhs, E rhs)
{
	return static_cast<E>(std::to_underlying(lhs) | std::to_underlying(rhs));
}

template<EnumFlag E>
[[nodiscard]] constexpr E operator&(E lhs, E rhs)
{
	return static_cast<E>(std::to_underlying(lhs) & std::to_underlying(rhs));
}

template<EnumFlag E>
[[nodiscard]] constexpr std::underlying_type_t<E> operator&(E lhs, uint32_t rhs)
{
	return std::to_underlying(lhs) & rhs;
}

BF_END_NAMESPACE
