#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H

#include <exception>
#include <string>
#include "BrokerIfc.h"
#include "SortedSet.h"
#include <functional>
#include <iostream>

class Client {
	struct strCompare{
		bool operator()(const std::string& s1, const std::string& s2){
			return s1.compare(s2) < 0;
		}
	};
	static int nextId;
    const int id;
    const int priority;

protected:
    SortedSet<Topic,strCompare> set;
    BrokerIfc& broker;
    std::ostream& messagesSink;

	void insertTopic(const Topic& t);
	void deleteTopic(const Topic& t);
	void deleteAllTopic();

public:
    class ClientException : public std::exception {};
    class IllegalPriority : public ClientException {};
    class NonSubscribedTopic : public ClientException {};
    class NonPublishedTopic : public ClientException {};

    /* Client Constructor
     *  @param priority - defines order of receiving messages from broker
     * 		lower values - higher priority. Negative values aren't allowed.
     * 	@param broker - message broker to send/receive messages to/from.
     * 	@param messagesSink - a stringstream used for printing received messages
     * 		std::cout by default
     * Throws ClientException::IllegalPriority if priority is negative.
     */
    Client(int priority, BrokerIfc& broker, std::ostream& messagesSink = std::cout);

    /* Copy C'tor and assignment operator are deleted.
     * Client (or any derived class) cannot be copied or assigned.
     * All usage of Client should be done with pointers/references.
     */
    Client(const Client& c) = delete;
    Client& operator=(const Client&) = delete;

    /* Client Destructor
     */
    virtual ~Client(){}

    /* Returns priority of client
     */
    int getPriority() const;

    /* Returns id of client
     */
    int getId() const;

    /* Prints maintenance message to messagesSink.
     * Message format: "Client #<id> received maintenance message: <message>"
     * 		where <id> is this client's id, and <message> is received parameter
     */
    void receiveMaintenanceMessage(const std::string& s) const;

    /* Checks whether client has published/subscribed to/from topic
     * @param t - topic to check for
     *
     * @Return:
     * 	true if client has published/subscribed to/from topic
     * 	false otherwise
     */
	bool topicExist(const Topic& t) const;
};

#endif //MTM4_CLIENT_H
