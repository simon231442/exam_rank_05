#include "searchable_tree_bag.hpp"


searchable_tree_bag::searchable_tree_bag()
{
}

searchable_tree_bag::searchable_tree_bag(searchable_tree_bag const & src) : array_bag(src)
{
}

searchable_tree_bag&	searchable_tree_bag::operator=(searchable_tree_bag const & rhs)
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

searchable_tree_bag::~searchable_tree_bag()
{
}

bool					searchable_tree_bag::has(int value) const
{
}
