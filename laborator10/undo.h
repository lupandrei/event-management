#pragma once
#include "activitate.h"
#include "repo.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};
class UndoAdauga :public ActiuneUndo {
	Event ActivitateAdaugata;
	Repo& rep;
	Repo& wish;
public:
	UndoAdauga(Repo& rep, Repo& wish, const Event& e) : rep{ rep }, wish{wish}, ActivitateAdaugata{ e } {}
	void doUndo()override {
		rep.deletebyid(ActivitateAdaugata.get_id());
		try {
			wish.deletebyid(ActivitateAdaugata.get_id());
		}
		catch (...) {}
	}
};
class UndoSterge :public ActiuneUndo {
	Event Activitate;
	Repo& rep;
	Repo& wish;
	bool wasInWishlist;
public:
	UndoSterge(Repo& rep, Repo& wish, const Event& e,bool was) :rep{ rep }, wish{ wish }, Activitate{ e }, wasInWishlist{was}{}
	void doUndo()override {
		rep.store(Activitate);
		if(wasInWishlist==true)
			wish.store(Activitate);
	}
};
class UndoModifica :public ActiuneUndo {
	Event Activitate;
	Repo& rep;
	Repo& wish;
public:
	UndoModifica(Repo& rep, Repo& wish, const Event& e) :rep{ rep }, wish{wish}, Activitate{ e }{}
	void doUndo()override {
		rep.update(Activitate);
		try {
			wish.update(Activitate);
		}
		catch (...) {}
	}
};