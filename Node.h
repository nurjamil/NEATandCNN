#pragma once
#ifndef NODE_H
#define NODE_H
#include <vector>
#include <iostream>
class Connection;
enum activation_function { sigmoid = 1, TanH = 2, ReLU = 3, softmax = 4 };
class Node
{
private:
	bool is_input;
	bool is_output;
	int node_number;


public:
	std::vector<Connection *> Idxconn_in;
	std::vector<Connection *> Idxconn_out;
	Node();
	Node(int node_number, bool isInput = false, bool is_output = false);
	//void addConnectionIn(Connection &in);
	//void addConnectionOut(Connection &out);
	//void deleteConnectionIn(Connection *conn);
	//void deleteConnectionOut(Connection *conn);
	//double activatedValue(activation_function afunc = sigmoid);
	bool isInput() const { return is_input; };
	void setIsOutput(bool isOutput);
	bool isOutput() const;
	//double getDValue() const;
	//void setDValue(double dValue);
	//double derivativeValue();
	void setIsInput(bool isInput);
	//void setValue(double value);
	//double getValue() const;
	int nodeNumber() const { return node_number; };
	~Node() {};
	friend class Individu;
	bool operator == (const Node&obj) {
		bool istrue = true;
		for (int i = 0; i < Idxconn_in.size(); ++i) {
			if ((Idxconn_in[i] == obj.Idxconn_in[i]) == false) {
				istrue = false;
					break;
			}
		}
		for (int i = 0; i < Idxconn_out.size(); ++i) {
			if ((Idxconn_out[i] == obj.Idxconn_out[i]) == false) {
				istrue = false;
				break;
			}
		}
		return (istrue) && (is_input == obj.is_input) && (is_output == obj.is_output) && (node_number == obj.node_number);
	}
	friend std::ostream & operator << (std::ostream &out, const Node & obj)
	{
		out << obj.is_input << "\n";
		out << obj.is_output << "\n";
		out << obj.node_number << "\n";
		return out;
	};

	friend std::istream & operator >> (std::istream &in, Node &obj)
	{
		in >> obj.is_input;
		in >> obj.is_output;
		in >> obj.node_number;
		return in;
	};
};

#endif

