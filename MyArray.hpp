#ifndef _MYARRAY_HPP_
#define _MYARRAY_HPP_

#include <Windows.h>
#include <iostream>
#include <string>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <span>
#include <utility>

class MyArray
{
public:
	explicit MyArray(size_t size);
	explicit MyArray(std::initializer_list<int> list);

	MyArray(const MyArray& originalArray);
	MyArray& operator= (const MyArray& originalArray);

	MyArray(MyArray&& originalArray) noexcept;
	MyArray& operator= (MyArray&& originalArray) noexcept;

	size_t size() const noexcept;
	~MyArray();

private:
	std::unique_ptr<int[]> ptr;
	size_t arrSize;
	void swap(MyArray &first, MyArray &second) noexcept;
};

#endif // !_MYARRAY_HPP_
