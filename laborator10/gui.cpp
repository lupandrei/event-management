#include "gui.h"
//void EventsGUI::wishlistmanagement()
//{
//	QWidget* Mainwishlistwindow = new QWidget;
//	QHBoxLayout* Mainwishlistlayout = new QHBoxLayout;
//	Mainwishlistwindow->setLayout(Mainwishlistlayout);
//
//
//	QWidget* left = new QWidget;
//	QHBoxLayout* lyleft = new QHBoxLayout;
//	left->setLayout(lyleft);
//
//	QWidget* listWidget = new QWidget();
//	QHBoxLayout* listlayout = new QHBoxLayout();
//	listWidget->setLayout(listlayout);
//	wishlist = new QListWidget();
//	listlayout->addWidget(wishlist);
//	lyleft->addWidget(listWidget);
//
//	QWidget* right = new QWidget;
//	QHBoxLayout* lyright = new QHBoxLayout;
//	right->setLayout(lyright);
//
//	QWidget* operations = new QWidget;
//	QVBoxLayout* lyoperations = new QVBoxLayout;
//	operations->setLayout(lyoperations);
//
//	QWidget* addwishlist = new QWidget;
//	QFormLayout* lyaddwishlist = new QFormLayout;
//	addwishlist->setLayout(lyaddwishlist);
//	btnaddwishlist = new QPushButton("Adauga in wishlist");
//	editAddWishlist = new QLineEdit();
//	lyaddwishlist->addRow(lbladdwishlist, editAddWishlist);
//	lyaddwishlist->addWidget(btnaddwishlist);
//	lyoperations->addWidget(addwishlist);
//
//	QWidget* generate = new QWidget;
//	QFormLayout* lygenerate = new QFormLayout;
//	generate->setLayout(lygenerate);
//	btngenerate = new QPushButton("Genereaza");
//	editGenerate = new QLineEdit();
//	lygenerate->addRow(lblgenerate, editGenerate);
//	lygenerate->addWidget(btngenerate);
//	lyoperations->addWidget(generate);
//
//	btndeletewishlist = new QPushButton("Sterge Wishlist");
//	lyright->addWidget(operations);
//	lyright->addWidget(btndeletewishlist);
//	Mainwishlistlayout->addWidget(left);
//	Mainwishlistlayout->addWidget(right);
//	connectSignalsWishlist();
//	reloadWishlist(srv.get_wishlist());
//	Mainwishlistwindow->show();
//
//	/*connectSignalsWishlist();
//	reloadWishlist(srv.get_wishlist());*/
//
//}
void EventsGUI::initializeGUIComponents()
{
	//QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	QWidget* left = new QWidget;
	//QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//adaugare
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editId = new QLineEdit;
	editTitlu = new QLineEdit;
	editDescriere = new QLineEdit;
	editTip = new QLineEdit;
	editDurata = new QLineEdit;

	
	lyForm->addRow(lblId, editId);
	lyForm->addRow(lblTitlu, editTitlu);
	lyForm->addRow(lblDescriere, editDescriere);
	lyForm->addRow(lblTip, editTip);
	lyForm->addRow(lblDurata, editDurata);
	btnAddEvent = new QPushButton("Adauga activitate");

	//delete modify search
	QWidget* form2 = new QWidget;
	QHBoxLayout* horizontal = new QHBoxLayout;
	form2->setLayout(horizontal);
	btnDeleteEvent = new QPushButton("Sterge");
	btnModifyEvent = new QPushButton("Modifica");
	btnSearchEvent = new QPushButton("Cauta");
	btnUndo = new QPushButton("Undo");
	horizontal->addWidget(btnDeleteEvent);
	horizontal->addWidget(btnModifyEvent);
	horizontal->addWidget(btnSearchEvent);
	horizontal->addWidget(btnUndo);

	QWidget* form3 = new QWidget;
	QHBoxLayout* horizontall = new QHBoxLayout;
	form3->setLayout(horizontall);
	btnWish = new QPushButton("WishList");
	horizontall->addWidget(btnWish);
	horizontall->addWidget(btnreadonly);

	//sortare
	QVBoxLayout* lySort = new QVBoxLayout;
	this->groupBox->setLayout(lySort);
	lySort->addWidget(radioSrtTitle);
	lySort->addWidget(radioSrtDescription);
	btnSort = new QPushButton("Sorteaza");
	lySort->addWidget(btnSort);

	//filtrare
	QWidget* filterform = new QWidget;
	QHBoxLayout* lyfilter = new QHBoxLayout;
	filterform->setLayout(lyfilter);

	QWidget* filterformdescription = new QWidget;
	QFormLayout* lyfilterdescription = new QFormLayout;
	filterformdescription->setLayout(lyfilterdescription);
	btnfilterByDescription = new QPushButton("Filtreaza dupa descriere");
	editFilterDescription = new QLineEdit();
	lyfilterdescription->addRow(lblFilterDescription, editFilterDescription);
	lyfilterdescription->addWidget(btnfilterByDescription);
	lyfilter->addWidget(filterformdescription);

	QWidget* filterformtype = new QWidget;
	QFormLayout* lyfiltertype = new QFormLayout;
	filterformtype->setLayout(lyfiltertype);
	btnfilterByType = new QPushButton("Filtreaza dupa tip");
	editFilterType = new QLineEdit();
	lyfiltertype->addRow(lblFilterType, editFilterType);
	lyfiltertype->addWidget(btnfilterByType);
	lyfilter->addWidget(filterformtype);



	lyForm->addWidget(btnAddEvent);
	lyForm->addWidget(form2);
	
	lyLeft->addWidget(form);
	lyForm->addWidget(form3);
	lyLeft->addWidget(groupBox);
	lyLeft->addWidget(filterform);

	for (const auto& ev : srv.raport())
	{
		QPushButton* nou = new QPushButton(QString::fromStdString(ev.first));
		actualbuttons.push_back(nou);
		lyLeft->addWidget(nou);
	}

	QWidget* right = new QWidget;
	QVBoxLayout* lyRigth = new QVBoxLayout;
	right->setLayout(lyRigth);;


	int lines = 10;
	int cols = 4;
	this->tableEvents = new QTableWidget(lines, cols);

	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Descriere" << "Tip" << "Durata";
	this->tableEvents->setHorizontalHeaderLabels(tblHeaderList);
	this->tableEvents->horizontalHeader()->sectionResizeMode(QHeaderView::ResizeToContents);
	lyRigth->addWidget(tableEvents);
	lyMain->addWidget(left);
	lyMain->addWidget(right);
}
void EventsGUI::connectSignalsSlots()
{
	QObject::connect(btnAddEvent, &QPushButton::clicked, this, &EventsGUI::guiAddEvents);
	QObject::connect(btnWish, &QPushButton::clicked, this, [&]() {
		WishListGui* wishlist = new WishListGui{ srv };
		});
	QObject::connect(btnreadonly, &QPushButton::clicked, this, [&]() {
		WishListReadOnly* readonly = new WishListReadOnly{ srv };
		});
	QObject::connect(btnDeleteEvent, &QPushButton::clicked, this, &EventsGUI::guiDeleteEvent);
	QObject::connect(btnModifyEvent, &QPushButton::clicked, this, &EventsGUI::guiModifyEvent);
	QObject::connect(btnSearchEvent, &QPushButton::clicked, this, &EventsGUI::guiFindEvent);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &EventsGUI::guiUndo);
	QObject::connect(btnSort, &QPushButton::clicked, [&]() {
		if (this->radioSrtTitle->isChecked())
			reloadList(this->srv.sortbytitle());
		else if (this->radioSrtDescription->isChecked())
			reloadList(this->srv.sortbydescription());
		});
	QObject::connect(btnfilterByDescription, &QPushButton::clicked, [&]() {
		reloadList(this->srv.filterbydescription(editFilterDescription->text().toStdString()));
		});
	QObject::connect(btnfilterByType, &QPushButton::clicked, [&]() {
		reloadList(this->srv.filterbytype(editFilterType->text().toStdString()));
		});
	for (auto& btn : actualbuttons)
	{
		QObject::connect(btn, &QPushButton::clicked,this, [=]() {
			for(const auto& b: srv.raport())
				if (b.first == btn->text().toStdString())
				{
					QMessageBox::information(this, "Info", QString::number(b.second));
				}
			});
	}

}

