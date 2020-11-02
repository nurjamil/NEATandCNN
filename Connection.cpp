
#include "Connection.h"
#include <iostream>


Connection::~Connection()
{
}


/*
void Connection::setWeight(double weight) {
	this->weight = weight;
}


double Connection::getWeight() {
	return this->weight + 0.0;
}

void Connection::updateWeight(const double &val) {
	this->weight = this->weight + val;
	//::cout << "updated";
}
*/
Connection::Connection(const Connection &conn) {
	nodeToIdx = conn.nodeToIdx;
	nodeFromIdx = conn.nodeFromIdx;
	innovationNumber = conn.innovationNumber;
	disable = conn.disable;
	weight = conn.weight;
}
int Connection::getnodeFromIdx() const {
	return this->nodeFromIdx;
}

int Connection::getnodeToIdx() const {
	return this->nodeToIdx;
}

bool Connection::isDisable() const {
	return disable;
}

Connection::Connection() {

}