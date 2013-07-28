// http://creativecommons.org/publicdomain/zero/1.0/

#include <cxxcompat/memory>
#include <vector>
#include <string>
#include <cassert>

struct caller {
    template <class T> caller(T fun) { fun(); }
};
# define CAT2(X, Y) X ## Y
# define CAT(X, Y) CAT2(X, Y)
# define TEST(NAME) caller CAT(__VAR, __LINE__) = []

TEST(single)
{
	{
		auto a = std::make_unique<std::vector<int>>();
		assert (bool(a));
		assert (a->size() == 0);
	}

	{
		auto a = std::make_unique<std::vector<int>>(5);
		assert (bool(a));
		assert (a->size() == 5);
	}

	{
		auto a = std::make_unique<std::vector<int>>(std::initializer_list<int>{1, 2, 3, 4});
		assert (bool(a));
		assert (a->size() == 4);
	}

	{
		auto a = std::make_unique<std::string>("hello");
		assert (bool(a));
		assert (a->size() == 5);
	}
};

TEST(array)
{
	{
		auto a = std::make_unique<int[]>(6);
		for (int i = 0; i < 6; ++i)
			assert (a[i] == 0);
	}
};

int main() {}
