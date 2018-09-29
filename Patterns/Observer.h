#pragma once


template<class TEvent> 
class Observer
{
public:
	Observer() {};
	virtual ~Observer() {};

	virtual void onEvent(TEvent&) = 0;

};


template<class TEvent>
class Observable
{
public:
	Observable() {};
	virtual ~Observable() {};

	void addObserver(Observer<TEvent>& observer) {
		_observers.insert(&observer);
	}
	void removeObserver(Observer<TEvent>& observer) {
		_observers.erase(&observer);
	}

protected:
	using Observers = std::set<Observer<TEvent>*>;

	void notifyAllObservers(TEvent& evt) const {
		for (const auto& observer : _observers)
		{
			observer->onEvent(evt);
		}
	}

	bool hasObservers() {
		return !_observers.empty();
	}
	Observers _observers;
};
class MarketData
{

};
class MarketBook : public Observer<MarketData> {
	virtual void onEvent(MarketData& mdata) {

	}
};



