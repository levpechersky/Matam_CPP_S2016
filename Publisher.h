#ifndef MTM4_PUBLISHER_H
#define MTM4_PUBLISHER_H

#include <exception>
#include <string>
#include <iostream>
#include "BrokerIfc.h"
#include "Client.h"

using std::ostream;
using std::cout;
using std::string;

class Publisher: public Client {

public:
	Publisher(int priority, BrokerIfc& broker, ostream& messagesSink = cout) :
		Client(priority, broker, messagesSink) {};

	Publisher(const Publisher& p) = default;
	Publisher& operator=(const Publisher&) = default;
	virtual ~Publisher(){};
	virtual void publishTopic(const Topic& t){};
	virtual void unpublishTopic(const Topic& t){};
	virtual void unpublishAll(){};
	virtual void sendMessage(const string& message, const Topic& t) const{};

};

#endif //MTM4_PUBLISHER_H
