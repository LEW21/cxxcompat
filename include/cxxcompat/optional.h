// Copyright (C) 2011 - 2012 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file licenses/Boost.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// The idea and interface is based on Boost.Optional library
// authored by Fernando Luis Cacciola Carballal

# pragma once

# include "cxxcompat_config.h"

# include <utility>
# include <cxxcompat/type_traits>
# include <initializer_list>
# include <cassert>
# include <functional>
# include <string>
# include <stdexcept>

# define REQUIRES(...) typename enable_if<__VA_ARGS__::value, bool>::type = false

namespace std
{
	// 20.6.4, optional for object types
	template <class T> class optional;


	// workaround: std utility functions aren't constexpr yet
	template <class T> inline constexpr T&& constexpr_forward(typename std::remove_reference<T>::type& t) noexcept
	{
		return static_cast<T&&>(t);
	}

	template <class T> inline constexpr T&& constexpr_forward(typename std::remove_reference<T>::type&& t) noexcept
	{
		static_assert(!std::is_lvalue_reference<T>::value, "!!");
		return static_cast<T&&>(t);
	}

	template <class T> inline constexpr typename std::remove_reference<T>::type&& constexpr_move(T&& t) noexcept
	{
		return static_cast<typename std::remove_reference<T>::type&&>(t);
	}

	template<class _Ty> inline constexpr _Ty * constexpr_addressof(_Ty& _Val)
	{
		return ((_Ty *) &(char&)_Val);
	}

	# if defined NDEBUG
	#  define ASSERTED_EXPRESSION(CHECK, EXPR) (EXPR)
	# else
	#  define ASSERTED_EXPRESSION(CHECK, EXPR) ((CHECK) ? (EXPR) : (fail(#CHECK, __FILE__, __LINE__), (EXPR)))
		inline void fail(const char* expr, const char* file, unsigned line)
		{
		# if defined __clang__ || defined __GNU_LIBRARY__
			__assert(expr, file, line);
		# elif defined __GNUC__
			_assert(expr, file, line);
		# else
		#	 error UNSUPPORTED COMPILER
		# endif
		}
	# endif


	template <typename T>
	struct has_overloaded_addressof
	{
		template <class X>
		static constexpr bool has_overload(...) { return false; }

		template <class X, size_t S = sizeof(std::declval< X&>().operator&()) >
		static constexpr bool has_overload(bool) { return true; }

		constexpr static bool value = has_overload<T>(true);
	};



	template <typename T, REQUIRES(!has_overloaded_addressof<T>)>
	constexpr T* static_addressof(T& ref)
	{
		return &ref;
	}

	template <typename T, REQUIRES(has_overloaded_addressof<T>)>
	T* static_addressof(T& ref)
	{
		return std::addressof(ref);
	}



	template <class U>
	struct is_not_optional
	{
		constexpr static bool value = true;
	};

	template <class T>
	struct is_not_optional<optional<T>>
	{
		constexpr static bool value = false;
	};


	constexpr struct trivial_init_t{} trivial_init{};


	// 20.6.5, In-place construction
	struct in_place_t{};
	constexpr in_place_t in_place{};


	// 20.6.6, Disengaged state indicator
	struct nullopt_t
	{
		struct init{};
		constexpr nullopt_t(init){};
	};
	constexpr nullopt_t nullopt{nullopt_t::init{}};


	// 20.6.7, class bad_optional_access
	class bad_optional_access : public logic_error {
	public:
		explicit bad_optional_access(const string& what_arg) : logic_error{what_arg} {}
		explicit bad_optional_access(const char* what_arg) : logic_error{what_arg} {}
	};


	template <class T>
	union storage_t
	{
		unsigned char dummy_;
		T value_;

		constexpr storage_t( trivial_init_t ) noexcept : dummy_() {};

		template <class... Args>
		constexpr storage_t( Args&&... args ) : value_(constexpr_forward<Args>(args)...) {}

		~storage_t(){}
	};


	template <class T>
	union constexpr_storage_t
	{
		unsigned char dummy_;
		T value_;

		constexpr constexpr_storage_t( trivial_init_t ) noexcept : dummy_() {};

		template <class... Args>
		constexpr constexpr_storage_t( Args&&... args ) : value_(constexpr_forward<Args>(args)...) {}

		~constexpr_storage_t() = default;
	};


	constexpr struct only_set_initialized_t{} only_set_initialized{};


	template <class T>
	struct optional_base
	{
		bool init_;
		storage_t<T> storage_;

		constexpr optional_base() noexcept : init_(false), storage_(trivial_init) {};

