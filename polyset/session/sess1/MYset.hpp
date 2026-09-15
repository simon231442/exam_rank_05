#pragma once

#include "searchable_bag.hpp"

class set {
	private :
		searchable_bag &	bag;
	public :
		set(searchable_bag & s_bag);
		~set();
		void				insert(int);
		void				insert(int *, int);
		void				print() const;
		void				clear();
		bool				has(int) const;
};


