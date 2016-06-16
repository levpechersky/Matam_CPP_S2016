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
	/* function object-
	 * Comparison function ,an equation between two client by priority and by ID.
	 * There are two implementations of the function,
	 * the first for references, and the second for pointers.
	 * @param- c1, c2 two client we want to rate.
	 *
	 * @Return:
	 * if priority of c1 is smaller than priority of c2 return true.
	 * if priority of c1 is bigger than priority of c2 return false.
	 * if the priorities are equal, the comparison was made by ID-
	 * if id of c1 is smaller than id of c2 return true.
	 * if id of c1 is bigger than id of c2 return false.
	 */
	class CompareClients {
	public:
		bool operator()(const Client& c1, const Client& c2) const {
			return c1.getPriority() == c2.getPriority() ?
					c1.getId() < c2.getId() :
					c1.getPriority() < c2.getPriority();
		}
		bool operator()(const Client* c1, const Client* c2) const {//TODO may be implemented uisng reference version
			return c1->getPriority() == c2->getPriority() ?
					c1->getId() < c2->getId() :
					c1->getPriority() < c2->getPriority();
		}
	};

	map<Topic,SortedSet<const Subscriber*, CompareClients>> subscriber_map;
	SortedSet<const Client*, CompareClients> client_set;

	/* After activating this method, each message sent by Publisher
	 * to the given topic, will reach to Subscriber.
	 *
	 * @param t - topic to send message.
	 * @param sub - Subscriber to send messages on a given topic.
     *
	 * @Return:
	 *  none
     */
	virtual void subscribeToTopic(const Subscriber& sub, const Topic& t);

	/* After activating this method, messages sent to this topic
	 * from the publisher does not reach the subscriber.
	 *
	 * @param t - topic, messages sent to this topic from the publisher
	 * 	does not reach the subscriber.
	 * @param sub-subscriber that the messages sent to the gievn topic,
	 * 	will not reach to him.
	 *
	 * @Return:
	 *  none
	 */
	virtual void unsubscribeToTopic(const Subscriber& sub, const Topic& t);

	/* After activating this method, each message sent by Publisher
	 * to the given topic, will reach to all the registered Subscribers
	 * ( to this topic ).
	 *
	 * @param t - topic to send message.
	 * @param pub - a Publisher would send a message to the given topic.
	 *
	 * @Return:
	 *  none
	 */
	virtual void publishTopic(const Publisher& pub, const Topic& t);

	/* After activating this method, Publisher can not send messages to This topic.
	 *
	 * @param t - topic that Publisher can not send messages to him.
	 * @param pub - a Publisher that could not send a message to the given topic.
	 *
	 * @Return:
	 *  none
	 */
	virtual void unpublishTopic(const Publisher& pub, const Topic& t);

	/* The function sends a message from a given Publisher to all
	 * Subscriber that registered on a given topic.
	 *
     * @param message - message to send.
     * @param t - the topic of the message.
     * @param sender -the Publisher that publish the message.
	 *
	 * @Return:
	 *  none
	 */
	virtual void publishMessage(const Topic& t, const std::string& message,
			const Client& sender) const;

	/* The function checks if a given client (Subscribers/ Publishers),
	 * registered / posted to all of Topics list
	 *
	 * @Return:
	 *  true - if the client (Subscribers/ Publishers), registered / posted
	 *  	to all of Topics list.
	 *  false - otherwise.
	 */
	static bool allTopicsMatch(const Client* client, std::list<Topic> list);

public:

    /* Broker default Constructor
     *
     *  @Return:
	 * 	a new Broker object.
     */
	Broker() = default;

	/* Broker copy constructor.
	 *
	 * @param Broker - the copied Broker.
	 *
	 * @Return:
	 * a new Broker object.
	 */
	Broker(const Broker&) = default;

	/* Broker assignment operator.
	 *
	 * Get a Broker object, and copy it to this.
	 * @param Broker - the copied Broker object.
	 *
	 * @Return:
	 * 	reference to this.
	 */
	Broker& operator=(const Broker&) = default;

	/* The function sends a control message from Broker to all Subscribers/ Publishers
     * that registered / posted to any of Topics list.
     *
     * @param list - list of topic.
     * @param str - control message.
	 *
	 * @Return:
	 *  none
	 */
	void sendMaintenanceMessageAny(std::list<Topic> list, std::string str);

	/* The function sends a control message from Broker to Subscribers/ Publishers
     * that registered / posted to all of Topics list.
     *
     * @param list - list of topic.
     * @param str - control message.
	 *
	 * @Return:
	 *  none
	 */
	void sendMaintenanceMessageAll(std::list<Topic> list, std::string str);

	/* Broker destructor.
	 * Delete the Broker object (this).
	 */
	virtual ~Broker() {}
};

#endif //MTM4_BROKER_H
