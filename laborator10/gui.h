#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qlistwidget.h>
#include "Service.h"
#include "observer.h"
#include <qpainter.h>
#include "MyListModel.h"
using std::vector;
using std::string;

class EventsGUI : public QWidget, public Observer {
	Service& srv;


	QHBoxLayout* lyMain = new QHBoxLayout;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	QLabel* lblId = new QLabel{ "Id:" };
	QLabel* lblTitlu = new QLabel{ "Titlu:" };
	QLabel* lblDescriere = new QLabel{ "Descriere:" };
	QLabel* lblTip = new QLabel{ "Tip:" };
	QLabel* lblDurata = new QLabel{ "Durata:" };
	QLabel* lblFilterDescription = new QLabel{ "descriere:" };
	QLabel* lblFilterType = new QLabel{ "tip:" };
	QLabel* lbladdwishlist = new QLabel{ "Adauga in wishlist:" };
	QLabel* lblgenerate = new QLabel{ " Genereaza:" };

	vector<string>butoane;
	vector<QPushButton*>actualbuttons;
	QVBoxLayout* lyBtn;
	QWidget* btndyn = new QWidget;

	QLineEdit* editId;
	QLineEdit* editTitlu;
	QLineEdit* editDescriere;
	QLineEdit* editTip;
	QLineEdit* editDurata;
	QLineEdit* editFilterDescription;
	QLineEdit* editFilterType;
	QLineEdit* editAddWishlist;
	QLineEdit* editGenerate;

	QListWidget* wishlist;

	QPushButton* btnAddEvent;
	QPushButton* btnDeleteEvent;
	QPushButton* btnModifyEvent;
	QPushButton* btnSearchEvent;
	QPushButton* btnfilterByDescription;
	QPushButton* btnfilterByType;
	QPushButton* btnUndo;
	QPushButton* btnWish;
	QPushButton* btnaddwishlist;
	QPushButton* btngenerate;
	QPushButton* btndeletewishlist;
	QPushButton* btnreadonly = new QPushButton("Wishlist read only");

	QTableWidget* tableEvents;
	QTableWidget* tableEventsWishlist;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));
	QRadioButton* radioSrtTitle = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radioSrtDescription = new QRadioButton(QString::fromStdString("Descriere"));
	QPushButton* btnSort;


	void update() override;
	//void wishlistmanagement();
	void adaugaButoane();
	//void connectSignalsWishlist();
	//void reloadWishlist(const vector<Event>);

protected:
	virtual void initializeGUIComponents();
	virtual void connectSignalsSlots();
	virtual void reloadList(const vector<Event>&);
	friend class WishListReadOnly;
public:
	EventsGUI(Service& srv) : srv{ srv } {
		this->srv.addObserver(this);
		initializeGUIComponents();
		reloadList(this->srv.get_all());
		//adaugaButoane();
		connectSignalsSlots();
	}
	void guiAddEvents();
	void guiDeleteEvent();
	void guiModifyEvent();
	void guiFindEvent();
	void guiUndo();
};

class WishListGui : public EventsGUI {
private:
	Service& srv;
	QLineEdit* editAddWishlist;
	QLineEdit* editGenerate;
	QTableWidget* tableEventsWishlist;
	QPushButton* btnWish;
	QPushButton* btnaddwishlist;
	QPushButton* btngenerate;
	QPushButton* btndeletewishlist;
	//QListWidget* wishlist;

	MyListModel* wishlist;
	QListView* wishlistview=new QListView();

	QLabel* lbladdwishlist = new QLabel{ "Adauga in wishlist:" };
	QLabel* lblgenerate = new QLabel{ " Genereaza:" };
	void connectSignalsSlots()override;
	void initializeGUIComponents()override;
	void reloadList(const vector<Event>&)override;
	void update()override;

public:
	WishListGui(Service& srv) : EventsGUI{ srv }, srv{ srv } {
		this->srv.addObserver(this);
		this->initializeGUIComponents();
		wishlist = new MyListModel(srv.get_wishlist());
		wishlistview->setModel(wishlist);
		this->connectSignalsSlots();
		this->reloadList(this->srv.get_wishlist());
	}

};
class WishListReadOnly : public Observer, public QWidget {
private:
	Service& srv;
	void update()override;

public:
	WishListReadOnly(Service& srv) :srv{ srv } {
		this->srv.addObserver(this);
		this->show();
	}
	void paintEvent(QPaintEvent* ev)override {
		QPainter p{ this };
		int x = 10;
		for (const auto& u : srv.get_wishlist())
		{
			p.drawRect(x, 0, 20, 50);
			x += 40;
		}
	}
};