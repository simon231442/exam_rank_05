#include "MYset.hpp"

set::set(searchable_bag & s_bag) : bag(s_bag) { }
set::~set() { }

void				set::insert(int value)
{
	if (!bag.has(value))
		bag.insert(value);
}

void				set::insert(int *values, int count)
{
	for (int i = 0; i < count; ++i)
		bag.insert(values[i]);
}

void				set::print() const
{
	bag.print();
}

void				set::clear()
{
	bag.clear();
}

bool				set::has(int value) const
{
	return bag.has(value);
}
