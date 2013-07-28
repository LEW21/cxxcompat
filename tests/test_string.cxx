// http://creativecommons.org/publicdomain/zero/1.0/

#include <cxxcompat/string>
#include <cassert>

# if CXXCOMPAT_HAS_USER_LITERALS
using namespace std14::literals;
# endif

struct caller {
    template <class T> caller(T fun) { fun(); }
};
# define CAT2(X, Y) X ## Y
# define CAT(X, Y) CAT2(X, Y)
# define TEST(NAME) caller CAT(__VAR, __LINE__) = []

# if CXXCOMPAT_HAS_USER_LITERALS
TEST(literals)
{
	{
		auto a = "hello"_s;
		assert(a.size() == 5);
		assert(a == "hello");
		assert(a == "hello"_s);
	}

	{
		auto a = L"hello"_s;
		assert(a.size() == 5);
		assert(a == L"hello");
		assert(a == L"hello"_s);
	}

	{
		auto a = u"hello"_s;
		assert(a.size() == 5);
		assert(a == u"hello");
		assert(a == u"hello"_s);
	}

	{
		auto a = U"hello"_s;
		assert(a.size() == 5);
		assert(a == U"hello");
		assert(a == U"hello"_s);
	}
};
# endif

int main() {}
