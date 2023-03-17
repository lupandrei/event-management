#pragma once
//#include "activitate.h"

//typedef Event Element;
#define InitialCapacity 5;
template <typename ElementT>
class Iterator;

template <typename ElementT>
class VectorDinamic {
public:
	VectorDinamic()noexcept;

	VectorDinamic(const VectorDinamic& ot)noexcept;

	~VectorDinamic()noexcept;

	VectorDinamic& operator=(const VectorDinamic& ot)noexcept;

	VectorDinamic(VectorDinamic&& ot)noexcept;

	VectorDinamic& operator=(VectorDinamic&& ot)noexcept;

	void add(const ElementT& el);

	ElementT& get(int poz)const;

	void set(int poz, const ElementT& el);

	int size()const noexcept;

	void del(ElementT el);

	friend class Iterator<ElementT>;
	Iterator<ElementT> begin();
	Iterator<ElementT> end();

private:
	int cp;
	int lg;
	ElementT* elems;
	void ensure_capacity();
};
template <typename ElementT>
class Iterator {
private:
	const VectorDinamic<ElementT>& v;
	int poz = 0;
public:

	Iterator(const VectorDinamic<ElementT>& v)noexcept;

	Iterator(const VectorDinamic<ElementT>& v, int poz) noexcept;



	bool valid()const noexcept;

	ElementT& element()noexcept;

	ElementT& operator*();

	Iterator& operator++()noexcept;

	bool operator==(const Iterator& ot)noexcept;

	bool operator!=(const Iterator& it)noexcept;

	void next() noexcept;
};

template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic() noexcept : elems{ new ElementT[5] }, cp{ 5 }, lg{ 0 }{}

template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(const VectorDinamic& ot) noexcept
{
	elems = new ElementT[ot.cp];
	for (int i = 0;i < ot.lg;i++)
		elems[i] = ot.elems[i];
	lg = ot.lg;
	cp = ot.cp;
}
template <typename ElementT>
VectorDinamic<ElementT>::~VectorDinamic() noexcept
{
	delete[]elems;
}
template <typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(const VectorDinamic<ElementT>& ot) noexcept
{
	if (this == &ot)
		return *this;
	delete[]elems;
	elems = new ElementT[ot.cp];
	for (int i = 0;i < ot.lg;i++)
		elems[i] = ot.elems[i];
	lg = ot.lg;
	cp = ot.cp;
	return *this;
}
template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(VectorDinamic&& ot) noexcept
{
	elems = ot.elems;
	lg = ot.lg;
	cp = ot.cp;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.cp = 0;
}
template <typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(VectorDinamic<ElementT>&& ot) noexcept
{
	if (this == &ot)
		return *this;
	delete[]elems;
	elems = ot.elems;
	lg = ot.lg;
	cp = ot.cp;
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cp = 0;
	return *this;
}
template <typename ElementT>
void VectorDinamic<ElementT>::add(const ElementT& el)
{
	ensure_capacity();
	elems[lg++] = el;
}
template <typename ElementT>
ElementT& VectorDinamic<ElementT>::get(int poz) const
{
	return elems[poz];
}
template <typename ElementT>
void VectorDinamic<ElementT>::set(int poz, const ElementT& el)
{
	elems[poz] = el;
}
template <typename ElementT>
int VectorDinamic<ElementT>::size() const noexcept
{
	return lg;
}
template <typename ElementT>
void VectorDinamic<ElementT>::del(ElementT el)
{
	for (int i = 0;i < lg;i++)
		if (el == elems[i])
		{
			for (int j = i;j < lg;j++)
				elems[i] = elems[i + 1];
		}
	lg--;
}
template <typename ElementT>
Iterator<ElementT> VectorDinamic<ElementT>::begin()
{
	return Iterator<ElementT>(*this);
}
template <typename ElementT>
Iterator<ElementT> VectorDinamic<ElementT>::end()
{
	return Iterator<ElementT>(*this, lg);
}
template <typename ElementT>
void VectorDinamic<ElementT>::ensure_capacity()
{
	if (lg < cp)
		return;
	cp *= 2;
	ElementT* aux = new ElementT[cp];
	for (int i = 0;i < lg;i++)
		aux[i] = elems[i];
	delete[]elems;
	elems = aux;
}

template <typename ElementT>
Iterator<ElementT>::Iterator(const VectorDinamic<ElementT>& v) noexcept :v{ v } {}

template <typename ElementT>
Iterator<ElementT>::Iterator(const VectorDinamic<ElementT>& v, int poz) noexcept :v{ v }, poz{ poz }{}

template <typename ElementT>
bool Iterator<ElementT>::valid() const noexcept
{
	return poz < v.lg;
}
template <typename ElementT>
ElementT& Iterator<ElementT>::element() noexcept
{
	return v.elems[poz];
}
template <typename ElementT>
ElementT& Iterator<ElementT>::operator*()
{
	return element();
}
template <typename ElementT>
Iterator<ElementT>& Iterator<ElementT>::operator++() noexcept
{
	next();
	return *this;
}
template <typename ElementT>
bool Iterator<ElementT>::operator==(const Iterator<ElementT>& ot) noexcept
{
	return poz == ot.poz;
}
template <typename ElementT>
bool Iterator<ElementT>::operator!=(const Iterator<ElementT>& ot) noexcept
{
	return poz != ot.poz;
}
template <typename ElementT>
void Iterator<ElementT>::next() noexcept
{
	poz++;
}
