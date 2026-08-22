#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public array_bag, public searchable_bag {
	private :
		bool					search(node* node, const int value) const;
	public :
		searchable_tree_bag();
		searchable_tree_bag(searchable_tree_bag const & src);
		~searchable_tree_bag();

		searchable_tree_bag&	operator=(searchable_tree_bag const & rhs);
		bool					has(int) const;
};

