#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H

#include <exception>
#include <string>
#include "BrokerIfc.h"
#include "SortedSet.h"
#include <functional>
#include <iostream>

class Client {
	/* function object-
	 * @param s1,s2- two strings we want to compare lexicographic.
	 *
	 * @Return:
     * If the first string lexicographic smaller form the second string,
     * returned true. otherwise, returned false.
	 */
	class strCompare{
	public:
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
     *
     * Throws:
     *  ClientException::IllegalPriority if priority is negative.
     *
     *  @Return:
	 * 	a new Client object.
     */
    Client(int priority, BrokerIfc& broker, std::ostream& messagesSink = std::cout);

    /* Copy C'tor and assignment operator are deleted.
     * Client (or any derived class) cannot be copied or assigned.
     * All usage of Client should be done with pointers/references.
     */
    Client(const Client& c) = delete;
    Client& operator=(const Client&) = delete;

	/* Client destructor.
	 * Delete the Client object (this).
	 */
    virtual ~Client(){}

    /* @Returns:
     *  priority of client
     */
    int getPriority() const;

    /* @Returns:
     *  id of client
     */
    int getId() const;

    /* Prints maintenance message to messagesSink.
     *
     * @param- s is message to print.
     *
     * Message format: "Client #<id> received maintenance message: <message>"
     * @param of message-
     * 	id- is this client's id.
     * 	message- is received parameter.
     *
     * @Return:
	 *  non.
     */
    void receiveMaintenanceMessage(const std::string& s) const;

    /* Checks whether client has published/subscribed to/from topic.
     *
     * @param t - topic to check for.
     *
     * @Return:
     * 	true if client has published/subscribed to/from topic
     * 	false otherwise
     */
	bool topicExist(const Topic& t) const;
};

#endif //MTM4_CLIENT_H
