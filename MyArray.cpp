#include "MyArray.hpp"

MyArray::MyArray(size_t size)
{
	this->arrSize = size;
	this->ptr = std::make_unique<int[]>(size);
}

MyArray::MyArray(std::initializer_list<int> list)
{
	this->arrSize = list.size();
	this->ptr = std::make_unique<int[]>(list.size());
	std::copy(std::begin(list), std::end(list), this->ptr.get());
}

MyArray::MyArray(const MyArray& originalArray)
{
	this->arrSize = originalArray.arrSize;
	this->ptr = std::make_unique<int[]>(originalArray.size());
	const std::span<const int> source{ originalArray.ptr.get(), originalArray.size() };
	std::copy(std::begin(source), std::end(source), this->ptr.get());
}

MyArray& MyArray::operator=(const MyArray& originalArray)
{
	MyArray temp(originalArray);
	if (this !=&originalArray)
	{
		swap(*this, temp);
	}
	return *this;
}

MyArray::MyArray(MyArray&& originalArray) noexcept
{
	this->arrSize = std::exchange(originalArray.arrSize, 0);
	this->ptr = std::move(originalArray.ptr);
}

size_t MyArray::size() const noexcept
{
	return arrSize;
}

void MyArray::swap(MyArray& first, MyArray& second) noexcept
{
	std::swap(first.arrSize, second.arrSize);
	first.ptr.swap(second.ptr);

}
