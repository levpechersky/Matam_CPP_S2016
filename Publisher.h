#ifndef MTM4_PUBLISHER_H
#define MTM4_PUBLISHER_H

#include <exception>
#include <string>
#include <iostream>
#include "BrokerIfc.h"
#include "Client.h"

class Publisher: public Client {
public:
    /* Publisher Constructor
     *  @param priority - defines order of receiving messages from broker
     * 		lower values - higher priority. Negative values aren't allowed.
     * 	@param broker - message broker to send/receive messages to/from.
     * 	@param messagesSink - a stringstream used for printing received messages
     * 		std::cout by default
     *
     *  @Return:
	 * 	a new Publisher object.
     */
	Publisher(int priority, BrokerIfc& broker,
			std::ostream& messagesSink = std::cout);

    /* Copy C'tor and assignment operator are deleted.
     * Publisher (or any derived class) cannot be copied or assigned.
     * All usage of Publisher should be done with pointers/references.
     */
	Publisher(const Publisher& p) = delete;
	Publisher& operator=(const Publisher&) = delete;

	/* Publisher destructor.
	 * Delete the Publisher object (this).
	 */
	virtual ~Publisher(){}

	/* After activating this method, each message sent by Publisher
	 * to the given topic, will reach to all the registered Subscribers
	 * ( to this topic ).
	 *
	 * @param t - topic to send message.
	 *
	 * @Return:
	 *  none
	 */
	virtual void publishTopic(const Topic& t);

	/* After activating this method, Publisher can not send messages to This topic.
	 *
	 * @param t - topic that Publisher can not send messages to him.
	 *
	 *  Throws:
     *  ClientException::NonPublishedTopic if trying to unpublish topic,
     *  Publisher didn't publish before
     *
	 * @Return:
	 *  none
	 */
	virtual void unpublishTopic(const Topic& t);

	/* After activation method the Publisher can not send messages to any topic.
	 *
	 *  Throws:
     *  ClientException::NonPublishedTopic if trying to unpublish topic,
     *  Publisher didn't publish before
     *
	 * @Return:
	 *  none
	 */
	virtual void unpublishAll();

	/* The function passes a message to all Subscribers that registered to topic.
	 *
	 * @param message - the message to be sent about the given topic.
	 * @param t - the topic of the message.
	 *
	 *  Throws:
     *  ClientException::NonPublishedTopic if the message has reached
     *  with topic that not made for him publishTopic.
     *
     * @Return:
	 *  none
	 */
	virtual void sendMessage(const std::string& message, const Topic& t) const;

};

#endif //MTM4_PUBLISHER_H
