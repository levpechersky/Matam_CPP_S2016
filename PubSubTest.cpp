#include <cstdlib>
#include "Broker.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"
#include "MtmTst.h"
using namespace std;

bool pubSubTestExample() {
    Broker broker;
    stringstream ss;
    Publisher p1(0, broker, ss);
    Subscriber s1(1, broker, ss);
    Subscriber s2(0, broker, ss);
    EncryptionPublisher ep1(1, broker, static_cast<char>(0xFF), ss);
    EncryptionSubscriber es1(2, broker, static_cast<char>(0xFF), ss);

    p1.publishTopic("Cat Videos");
    p1.publishTopic("Dog Videos");
    ep1.publishTopic("Marianas Web");

    s1.subscribeToTopic("Cat Videos");
    s2.subscribeToTopic("Cat Videos");
    s2.subscribeToTopic("Dog Videos");
    es1.subscribeToTopic("Marianas Web");

    p1.sendMessage("This is a cat video", "Cat Videos");
    p1.sendMessage("This is a dog video", "Dog Videos");
    ep1.sendMessage("This is a big secret", "Marianas Web");

    stringstream expected;
    expected << "Topic: " << "Cat Videos" << ". Sender: #" << p1.getId() <<
            ". Receiver: #" << s2.getId() << ". Message: " << "This is a cat video" << endl;
    expected << "Topic: " << "Cat Videos" << ". Sender: #" << p1.getId() <<
    ". Receiver: #" << s1.getId() << ". Message: " << "This is a cat video" << endl;
    expected << "Topic: " << "Dog Videos" << ". Sender: #" << p1.getId() <<
    ". Receiver: #" << s2.getId() << ". Message: " << "This is a dog video" << endl;
    expected << "Topic: " << "Marianas Web" << ". Sender: #" << ep1.getId() <<
    ". Receiver: #" << es1.getId() << ". Message: " << "This is a big secret" << endl;

    ASSERT_EQUALS(expected.str(), ss.str());

    return true;
}

/**************ConstructorTest********************/
/* This part of the test checks the constructor
 * of all classes.
*************************************************/

bool clientConstructorTest(){
	Broker broker;
	ASSERT_THROW(Client::IllegalPriority,Client(-1,broker));
	ASSERT_NO_THROW(Client(1,broker));
	stringstream ss;
	ASSERT_NO_THROW(Client(1,broker,ss));
	return true;

}

bool publisherConstructorTest(){
	Broker broker;
	ASSERT_THROW(Client::IllegalPriority,Publisher(-1,broker));
	ASSERT_NO_THROW(Publisher(1,broker));
	stringstream ss;
	ASSERT_NO_THROW(Publisher(1,broker,ss));
	return true;

}

bool subscriberConstructorTest(){
	Broker broker;
	ASSERT_THROW(Client::IllegalPriority,Subscriber(-1,broker));
	ASSERT_NO_THROW(Subscriber(1,broker));
	stringstream ss;
	ASSERT_NO_THROW(Subscriber(1,broker,ss));
	return true;

}

bool brokerConstructorTest(){
	Broker broker;
	return true;
}

/********************getTest***********************/
/* This part of the test checks the get functions,
 * these functions are methods of the class.
*************************************************/

bool clientGetIdTest(){
    Broker broker;
    stringstream ss;

    Publisher p1(0, broker, ss);
    int offset=p1.getId();
    Subscriber s1(0, broker, ss);
    Subscriber s2(0, broker, ss);

    ASSERT_EQUALS(offset,p1.getId());
    ASSERT_EQUALS(++offset,s1.getId());
    ASSERT_EQUALS(++offset,s2.getId());

    return true;
}

bool clientGetPriorityTest(){

    Broker broker;
    stringstream ss;

    Publisher p1(0, broker, ss);
    Subscriber s1(1, broker, ss);
    Subscriber s2(2, broker, ss);

    ASSERT_EQUALS(0,p1.getPriority());
    ASSERT_EQUALS(1,s1.getPriority());
    ASSERT_EQUALS(2,s2.getPriority());

	 return true;

}

