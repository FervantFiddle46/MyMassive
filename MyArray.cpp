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


MyArray& MyArray::operator=(MyArray&& originalArray) noexcept
{
	if (this!= &originalArray)
	{
		this->arrSize = std::exchange(originalArray.arrSize, 0);
		this->ptr = std::move(originalArray.ptr);
	}
	return *this;
}

std::string MyArray::toString() const
{
	const std::span<const int> items{ this->ptr.get(), this->arrSize };
	std::ostringstream output;

	for (size_t i = 0; const auto& item : items )
	{
		i++;
		output << item << (i < this->arrSize ? ", " : "");
	}
	return output.str();
}

bool MyArray::operator==(const MyArray& originalArray) const noexcept
{
	const std::span<const int> leftArr{ this->ptr.get(), this->arrSize };
	const std::span<const int> rightArr{ originalArray.ptr.get(), originalArray.arrSize };
	return std::equal(std::begin(leftArr), std::end(leftArr), std::begin(rightArr), std::end(rightArr));
}

MyArray::operator bool() const noexcept
{
	return size() != 0;
}

int& MyArray::operator[](size_t index)
{
	if (index >= this->arrSize)
	{
		throw std::out_of_range("Error");
	}
	return this->ptr[index];
}

const int& MyArray::operator[](size_t index) const
{
	if (index >= this->arrSize)
	{
		throw std::out_of_range("Error");
	}
	return this->ptr[index];
}

MyArray& MyArray::operator++()
{
	const std::span<int> items{ this->ptr.get(),this->arrSize };
	std::for_each(std::begin(items), std::end(items), [](auto& i) {i++; });
	return *this;
}

MyArray MyArray::operator++(int)
{
	MyArray temp(*this);
	++(*this);
	return temp;
}

MyArray& MyArray::operator+=(int value)
{
	const std::span<int> items{ this->ptr.get(),this->arrSize };
	std::for_each(std::begin(items), std::end(items), [value](auto& i) {i += value; });
	return *this;
}

size_t MyArray::size() const noexcept
{
	return arrSize;
}

MyArray::~MyArray()
{
}

void MyArray::swap(MyArray& first, MyArray& second) noexcept
{
	std::swap(first.arrSize, second.arrSize);
	first.ptr.swap(second.ptr);

}

std::istream& operator>>(std::istream& in, MyArray& obj) // std::cin >> arr
{
	std::span<int> items(obj.ptr.get(), obj.arrSize);
	for (auto &i : items)
	{
		in >> i;
	}
	return in;
}
