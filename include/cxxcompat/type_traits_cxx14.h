// Copyright (c) 2009-2013 by the contributors listed in CREDITS.TXT:
// http://llvm.org/svn/llvm-project/libcxx/trunk/CREDITS.TXT
//
// Use, modification, and distribution is subject to the LLVM Software
// License. (See accompanying file licenses/LLVM.txt)

# pragma once

namespace std
{
# if !(LIBCXX_GTE_(3,4,0) && _LIBCPP_STD_VER > 11)
// libcxx change: http://llvm.org/viewvc/llvm-project/libcxx/trunk/include/type_traits?r1=181935&r2=185597
#  if CXXCOMPAT_HAS_ALIAS_TEMPLATES
	// const-volatile modifications:
	template <class T>
	using remove_const_t    = typename remove_const<T>::type;
	template <class T>
	using remove_volatile_t = typename remove_volatile<T>::type;
	template <class T>
	using remove_cv_t       = typename remove_cv<T>::type;
	template <class T>
	using add_const_t       = typename add_const<T>::type;
	template <class T>
	using add_volatile_t    = typename add_volatile<T>::type;
	template <class T>
	using add_cv_t          = typename add_cv<T>::type;

	// reference modifications:
	template <class T>
	using remove_reference_t     = typename remove_reference<T>::type;
	template <class T>
	using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
	template <class T>
	using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

	// sign modifications:
	template <class T>
	using make_signed_t   = typename make_signed<T>::type;
	template <class T>
	using make_unsigned_t = typename make_unsigned<T>::type;

	// array modifications:
	template <class T>
	using remove_extent_t      = typename remove_extent<T>::type;
	template <class T>
	using remove_all_extents_t = typename remove_all_extents<T>::type;

	// pointer modifications:
	template <class T>
	using remove_pointer_t = typename remove_pointer<T>::type;
	template <class T>
	using add_pointer_t    = typename add_pointer<T>::type;

# if LIBSTDCXX
#  define DEFAULT_ALIGNMENT(_Len) alignof(typename __aligned_storage_msa<_Len>::__type)
# elif LIBCXX
#  define DEFAULT_ALIGNMENT(_Len) __find_max_align<__all_types, _Len>::value
# endif
	// other transformations:
# ifdef DEFAULT_ALIGNMENT
	template <size_t Len, std::size_t Align=DEFAULT_ALIGNMENT(Len)>
	using aligned_storage_t = typename aligned_storage<Len,Align>::type;
#  undef DEFAULT_ALIGNMENT
# endif
# if !(defined LIBSTDCXX)
	template <std::size_t Len, class... Types>
	using aligned_union_t   = typename aligned_union<Len,Types...>::type;
# endif
	template <class T>
	using decay_t           = typename decay<T>::type;
	template <bool b, class T=void>
	using enable_if_t       = typename enable_if<b,T>::type;
	template <bool b, class T, class F>
	using conditional_t     = typename conditional<b,T,F>::type;
	template <class... T>
	using common_type_t     = typename common_type<T...>::type;
	template <class T>
	using underlying_type_t = typename underlying_type<T>::type;
	template <class F, class... ArgTypes>
	using result_of_t       = typename result_of<F(ArgTypes...)>::type;
#  endif
# endif
}
