#pragma once

#include "searchable_bag.hpp"

class set
{
 private:
	set();
	set(const set& source);
	set& operator=(const set& source);
	searchable_bag& bag;
 public:
	set(searchable_bag& s_bag);

	bool has(int) const;
	void insert(int);
	void insert(int *, int);
	void print() const;
	void clear();

	const searchable_bag& get_bag();

	~set();
};
