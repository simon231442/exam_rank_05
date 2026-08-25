#pragma once

#include "searchable_bag.hpp"

class set {
	private :
		searchable_bag&				bag;
	public :
		set() = delete;
		set(set const & src) = delete;
		set& 						operator=(set const& src) = delete;
		~set();

		set(searchable_bag & s_bag);

		bool						has(int) const;
		void						insert(int);
		void						insert(int *, int);
		void						print() const;
		void						clear();

		const searchable_bag&		get_bag();
};

