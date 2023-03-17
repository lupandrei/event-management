#include "activitate.h"


void Event::set_title(const string& t)
{
    this->title = t;
}

void Event::set_description(const string& d)
{
    this->description = d;
}

void Event::set_type(const string& _type)
{
    this->type = _type;
}

void Event::set_time(float _time) noexcept
{
    this->time = _time;
}

bool Event::cmp(const Event& e2) noexcept
{
    return this->get_title() < e2.get_title();
}

bool Event::operator==(const Event& ot) noexcept
{
    return this->id == ot.id;
}

const Event& Event::operator=(const Event& e1)
{
    this->id = e1.id;
    this->title = e1.title;
    this->description = e1.description;
    this->type = e1.type;
    this->time = e1.time;
    return *this;
}

ostream& operator<<(ostream& os, const Event& ev)
{
    os << ev.get_id() << "/" << ev.get_title() << "/" << ev.get_type() << "/" << ev.get_description() << "/" << ev.get_time() << "/" << ev.get_time() << "\n";
    return os;
}
