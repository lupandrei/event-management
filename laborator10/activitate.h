#pragma once
#include <iostream>
#include <string>
using std::ostream;
using std::string;
using std::cout;
class Event {
private:
	int id;
	string title;
	string description;
	string type;
	float time;
public:
	Event()noexcept = default;
	Event(int id, const string t, const string d, const string type, float time) :id{ id }, title{ t }, description{ d }, type{ type }, time{ time }{}

	Event(const Event& ot) :id{ ot.id }, title{ ot.title }, description{ ot.description }, type{ ot.type }, time{ ot.time }{
	}

	int get_id() const noexcept {
		return this->id;
	}
	const string& get_title() const noexcept {
		return this->title;
	}
	const string& get_description() const noexcept {
		return this->description;
	}
	const string& get_type() const noexcept {
		return this->type;
	}
	float get_time() const noexcept {
		return this->time;
	}


	void set_title(const string& t);
	void set_description(const string& d);

	void set_type(const string& type);

	void set_time(float time) noexcept;

	bool cmp(const Event& e2) noexcept;

	bool operator==(const Event& ot) noexcept;

	const Event& operator=(const Event& e1);
	friend ostream& operator<<(ostream& os, const Event& ev);
};