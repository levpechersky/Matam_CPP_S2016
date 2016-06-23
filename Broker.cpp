/*
 * Broker.cpp
 *
 */
#include "Broker.h"
using std::pair;

void Broker::subscribeToTopic(const Subscriber& sub,const Topic& t) {
	auto it = subscriber_map.find(t);
	if (it == subscriber_map.end()) {
		SortedSet<const Subscriber*, CompareClients> set;
		set.insert(&sub);
		subscriber_map.insert(
			pair<Topic, SortedSet<const Subscriber*, CompareClients>>(t, set));
	} else {
		subscriber_map.at(t).insert(&sub);
	}
	client_set.insert(&sub);
}

void Broker::unsubscribeToTopic(const Subscriber& sub, const Topic& t) {
	auto it = subscriber_map.find(t);
	if (it == subscriber_map.end())	return;
	subscriber_map.at(t).remove(&sub);
	if (sub.outOfTopics()) {
		client_set.remove(&sub);
	}
}

void Broker::publishTopic(const Publisher& pub, const Topic& t) {
	client_set.insert(&pub);
}

void Broker::unpublishTopic(const Publisher& pub, const Topic& t) {
	if (pub.outOfTopics()) {
		client_set.remove(&pub);
	}
}

void Broker::sendMaintenanceMessageAny(const std::list<Topic>& list,
		const std::string& str) const {
	auto set_end = client_set.end();
	auto list_end = list.end();
	for (auto set_it = client_set.begin(); set_it != set_end; set_it++) {
		for (auto list_it = list.begin(); list_it != list_end; list_it++) {
			if ((*set_it)->topicExist(*list_it)) {
				(*set_it)->receiveMaintenanceMessage(str);
				break;
			}
		}
	}
}

void Broker::sendMaintenanceMessageAll(const std::list<Topic>& list,
		const std::string& str) const {
	if (list.size() == 0)
		return;
	auto set_end = client_set.end(), set_it = client_set.begin();
	for (; set_it != set_end; set_it++) {
		if (allTopicsMatch(*set_it, list)) {
			(*set_it)->receiveMaintenanceMessage(str);
		}
	}
}

bool Broker::allTopicsMatch(const Client* client, const std::list<Topic>& list){
	auto list_end = list.end(), list_it = list.begin();
	for (; list_it != list_end; list_it++) {
		if (!client->topicExist(*list_it)) {
			return false;
		}
	}
	return true;
}

void Broker::publishMessage(const Topic& t, const std::string& message,
		const Client& sender) const {
	auto it = subscriber_map.find(t);
	if (it == subscriber_map.end()) return;
	SortedSet<const Subscriber*, CompareClients> set = subscriber_map.at(t);
	auto set_end = set.end(), set_it = set.begin();
	for (; set_it != set_end; set_it++) {
		(*set_it)->receiveMessage(message, t, sender);
	}
}


