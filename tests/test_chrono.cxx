// http://creativecommons.org/publicdomain/zero/1.0/

#include <cxxcompat/chrono>
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
		auto a = 61_s;
		auto b = 1_min;
		assert(a > b);
		a -= 2_s;
		assert(a < b);
	}

	{
		auto a = 61_min;
		auto b = 1_h;
		assert(a > b);
		a -= 2_min;
		assert(a < b);
	}
};
# endif

int main() {}
