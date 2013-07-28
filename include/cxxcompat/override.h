// http://creativecommons.org/publicdomain/zero/1.0/

# pragma once

# include "cxxcompat_config.h"

# if CLANG_LT_(3,0,0) || GCC_LT_(4,7,0)
// It's impossible to get override-checking in the compiler,
// so at least stop it from screaming.
#  ifndef override
#   define override
#  endif
# endif
