#pragma once

#include "searchable_bag.hpp"
#include "array_bag.hpp"

class searchable_array_bag : public searchable_bag, public array_bag {
	public :
		searchable_array_bag();
		searchable_array_bag(searchable_array_bag const & src);
		searchable_array_bag&	operator=(searchable_array_bag const & rhs);
		~searchable_array_bag();

		bool					has(int) const;
};
