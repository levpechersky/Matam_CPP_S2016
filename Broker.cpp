/*
 * Broker.cpp
 *
 */
#include "Broker.h"
using std::pair;

void Broker::subscribeToTopic(const Subscriber& sub,const Topic& t) {
	map<Topic,SortedSet<Subscriber*, CompareClients>>::iterator it=subscriber_map.find(t);
	if (it != subscriber_map.end()){
	SortedSet<Subscriber*, CompareClients> set;
	set.insert(const_cast<Subscriber * const>(&sub));
	subscriber_map.insert(pair<Topic,SortedSet<Subscriber*, CompareClients>>(t,set));
	}else{
		subscriber_map.at(t).insert(const_cast<Subscriber * const>(&sub));
	}
	client_set.insert(const_cast<Subscriber * const>(&sub));
}

void Broker::unsubscribeToTopic(const Subscriber& sub, const Topic& t) {
	map<Topic,SortedSet<Subscriber*, CompareClients>>::iterator it=subscriber_map.find(t);
	if (it == subscriber_map.end()) return;
	subscriber_map.at(t).remove(const_cast<Subscriber * const>(&sub));
	client_set.remove(const_cast<Subscriber * const>(&sub));
}

void Broker::publishTopic(const Publisher& pub, const Topic& t) {
	client_set.insert(const_cast<Publisher * const>(&pub));
}


void Broker::unpublishTopic(const Publisher& pub, const Topic& t) {
	client_set.remove(const_cast<Publisher * const>(&pub));
}

void Broker::sendMaintenanceMessageAny(std::list<Topic> list,std::string str){
	auto set_end = client_set.end(), set_it = client_set.begin();
	for (; set_it != set_end; set_it++) {
		 if(allTopicsMatch(*set_it, list)){
			(*set_it)->receiveMaintenanceMessage(str);
		 }
	}

}
void Broker::sendMaintenanceMessageAll(std::list<Topic> list,std::string str){
	auto set_end = client_set.end(), set_it = client_set.begin();
	auto list_end = list.end(), list_it = list.begin();

	for (; set_it != set_end; set_it++) {
	   for (; list_it != list_end; list_it++) {
		 if((*set_it)->topicExist(*list_it)){
			(*set_it)->receiveMaintenanceMessage(str);
		 }
	   }
	}
}

bool Broker::allTopicsMatch(Client* client, std::list<Topic> list){
	auto list_end = list.end(), list_it = list.begin();
	for (; list_it != list_end; list_it++) {
		if(!client->topicExist(*list_it)){
			return false;
		}
	}
	return true;
}
