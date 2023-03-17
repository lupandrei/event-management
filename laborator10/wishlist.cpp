#include "wishlist.h"
#include "wishlistexceptii.h"
void Wishlist::add(const Event& e)
{
	const auto& p = find(list.begin(), list.end(), e);
	if (p != list.end())
		throw WishlistException("Exista deja activitatea cu acest titlu in wishlist\n");
	list.push_back(e);
}

void Wishlist::del() noexcept
{
	list.clear();
}
void Wishlist::removeEvent(const Event& e)
{
	auto it = find(list.begin(), list.end(), e);
	if (it != list.end())
		list.erase(it);
}
int Wishlist::size()
{
	return list.size();
}

void Wishlist::update(const Event& e)
{
}

const vector<Event>& Wishlist::get_all()
{
	return this->list;
}
