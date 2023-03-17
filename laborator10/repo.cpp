#include "repo.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
const Event& Repo::findbyid(int id)
{

    for (Event& p : events) {
        if (p.get_id() == id)
            return p;
    }
    /*Iterator<Event> it{ events };
    while (it.valid())
    {
        if (id == it.element().get_id())
            return *it;
        it.next();
    }*/
    throw RepoException("Nu exista eveniment cu id-ul dat\n");
}

void Repo::store(Event& e)
{
    const auto& p = find(events.begin(), events.end(), e);
    if (p != events.end())
        throw RepoException("Evenimentul exista deja\n");
    else
        events.push_back(e);


    /*Iterator<Event> it(events);
    while (it.valid())
    {
        if (e == it.element())
            throw RepoException("Evenimentul exista deja\n");
        it.next();
    }
    events.add(e);*/
}

void Repo::update(Event& e)
{

    const auto& p = find(events.begin(), events.end(), e);
    if (p != events.end())
    {
        *p = e;
    }
    else
        throw RepoException("Nu exista eveniment cu id-ul dat\n");
    /*Iterator<Event> it(events);
    int ok = 0;
    while (it.valid())
    {
        if (e == it.element())
        {
            *it = e;
            ok = 1;
        }
        it.next();
    }
    if(!ok)
        throw RepoException("Nu exista eveniment cu id-ul dat\n");*/
}

int Repo::size()noexcept
{
    return this->events.size();
}

void Repo::deletebyid(int id)
{
    const auto& p = find_if(this->events.begin(), this->events.end(), [=](const Event& n)noexcept {return n.get_id() == id;});
    if (p != this->events.end())
    {
        this->events.erase(p);
    }
    else {
        throw RepoException("Nu exista eveniment cu id-ul dat\n");
    }
    /*Iterator<Event> it{ events };
    int ok = 0;
    while (it.valid())
    {
        Event temp = it.element();
        if (id == temp.get_id())
        {
            events.del(*it);
            ok = 1;
            break;
        }
        it.next();
    }
    if (!ok)
        throw RepoException("Nu exista eveniment cu id-ul dat\n");*/

}

void Repo::del()
{
    events.clear();
}

const vector<Event>& Repo::get_all() noexcept
{
    return this->events;
}
//VectorDinamic<Event>& Repo::get_all() noexcept {
//    return this->events;
//}

Repo::~Repo()
{
}

void FileRepo::loadfromfile()
{
    std::ifstream fin(Filename);
    if (!fin.is_open())
    {
        throw RepoException(Filename + " didn't open!");
    }
    while (!fin.eof())
    {
        int id;
        fin >> id;
        if (fin.eof())
            break;
        std::string titlu;
        fin >> titlu;
        std::string descriere;
        fin >> descriere;
        std::string tip;
        fin >> tip;
        float durata;
        fin >> durata;
        Event ev(id, titlu, descriere, tip, durata);
        Repo::store(ev);
    }
    fin.close();
}

void FileRepo::writetofile()
{
    std::ofstream fout(Filename);
    if (!fout.is_open())
        throw RepoException(Filename + " didn't open!");
    for (const auto& ev : get_all())
    {
        fout << ev.get_id();
        fout << endl;
        fout << ev.get_title();
        fout << endl;
        fout << ev.get_description();
        fout << endl;
        fout << ev.get_type();
        fout << endl;
        fout << ev.get_time();
        fout << endl;
    }
    fout.close();
}
