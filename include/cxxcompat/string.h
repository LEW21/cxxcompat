// http://creativecommons.org/publicdomain/zero/1.0/

# pragma once

# include <string>
# include "cxxcompat_config.h"

// We unfortunately cannot support the correct suffixes as they're reserved.
// We define _-prefixed suffixes in a custom namespace, that can be used instead.
namespace std14
{
	using namespace std;

# if CXXCOMPAT_HAS_USER_LITERALS
	inline namespace literals
	{
		inline namespace string_literals
		{
			// 21.7, suffix for basic_string literals:
			inline string operator "" _s(const char *str, size_t len) {return string(str, len);}
			inline u16string operator "" _s(const char16_t *str, size_t len) {return u16string(str, len);}
			inline u32string operator "" _s(const char32_t *str, size_t len) {return u32string(str, len);}
			inline wstring operator "" _s(const wchar_t *str, size_t len) {return wstring(str, len);}
		}
	}
# endif
}
