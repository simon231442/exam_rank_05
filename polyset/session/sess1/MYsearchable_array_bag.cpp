#include "MYsearchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() {}

searchable_array_bag::searchable_array_bag(searchable_array_bag const & src) : array_bag(src) { };

searchable_array_bag &		searchable_array_bag::operator=(searchable_array_bag const & rhs)
{
	if (this != &rhs)
		searchable_bag::operator=(rhs);
	return *this;
}

searchable_array_bag::~searchable_array_bag() {}

bool						searchable_array_bag::has(int value) const
{
	for (int i = 0; i < size; i++)
	{
		if (data[i] == value)
			return true;
	}
	return false;
}

