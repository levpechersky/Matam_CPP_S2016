#include <cstdlib>
#include "Broker.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"
#include "MtmTst.h"
using namespace std;

int Client::nextId=0;

bool pubSubTestExample() {
    Broker broker;
    stringstream ss;
    Publisher p1(0, broker, ss);
    Subscriber s1(1, broker, ss);
    Subscriber s2(0, broker, ss);
//    EncryptionPublisher ep1(1, broker, static_cast<char>(0xFF), ss);
//    EncryptionSubscriber es1(2, broker, static_cast<char>(0xFF), ss);

//    p1.publishTopic("Cat Videos");
//    p1.publishTopic("Dog Videos");
//    ep1.publishTopic("Marianas Web");
//
//    s1.subscribeToTopic("Cat Videos");
//    s2.subscribeToTopic("Cat Videos");
//    s2.subscribeToTopic("Dog Videos");
//    es1.subscribeToTopic("Marianas Web");
//
//    p1.sendMessage("This is a cat video", "Cat Videos");
//    p1.sendMessage("This is a dog video", "Dog Videos");
//    ep1.sendMessage("This is a big secret", "Marianas Web");

//    stringstream expected;
//    expected << "Topic: " << "Cat Videos" << ". Sender: #" << p1.getId() <<
//            ". Receiver: #" << s2.getId() << ". Message: " << "This is a cat video" << endl;
//    expected << "Topic: " << "Cat Videos" << ". Sender: #" << p1.getId() <<
//    ". Receiver: #" << s1.getId() << ". Message: " << "This is a cat video" << endl;
//    expected << "Topic: " << "Dog Videos" << ". Sender: #" << p1.getId() <<
//    ". Receiver: #" << s2.getId() << ". Message: " << "This is a dog video" << endl;
//    expected << "Topic: " << "Marianas Web" << ". Sender: #" << ep1.getId() <<
//    ". Receiver: #" << es1.getId() << ". Message: " << "This is a big secret" << endl;
//
//    ASSERT_EQUALS(expected.str(), ss.str());

    return true;
}

int main() {
    RUN_TEST(pubSubTestExample);
    return true;
}

