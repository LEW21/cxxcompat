// http://creativecommons.org/publicdomain/zero/1.0/

# pragma once

# include <chrono>
# include "cxxcompat_config.h"

// We unfortunately cannot support the correct suffixes as they're reserved.
// We define _-prefixed suffixes in a custom namespace, that can be used instead.
namespace std14
{
	using namespace std;

# if CXXCOMPAT_HAS_USER_LITERALS
	inline namespace literals
	{
		inline namespace chrono_literals
		{
			// 20.13.5.8, suffixes for duration literals
			constexpr chrono::hours                                operator "" _h(unsigned long long h)   { return chrono::hours{h}; }
			constexpr chrono::duration<long double, ratio<3600,1>> operator "" _h(long double h)          { return chrono::duration<long double, ratio<3600,1>>{h}; }
			constexpr chrono::minutes                              operator "" _min(unsigned long long m) { return chrono::minutes{m}; }
			constexpr chrono::duration<long double, ratio<60,1>>   operator "" _min(long double m)        { return chrono::duration<long double, ratio<60,1>>{m}; }
			constexpr chrono::seconds                              operator "" _s(unsigned long long s)   { return chrono::seconds{s}; }
			constexpr chrono::duration<long double>                operator "" _s(long double s)          { return chrono::duration<long double>{s}; }
			constexpr chrono::milliseconds                         operator "" _ms(unsigned long long ms) { return chrono::milliseconds{ms}; }
			constexpr chrono::duration<long double, milli>         operator "" _ms(long double ms)        { return chrono::duration<long double, milli>{ms}; }
			constexpr chrono::microseconds                         operator "" _us(unsigned long long us) { return chrono::microseconds{us}; }
			constexpr chrono::duration<long double, micro>         operator "" _us(long double us)        { return chrono::duration<long double, micro>{us}; }
			constexpr chrono::nanoseconds                          operator "" _ns(unsigned long long ns) { return chrono::nanoseconds{ns}; }
			constexpr chrono::duration<long double, nano>          operator "" _ns(long double ns)        { return chrono::duration<long double, nano>{ns}; }
		}
	}
# endif
}
