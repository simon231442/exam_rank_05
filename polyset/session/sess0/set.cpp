#include "set.hpp"

set::~set() {}

set::set(searchable_bag & s_bag) : bag(s_bag) {}

bool	set::has(int value) const { return bag.has(value); }

void	set::insert(int value)
{
	if (!(this->has(value)))
			bag.insert(value);
}

void	set::insert(int *value, int size)
{
	for (int i = 0; i < size; i++)
			this->insert(value[i]);
}

void	set::print() const { bag.print(); }

void	set::clear() { bag.clear(); }

const searchable_bag&		set::get_bag() { return this->bag; }

