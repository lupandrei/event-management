#include "service.h"
#include <iostream>
vector<Event> Service::filter(function<bool(const Event&)> filterfunction)
{
    vector<Event> aux = get_all();
    vector<Event>res;
    /*for (const auto& ev : aux)
        if (filterfunction(ev))
            res.push_back(ev);*/
    copy_if(aux.begin(), aux.end(), back_inserter(res), filterfunction);
    return res;
}

vector<Event> Service::sortare(bool(*sortfunction)(const Event&, const Event&))
{
    vector<Event>res = get_all();
    //for (int i = 0;i < res.size() - 1;i++) {
    //    for (int j = i + 1;j < res.size();j++)
    //        if (sortfunction(res.at(i), res.at(j)))
    //            swap(res.at(i), res.at(j));
    //}
    sort(res.begin(), res.end(), sortfunction);
    return res;
}

int Service::size() noexcept
{
    return this->repo.size();
}

void Service::storeEvent(int id, const string& title, const string& description, const string& type, float time)
{
    Event ev(id, title, description, type, time);
    this->val.validateEvent(ev);
    this->repo.store(ev);
    //undoActiune.push_back(std::make_unique<UndoAdauga>(repo, ev));
    undoActiune.push_back(new UndoAdauga(this->repo, this->wishlist, ev));
    NotifyAll();
}


void Service::deleteEvent(int id)
{
    bool was = true;
    Event ev = findbyid(id);
    this->repo.deletebyid(id);
    //undoActiune.push_back(std::make_unique<UndoSterge>(repo, ev));
    try {
        this->wishlist.deletebyid(ev.get_id());
        
    }
    catch (...) {
        was = false;
    }
    undoActiune.push_back(new UndoSterge(this->repo, this->wishlist, ev,was));
    NotifyAll();
}

void Service::updateEvent(int id, const string& title, const string& description, const string& type, float time)
{
    Event ant = findbyid(id);
    Event ev(id, title, description, type, time);
    this->val.validateEvent(ev);
    this->repo.update(ev);
    //undoActiune.push_back(std::make_unique<UndoModifica>(repo, ant));
    undoActiune.push_back(new UndoModifica(this->repo, this->wishlist, ev));
    try {
        wishlist.store(ev);
    }
    catch (...) {}
    NotifyAll();
}

const vector<Event>& Service::get_all()const
{
    return this->repo.get_all();
}

const Event& Service::findbyid(int id)
{
    return this->repo.findbyid(id);
}


vector<Event> Service::filterbydescription(const string& description)
{
    //vector<Event>res;
    //vector<Event>rp = this->repo.get_all();
    //copy_if(rp.begin(), rp.end(), back_inserter(res), [&](const Event& ev)noexcept {return ev.get_description() == description;});
    //return res;
    return this->filter([&](const Event& ev)noexcept {return ev.get_description() == description;});
}

vector<Event> Service::filterbytype(const string& type)
{
    return this->filter([&](const Event& ev)noexcept {return ev.get_type() == type;});
}

vector<Event> Service::sortbytitle()
{
    return this->sortare([](const Event& e1, const Event& e2)noexcept {return e1.get_title() < e2.get_title();});
}

vector<Event> Service::sortbydescription()
{
    return this->sortare([](const Event& e1, const Event& e2)noexcept {return e1.get_description() < e2.get_description();});
}

void Service::generate(int n)
{
    vector<Event>repolist = this->get_all();
    random_device rd;
    mt19937 generator(rd());
    if (n > repolist.size())
        throw ServiceException("Nu exista suficiente activitati\n");
    this->wishlist.del();
    while (n)
    {
        mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, repolist.size() - 1);
        int rndNr = dist(mt);// numar aleator intre [0,size-1]
        try {
            this->wishlist.store(repolist.at(rndNr));
            n--;
        }
        catch(...){}
    }
    NotifyAll();
}

void Service::add_to_wishlist(const string& title)
{
    vector<Event>repolist = this->get_all();
    const auto& p = find_if(repolist.begin(), repolist.end(), [=](const Event& ev) {return ev.get_title() == title;});
    if (p != repolist.end())
    {
        this->wishlist.store(*p);
    }
    else
        throw ServiceException("Nu exista activitate cu titlul dat\n");
    NotifyAll();
}

void Service::delete_wishlist()
{
    this->wishlist.del();
    NotifyAll();
}

const vector<Event>& Service::get_wishlist()
{
    return this->wishlist.get_all();
}

map<string, int> Service::raport()
{
    map <string, int>res;
    map<string, int>::iterator it;
    vector<Event>vec = this->get_all();
    for (Event& ev : vec)
    {
        it = res.find(ev.get_type());
        if (it != res.end())
        {
            (*it).second++;
        }
        else
            res.insert({ ev.get_type(), 1 });
    }
    return res;
}

void Service::undo()
{
    if (undoActiune.empty())
        throw ServiceException("Nu mai exista operatii\n");
    undoActiune.back()->doUndo();
    undoActiune.pop_back();
    NotifyAll();
}

Service::~Service()
{
}
