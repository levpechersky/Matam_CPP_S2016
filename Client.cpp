/*
 * Client.cpp
 *
 */
#include "Client.h"

Client::Client(int priority, BrokerIfc& broker, std::ostream& messagesSink):
   id(nextId),priority(priority),set(SortedSet<Topic,strCompare>())
   ,broker(broker),messagesSink(messagesSink){
}
int Client::getPriority() const{
	return priority;
}
int Client::getId() const{
	return id;
}
void Client::insertTopic(const Topic& t){
	set.insert(t);
}
void Client::deleteTopic(const Topic& t) {
	set.remove(t);
}
void Client::deleteAllTopic(){
	auto this_end = set.end(), it=set.begin();
	for(;it != this_end ;it++){
		set.remove(*it);
		it=set.begin();
		//this_end = set.end(); Has been pointing to illegal organ
	}
}
bool Client::topicExist(const Topic& t) const{
	auto it=set.find(t),this_end = set.end();
	return it!=this_end;
}
void Client::receiveMaintenanceMessage(const std::string& s) const {
	messagesSink << "Client #" << getId() << " received maintenance message: " << s << std::endl;
}
