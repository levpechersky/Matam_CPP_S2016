#include "Publisher.h"
#include "EncryptionPublisher.h"
#include <string>

using std::string;

void EncryptionPublisher::sendMessage(const string& message,
		const Topic& t) const {
	string temp(message);
	for (unsigned int i = 0; i < temp.length(); i++) {
		temp[i] ^= key;
	}
	Publisher::sendMessage(temp, t);
}
