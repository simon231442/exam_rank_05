#include "set.hpp"

set::~set() {}

set::set(searchable_bag & s_bag) : bag(s_bag) {}

bool	set::has(int value) const { return bag.has(value); }

void	set::insert(int value)
{
	if (!(this->has(value)))
			bag.insert(value);
}

	for (int i = 0; i < size; i++)
			this->insert(data[i]);
}

void	set::print() const { bag.print(); }

void	set::clear() { bag.clear(); }

searchable const &		set::get_bag() { return this->bag; }

