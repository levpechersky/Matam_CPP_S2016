#ifndef MTM4_BROKER_H
#define MTM4_BROKER_H

#include <map>
#include <list>
#include "SortedSet.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "BrokerIfc.h"
using std::map;

class Broker: public BrokerIfc {
	class CompareClients {
	public:
		bool operator()(const Client& c1, const Client& c2) const {
			return c1.getPriority() == c2.getPriority() ?
					c1.getId() < c2.getId() :
					c1.getPriority() < c2.getPriority();//TODO consider implementing in cpp
		}
		bool operator()(const Client* c1, const Client* c2) const {
			return c1->getPriority() == c2->getPriority() ?
					c1->getId() < c2->getId() :
					c1->getPriority() < c2->getPriority();//TODO consider implementing in cpp
		}
	};

	map<Topic,SortedSet<const Subscriber*, CompareClients>> subscriber_map;
	SortedSet<const Client*, CompareClients> client_set;


	virtual void subscribeToTopic(const Subscriber& sub, const Topic& t);

	virtual void unsubscribeToTopic(const Subscriber& sub, const Topic& t);

	virtual void publishTopic(const Publisher& pub, const Topic& t);
	virtual void unpublishTopic(const Publisher& pub, const Topic& t);

	virtual void publishMessage(const Topic& t, const std::string& message,
			const Client& sender) const;
	void sendMaintenanceMessageAny(std::list<Topic> list,std::string str);
	void sendMaintenanceMessageAll(std::list<Topic> list,std::string str);
	static bool allTopicsMatch(const Client* client,std::list<Topic> list);

public://TODO moved to public temporarily
	Broker() = default;
	Broker(const Broker&) = default;
	Broker& operator=(const Broker&) = default;
	virtual ~Broker() {}

};

#endif //MTM4_BROKER_H
