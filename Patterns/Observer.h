#pragma once
#include <set>

template<class TEvent> 
class Observer
{
public:
	Observer() {};
	virtual ~Observer() {};

	virtual void onEvent(const TEvent&) = 0;

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

	void notifyAllObservers(const TEvent& evt) const {
		for (auto& observer : _observers)
		{
			observer->onEvent(evt);
		}
	}

	bool hasObservers() {
		return !_observers.empty();
	}
	Observers _observers;
};

struct MarketData
{
	MarketData(int bid, int ask) :
		Bid(bid),
		Ask(ask) {}
	int Bid;
	int Ask;
};

class MarketBook : public Observable<MarketData> {
public:
	void OnUpdate(const MarketData& data)
	{
		notifyAllObservers(data);
	}
};


class TradingStrategy : public Observer<MarketData>
{
public:
	void onEvent(const MarketData& event) override {
		std::cout << "TradingStrategy got the event : Bid = " << event.Bid << " , Ask= " << event.Ask << std::endl;
	}
};

class TradeBook : public Observer<MarketData>
{
public:
	void onEvent(const MarketData& event) override {
		std::cout << "TradeBook got the event : Bid = " << event.Bid << " , Ask= " << event.Ask << std::endl;
	}
};

class Client {
public:
	Client() {
		marketbook.addObserver(*(new TradingStrategy()));
		marketbook.addObserver(*(new TradeBook()));
	}
	void process(){
		MarketData data(300,400);
		marketbook.OnUpdate(data);
	}
	MarketBook marketbook;
};

void testObserver()
{
	Client client;
	client.process();
}

