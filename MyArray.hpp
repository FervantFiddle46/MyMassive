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
#include <sstream>

class MyArray
{
public:
	explicit MyArray(size_t size);
	explicit MyArray(std::initializer_list<int> list);

	MyArray(const MyArray& originalArray);
	MyArray& operator= (const MyArray& originalArray);

	MyArray(MyArray&& originalArray) noexcept;
	MyArray& operator= (MyArray&& originalArray) noexcept;

	std::string toString() const;

	bool operator== (const MyArray& originalArray) const noexcept;
	explicit operator bool() const noexcept;

	int& operator[](size_t index);
	const int& operator[](size_t index) const;

	MyArray& operator++();
	MyArray operator++(int);
	MyArray& operator+=(int value);

	size_t size() const noexcept;
	~MyArray();

private:
	std::unique_ptr<int[]> ptr;
	size_t arrSize;
	void swap(MyArray &first, MyArray &second) noexcept;

	friend std::istream& operator>> (std::istream& in, MyArray& obj);
};

std::ostream& operator<<(std::ostream &out, const MyArray& obj)
{
	out << obj.toString();
	return out;
}

#endif // !_MYARRAY_HPP_
