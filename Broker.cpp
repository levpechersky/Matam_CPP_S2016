/*
 * Broker.cpp
 *
 */
#include "Broker.h"

void Broker::subscribeToTopic(const Subscriber& sub, const Topic& t) {
	subscribers.insert(const_cast<Subscriber * const>(&sub));
}

void Broker::unsubscribeToTopic(const Subscriber& sub, const Topic& t) {
	subscribers.remove(const_cast<Subscriber * const>(&sub));
}

void Broker::publishTopic(const Publisher& pub, const Topic& t) {
	publishers.insert(const_cast<Publisher * const>(&pub));
}

void Broker::unpublishTopic(const Publisher& pub, const Topic& t) {
	publishers.remove(const_cast<Publisher * const>(&pub));
}

void Broker::publishMessage(const Topic& t, const std::string& message,
		const Client& sender) const {

}

