/*
 * Client.cpp
 *
 *  Created on: 10 αιεπ 2016
 *      Author: batel
 */
#include "Client.h"

Client::Client(int priority, BrokerIfc& broker, std::ostream& messagesSink):
   id(nextId),priority(priority),
   set(SortedSet<Topic,strCompare>()),
   broker(broker),sink(messagesSink){
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
void Client::deleteTopic(const Topic& t){
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