/************************topicTest*****************************/
/* This part of the test checks the functions administering
 * adding, removing and existence of topic.
*************************************************************/
bool clientTopicExistTest(){
    Broker broker;
    stringstream ss;
    Publisher p1(0, broker, ss);
    Subscriber s1(1, broker, ss);
    Subscriber s2(0, broker, ss);

    p1.publishTopic("Cat Videos");
    p1.publishTopic("Dog Videos");
    s1.subscribeToTopic("FOOD magazine");
    s2.subscribeToTopic("wonderful world magazine");
    s2.subscribeToTopic("Butterflies Videos");

    ASSERT_EQUALS(false,s1.topicExist("Topic Does Not Exist"));
    ASSERT_EQUALS(false,s2.topicExist("Topic Does Not Exist"));
    ASSERT_EQUALS(false,p1.topicExist("Topic Does Not Exist"));

    ASSERT_EQUALS(true,p1.topicExist("Cat Videos"));
    ASSERT_EQUALS(true,p1.topicExist("Dog Videos"));
    ASSERT_EQUALS(true,s1.topicExist("FOOD magazine"));
    ASSERT_EQUALS(true,s2.topicExist("wonderful world magazine"));
    ASSERT_EQUALS(true,s2.topicExist("Butterflies Videos"));

    ASSERT_EQUALS(false,s1.topicExist("Butterflies Videos"));
    ASSERT_EQUALS(false,s2.topicExist("FOOD magazine"));
    ASSERT_EQUALS(false,p1.topicExist("FOOD magazine"));

	return true;
}
bool publishAndUnpublishTopicTest(){
    Broker broker;
    stringstream ss;
    Publisher p1(0, broker, ss);
    p1.publishTopic("Cat Videos");
    ASSERT_EQUALS(true,p1.topicExist("Cat Videos"));
    p1.publishTopic("Cat Videos");
    ASSERT_NO_THROW(p1.unpublishTopic("Cat Videos"));
    ASSERT_EQUALS(false,p1.topicExist("Cat Videos"));

    p1.publishTopic("Dog Videos");
    p1.publishTopic("Dog Videos");
    ASSERT_EQUALS(true,p1.topicExist("Dog Videos"));
    ASSERT_NO_THROW(p1.unpublishTopic("Dog Videos"));
    ASSERT_EQUALS(false,p1.topicExist("Dog Videos"));

    ASSERT_THROW(Client::NonPublishedTopic,p1.unpublishTopic("Dog Videos"));
    ASSERT_THROW(Client::NonPublishedTopic,p1.unpublishTopic("Topic Does Not Exist"));

    p1.publishTopic("Cat Videos");
    p1.publishTopic("Cat Videos");
    ASSERT_EQUALS(true,p1.topicExist("Cat Videos"));
    ASSERT_NO_THROW(p1.unpublishTopic("Cat Videos"));
    ASSERT_THROW(Client::NonPublishedTopic,p1.unpublishTopic("Cat Videos"));

	return true;
}

bool subscribeAndUnsubscribeToTopicTest(){
    Broker broker;
    stringstream ss;
    Subscriber s1(0, broker, ss);
    s1.subscribeToTopic("Cat Videos");
    ASSERT_EQUALS(true,s1.topicExist("Cat Videos"));
    s1.subscribeToTopic("Cat Videos");
    ASSERT_NO_THROW(s1.unsubscribeToTopic("Cat Videos"));
    ASSERT_EQUALS(false,s1.topicExist("Cat Videos"));

    s1.subscribeToTopic("Dog Videos");
    s1.subscribeToTopic("Dog Videos");
    ASSERT_EQUALS(true,s1.topicExist("Dog Videos"));
    ASSERT_NO_THROW(s1.unsubscribeToTopic("Dog Videos"));
    ASSERT_EQUALS(false,s1.topicExist("Dog Videos"));

    ASSERT_THROW(Client::NonSubscribedTopic,s1.unsubscribeToTopic("Dog Videos"));
    ASSERT_THROW(Client::NonSubscribedTopic,s1.unsubscribeToTopic("Topic Does Not Exist"));

    s1.subscribeToTopic("Dog Videos");
    s1.subscribeToTopic("Dog Videos");
    ASSERT_EQUALS(true,s1.topicExist("Dog Videos"));
    ASSERT_NO_THROW(s1.unsubscribeToTopic("Dog Videos"));
    ASSERT_THROW(Client::NonSubscribedTopic,s1.unsubscribeToTopic("Dog Videos"));

	return true;
}

