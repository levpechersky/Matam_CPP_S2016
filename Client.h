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
	SortedSet<Topic,strCompare> set;

protected:
    BrokerIfc& broker;
    std::ostream& sink;
	void insertTopic(const Topic& t);
	void deleteTopic(const Topic& t);
	void deleteAllTopic();

public:
    class ClientException : public std::exception {};
    class IllegalPriority : public ClientException {};
    class NonSubscribedTopic : public ClientException {};
    class NonPublishedTopic : public ClientException {};

    Client(int priority, BrokerIfc& broker, std::ostream& messagesSink = std::cout);
    Client(const Client& c) = default;
    Client& operator=(const Client&) = default;
    virtual ~Client(){};
    int getPriority() const;
    int getId() const;
    void receiveMaintenanceMessage(const std::string& s) const;
};

#endif //MTM4_CLIENT_H
