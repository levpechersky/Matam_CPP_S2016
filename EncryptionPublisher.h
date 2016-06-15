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
	EncryptionPublisher(int priority, BrokerIfc& broker, char key,
			ostream& messagesSink = cout) :
			Publisher(priority, broker, messagesSink), key(key) {};

	EncryptionPublisher(const EncryptionPublisher& p) = delete;
	EncryptionPublisher& operator=(const EncryptionPublisher&) = delete;

	virtual ~EncryptionPublisher(){}
	virtual void sendMessage(const string& message, const Topic& t) const
			override;
};

#endif //MTM4_ENCRYPTIONPUBLISHER_H