		constexpr explicit optional_base(only_set_initialized_t, bool init) noexcept : init_(init), storage_(trivial_init) {};

		explicit constexpr optional_base(const T& v) : init_(true), storage_(v) {}

		explicit constexpr optional_base(T&& v) : init_(true), storage_(constexpr_move(v)) {}

		template <class... Args> explicit optional_base(in_place_t, Args&&... args)
				: init_(true), storage_(constexpr_forward<Args>(args)...) {}

		template <class U, class... Args, REQUIRES(is_constructible<T, std::initializer_list<U>>)>
		explicit optional_base(in_place_t, std::initializer_list<U> il, Args&&... args)
				: init_(true), storage_(il, std::forward<Args>(args)...) {}

		~optional_base() { if (init_) storage_.value_.T::~T(); }
	};


	template <class T>
	struct constexpr_optional_base
	{
		bool init_;
		constexpr_storage_t<T> storage_;

		constexpr constexpr_optional_base() noexcept : init_(false), storage_(trivial_init) {};

		constexpr explicit constexpr_optional_base(only_set_initialized_t, bool init) noexcept : init_(init), storage_(trivial_init) {};

		explicit constexpr constexpr_optional_base(const T& v) : init_(true), storage_(v) {}

		explicit constexpr constexpr_optional_base(T&& v) : init_(true), storage_(constexpr_move(v)) {}

		template <class... Args> explicit constexpr constexpr_optional_base(in_place_t, Args&&... args)
			: init_(true), storage_(constexpr_forward<Args>(args)...) {}

		template <class U, class... Args, REQUIRES(is_constructible<T, std::initializer_list<U>>)>
		explicit constexpr_optional_base(in_place_t, std::initializer_list<U> il, Args&&... args)
			: init_(true), storage_(il, std::forward<Args>(args)...) {}

		~constexpr_optional_base() = default;
	};

	# if CXXCOMPAT_HAS_ALIAS_TEMPLATES
	template <class T>
	using OptionalBase = typename std::conditional<
		std::is_trivially_destructible<T>::value,
		constexpr_optional_base<T>,
		optional_base<T>
	>::type;
	# else
		# define OptionalBase optional_base
	# endif

	template <class T>
	class optional : private OptionalBase<T>
	{
		static_assert( !std::is_same<typename std::decay<T>::type, nullopt_t>::value, "bad T" );
		static_assert( !std::is_same<typename std::decay<T>::type, in_place_t>::value, "bad T" );


		constexpr bool initialized() const noexcept { return OptionalBase<T>::init_; }
		T* dataptr() {	return std::addressof(OptionalBase<T>::storage_.value_); }
		constexpr const T* dataptr() const { return static_addressof(OptionalBase<T>::storage_.value_); }

	# if CXXCOMPAT_HAS_THIS_RVALUE_REFS
		constexpr const T& contained_val() const& { return OptionalBase<T>::storage_.value_; }
		T& contained_val() & { return OptionalBase<T>::storage_.value_; }
		T&& contained_val() && { return std::move(OptionalBase<T>::storage_.value_); }
	# else
		constexpr const T& contained_val() const { return OptionalBase<T>::storage_.value_; }
		T& contained_val() { return OptionalBase<T>::storage_.value_; }
	# endif

		void clear() noexcept {
			if (initialized()) dataptr()->T::~T();
			OptionalBase<T>::init_ = false;
		}

		template <class... Args>
		void initialize(Args&&... args) noexcept(noexcept(T(std::forward<Args>(args)...)))
		{
			assert(!OptionalBase<T>::init_);
			new (dataptr()) T(std::forward<Args>(args)...);
			OptionalBase<T>::init_ = true;
		}

		template <class U, class... Args>
		void initialize(std::initializer_list<U> il, Args&&... args) noexcept(noexcept(T(il, std::forward<Args>(args)...)))
		{
			assert(!OptionalBase<T>::init_);
			new (dataptr()) T(il, std::forward<Args>(args)...);
			OptionalBase<T>::init_ = true;
		}

	public:
		typedef T value_type;

		// 20.6.5.1, constructors
		constexpr optional() noexcept : OptionalBase<T>()	{};
		constexpr optional(nullopt_t) noexcept : OptionalBase<T>() {};

		optional(const optional& rhs)
		: OptionalBase<T>(only_set_initialized, rhs.initialized())
		{
			if (rhs.initialized()) new (dataptr()) T(*rhs);
		}

		optional(optional&& rhs) noexcept(std::is_nothrow_move_constructible<T>::value)
		: OptionalBase<T>(only_set_initialized, rhs.initialized())
		{
			if (rhs.initialized()) new (dataptr()) T(std::move(*rhs));
		}

