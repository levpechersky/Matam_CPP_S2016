#include "Publisher.h"
#include "Broker.h"
#include <string>

void Publisher::publishTopic(const Topic& t){
	if(set.insert(t)){
		broker.publishTopic(*this, t);
	}
}

void Publisher::unpublishTopic(const Topic& t){
	if(set.remove(t)){
		broker.unpublishTopic(*this, t);
	}
}

void Publisher::unpublishAll(){
	auto i = set.begin(), end = set.end();
	while(i != end){
		Topic temp = *i;
		set.remove(temp);
		i=set.begin();
	}
}

void Publisher::sendMessage(const std::string& message, const Topic& t) const{
	if(!topicExist(t)){
		throw NonPublishedTopic();
	}
	broker.publishMessage(t, message, *this);
}
