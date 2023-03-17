#include "teste.h"
#include <fstream>
using std::cout;
void teste::tests_domain()
{
	Event e;
	constexpr int id = 10;
	string title = "titlu";
	string type = "type";
	string description = "description";
	constexpr float time = 10.5;
	Event e1(id, title, description, type, time);
	cout << e1;
	//getteri
	assert(e1.get_id() == 10);
	assert(e1.get_title() == "titlu");
	assert(e1.get_type() == "type");
	assert(e1.get_description() == "description");
	assert(e1.get_time() == time);
	Event e2(e1);//copiere
	assert(e1.get_id() == e2.get_id());
	assert(e1.get_title() == e2.get_title());
	assert(e1.get_type() == e2.get_type());
	assert(e1.get_description() == e2.get_description());
	assert(e1.get_time() == e2.get_time());
	//setteri
	e2.set_description("desc2");
	e2.set_title("nou");
	e2.set_time(200);
	e2.set_type("tip");
	assert(e2.get_id() == 10);
	assert(e2.get_title() == "nou");
	assert(e2.get_type() == "tip");
	assert(e2.get_description() == "desc2");
	assert(e2.get_time() == 200);
	assert(e1.cmp(e2) == false);//cmp
	assert(e1 == e2);//operator == 

}
void teste::tests_repo()
{
	Repo repotest;
	Event e1(1, "titlu1", "descriere1", "tip1", 10);
	Event e2(1, "titlu2", "descriere2", "tip2", 20);
	assert(repotest.size() == 0);
	repotest.store(e1);
	assert(repotest.size() == 1);
	try {
		repotest.store(e2);
		//assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "Evenimentul exista deja\n");
	}
	repotest.update(e2);
	Event cautat = repotest.findbyid(1);
	assert(cautat.get_title() == "titlu2");
	assert(cautat.get_description() == "descriere2");
	assert(cautat.get_type() == "tip2");
	assert(cautat.get_time() == 20);
	Event e3(3, "titlu3", "descriere3", "tip3", 30);
	try {
		repotest.findbyid(3);
		//assert(false);
	}
	catch (const RepoException& re) {
		assert(re.get_message() == "Nu exista eveniment cu id-ul dat\n");
		assert(true);
	}
	try {
		repotest.update(e3);
	}
	catch (const RepoException& re) {
		assert(re.get_message() == "Nu exista eveniment cu id-ul dat\n");
	}
	try {
		repotest.deletebyid(3);
	}
	catch (const RepoException& re) {
		assert(re.get_message() == "Nu exista eveniment cu id-ul dat\n");
	}
	repotest.deletebyid(1);
	assert(repotest.size() == 0);

}
void teste::test_find_srv()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	srvtest.storeEvent(1, "titlu1", "descriere1", "tip1", 10);
	srvtest.findbyid(1);
	assert(true);
}
void teste::test_service_add_delete_modify()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	assert(srvtest.size() == 0);
	Event e1(1, "titlu1", "descriere1", "tip1", 10);
	Event e2(1, "titlu2", "descriere2", "tip2", 20);
	srvtest.storeEvent(1, "titlu1", "descriere1", "tip1", 10);
	vector<Event> t = srvtest.get_all();
	assert(t.size() == 1);
	assert(srvtest.size() == 1);
	try {
		srvtest.storeEvent(1, "", "", "", -5);
	}
	catch (const ValidationException& ve) {
		assert(ve.get_message() == "Invalid title\nInvalid description\nInvalid type\nInvalid time\n");
	}
	try {
		srvtest.storeEvent(1, "titlu2", "descriere2", "tip2", 20);
	}
	catch (const RepoException& re) {
		assert(re.get_message() == "Evenimentul exista deja\n");
	}
	srvtest.updateEvent(1, "titlu2", "descriere2", "tip2", 20);
	assert(true);
	try {
		srvtest.deleteEvent(3);
	}
	catch (const RepoException& re) {
		assert(re.get_message() == "Nu exista eveniment cu id-ul dat\n");
	}
	srvtest.deleteEvent(1);
	assert(true);
}

void teste::test_filter_by_description()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	srvtest.storeEvent(1, "titlu1", "descriere", "tip1", 10);
	srvtest.storeEvent(2, "titlu2", "descriere", "tip2", 20);
	srvtest.storeEvent(3, "titlu1", "descriere321", "tip1", 10);
	srvtest.storeEvent(5, "titlu1", "descriere", "tip1", 10);
	srvtest.storeEvent(6, "titlu1", "descriere", "tip1", 10);
	vector<Event>res = srvtest.filterbydescription("descriere");
	assert(res.size() == 4);
}

void teste::test_filter_by_type()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	srvtest.storeEvent(1, "titlu1", "descriere", "tip", 10);
	srvtest.storeEvent(5, "titlu1", "descriere", "tip", 10);
	srvtest.storeEvent(6, "titlu1", "descriere", "tip", 10);
	srvtest.storeEvent(7, "titlu2", "descriere232", "tip2", 20);
	vector<Event>res = srvtest.filterbytype("tip");
	assert(res.size() == 3);
}


void teste::test_sort_by_title()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	srvtest.storeEvent(1, "d", "descriere", "tip", 10);
	srvtest.storeEvent(2, "a", "descriere", "tip2", 20);
	srvtest.storeEvent(3, "c", "descriere321", "tip1", 10);
	vector<Event>res = srvtest.sortbytitle();
	assert(res.at(0).get_title() == "a");
	assert(res.at(1).get_title() == "c");
	assert(res.at(2).get_title() == "d");

}

