#pragma once
#include <vector>
#include <algorithm>
#include "activitate.h"
using std::vector;
class Wishlist {
private:
	vector<Event>list;
public:
	void add(const Event& e);
	void del()noexcept;
	void removeEvent(const Event& e);
	int size();
	void update(const Event& e);
	const vector<Event>& get_all();
};