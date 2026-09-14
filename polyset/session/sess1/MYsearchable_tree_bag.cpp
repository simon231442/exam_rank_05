#include "MYsearchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() { }

searchable_tree_bag::searchable_tree_bag(searchable_tree_bag const & src) : tree_bag(src) { };

searchable_tree_bag &	searchable_tree_bag::operator=(searchable_tree_bag const & rhs)
{
	if (this != &rhs)
		tree_bag::operator=(rhs);
	return *this;
}

searchable_tree_bag::~searchable_tree_bag() { }

static bool				search_value(node node, int value)
{
	if (node == 0)
		return false;
	if (node.value == value)
		return true;
	if (node.value < value)
		return search_value(*(node.l), value);
	return search_value(*(node.r), value);
}

bool					searchable_tree_bag::has(int value)
{
	return search_value(*tree, value);
}
