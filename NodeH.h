#pragma once
#ifndef NODEH_H
#define NODEH_H
#include <iostream>
class NodeH
{
private:
	int createFrom;
	int nodeNumber, innovationCreated;
public:
	NodeH();
	NodeH(int createFrom, int nodeNumber, int innovationCreated) : createFrom(createFrom), nodeNumber(nodeNumber), innovationCreated(innovationCreated) {};
	~NodeH();
	friend class HistoricalMarking;
	friend class Individu;
	bool operator == (const NodeH&obj) {
		return (createFrom == obj.createFrom) && (nodeNumber == obj.nodeNumber) && (innovationCreated == obj.innovationCreated);
	}
	friend std::ostream & operator << (std::ostream &out, const NodeH &obj)
	{
		out << obj.createFrom << "\n";
		out << obj.nodeNumber << "\n";
		out << obj.innovationCreated << "\n";
		return out;
	};

	friend std::istream & operator >> (std::istream &in, NodeH &obj)
	{
		in >> obj.createFrom;
		in >> obj.nodeNumber;
		in >> obj.innovationCreated;
		return in;
	};
};

#endif