void EventsGUI::update()
{
	reloadList(this->srv.get_all());
}

void EventsGUI::reloadList(const vector<Event>& events)
{
	this->tableEvents->clearContents();
	this->tableEvents->setRowCount(events.size());
	int line = 0;
	for (auto& ev : events)
	{
		this->tableEvents->setItem(line, 0, new QTableWidgetItem(QString::fromStdString(ev.get_title())));
		this->tableEvents->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(ev.get_description())));
		this->tableEvents->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(ev.get_type())));
		this->tableEvents->setItem(line, 3, new QTableWidgetItem(QString::number(ev.get_time())));
		line++;
	}
}

void EventsGUI::adaugaButoane()
{
	map<string, int>raport = this->srv.raport();

	for (auto it = actualbuttons.begin();it < actualbuttons.end();it++)
	{
		QPushButton* btn = *it;
		if (raport.find((*it)->text().toStdString()) == raport.end())
		{
			actualbuttons.erase(it);
			delete btn;
			break;
		}
	}
	for (const auto& ev : raport)
	{
		bool found = false;
		for (auto it = actualbuttons.begin();it < actualbuttons.end();it++)
		{
			if (ev.first == (*it)->text().toStdString())
			{
				found = true;
				break;
			}
		}
			if (!found)
			{
				QPushButton* nou = new QPushButton(QString::fromStdString(ev.first));
				actualbuttons.push_back(nou);
				lyLeft->addWidget(nou);
				QObject::connect(nou, &QPushButton::clicked, this, [=]() {
					for (const auto& b : srv.raport())
						if (b.first == nou->text().toStdString())
						{
							QMessageBox::information(this, "Info", QString::number(b.second));
						}
					});
			}
	}
}

