#include "Client.h"
#include "Subscriber.h"
#include "Broker.h"
#include <string>

using std::cout;
using std::endl;
using std::string;

Subscriber::Subscriber(int priority, BrokerIfc& broker, ostream& messagesSink) :
		Client(priority, broker, messagesSink) {
	if (priority < 0) {
		throw IllegalPriority();
	}
}

void Subscriber::subscribeToTopic(const Topic& t) {
	if (set.insert(t)) {
		broker.subscribeToTopic(*this, t);
	}
}

void Subscriber::unsubscribeToTopic(const Topic& t) {
	if (set.remove(t)) {
		broker.unsubscribeToTopic(*this, t);
	} //TODO else - throw  NonSubscribedTopic
}

void Subscriber::unsubscribeAll(){
	auto i = set.begin(), end = set.end();
	while(i != end){
		unsubscribeToTopic(*i);
		i=set.begin();
	}
}
void Subscriber::receiveMessage(const string& message, const Topic& t,
		const Client& sender) const {
	if (!topicExist(t)) {
		throw NonSubscribedTopic();
	}
	messagesSink << "Topic: " << t << ". Sender: #" << sender.getId()
			<< ". Receiver: #" << getId() << ". Message: " << message
			<< endl;
}
