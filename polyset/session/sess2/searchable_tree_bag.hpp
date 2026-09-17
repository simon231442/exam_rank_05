#pragma once

#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class searchable_tree_bag : public searchable_bag, public array_bag {
	public :
		searchable_tree_bag();
		searchable_tree_bag(searchable_tree_bag const & src);
		searchable_tree_bag&	operator=(searchable_tree_bag const & rhs);
		~searchable_tree_bag();

		bool					has(int) const;
		bool					search(node* node, int value) const;
};