bool unsubscribeAllTest(){
    Broker broker;
    stringstream ss;
    Subscriber s1(0, broker, ss);
    s1.subscribeToTopic("Cat Videos");
    s1.subscribeToTopic("FOOD magazine");
    s1.subscribeToTopic("Butterflies Videos");
    s1.unsubscribeAll();
    ASSERT_EQUALS(false,s1.topicExist("Cat Videos"));
    ASSERT_EQUALS(false,s1.topicExist("FOOD magazine"));
    ASSERT_EQUALS(false,s1.topicExist("Butterflies Videos"));

    ASSERT_THROW(Client::NonSubscribedTopic,s1.unsubscribeToTopic("Cat Videos"));
    ASSERT_THROW(Client::NonSubscribedTopic,s1.unsubscribeToTopic("Topic Does Not Exist"));
	return true;
}
bool unpublishAllTest(){
    Broker broker;
    stringstream ss;
    Publisher p1(0, broker, ss);
    p1.publishTopic("Cat Videos");
    p1.publishTopic("FOOD magazine");
    p1.publishTopic("Butterflies Videos");
    p1.unpublishAll();
    ASSERT_EQUALS(false,p1.topicExist("Cat Videos"));
    ASSERT_EQUALS(false,p1.topicExist("FOOD magazine"));
    ASSERT_EQUALS(false,p1.topicExist("Butterflies Videos"));

    ASSERT_THROW(Client::NonPublishedTopic,p1.unpublishTopic("Cat Videos"));
    ASSERT_THROW(Client::NonPublishedTopic,p1.unpublishTopic("Topic Does Not Exist"));
	return true;
}
/*****************Broker sending a message Test*****************/
/* the following tests, check all functions ends a message from
 * Broker to Publisher/ Subscriber.
**************************************************************/

string encode(string s, char key) {
	string temp(s);
	for (unsigned int i = 0; i < temp.length(); i++) {
		temp[i] ^= key;
	}
	return temp;
}

void printExpectedAndActual(const stringstream& expected, const stringstream& actual) {
	cout << "Expected:" << endl << expected.str() << endl
			<< "Actual:" << endl << actual.str() << endl;
}

bool messagePriorityTest(){
	Broker broker;
	stringstream ss, empty;
	string message = "Hello!";

	const Subscriber s0(0, broker, empty);//subscribed to nothing
	Subscriber s1(0, broker, ss);
	Subscriber s2(1, broker, ss);
	Subscriber s3(1, broker, ss);
	EncryptionSubscriber es4(2, broker, '$', ss);
	EncryptionSubscriber es5(2, broker, '*', ss);
	Subscriber s6(0, broker, ss);
	Subscriber s7(1, broker, ss);
	Subscriber s8(1, broker, ss);

	/* Order: s0, s1, s6;   s2, s3, s7, s8;   es4, es5; */

	Publisher pub(0, broker, ss);
	pub.publishTopic("T");

	s1.subscribeToTopic("T");
	s2.subscribeToTopic("T");
	s3.subscribeToTopic("T");
	s6.subscribeToTopic("T");
	s7.subscribeToTopic("T");
	s8.subscribeToTopic("T");
	es4.subscribeToTopic("T");
	es5.subscribeToTopic("T");

	pub.sendMessage(message, "T");

    stringstream expected;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << s1.getId() << ". Message: " << message
			<< endl;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << s6.getId() << ". Message: " << message
			<< endl;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << s2.getId() << ". Message: " << message
			<< endl;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << s3.getId() << ". Message: " << message
			<< endl;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << s7.getId() << ". Message: " << message
			<< endl;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << s8.getId() << ". Message: " << message
			<< endl;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << es4.getId() << ". Message: "
			<< encode(message, '$') << endl;
	expected << "Topic: " << "T" << ". Sender: #" << pub.getId()
			<< ". Receiver: #" << es5.getId() << ". Message: "
			<< encode(message, '*') << endl;

   //(expected, ss);
   ASSERT_EQUALS(expected.str(), ss.str());
   ASSERT_EQUALS(empty.str(), stringstream().str());
   return true;
}

