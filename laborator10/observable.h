#pragma once
#include <vector>
#include "observer.h"
using std::vector;
class Observable {
private:
	vector<Observer*>observers;
public:
	void addObserver(Observer* obs)
	{
		observers.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		auto it = std::find(this->observers.begin(), this->observers.end(), obs);
		if (it != this->observers.end()) {
			this->observers.erase(it);
		}
	}
	void NotifyAll()
	{
		for (auto ob : observers)
		{
			ob->update();
		}
	}
};