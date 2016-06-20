/*
 * Client.cpp
 *
 */
#include "Client.h"

int Client::nextId = 0;

Client::Client(int priority, BrokerIfc& broker, std::ostream& messagesSink) :
		id(nextId), priority(priority),
		set(SortedSet<Topic, strCompare>()),
		broker(broker), messagesSink(messagesSink) {
	if (priority < 0) {
		throw IllegalPriority();
	}
	nextId++;
}

int Client::getPriority() const {
	return priority;
}

int Client::getId() const {
	return id;
}

bool Client::topicExist(const Topic& t) const {
	auto it = set.find(t), this_end = set.end();
	return it != this_end;
}

bool Client::outOfTopics() const {
	return set.size() == 0;
}

void Client::receiveMaintenanceMessage(const std::string& s) const {
	messagesSink << "Client #" << getId() << " received maintenance message: "
			<< s << std::endl;
}
