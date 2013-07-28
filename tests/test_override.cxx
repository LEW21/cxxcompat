// http://creativecommons.org/publicdomain/zero/1.0/

#include <cxxcompat/override>

class Base
{
	virtual void awesome();
};

class Derived: Base
{
	void awesome() override;
};

int main() {}
