// http://creativecommons.org/publicdomain/zero/1.0/

#pragma once

#include <exception>
// Why? We need any Standard Library's header, to be able to determine its version.
// And this is one of the most basic ones.

# ifndef __has_feature
#  define __has_feature(x) 0
# endif

# if defined __clang__
#  define CLANG (__clang_major__ * 10000) + (__clang_minor__ * 100) + __clang_patchlevel__
# elif defined __GNUC__
#  define GCC (__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__
# endif

# if defined __GLIBCXX__
#  if !(defined LIBSTDCXX)
#   if defined GCC
#    define LIBSTDCXX GCC
#   else
#    warning You should provide libstdc++ version by defining LIBSTDCXX. Assuming newest existing...
#    define LIBSTDCXX 99999
#   endif
#  endif
# else
#  undef LIBSTDCXX
# endif

# if defined _LIBCPP_VERSION
#  if !(defined LIBCXX)
#   if defined CLANG
#    define LIBCXX CLANG
#   else // TODO determine version using _LIBCPP_VERSION... No idea what 1101 means...
#    warning You need to provide libc++ version by defining LIBCXX. Assuming newest existing...
#    define LIBCXX 99999
#   endif
#  endif
# else
#  undef LIBCXX
# endif

# if (defined LIBSTDCXX) && (defined LIBCXX)
#  error You have achieved the impossible - mixed libstdc++ and libc++ in some way...
# elif !(defined LIBSTDCXX) && !(defined LIBCXX)
#  error libstdc++ or libc++ required.
# endif

# define VERSION_GTE_(VER, x,y,z) (VER && VER >= ((x * 10000) + (y * 100) + z))
# define VERSION_GT_(VER,  x,y,z) (VER && VER >  ((x * 10000) + (y * 100) + z))
# define VERSION_LTE_(VER, x,y,z) (VER && VER <= ((x * 10000) + (y * 100) + z))
# define VERSION_LT_(VER,  x,y,z) (VER && VER <  ((x * 10000) + (y * 100) + z))
# define VERSION_E_(VER,   x,y,z) (VER && VER =  ((x * 10000) + (y * 100) + z))
# define VERSION_NE_(VER,  x,y,z) (VER && VER != ((x * 10000) + (y * 100) + z))

# define GCC_GTE_(x,y,z) VERSION_GTE_(GCC, x,y,z)
# define GCC_GT_(x,y,z)  VERSION_GT_ (GCC, x,y,z)
# define GCC_LTE_(x,y,z) VERSION_LTE_(GCC, x,y,z)
# define GCC_LT_(x,y,z)  VERSION_LT_ (GCC, x,y,z)
# define GCC_E_(x,y,z)   VERSION_E_  (GCC, x,y,z)
# define GCC_NE_(x,y,z)  VERSION_NE_ (GCC, x,y,z)

# define CLANG_GTE_(x,y,z) VERSION_GTE_(CLANG, x,y,z)
# define CLANG_GT_(x,y,z)  VERSION_GT_ (CLANG, x,y,z)
# define CLANG_LTE_(x,y,z) VERSION_LTE_(CLANG, x,y,z)
# define CLANG_LT_(x,y,z)  VERSION_LT_ (CLANG, x,y,z)
# define CLANG_E_(x,y,z)   VERSION_E_  (CLANG, x,y,z)
# define CLANG_NE_(x,y,z)  VERSION_NE_ (CLANG, x,y,z)

# define LIBSTDCXX_GTE_(x,y,z) VERSION_GTE_(LIBSTDCXX, x,y,z)
# define LIBSTDCXX_GT_(x,y,z)  VERSION_GT_ (LIBSTDCXX, x,y,z)
# define LIBSTDCXX_LTE_(x,y,z) VERSION_LTE_(LIBSTDCXX, x,y,z)
# define LIBSTDCXX_LT_(x,y,z)  VERSION_LT_ (LIBSTDCXX, x,y,z)
# define LIBSTDCXX_E_(x,y,z)   VERSION_E_  (LIBSTDCXX, x,y,z)
# define LIBSTDCXX_NE_(x,y,z)  VERSION_NE_ (LIBSTDCXX, x,y,z)

# define LIBCXX_GTE_(x,y,z) VERSION_GTE_(LIBCXX, x,y,z)
# define LIBCXX_GT_(x,y,z)  VERSION_GT_ (LIBCXX, x,y,z)
# define LIBCXX_LTE_(x,y,z) VERSION_LTE_(LIBCXX, x,y,z)
# define LIBCXX_LT_(x,y,z)  VERSION_LT_ (LIBCXX, x,y,z)
# define LIBCXX_E_(x,y,z)   VERSION_E_  (LIBCXX, x,y,z)
# define LIBCXX_NE_(x,y,z)  VERSION_NE_ (LIBCXX, x,y,z)

# if __has_feature(cxx_alias_templates) || GCC_GTE_(4,7,0)
#  define CXXCOMPAT_HAS_ALIAS_TEMPLATES 1
# else
#  define CXXCOMPAT_HAS_ALIAS_TEMPLATES 0
# endif

# if __has_feature(cxx_nonstatic_member_init) || GCC_GTE_(4,7,0)
#  define CXXCOMPAT_HAS_NONSTATC_MEMBER_INIT 1
# else
#  define CXXCOMPAT_HAS_NONSTATC_MEMBER_INIT 0
# endif

# if __has_feature(cxx_rvalue_references) || GCC_GTE_(4,8,1)
#  define CXXCOMPAT_HAS_THIS_RVALUE_REFS 1
# else
#  define CXXCOMPAT_HAS_THIS_RVALUE_REFS 0
# endif
