#pragma once
#include <vector>

class IVisitable;

class IVisitor
{
public:
	IVisitor();
	virtual ~IVisitor();

	virtual void visit(IVisitable&) = 0;

};

class IVisitable
{
public:
	IVisitable();
	virtual ~IVisitable();

	void onVisitBy(IVisitor& visitor)
	{
		visitor.visit(*this);
	}
};



class OrderMsg : public IVisitable
{
public:
	char MsgType;
	
};


class RVDeserializer : IVisitor
{
	void publishToGUI()
	{
		OrderMsg msg;
		msg.onVisitBy(*this);
	}

	virtual void visit(IVisitable& visitable)
	{
		OrderMsg& msg = static_cast<OrderMsg&>(visitable);
		switch (msg.MsgType)
		{
		case 'A':
			// deserializeOrderCreateMsg(static_cast<OrderCreateMsg&>(msg));
			break;
		case 'B':
			//deserializeOrderAmendMsg(static_cast<OrderAmendMsg&>(msg));
			break;
		case 'C':
			//deserializeOrderCancelMsg(static_cast<OrderCancelMsg&>(msg));
			break;
		}
	}
};
