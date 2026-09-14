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
	if (node.value == value)
		return true;
	return false;
}

bool					searchable_tree_bag::has(int value)
{
	if (search_value(tree->node, value))
		return true;



