#pragma once
#ifndef my_dynamic_array_
#define my_dynamic_array_

#include <iostream>
#include <initializer_list>

using int64 = long long;

template<class dynamic_array> class dynamic_array_const_iterator
{

public:

	using val_type = typename dynamic_array::val_type;
	using ptr_type = typename dynamic_array::const_ptr;
	using ref_type = typename dynamic_array::const_ref;

public:

	constexpr dynamic_array_const_iterator(const ptr_type ptr) :arr_ptr(ptr)
	{

	}

	constexpr dynamic_array_const_iterator& operator++() noexcept
	{
		arr_ptr++;
		return *this;
	}

	constexpr dynamic_array_const_iterator& operator--() noexcept
	{
		arr_ptr--;
		return *this;
	}

	constexpr dynamic_array_const_iterator operator++(int) noexcept
	{
		dynamic_array_const_iterator iterator = *this;
		++(*this);
		return iterator;
	}

	constexpr dynamic_array_const_iterator operator--(int) noexcept
	{
		dynamic_array_const_iterator iterator = *this;
		--(*this);
		return iterator;
	}

	constexpr ref_type operator[] (int64 index)const noexcept
	{
		return *(arr_ptr + index);
	}

	constexpr ptr_type operator->()const noexcept
	{
		return arr_ptr;
	}

	constexpr ref_type operator*()const noexcept
	{
		return *arr_ptr;
	}

	constexpr bool operator == (const dynamic_array_const_iterator& that)const
	{
		return this->arr_ptr == that.arr_ptr;
	}

	constexpr bool operator != (const dynamic_array_const_iterator& that)const
	{
		return this->arr_ptr != that.arr_ptr;
	}

private:

	ptr_type arr_ptr;

};

template<class dynamic_array> class dynamic_array_iterator
{

public:

	using val_type = typename dynamic_array::val_type;
	using ptr_type = val_type*;
	using ref_type = val_type&;

public:

	constexpr dynamic_array_iterator(const ptr_type ptr) :arr_ptr(ptr)
	{

	}

	constexpr dynamic_array_iterator& operator++() noexcept
	{
		arr_ptr++;
		return *this;
	}

	constexpr dynamic_array_iterator& operator--() noexcept
	{
		arr_ptr--;
		return *this;
	}

	constexpr dynamic_array_iterator operator++(int) noexcept
	{
		dynamic_array_iterator iterator = *this;
		++(*this);
		return iterator;
	}

	constexpr dynamic_array_iterator operator--(int) noexcept
	{
		dynamic_array_iterator iterator = *this;
		--(*this);
		return iterator;
	}

	constexpr ref_type operator[] (int64 index)noexcept
	{
		return *(arr_ptr + index);
	}

	constexpr ptr_type operator->()noexcept
	{
		return arr_ptr;
	}

	constexpr ref_type operator*()noexcept
	{
		return *arr_ptr;
	}

	constexpr bool operator == (const dynamic_array_iterator& that)const
	{
		return this->arr_ptr == that.arr_ptr;
	}

	constexpr bool operator != (const dynamic_array_iterator& that)const
	{
		return this->arr_ptr != that.arr_ptr;
	}

private:

	ptr_type arr_ptr;

};

