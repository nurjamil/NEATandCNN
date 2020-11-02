
#include "Node.h"
#include <math.h>




/*
void Node::deleteConnectionIn(Connection *conn) {
	for (std::vector<Connection *>::iterator itr = conn_in.begin(), int i=0; itr != conn_in.end(); ++itr,++i) {
		if (*itr == conn) conn_in.erase(conn_in.begin() + i);
	}
}
void Node::deleteConnectionOut(Connection *conn) {
	for (std::vector<Connection *>::iterator itr = conn_out.begin(), int i = 0; itr != conn_out.end(); ++itr, ++i) {
		if (*itr == conn) conn_out.erase(conn_out.begin() + i);
	}
}
*/

/*double Node::activatedValue(activation_function afunc) {
	if (afunc == sigmoid) {
		this->value = 1.0 / (1.0 + exp((this->value - (2.0*this->value))));
	}
	return value;
}

void Node::setValue(double value) {
	this->value = 1.0 / (1.0 + exp((value - (2.0*value))));
}

double Node::getValue() const {
	return value;
}*/

void Node::setIsInput(bool isInput) {
	this->is_input = isInput;
}

/*double Node::getDValue() const {
	return dValue;
}

void Node::setDValue(double dValue) {
	this->dValue = dValue;
}


double Node::derivativeValue() {
	return (this->value)*(1.0 - this->value);
}
*/
Node::Node(int node_number, bool isInput, bool isOutput) {
	this->node_number = node_number;
	this->is_input = isInput;
	this->is_output = isOutput;
}

void Node::setIsOutput(bool isOutput) {
	this->is_output = isOutput;
}

bool Node::isOutput() const {
	return this->is_output;
}

Node::Node() {

}

