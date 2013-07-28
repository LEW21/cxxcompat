// Copyright (c) 2009-2013 by the contributors listed in CREDITS.TXT:
// http://llvm.org/svn/llvm-project/libcxx/trunk/CREDITS.TXT
//
// Use, modification, and distribution is subject to the LLVM Software
// License. (See accompanying file licenses/LLVM.txt)

# pragma once

# include <memory>
# include "cxxcompat_config.h"

namespace std
{
# if !LIBCXX_GT_(3,3,0)
// libcxx change: http://llvm.org/viewvc/llvm-project/libcxx/trunk/include/memory?r1=183481&r2=185352
	template<class _Tp>
	struct __unique_if
	{
		typedef unique_ptr<_Tp> __unique_single;
	};

	template<class _Tp>
	struct __unique_if<_Tp[]>
	{
		typedef unique_ptr<_Tp[]> __unique_array_unknown_bound;
	};

	template<class _Tp, size_t _Np>
	struct __unique_if<_Tp[_Np]>
	{
		typedef void __unique_array_known_bound;
	};

	template<class _Tp, class... _Args>
	inline typename __unique_if<_Tp>::__unique_single
	make_unique(_Args&&... __args)
	{
		return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...));
	}

	template<class _Tp>
	inline typename __unique_if<_Tp>::__unique_array_unknown_bound
	make_unique(size_t __n)
	{
		typedef typename remove_extent<_Tp>::type _Up;
		return unique_ptr<_Tp>(new _Up[__n]());
	}

	template<class _Tp, class... _Args>
		typename __unique_if<_Tp>::__unique_array_known_bound
		make_unique(_Args&&...) = delete;
#endif
}
