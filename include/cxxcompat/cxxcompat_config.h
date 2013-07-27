#pragma once

# ifndef __has_feature
#  define __has_feature(x) 0
# endif

# if defined __clang__
#  define CLANG_VER (__clang_major__ * 10000) + (__clang_minor__ * 100) + __clang_patchlevel__
# elif defined __GNUC__
#  define GCC_VER (__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__
# endif

# define CLANG(x, y, z) (CLANG_VER && CLANG_VER >= ((x * 10000) + (y * 100) + z))
# define GCC(x, y, z)   (GCC_VER   && GCC_VER   >= ((x * 10000) + (y * 100) + z))

# if __has_feature(cxx_alias_templates) || GCC(4,7,0)
#  define CXXCOMPAT_HAS_ALIAS_TEMPLATES 1
# else
#  define CXXCOMPAT_HAS_ALIAS_TEMPLATES 0
# endif

# if __has_feature(cxx_rvalue_references) || GCC(4,8,1)
#  define CXXCOMPAT_HAS_THIS_RVALUE_REFS 1
# else
#  define CXXCOMPAT_HAS_THIS_RVALUE_REFS 0
# endif
