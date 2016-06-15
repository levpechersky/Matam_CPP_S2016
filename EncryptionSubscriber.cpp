#include "Subscriber.h"
#include "EncryptionSubscriber.h"
#include <string>

using std::string;

void EncryptionSubscriber::receiveMessage(const string& message, const Topic& t,
		const Client& sender) const {
	string temp(message);
	for (unsigned int i = 0; i < temp.length(); i++) {
		temp[i] ^= key;
	}
	Subscriber::receiveMessage(temp, t, sender);
}
