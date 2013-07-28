// Copyright (C) 2011 - 2012 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file licenses/Boost.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

# pragma once

# include <type_traits>
# include "cxxcompat_config.h"

namespace std
{
# if LIBSTDCXX_LT_(4,8,0)
	# if CXXCOMPAT_HAS_ALIAS_TEMPLATES
		template <class T>
		using is_trivially_destructible = typename std::has_trivial_destructor<T>;
	# endif
# endif

# if LIBSTDCXX_LT_(4,7,0)
	template <class T>
	struct is_nothrow_move_constructible
	{
		constexpr static bool value = std::is_nothrow_constructible<T, T&&>::value;
	};

	template <class T, class U>
	struct is_assignable
	{
		template <class X, class Y>
		static constexpr bool has_assign(...) { return false; }

		template <class X, class Y, size_t S = sizeof(std::declval<X>() = std::declval<Y>()) >
		static constexpr bool has_assign(bool) { return true; }

		constexpr static bool value = has_assign<T, U>(true);
	};

	template <class T>
	struct is_nothrow_move_assignable
	{
		template <class X, bool has_any_move_massign>
		struct has_nothrow_move_assign {
			constexpr static bool value = false;
		};

		template <class X>
		struct has_nothrow_move_assign<X, true> {
			constexpr static bool value = noexcept( std::declval<X&>() = std::declval<X&&>() );
		};

		constexpr static bool value = has_nothrow_move_assign<T, is_assignable<T&, T&&>::value>::value;
	};
# endif
}
