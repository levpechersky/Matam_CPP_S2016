#include "Subscriber.h"
#include "EncryptionSubscriber.h"
#include <string>

void EncryptionSubscriber::receiveMessage(const string& message, const Topic& t,
										  const Client& sender) const {
	std::string temp(message);
	for(unsigned int i=0; i<temp.length(); i++){
		temp[i] ^= key;
	}
	Subscriber::receiveMessage(temp, t, sender);
}