bool maintenanceMessageAnyTest(){
	Broker broker;
	stringstream ss, empty;
	string message = "Today's gonna be a party!",
			error = "You shouldn't print that";
	list<Topic> topics, empty_list;
	topics.push_front("Sex");
	topics.push_front("Drugs");
	topics.push_front("Rock-n-Roll");

	broker.sendMaintenanceMessageAny(topics, message);

	Publisher p0(1, broker, empty);
	p0.publishTopic("Matam");//Unrelated
	Publisher p1(1, broker, ss);
	p1.publishTopic("Sex");//In list
	Publisher p2(1, broker, ss);
	p2.publishTopic("Drugs");//In list
	EncryptionPublisher p3(1, broker, '$', ss);
	p3.publishTopic("Rock-n-Roll");//In list
	Publisher p4(1, broker, ss);
	p4.publishTopic("Sex");
	p4.publishTopic("Drugs");
	p4.publishTopic("C++");//Few topics in list, not all of them

	Subscriber s0(0, broker, empty);
	s0.subscribeToTopic("Matam");//Unrelated
	Subscriber s1(0, broker, ss);
	s1.subscribeToTopic("Sex");//In list
	Subscriber s2(0, broker, ss);
	s2.subscribeToTopic("Drugs");//In list
	EncryptionSubscriber s3(0, broker, '*', ss);
	s3.subscribeToTopic("Rock-n-Roll");//In list
	Subscriber s4(0, broker, ss);
	s4.subscribeToTopic("Sex");
	s4.subscribeToTopic("Drugs");
	s4.subscribeToTopic("C++");//Few topics in list, not all of them

	broker.sendMaintenanceMessageAny(topics, message);
	broker.sendMaintenanceMessageAny(empty_list, error);

	stringstream expected;
	expected << "Client #" << s1.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << s2.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << s3.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << s4.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << p1.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << p2.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << p3.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << p4.getId() << " received maintenance message: "
			<< message << endl;

//	printExpectedAndActual(expected, ss);
	ASSERT_EQUALS(expected.str(), ss.str());
	ASSERT_EQUALS(empty.str(), stringstream().str());
	return true;
}

bool maintenanceMessageAllTest(){
	Broker broker;
	stringstream ss, empty;
	string message = "Today's gonna be a party!",
			error = "You shouldn't print that";
	list<Topic> topics, empty_list;
	topics.push_front("Sex");
	topics.push_front("Drugs");
	topics.push_front("Rock-n-Roll");

	broker.sendMaintenanceMessageAll(topics, message);

	Publisher p0(1, broker, empty);
	p0.publishTopic("Matam");//Unrelated
	Publisher p1(1, broker, empty);
	p1.publishTopic("Sex");// 1 of 3
	Publisher p2(1, broker, empty);
	p2.publishTopic("Sex");
	p2.publishTopic("Drugs");
	p2.publishTopic("C++");// 2 of 3
	Publisher p3(1, broker, ss);
	p3.publishTopic("Sex");
	p3.publishTopic("Drugs");
	p3.publishTopic("Rock-n-Roll");
	p3.publishTopic("C++");// 3 of 3 + additional topic
	EncryptionPublisher p4(1, broker, 'a', ss);
	p4.publishTopic("Sex");
	p4.publishTopic("Drugs");
	p4.publishTopic("Rock-n-Roll");// 3 of 3


	Subscriber s0(0, broker, empty);
	s0.subscribeToTopic("Matam");//Unrelated
	Subscriber s1(0, broker, empty);
	s1.subscribeToTopic("Sex");// 1 of 3
	Subscriber s2(0, broker, empty);
	s2.subscribeToTopic("Sex");
	s2.subscribeToTopic("Drugs");
	s2.subscribeToTopic("C++");// 2 of 3
	Subscriber s3(0, broker, ss);
	s3.subscribeToTopic("Sex");
	s3.subscribeToTopic("Drugs");
	s3.subscribeToTopic("Rock-n-Roll");
	s3.subscribeToTopic("C++");// 3 of 3 + additional topic
	EncryptionSubscriber s4(0, broker, ' ',ss);
	s4.subscribeToTopic("Sex");
	s4.subscribeToTopic("Drugs");
	s4.subscribeToTopic("Rock-n-Roll");// 3 of 3

	broker.sendMaintenanceMessageAll(topics, message);
	//broker.sendMaintenanceMessageAll(empty_list, error); TODO check that case

	stringstream expected;
	expected << "Client #" << s3.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << s4.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << p3.getId() << " received maintenance message: "
			<< message << endl;
	expected << "Client #" << p4.getId() << " received maintenance message: "
			<< message << endl;

//	printExpectedAndActual(expected, ss);
	ASSERT_EQUALS(expected.str(), ss.str());
	ASSERT_EQUALS(empty.str(), stringstream().str());
	return true;
}

