#pragma once
#include <vector>
#include <exception>
#include "activitate.h"
#include "repoexceptii.h"
#include <iostream>
#include <algorithm>
#include "VectorDinamic.h"
using std::exception;
using std::vector;
//template <typename Event>
class Repo {
private:
	//VectorDinamic<Event> events;
	vector<Event>events;
public:
	Repo() = default;
	virtual const Event& findbyid(int id);
	virtual void store(Event& e);
	virtual void update(Event& e);
	virtual int size() noexcept;
	virtual void deletebyid(int id);
	virtual void del();
	//vector <Event>& get_all() noexcept;
	virtual const vector<Event>& get_all() noexcept;
	~Repo();

};
class FileRepo : public Repo {
private:
	std::string Filename;

	void loadfromfile();
	void writetofile();
public:
	FileRepo(std::string Fname) : Repo(), Filename{ Fname }{
		loadfromfile();
	}
	void store(Event& ev)override {
		Repo::store(ev);
		writetofile();
	}
	void deletebyid(int id) override {
		Repo::deletebyid(id);
		writetofile();
	}
	void update(Event& e)override {
		Repo::update(e);
		writetofile();
	}
	const Event& findbyid(int id)override {
		return Repo::findbyid(id);
	}
	const vector<Event>& get_all() noexcept override {
		return Repo::get_all();
	}
	int size() noexcept override {
		return Repo::size();
	}
	void del()override {
		Repo::del();
		writetofile();
	}

};