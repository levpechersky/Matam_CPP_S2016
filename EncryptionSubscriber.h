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
	EncryptionSubscriber(int priority, BrokerIfc& broker, char key,
			ostream& messagesSink = cout) :
			Subscriber(priority, broker, messagesSink), key(key) {};

	EncryptionSubscriber(const EncryptionSubscriber& p) = delete;
	EncryptionSubscriber& operator=(const EncryptionSubscriber&) = delete;

	virtual ~EncryptionSubscriber(){}
	virtual void receiveMessage(const string& message, const Topic& t,
			const Client& sender) const override;
};


#endif //MTM4_ENCRYPTIONSUBSCRIBER_H