//void EventsGUI::connectSignalsWishlist()
//{
//	QObject::connect(btnaddwishlist, &QPushButton::clicked, this, [&]() {
//		try {
//			srv.add_to_wishlist(editAddWishlist->text().toStdString());
//			reloadWishlist(srv.get_wishlist());
//		}
//		catch (const ServiceException& se) {
//			QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
//		}
//		catch (const RepoException& re) {
//			QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.get_message()));
//		}
//		});
//	QObject::connect(btngenerate, &QPushButton::clicked, this, [&]() {
//		try {
//			srv.generate(editGenerate->text().toInt());
//			reloadWishlist(srv.get_wishlist());
//		}
//		catch (const ServiceException& se) {
//			QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
//		}
//		catch (const RepoException& re) {
//			QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.get_message()));
//		}
//		});
//	QObject::connect(btndeletewishlist, &QPushButton::clicked, this, [&]() {
//			srv.delete_wishlist();
//			reloadWishlist(srv.get_wishlist());
//		});
//}

//void EventsGUI::reloadWishlist(const vector<Event>events)
//{
//	/*this->tableEventsWishlist->clearContents();
//	this->tableEventsWishlist->setRowCount(events.size());
//	int line = 0;
//	for (auto& ev : events)
//	{
//		this->tableEventsWishlist->setItem(line, 0, new QTableWidgetItem(QString::fromStdString(ev.get_title())));
//		this->tableEventsWishlist->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(ev.get_description())));
//		this->tableEventsWishlist->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(ev.get_type())));
//		this->tableEventsWishlist->setItem(line, 3, new QTableWidgetItem(QString::number(ev.get_time())));
//		line++;
//	}*/
//	wishlist->clear();
//	for (const auto& a : events)
//	{
//		QListWidgetItem* item = new	QListWidgetItem(QString::fromStdString(a.get_title()));
//		wishlist->addItem(item);
//	}
//}

void EventsGUI::guiAddEvents()
{
	try {
		int id = editId->text().toInt();
		string titlu = editTitlu->text().toStdString();
		string descriere = editDescriere->text().toStdString();
		string tip = editTip->text().toStdString();
		double durata = editDurata->text().toDouble();

		editId->clear();
		editTitlu->clear();
		editDescriere->clear();
		editTip->clear();
		editDurata->clear();

		this->srv.storeEvent(id,titlu, descriere, tip, durata);
		this->adaugaButoane();
		this->reloadList(this->srv.get_all());
		

	
		QMessageBox::information(this, "Info", QString::fromStdString("Activitate adaugata cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_message()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_message()));
	}
}

void EventsGUI::guiDeleteEvent()
{
	try {
		int id = editId->text().toInt();

		editId->clear();
		editTitlu->clear();
		editDescriere->clear();
		editTip->clear();
		editDurata->clear();

		this->srv.deleteEvent(id);
		this->adaugaButoane();
		this->reloadList(this->srv.get_all());
		QMessageBox::information(this, "Info", QString::fromStdString("Stergere realizata cu succes!"));
	}
	catch (const ServiceException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_message()));
	}
}

void EventsGUI::guiModifyEvent()
{
	try {
		int id = editId->text().toInt();
		string titlu = editTitlu->text().toStdString();
		string descriere = editDescriere->text().toStdString();
		string tip = editTip->text().toStdString();
		double durata = editDurata->text().toDouble();

		editId->clear();
		editTitlu->clear();
		editDescriere->clear();
		editTip->clear();
		editDurata->clear();

		this->srv.updateEvent(id, titlu, descriere, tip, durata);
		this->adaugaButoane();
		this->reloadList(this->srv.get_all());
		QMessageBox::information(this, "Info", QString::fromStdString("Modificare realizata cu succes!"));
	}
	catch (const ServiceException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_message()));
	}
	catch (const ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_message()));
	}

}

