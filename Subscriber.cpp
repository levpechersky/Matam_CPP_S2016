#include "Client.h"
#include "Subscriber.h"
#include "Broker.h"
#include <string>

Subscriber::Subscriber(int priority, BrokerIfc& broker, ostream& messagesSink) :
   Client(priority, broker,messagesSink) {
      if(priority<0){
	     throw IllegalPriority();
      }
}

void Subscriber::subscribeToTopic(const Topic& t){
	if(set.insert(t)){
		broker.subscribeToTopic(*this, t);
	}
}

void Subscriber::unsubscribeToTopic(const Topic& t){
	if(set.remove(t)){
		broker.unsubscribeToTopic(*this, t);
	}
}

void Subscriber::unsubscribeAll(){
	auto i = set.begin(), end = set.end();
	while(i != end){
		Topic temp = *i;
		set.remove(temp);
		i=set.begin();
	}
}

void Subscriber::receiveMessage(const std::string& message, const Topic& t,
								const Client& sender) const {
	if(!topicExist(t)){
		throw NonSubscribedTopic();
	}
	cout << "Topic: " << t << ". Sender: " << sender.getId() << ". Receiver: "
		<< getId() << ". Message: " << message << std::endl;
}
