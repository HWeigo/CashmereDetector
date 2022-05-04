#pragma once

#include "CashmereDetector.h"


class BaseObserver {
public:
	virtual void update() = 0;
};

class BaseSubject
{
private:
	list<BaseObserver*> observers;

public:

	void registerObserver(BaseObserver *ob) {
		observers.push_back(ob);
	}
	void removeObserver(BaseObserver *ob) {
		observers.remove(ob);
	}

	void notifyObservers() {
		for (auto observer : observers) {
			observer->update();
		}
	}
};

class PushMessageObserver : public BaseObserver{
public:
	PushMessageObserver(CashmereDetector *ui, BaseSubject *sub) : ui_(ui), subject_(sub) {
		sub->registerObserver(this);
	};

	void update() {
		ui_->PushMessage("update");
	};
private:
	CashmereDetector *ui_;
	BaseSubject *subject_;
};

class VideoSubject : public BaseSubject {
public:
	void NewInput() {
		notifyObservers();
	}
};


