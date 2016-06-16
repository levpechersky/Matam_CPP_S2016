#include "Publisher.h"
#include "Broker.h"
#include <string>

using std::ostream;
using std::string;

Publisher::Publisher(int priority, BrokerIfc& broker, ostream& messagesSink) :
		Client(priority, broker, messagesSink) {
	if (priority < 0) {
		throw IllegalPriority();
	}
}

void Publisher::publishTopic(const Topic& t) {
	if (set.insert(t)) {
		broker.publishTopic(*this, t);
	}
}

void Publisher::unpublishTopic(const Topic& t) {
	if (!set.remove(t)) {
		throw NonPublishedTopic();
	} else {
		broker.unpublishTopic(*this, t);
	}
}

void Publisher::unpublishAll(){
	auto i = set.begin(), end = set.end();
	while(i != end){
		unpublishTopic(*i);
		i=set.begin();
	}
}

void Publisher::sendMessage(const string& message, const Topic& t) const {
	if (!topicExist(t)) {
		throw NonPublishedTopic();
	}
	broker.publishMessage(t, message, *this);
}