void EventsGUI::guiFindEvent()
{
	try {
		int id = editId->text().toInt();

		editId->clear();
		editTitlu->clear();
		editDescriere->clear();
		editTip->clear();
		editDurata->clear();

		Event ev = this->srv.findbyid(id);
		QString str = QString::number(ev.get_id());
		str += QString::fromStdString("\n");
		str += QString::fromStdString(ev.get_title());
		str += QString::fromStdString("\n");
		str += QString::fromStdString(ev.get_description());
		str += QString::fromStdString("\n");
		str += QString::fromStdString(ev.get_type());
		str += QString::fromStdString("\n");
		str += QString::number(ev.get_time());
		str += QString::fromStdString("\n");
		QMessageBox::information(this, "Info", str);
	}
	catch (const ServiceException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_message()));
	}
	catch (const ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_message()));
	}
}

void EventsGUI::guiUndo()
{
	try {
		this->srv.undo();
		this->adaugaButoane();
		reloadList(this->srv.get_all());
		QMessageBox::information(this, "Info", QString("Comanda realizata cu succes!"));
	}
	catch (const ServiceException& se)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
	}
}

void WishListGui::connectSignalsSlots()
{
	QObject::connect(btnaddwishlist, &QPushButton::clicked, this, [&]() {
		try {
			srv.add_to_wishlist(editAddWishlist->text().toStdString());
			reloadList(srv.get_wishlist());
		}
		catch (const ServiceException& se) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
		}
		catch (const RepoException& re) {
			QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.get_message()));
		}
		});
	QObject::connect(btngenerate, &QPushButton::clicked, this, [&]() {
		try {
			srv.generate(editGenerate->text().toInt());
			reloadList(srv.get_wishlist());
		}
		catch (const ServiceException& se) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_message()));
		}
		catch (const RepoException& re) {
			QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.get_message()));
		}
		});
	QObject::connect(btndeletewishlist, &QPushButton::clicked, this, [&]() {
		srv.delete_wishlist();
		reloadList(srv.get_wishlist());
		});
}

void WishListGui::initializeGUIComponents()
{
	QWidget* Mainwishlistwindow = new QWidget;
	QHBoxLayout* Mainwishlistlayout = new QHBoxLayout;
	Mainwishlistwindow->setLayout(Mainwishlistlayout);


	QWidget* left = new QWidget;
	QHBoxLayout* lyleft = new QHBoxLayout;
	left->setLayout(lyleft);

	QWidget* listWidget = new QWidget();
	QHBoxLayout* listlayout = new QHBoxLayout();
	listWidget->setLayout(listlayout);
	//wishlist = new QListWidget();
	listlayout->addWidget(wishlistview);
	lyleft->addWidget(listWidget);

	QWidget* right = new QWidget;
	QHBoxLayout* lyright = new QHBoxLayout;
	right->setLayout(lyright);

	QWidget* operations = new QWidget;
	QVBoxLayout* lyoperations = new QVBoxLayout;
	operations->setLayout(lyoperations);

	QWidget* addwishlist = new QWidget;
	QFormLayout* lyaddwishlist = new QFormLayout;
	addwishlist->setLayout(lyaddwishlist);
	btnaddwishlist = new QPushButton("Adauga in wishlist");
	editAddWishlist = new QLineEdit();
	lyaddwishlist->addRow(lbladdwishlist, editAddWishlist);
	lyaddwishlist->addWidget(btnaddwishlist);
	lyoperations->addWidget(addwishlist);

	QWidget* generate = new QWidget;
	QFormLayout* lygenerate = new QFormLayout;
	generate->setLayout(lygenerate);
	btngenerate = new QPushButton("Genereaza");
	editGenerate = new QLineEdit();
	lygenerate->addRow(lblgenerate, editGenerate);
	lygenerate->addWidget(btngenerate);
	lyoperations->addWidget(generate);

	btndeletewishlist = new QPushButton("Sterge Wishlist");
	lyright->addWidget(operations);
	lyright->addWidget(btndeletewishlist);
	Mainwishlistlayout->addWidget(left);
	Mainwishlistlayout->addWidget(right);
	//connectSignalsSlots();
	//reloadList(srv.get_wishlist());
	Mainwishlistwindow->show();
}

void WishListGui::reloadList(const vector<Event>& events)
{
	/*wishlist->clear();
	for (const auto& a : events)
	{
		string format{ '[' + std::to_string(a.get_id()) + ']' + a.get_title() };
		QListWidgetItem* item = new	QListWidgetItem(QString::fromStdString(format));
		wishlist->addItem(item);
	}*/
	wishlist->setEvents(events);
}

void WishListGui::update()
{
	reloadList(this->srv.get_wishlist());
}

void WishListReadOnly::update()
{
	repaint();
}