		constexpr optional(const T& v) : OptionalBase<T>(v) {}

		constexpr optional(T&& v) : OptionalBase<T>(constexpr_move(v)) {}

		template <class... Args>
			constexpr explicit optional(in_place_t, Args&&... args)
					: OptionalBase<T>(in_place_t{}, constexpr_forward<Args>(args)...) {}

		template <class U, class... Args, REQUIRES(is_constructible<T, std::initializer_list<U>>)>
			explicit optional(in_place_t, std::initializer_list<U> il, Args&&... args)
					: OptionalBase<T>(in_place_t{}, il, constexpr_forward<Args>(args)...) {}

		// 20.6.4.2 Destructor
		~optional() = default;

		// 20.6.4.3, assignment
		optional& operator=(nullopt_t) noexcept
		{
			clear();
			return *this;
		}

		optional& operator=(const optional& rhs)
		{
			if			(initialized() == true	&& rhs.initialized() == false) clear();
			else if (initialized() == false && rhs.initialized() == true)	initialize(*rhs);
			else if (initialized() == true	&& rhs.initialized() == true)	contained_val() = *rhs;
			return *this;
		}

		optional& operator=(optional&& rhs)
		noexcept(std::is_nothrow_move_assignable<T>::value && std::is_nothrow_move_constructible<T>::value)
		{
			if			(initialized() == true	&& rhs.initialized() == false) clear();
			else if (initialized() == false && rhs.initialized() == true)	initialize(std::move(*rhs));
			else if (initialized() == true	&& rhs.initialized() == true)	contained_val() = std::move(*rhs);
			return *this;
		}

		template <class U>
		auto operator=(U&& v)
		-> typename enable_if
		<
			is_same<typename remove_reference<U>::type, T>::value,
			optional&
		>::type
		{
			if (initialized()) { contained_val() = std::forward<U>(v); }
			else							 { initialize(std::forward<U>(v));	}
			return *this;
		}


		template <class... Args>
		void emplace(Args&&... args)
		{
			clear();
			initialize(std::forward<Args>(args)...);
		}

		template <class U, class... Args>
		void emplace(initializer_list<U> il, Args&&... args)
		{
			clear();
			initialize<U, Args...>(il, std::forward<Args>(args)...);
		}

		// 20.6.4.4 Swap
		void swap(optional<T>& rhs) noexcept(is_nothrow_move_constructible<T>::value && noexcept(swap(declval<T&>(), declval<T&>())))
		{
			if      (initialized() == true  && rhs.initialized() == false) { rhs.initialize(std::move(**this)); clear(); }
			else if (initialized() == false && rhs.initialized() == true)  { initialize(std::move(*rhs)); rhs.clear(); }
			else if (initialized() == true  && rhs.initialized() == true)  { using std::swap; swap(**this, *rhs); }
		}

		// 20.6.4.5 Observers
		constexpr T const* operator ->() const {
			return ASSERTED_EXPRESSION(initialized(), dataptr());
		}

		T* operator ->() {
			assert (initialized());
			return dataptr();
		}

		constexpr T const& operator *() const {
			return ASSERTED_EXPRESSION(initialized(), contained_val());
		}

		T& operator *() {
			assert (initialized());
			return contained_val();
		}

		constexpr explicit operator bool() const noexcept { return initialized(); }

		constexpr T const& value() const {
			return initialized() ? contained_val() : (throw bad_optional_access("bad optional access"), contained_val());
		}

		T& value() {
			return initialized() ? contained_val() : (throw bad_optional_access("bad optional access"), contained_val());
		}

	# if CXXCOMPAT_HAS_THIS_RVALUE_REFS
		template <class V>
		constexpr T value_or(V&& v) const&
		{
			return *this ? **this : static_cast<T>(constexpr_forward<V>(v));
		}

		template <class V>
		T value_or(V&& v) &&
		{
			return *this ? std::move(const_cast<optional<T>&>(*this).contained_val()) : static_cast<T>(constexpr_forward<V>(v));
		}
	# else
		template <class V>
		constexpr T value_or(V&& v) const
		{
			return *this ? **this : static_cast<T>(constexpr_forward<V>(v));
		}
	# endif

	};


	// 20.6.8, Relational operators
	template <class T> constexpr bool operator==(const optional<T>& x, const optional<T>& y)
	{
		return bool(x) != bool(y) ? false : bool(x) == false ? true : *x == *y;
	}

	template <class T> constexpr bool operator!=(const optional<T>& x, const optional<T>& y)
	{
		return !(x == y);
	}

