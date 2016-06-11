#ifndef MTM4_SUBSCRIBER_H
#define MTM4_SUBSCRIBER_H

#include <exception>
#include <string>
#include <iostream>
#include "BrokerIfc.h"
#include "Client.h"

using std::ostream;
using std::cout;
using std::string;

class Subscriber : public Client {

public:
	Subscriber(int priority, BrokerIfc& broker, ostream& messagesSink = cout) :
			Client(priority, broker, messagesSink) {};

	Subscriber(const Subscriber& p) = default;
	Subscriber& operator=(const Subscriber&) = default;
	virtual ~Subscriber(){};
	virtual void subscribeToTopic(const Topic& t){};
	virtual void unsubscribeToTopic(const Topic& t){};
	virtual void unsubscribeAll(){};
	virtual void receiveMessage(const string& message, const Topic& t,
			const Client& sender) const{};

};


#endif //MTM4_SUBSCRIBER_H
