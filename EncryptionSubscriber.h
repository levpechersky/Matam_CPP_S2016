//
// Created by izikgo on 5/23/2016.
//

#ifndef MTM4_ENCRYPTIONSUBSCRIBER_H
#define MTM4_ENCRYPTIONSUBSCRIBER_H

#include <exception>
#include <string>
#include <iostream>
#include "BrokerIfc.h"
#include "Client.h"
#include "Subscriber.h"

using std::ostream;
using std::cout;
using std::string;

class EncryptionSubscriber : public Subscriber {
	const char key;
public:
    /* EncryptionSubscriber Constructor
     *  @param priority - defines order of receiving messages from broker
     * 		lower values - higher priority. Negative values aren't allowed.
     * 	@param broker - message broker to receive messages from.
     * 	@param key - a key used to decrypt messages	(look receiveMessage
     * 		description)
     * 	@param messagesSink - a stringstream used for printing received messages
     * 		std::cout by default
     *
     *  @Return:
	 * 	a new EncryptionSubscriber object.
     */
	EncryptionSubscriber(int priority, BrokerIfc& broker, char key,
			ostream& messagesSink = cout) :
			Subscriber(priority, broker, messagesSink), key(key) {};

    /* Copy C'tor and assignment operator are deleted.
     * EncryptionSubscriber (or any derived class) cannot be copied or assigned.
     * All usage of EncryptionSubscriber should be done with pointers/references.
     */
	EncryptionSubscriber(const EncryptionSubscriber& p) = delete;
	EncryptionSubscriber& operator=(const EncryptionSubscriber&) = delete;

	/* EncryptionSubscriber destructor.
	 * Delete the EncryptionSubscriber object (this).
	 */
	virtual ~EncryptionSubscriber(){}

    /* Decrypts a message using key, and prints message to messagesSink.
     * Decryption is done in a symmetrical way to encryption - by applying
     * bitwise XOR to each character of the message. If encryption and
     * decryption keys are equal - message will be restored to the original.
     * Otherwise message content will be unreadable.
     *
     * @param message - message to print to messagesSink.
     * @param t - the topic of the message.
     * @param sender -the Publisher that publish the message.
     *
     * Message format: “Topic: <topic>. Sender: #<sender_id>. Receiver: #<receiver_id>.
     * Message: <message_content>”.
     * 		receiver_id- the id of Subscriber that received the message.
     * 		sender_id- the is of the Publisher that publish the message.
     * 		topic-subject to registered subscriber.
     * 		message_content-The message was sent regarding the Publisher.
     *
     * @Return:
	 *  none
     */
	virtual void receiveMessage(const string& message, const Topic& t,
			const Client& sender) const override;
};


#endif //MTM4_ENCRYPTIONSUBSCRIBER_H
