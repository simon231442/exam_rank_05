#include "searchable_array_bag.hpp"


searchable_array_bag::searchable_array_bag()
{
}

searchable_array_bag::searchable_array_bag(searchable_array_bag const & src) : array_bag(src)
{
}

searchable_array_bag&	searchable_array_bag::operator=(searchable_array_bag const & rhs)
{
	if (this != &rhs)
	{
		if (data != 0)
		{
			delete[] data;
			data = 0;
		}
		size = rhs.size;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = rhs.data[i];
	}
	return *this;
}

searchable_array_bag::~searchable_array_bag()
{
}

bool					searchable_array_bag::has(int value) const
{
	for (int i = 0; i < size; ++i)
	{
		if (data[i] == value)
			return true;
	}
	return false;
}