void teste::test_sort_by_description()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	srvtest.storeEvent(1, "titlu1", "d", "tip", 10);
	srvtest.storeEvent(2, "titlu2", "a", "tip", 20);
	srvtest.storeEvent(3, "titlu1", "c", "tip", 10);
	srvtest.storeEvent(4, "titlu1", "e", "tip", 10);
	srvtest.storeEvent(5, "titlu1", "f", "tip", 10);
	srvtest.storeEvent(6, "titlu1", "g", "tip", 10);
	vector<Event>res = srvtest.sortbydescription();
	assert(res.at(0).get_description() == "a");
	assert(res.at(1).get_description() == "c");
	assert(res.at(2).get_description() == "d");
}

void teste::test_wishlist_add_generate_delete()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	srvtest.storeEvent(1, "titlu1", "d", "tip", 10);
	srvtest.storeEvent(2, "titlu2", "a", "tip", 20);
	srvtest.storeEvent(3, "titlu3", "c", "tip", 10);
	srvtest.storeEvent(4, "titlu4", "e", "tip", 10);
	srvtest.storeEvent(5, "titlu5", "f", "tip", 10);
	srvtest.storeEvent(6, "titlu6", "g", "tip", 10);
	try {
		srvtest.generate(10);
	}
	catch (const ServiceException& se) {
		assert(se.get_message() == "Nu exista suficiente activitati\n");
	}
	srvtest.generate(1);
	assert(true);
	assert(list.size() == 1);
	list.del();
	try {
		srvtest.add_to_wishlist("ada");
	}
	catch (const ServiceException& se) {
		assert(se.get_message() == "Nu exista activitate cu titlul dat\n");
		assert(true);
	}
	srvtest.add_to_wishlist("titlu1");
	try {
		srvtest.add_to_wishlist("titlu1");
	}
	catch (const RepoException& we) {
		assert(we.get_message().size() >0);
	}
	assert(list.size() == 1);
	vector<Event>test = srvtest.get_wishlist();
	assert(test.size() == 1);
	srvtest.delete_wishlist();
}

void teste::test_raport()
{
	map<string, int>res;
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	srvtest.storeEvent(1, "titlu1", "d", "tip1", 10);
	srvtest.storeEvent(2, "titlu1", "d", "tip1", 10);
	srvtest.storeEvent(3, "titlu3", "c", "tip2", 10);
	srvtest.storeEvent(4, "titlu4", "e", "tip3", 10);
	srvtest.storeEvent(5, "titlu4", "e", "tip2", 10);
	res = srvtest.raport();
	assert(res["tip1"] == 2);
	assert(res["tip2"] == 2);
	assert(res["tip3"] == 1);
}

void teste::test_undo()
{
	Repo repotest;
	Validator validtest;
	Repo list;
	Service srvtest{ validtest,repotest,list };
	try {
		srvtest.undo();
	}
	catch (const ServiceException& se) {
		assert(se.get_message() == "Nu mai exista operatii\n");
	}
	srvtest.storeEvent(1, "titlu1", "d", "tip1", 10);
	srvtest.storeEvent(2, "titlu2", "d2", "tip2", 100);
	assert(repotest.size() == 2);
	srvtest.undo();
	assert(repotest.size() == 1);
	srvtest.deleteEvent(1);
	assert(repotest.size() == 0);
	srvtest.undo();
	assert(repotest.size() == 1);
	srvtest.updateEvent(1, "titlu2", "d2", "tip2", 100);
	srvtest.undo();
}

void teste::test_file()
{
	try {
		FileRepo filerepo("testfilerepo-1.txt");
	}
	catch (const RepoException& re) {
		assert(re.get_message() == "testfilerepo-1.txt didn't open!");
	}
	FileRepo filerepo("testfilerepo1.txt");
	Event ev1(1, "titlu1", "d", "tip1", 10);
	Event ev2(2, "titlu2", "d2", "tip2", 100);
	filerepo.store(ev1);
	try {
		filerepo.store(ev2);
	}
	catch (const RepoException& re) {
		assert(re.get_message() == "Evenimentul exista deja\n");
	}
	assert(filerepo.size() == 2);
	filerepo.deletebyid(1);
	assert(filerepo.size() == 1);
	Event ev3(2, "titlu10512341", "d234123412", "tip2sfdadf", 1040);
	filerepo.update(ev3);
	filerepo.findbyid(2);
}



void teste::run_tests()
{
	cout << "start domain tests\n";
	this->tests_domain();
	cout << "end domain tests\n";
	cout << "start repo tests\n";
	this->tests_repo();
	cout << "end repo tests\n";
	cout << "start service tests\n";
	this->test_find_srv();
	this->test_service_add_delete_modify();
	this->test_filter_by_description();
	this->test_filter_by_type();
	this->test_sort_by_title();
	this->test_sort_by_description();
	cout << "\nstop service tests\n";
	cout << "start wishlist tests\n";
	this->test_wishlist_add_generate_delete();
	cout << "stop wishlist tests\n";
	cout << "raport start\n";
	this->test_raport();
	cout << "raport end\n";
	cout << "test undo\n";
	this->test_undo();
	cout << "stop test undo\n";
	cout << "start file test\n";
	this->test_file();
	cout << "stop file test\n";
}