template<class arr_type> class dynamic_array {

protected:

	arr_type* arr_ptr = nullptr;

	int64 arr_siz;
	int64 arr_cap;

	constexpr void reallocate(const int64 new_cap, const bool copy = true)noexcept
	{
		// 1. allocate a new block of memory
		// 2. copy/move old elements into new block
		// 3. delete old block of memory

		arr_type* new_ptr = new arr_type[arr_cap = new_cap];

		if (new_cap < arr_siz)
			arr_siz = new_cap;

		if (copy)
		{
			for (int64 i = 0; i < arr_siz; ++i)
			{
				*(new_ptr + i) = std::move(*(arr_ptr + i));
			}
		}

		delete[]arr_ptr;
		arr_ptr = new_ptr;
		new_ptr = nullptr;
	}

public:

	using val_type = arr_type;
	using const_ptr = typename const arr_type*;
	using const_ref = typename const arr_type&;
	using iterator = dynamic_array_iterator<dynamic_array<arr_type>>;
	using const_iterator = dynamic_array_const_iterator<dynamic_array<arr_type>>;

public:

	constexpr dynamic_array()noexcept : arr_siz(0ll), arr_cap(2ll)
	{
		arr_ptr = new arr_type[2ll];
	}

	constexpr dynamic_array(const int64 x)noexcept : arr_siz(x), arr_cap(x)
	{
		if (x < 2ll)
		{
			arr_siz = 0ll;
			arr_cap = 2ll;
		}

		arr_ptr = new arr_type[arr_cap];
	}

	constexpr dynamic_array(const int64 x, const arr_type& val) : arr_siz(x), arr_cap(x)
	{
		if (x < 2ll)
		{
			arr_siz = arr_cap = 2ll;
		}

		arr_ptr = new arr_type[arr_cap];

		for (int64 i = 0; i < arr_siz; ++i)
		{
			*(arr_ptr + i) = val;
		}
	}

	constexpr dynamic_array(const std::initializer_list<arr_type>& list)noexcept : arr_siz(arr_cap = list.size())
	{
		if (arr_cap < 2ll)
		{
			arr_cap = 2ll;
		}
		int64 index = 0; arr_ptr = new arr_type[arr_cap];

		for (const auto& x : list)
		{
			*(arr_ptr + index) = x;

			++index;
		}
	}

	constexpr dynamic_array(const dynamic_array& x)noexcept : arr_siz(x.arr_siz), arr_cap(x.arr_cap)
	{
		//std::cout << "\ncopy = constructor";
		arr_ptr = new arr_type[arr_cap];

		for (int64 i = 0; i < arr_siz; ++i)
		{
			*(arr_ptr + i) = *(x.arr_ptr + i);
		}
	}

	constexpr dynamic_array(dynamic_array&& x)noexcept
	{

		//std::cout << "\nmove constructor";

		arr_ptr = x.arr_ptr;
		arr_siz = x.arr_siz;
		arr_cap = x.arr_cap;

		x.arr_ptr = nullptr;
		x.arr_siz = 0;
		x.arr_cap = 0;
	}

	constexpr ~dynamic_array()noexcept
	{
		delete[]arr_ptr;

		arr_siz = 0ll;
		arr_cap = 0ll;
	}

	constexpr operator int64()const noexcept
	{
		return arr_siz;
	}

	constexpr operator size_t()const noexcept
	{
		return (size_t)arr_siz;
	}

	constexpr operator const std::initializer_list<arr_type>()const noexcept
	{
		return std::initializer_list<arr_type>(arr_ptr, arr_ptr + arr_siz);
	}

	constexpr dynamic_array& operator = (const int64 x)noexcept
	{
		delete[]arr_ptr; arr_siz = x; arr_cap = x;

		if (x < 2ll)
		{
			arr_siz = 0ll;
			arr_cap = 2ll;
		}

		arr_ptr = new arr_type[arr_cap];

		return *this;
	}

	constexpr dynamic_array& operator = (const dynamic_array& x)noexcept
	{
		
		if (this == &x)
		{
			return *this;
		}

		//std::cout << "\ncopy = constructor";

		if (arr_cap < x.arr_siz)
		{
			delete[]arr_ptr;

			arr_ptr = new arr_type[arr_cap = x.arr_cap];
		}

		arr_siz = x.arr_siz;

		for (int64 i = 0; i < arr_siz; ++i)
		{
			*(arr_ptr + i) = *(x.arr_ptr + i);
		}

		return *this;
	};

	constexpr dynamic_array& operator = (const std::initializer_list<arr_type>& list)noexcept
	{
		// do nothing
		return *this;
	}

	constexpr dynamic_array& operator = (dynamic_array&& x)noexcept
	{
		if (this == &x)
		{
			return *this;
		}

		//std::cout << "\nmove = constructor";

		delete[]arr_ptr;

		arr_ptr = x.arr_ptr;
		arr_siz = x.arr_siz;
		arr_cap = x.arr_cap;

		x.arr_ptr = nullptr;
		x.arr_siz = 0;
		x.arr_cap = 0;

		return *this;
	}

	constexpr void push_back(const arr_type& val)noexcept
	{
		if (arr_siz >= arr_cap)
		{
			reallocate(static_cast<int64>(1.618f * arr_cap));
		}

		*(arr_ptr + arr_siz) = val;

		++arr_siz;
	}

	constexpr void push_back(arr_type&& val)noexcept
	{
		if (arr_siz >= arr_cap)
		{
			reallocate(static_cast<int64>(1.618f * arr_cap));
		}

		*(arr_ptr + arr_siz) = std::move(val);

		++arr_siz;
	}

	constexpr void reserve(const int64 siz)
	{
		if (siz > arr_cap) reallocate(siz);
	}

	constexpr void pop_back()noexcept
	{
		if (arr_siz > 0)
		{
			--arr_siz;

			(arr_ptr + arr_siz)->~arr_type();
		}
	}

	constexpr void clear()noexcept
	{
		for (int64 i = 0; i < arr_siz; ++i)
		{
			(arr_ptr + i)->~arr_type;
		}

		arr_siz = 0;
	}

	template<class... Args> arr_type& emplace_back(Args&&... args)
	{
		if (arr_siz >= arr_cap)
		{
			reallocate(static_cast<int64>(1.618f * arr_cap));
		}

		new(arr_ptr + arr_siz) arr_type(std::forward<Args>(args)...);

		return *(arr_ptr + arr_siz++);
	}

	constexpr arr_type& operator[](const int64& x)
	{
		if (x < arr_siz) return *(arr_ptr + x);

		throw("Error");
	}

	constexpr arr_type& front()noexcept
	{
		return *arr_ptr;
	}

	constexpr arr_type& back()noexcept
	{
		return *(arr_ptr + arr_siz - 1);
	}

	constexpr const arr_type& operator[](const int64& x)const
	{
		if (x < arr_siz) return *(arr_ptr + x);

		throw("Error");
	}

	constexpr const arr_type& front()const noexcept
	{
		return *arr_ptr;
	}

	constexpr const arr_type& back()const noexcept
	{
		return *(arr_ptr + arr_siz - 1);
	}

	[[nodiscard]] constexpr arr_type* data()noexcept
	{
		return arr_ptr;
	}

	[[nodiscard]] constexpr iterator begin()noexcept
	{
		return iterator(arr_ptr);
	}

	[[nodiscard]] constexpr iterator end()noexcept
	{
		return iterator(arr_ptr + arr_siz);
	}

	[[nodiscard]] constexpr const_iterator begin()const noexcept
	{
		return const_iterator(arr_ptr);
	}

	[[nodiscard]] constexpr const_iterator end()const noexcept
	{
		return const_iterator(arr_ptr + arr_siz);
	}

	[[nodiscard]] constexpr const arr_type* data()const noexcept
	{
		return arr_ptr;
	}

	[[nodiscard]] constexpr bool operator == (const dynamic_array& x)const noexcept
	{
		if (arr_ptr == x.arr_ptr)
		{
			return true;
		}

		if (arr_siz == x.arr_siz)
		{
			for (int64 i = 0; i < arr_siz; ++i)
			{
				if (*(arr_ptr + i) != *(x.arr_ptr + i))
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	[[nodiscard]] constexpr bool operator != (const dynamic_array& x)const noexcept
	{
		if (arr_ptr == x.arr_ptr)
		{
			return false;
		}
		if (arr_siz == x.arr_siz)
		{
			for (int64 i = 0; i < arr_siz; ++i)
			{
				if (*(arr_ptr + i) != *(x.arr_ptr + i))
				{
					return true;
				}
			}
			return false;
		}

		return true;
	}

	[[nodiscard]] constexpr const int64 size()const
	{
		return arr_siz;
	}

	[[nodiscard]] constexpr const int64 capacity()const
	{
		return arr_cap;
	}

	[[nodiscard]] constexpr bool is_empty()const
	{
		return arr_siz == 0 ? true : false;
	}

	constexpr void print(const char c = ' ')const
	{
		std::cout << "\n( ";
		for (int64 i = 0; i < arr_siz; ++i)
		{
			std::cout << *(arr_ptr + i) << c;
		}
		std::cout << ")";
	}

};

template<class arr_type> std::ostream& operator << (std::ostream& cout, const dynamic_array<arr_type>& x)
{
	x.print();
	return cout;
}

inline void print_container(auto x)
{
	std::cout << std::endl;

	for (const auto& i : x)
	{
		std::cout << i << ' ';
	}
}

#endif // my_dynamic_array_




