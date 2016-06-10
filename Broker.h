#ifndef MTM4_BROKER_H
#define MTM4_BROKER_H

#include <map>
#include <list>
#include "SortedSet.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "BrokerIfc.h"

class Broker: public BrokerIfc {
	class CompareClients {
	public:
		bool operator()(const Client& c1, const Client& c2) const;
	};

	SortedSet<Publisher*, CompareClients> publishers;
	SortedSet<Subscriber*, CompareClients> subscribers;

	Broker() = default;
	Broker(const Broker&) = default;
	Broker& operator=(const Broker&) = default;
	virtual ~Broker() {}

	virtual void subscribeToTopic(const Subscriber& sub, const Topic& t);

	virtual void unsubscribeToTopic(const Subscriber& sub, const Topic& t);

	virtual void publishTopic(const Publisher& pub, const Topic& t);

	virtual void unpublishTopic(const Publisher& pub, const Topic& t);

	virtual void publishMessage(const Topic& t, const std::string& message,
			const Client& sender) const;

public:

};

#endif //MTM4_BROKER_H