	template <class T> constexpr bool operator<(const optional<T>& x, const optional<T>& y)
	{
		return (!y) ? false : (!x) ? true : *x < *y;
	}

	template <class T> constexpr bool operator>(const optional<T>& x, const optional<T>& y)
	{
		return (y < x);
	}

	template <class T> constexpr bool operator<=(const optional<T>& x, const optional<T>& y)
	{
		return !(y < x);
	}

	template <class T> constexpr bool operator>=(const optional<T>& x, const optional<T>& y)
	{
		return !(x < y);
	}


	// 20.6.9 Comparison with nullopt
	template <class T> constexpr bool operator==(const optional<T>& x, nullopt_t) noexcept
	{
		return (!x);
	}

	template <class T> constexpr bool operator==(nullopt_t, const optional<T>& x) noexcept
	{
		return (!x);
	}

	template <class T> constexpr bool operator!=(const optional<T>& x, nullopt_t) noexcept
	{
		return bool(x);
	}

	template <class T> constexpr bool operator!=(nullopt_t, const optional<T>& x) noexcept
	{
		return bool(x);
	}

	template <class T> constexpr bool operator<(const optional<T>&, nullopt_t) noexcept
	{
		return false;
	}

	template <class T> constexpr bool operator<(nullopt_t, const optional<T>& x) noexcept
	{
		return bool(x);
	}

	template <class T> constexpr bool operator<=(const optional<T>& x, nullopt_t) noexcept
	{
		return (!x);
	}

	template <class T> constexpr bool operator<=(nullopt_t, const optional<T>&) noexcept
	{
		return true;
	}

	template <class T> constexpr bool operator>(const optional<T>& x, nullopt_t) noexcept
	{
		return bool(x);
	}

	template <class T> constexpr bool operator>(nullopt_t, const optional<T>&) noexcept
	{
		return false;
	}

	template <class T> constexpr bool operator>=(const optional<T>&, nullopt_t) noexcept
	{
		return true;
	}

	template <class T> constexpr bool operator>=(nullopt_t, const optional<T>& x) noexcept
	{
		return (!x);
	}



	// 20.6.10, Comparison with T
	template <class T> constexpr bool operator==(const optional<T>& x, const T& v)
	{
		return bool(x) ? *x == v : false;
	}

	template <class T> constexpr bool operator==(const T& v, const optional<T>& x)
	{
		return bool(x) ? v == *x : false;
	}

	template <class T> constexpr bool operator!=(const optional<T>& x, const T& v)
	{
		return bool(x) ? *x != v : true;
	}

	template <class T> constexpr bool operator!=(const T& v, const optional<T>& x)
	{
		return bool(x) ? v != *x : true;
	}

	template <class T> constexpr bool operator<(const optional<T>& x, const T& v)
	{
		return bool(x) ? *x < v : true;
	}

	template <class T> constexpr bool operator>(const T& v, const optional<T>& x)
	{
		return bool(x) ? v > *x : true;
	}

	template <class T> constexpr bool operator>(const optional<T>& x, const T& v)
	{
		return bool(x) ? *x > v : false;
	}

	template <class T> constexpr bool operator<(const T& v, const optional<T>& x)
	{
		return bool(x) ? v < *x : false;
	}

	template <class T> constexpr bool operator>=(const optional<T>& x, const T& v)
	{
		return bool(x) ? *x >= v : false;
	}

	template <class T> constexpr bool operator<=(const T& v, const optional<T>& x)
	{
		return bool(x) ? v <= *x : false;
	}

	template <class T> constexpr bool operator<=(const optional<T>& x, const T& v)
	{
		return bool(x) ? *x <= v : true;
	}

	template <class T> constexpr bool operator>=(const T& v, const optional<T>& x)
	{
		return bool(x) ? v >= *x : true;
	}


	// 20.6.12 Specialized algorithms
	template <class T>
	void swap(optional<T>& x, optional<T>& y) noexcept(noexcept(x.swap(y)))
	{
		x.swap(y);
	}


	template <class T>
	constexpr optional<typename decay<T>::type> make_optional(T&& v)
	{
		return optional<typename decay<T>::type>(constexpr_forward<T>(v));
	}

	template <class X>
	constexpr optional<X&> make_optional(reference_wrapper<X> v)
	{
		return optional<X&>(v.get());
	}

	template <typename T>
	struct hash<std::optional<T>>
	{
		typedef typename hash<T>::result_type result_type;
		typedef std::optional<T> argument_type;

		constexpr result_type operator()(argument_type const& arg) const {
			return arg ? std::hash<T>{}(*arg) : result_type{};
		}
	};
}

# ifdef OptionalBase
	# undef OptionalBase
# endif
