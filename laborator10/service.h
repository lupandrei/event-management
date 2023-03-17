#pragma once
#include <functional>
#include "repo.h"
#include "undo.h"
#include "wishlist.h"
#include "validare.h"
#include "VectorDinamic.h"
#include <algorithm>
#include <random>
#include <string>
#include <map>
#include "serviceexceptii.h"
#include "observable.h"
using std::string;
using std::swap;
using std::sort;
using std::mt19937;
using std::random_device;
using std::shuffle;
using std::function;
using std::map;
using std::unique_ptr;

class Service:public Observable {
private:
	Validator& val;
	Repo& repo;
	Repo& wishlist;
	vector <ActiuneUndo*>undoActiune;
	/*
	* Metoda generala de filtrare
	* Input: filterfunction-bool
	* output: vector cu eventurile care au trecut de filtrare
	*/
	vector<Event> filter(function <bool(const Event&)> filterfunction);

	/*
	* Metoda generala de sortare.
	* input: sortfunction
	* output: vector cu eventurile sortate dupa criteriul dat
	*/
	vector<Event>sortare(bool(*sortfunction)(const Event&, const Event&));
public:
	Service(Validator& _val, Repo& _repo, Repo& _wishlist)noexcept :val{ _val }, repo{ _repo }, wishlist{ _wishlist }{}
	int size()noexcept;
	void storeEvent(int, const string&, const string&, const string&, float);
	void deleteEvent(int);
	void updateEvent(int, const string&, const string&, const string&, float);
	const vector<Event>& get_all()const;
	const Event& findbyid(int id);
	vector<Event>filterbydescription(const string&);
	vector<Event>filterbytype(const string&);
	vector<Event>sortbytitle();
	vector<Event>sortbydescription();
	void generate(int n);
	void add_to_wishlist(const string& title);
	void delete_wishlist();
	const vector<Event>& get_wishlist();
	map<string, int>raport();
	void undo();
	~Service();
};