bool testSendReceiveMessage() {
	Broker broker;
	stringstream ss, empty;

	const Subscriber s0(0, broker, empty); //subscribed to nothing
	Subscriber s1(0, broker, ss);
	Subscriber s2(1, broker, ss);
	Subscriber s3(1, broker, ss);
	EncryptionSubscriber es4(2, broker, '$', ss);
	EncryptionSubscriber es5(2, broker, '*', ss);
	Subscriber s6(3, broker, empty); //subscribed to unexisting topic

	EncryptionPublisher ep7(2, broker, '$', ss);
	EncryptionPublisher ep8(0, broker, '*', ss);
	Publisher p9(0, broker, ss); //Number of topics and subscribers
	Publisher p10(3, broker, ss); //has topic, never publishes
	const Publisher p11(1, broker, empty); //will never publish topic
	Publisher p12(1, broker, ss); //publishes, no subscribers

	/*Order: s0, s1, ep8, p9;
	 s2, s3, p11;
	 es4, es5, ep7;
	 s6, p10;		 */
//Setting up:
	s6.subscribeToTopic("Easy and well-payed jobs"); //No such topic
	p12.publishTopic("Matam Assignments"); //No subscribers

	p10.publishTopic("Half-life 3"); //Never sends messages
	s1.subscribeToTopic("Half-life 3");
	s2.subscribeToTopic("Half-life 3");
	s3.subscribeToTopic("Half-life 3");

	p9.publishTopic("Cars");
	p9.publishTopic("Art");
	p9.publishTopic("Girls");
	s1.subscribeToTopic("Girls");
	s2.subscribeToTopic("Girls");
	s3.subscribeToTopic("Girls");
	s3.subscribeToTopic("Cars");
	s3.subscribeToTopic("Art");

	ep7.publishTopic("TOR");
	ep7.publishTopic("Conspiracy");
	ep8.publishTopic("Conspiracy");
	es4.subscribeToTopic("Conspiracy");
	es5.subscribeToTopic("TOR");

	p10.publishTopic("Art");
	p10.publishTopic("Girls");

	s1.subscribeToTopic("Art");

//Testing:
	{ //Exceptions
		ASSERT_THROW(Client::NonSubscribedTopic,
				s1.receiveMessage("message", "No such topic", p9));
		ASSERT_THROW(Client::NonSubscribedTopic,
				es4.receiveMessage("message", "No such topic", p9));
	}
	{ //No subscribers, nothing printed, nothing changes
		stringstream expected;
		ss.str("");
		ss.clear();
		p12.sendMessage("Assignment 5 is coming!", "Matam Assignments");
		ASSERT_EQUALS(expected.str(), ss.str());
	}
	{
		stringstream expected;
		ss.str("");
		ss.clear();
		string message = "Trump is reptiloid!";
		ASSERT_NO_THROW(ep7.sendMessage(message, "Conspiracy"));
		expected << "Topic: " << "Conspiracy" << ". Sender: #" << ep7.getId()
				<< ". Receiver: #" << es4.getId() << ". Message: " << message
				<< endl;
		ASSERT_EQUALS(expected.str(), ss.str());
	}
	{
		stringstream expected;
		ss.str("");
		ss.clear();
		string message = "New HiddenWiki URL";
		ASSERT_NO_THROW(es5.unsubscribeToTopic("TOR")); // <======Pub/Sub Change========
		ASSERT_NO_THROW(es4.subscribeToTopic("TOR")); // <======Pub/Sub Change========
		ASSERT_NO_THROW(ep7.sendMessage(message, "TOR"));
		expected << "Topic: " << "TOR" << ". Sender: #" << ep7.getId()
				<< ". Receiver: #" << es4.getId() << ". Message: " << message
				<< endl;
		ASSERT_EQUALS(expected.str(), ss.str());
	}
	{
		stringstream expected;
		ss.str("");
		ss.clear();
		string message = "USA didn't land on Moon!";
		ASSERT_NO_THROW(es5.subscribeToTopic("Conspiracy")); // <======Pub/Sub Change========
		ASSERT_NO_THROW(ep8.sendMessage(message, "Conspiracy"));
		expected << "Topic: " << "Conspiracy" << ". Sender: #" << ep8.getId()
				<< ". Receiver: #" << es4.getId() << ". Message: "
				<< encode(encode(message, '*'), '$') << endl;
		expected << "Topic: " << "Conspiracy" << ". Sender: #" << ep8.getId()
				<< ". Receiver: #" << es5.getId() << ". Message: " << message
				<< endl;
		ASSERT_EQUALS(expected.str(), ss.str());
	}
	{
		stringstream expected;
		ss.str("");
		ss.clear();
		string message = "Bugatti Chiron";
		ASSERT_NO_THROW(p9.sendMessage(message, "Cars"));
		expected << "Topic: " << "Cars" << ". Sender: #" << p9.getId()
				<< ". Receiver: #" << s3.getId() << ". Message: " << message
				<< endl;
		ASSERT_EQUALS(expected.str(), ss.str());
	}
	{
		string message = "Jacek Yerka";
		ASSERT_NO_THROW(p9.unpublishTopic("Art")); // <======Pub/Sub Change========
		ASSERT_THROW(Client::NonPublishedTopic, p9.sendMessage(message, "Art"));
	}
	{
		stringstream expected;
		ss.str("");
		ss.clear();
		string message = "Avril Lavigne";
		ASSERT_NO_THROW(s3.unsubscribeAll()); // <======Pub/Sub Change========
		ASSERT_NO_THROW(p9.sendMessage("Avril Lavigne", "Girls"));
		expected << "Topic: " << "Girls" << ". Sender: #" << p9.getId()
				<< ". Receiver: #" << s1.getId() << ". Message: " << message
				<< endl;
		expected << "Topic: " << "Girls" << ". Sender: #" << p9.getId()
				<< ". Receiver: #" << s2.getId() << ". Message: " << message
				<< endl;
		ASSERT_EQUALS(expected.str(), ss.str());
	}
	{
		stringstream expected;
		ss.str("");
		ss.clear();
		string message = "Street-Art in Tel Aviv";
		ASSERT_NO_THROW(p10.sendMessage(message, "Art"));
		expected << "Topic: " << "Art" << ". Sender: #" << p10.getId()
				<< ". Receiver: #" << s1.getId() << ". Message: " << message
				<< endl;
		ASSERT_EQUALS(expected.str(), ss.str());
	}
	return true;
}

int main() {
    RUN_TEST(pubSubTestExample);
    RUN_TEST(clientConstructorTest);
    RUN_TEST(publisherConstructorTest);
    RUN_TEST(subscriberConstructorTest);
    RUN_TEST(brokerConstructorTest);
    RUN_TEST(clientTopicExistTest);
    RUN_TEST(clientGetIdTest);
    RUN_TEST(clientGetPriorityTest);
    RUN_TEST(publishAndUnpublishTopicTest);
    RUN_TEST(subscribeAndUnsubscribeToTopicTest);
    RUN_TEST(unsubscribeAllTest);
    RUN_TEST(unpublishAllTest);
    RUN_TEST(messagePriorityTest);
    RUN_TEST(maintenanceMessageAnyTest);
    RUN_TEST(maintenanceMessageAllTest);
    RUN_TEST(testSendReceiveMessage);
    return true;
}

