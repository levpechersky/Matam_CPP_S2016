//
// Created by izikgo on 5/23/2016.
//

#ifndef MTM4_ENCRYPTIONPUBLISHER_H
#define MTM4_ENCRYPTIONPUBLISHER_H

#include <exception>
#include <string>
#include <iostream>
#include "BrokerIfc.h"
#include "Client.h"
#include "Publisher.h"

using std::ostream;
using std::cout;
using std::string;

class EncryptionPublisher: public Publisher {
	const char key;
public:
    /* EncryptionPublisher Constructor
     *  @param priority - defines order of receiving messages from broker
     * 		lower values - higher priority. Negative values aren't allowed.
     * 	@param broker - message broker to send/receive messages to/from.
     * 	@param key - a key used to encrypt messages	(look sendMessage
     * 		description)
     * 	@param messagesSink - a stringstream used for printing received messages
     * 		std::cout by default
     *
     *  @Return:
	 * 	a new EncryptionPublisher object.
     */
	EncryptionPublisher(int priority, BrokerIfc& broker, char key,
			ostream& messagesSink = cout) :
			Publisher(priority, broker, messagesSink), key(key) {};

    /* Copy C'tor and assignment operator are deleted.
     * EncryptionPublisher (or any derived class) cannot be copied or assigned.
     * All usage of EncryptionPublisher should be done with pointers/references.
     */
	EncryptionPublisher(const EncryptionPublisher& p) = delete;
	EncryptionPublisher& operator=(const EncryptionPublisher&) = delete;

	/* EncryptionPublisher destructor.
	 * Delete the EncryptionPublisher object (this).
	 */
	virtual ~EncryptionPublisher(){}

	/* The function passes a message to all Subscribers that registered to topic
	 * A message is encrypted by applying bitwise XOR for each symbol with
	 * a key (single character). Subscriber with different key will receive
	 * unreadable text.
	 *
	 * @param message - the message to be sent about the given topic.
	 * @param t - the topic of the message.
     *
     * @Return:
	 *  none
	 */
	virtual void sendMessage(const string& message, const Topic& t) const
			override;
};

#endif //MTM4_ENCRYPTIONPUBLISHER_H
