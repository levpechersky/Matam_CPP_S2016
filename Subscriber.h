#ifndef MTM4_SUBSCRIBER_H
#define MTM4_SUBSCRIBER_H

#include <exception>
#include <string>
#include <iostream>
#include "BrokerIfc.h"
#include "Client.h"

using std::ostream;
using std::cout;
using std::string;

class Subscriber : public Client {
public:
    /* Subscriber Constructor
     *  @param priority - defines order of receiving messages from broker
     * 		lower values - higher priority. Negative values aren't allowed.
     * 	@param broker - message broker to send/receive messages to/from.
     * 	@param messagesSink - a stringstream used for printing received messages
     * 		std::cout by default
     *
     *  @Return:
	 * 	a new Subscriber object.
     */
	Subscriber(int priority, BrokerIfc& broker,
			ostream& messagesSink = std::cout);

    /* Copy C'tor and assignment operator are deleted.
     * Subscriber (or any derived class) cannot be copied or assigned.
     * All usage of Subscriber should be done with pointers/references.
     */
	Subscriber(const Subscriber& p) = delete;
	Subscriber& operator=(const Subscriber&) = delete;

	/* Subscriber destructor.
	 * Delete the Subscriber object (this).
	 */
	virtual ~Subscriber(){}

	/* After activating this method, each message sent by Publisher
	 * to the given topic, will reach to Subscriber.
	 *
	 * @param t - topic to send message.
	 *
	 * @Return:
	 *  none
	 */
	virtual void subscribeToTopic(const Topic& t);

	/* After activating this method, messages sent to this topic
	 * from the publisher does not reach the subscriber.
	 *
	 * @param t - topic, messages sent to this topic from the publisher
	 * does not reach the subscriber.
	 *
     * Throws:
     *  ClientException::NonSubscribedTopic in case of trying to unsubscribe
     *  from a topic, Subscriber was never subscribed to.
     *
	 * @Return:
	 *  none
	 */
	virtual void unsubscribeToTopic(const Topic& t);

	/* After activation method will not be accepted no message
	 * to the subscriber from any publisher.
	 *
     * Throws:
     *  ClientException::NonSubscribedTopic in case of trying to unsubscribe
     *  from a topic, Subscriber was never subscribed to.
     *
	 * @Return:
	 *  none
	 */
	virtual void unsubscribeAll();

    /* Prints message to messagesSink.
     *
     * @param message - message to print to messagesSink.
     * @param t - the topic of the message.
     * @param sender - the Publisher that publish the message.
     *
     * Message format: “Topic: <topic>. Sender: #<sender_id>. Receiver: #<receiver_id>.
     * Message: <message_content>”.
     * 		receiver_id- the id of Subscriber that received the message.
     * 		sender_id- the is of the Publisher that publish the message.
     * 		topic-subject to registered subscriber.
     * 		message_content-The message was sent regarding the Publisher.
     *
     * Throws:
     *  ClientException::NonSubscribedTopic if the message has reached
     *  with topic that not made for him subscription.
     *
     * @Return:
	 *  none
     */
	virtual void receiveMessage(const string& message, const Topic& t,
			const Client& sender) const;

};


#endif //MTM4_SUBSCRIBER_H
