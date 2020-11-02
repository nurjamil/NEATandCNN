#pragma once
#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>
class Connection
{
private:
	bool disable;
	int nodeToIdx;
	int nodeFromIdx;
	int innovationNumber;

public:
	double weight;
	Connection();
	Connection(int innovationNumber, int nodeFromIdx, int nodeToIdx, bool disable = false) : innovationNumber(innovationNumber), nodeFromIdx(nodeFromIdx), nodeToIdx(nodeToIdx), disable(disable) {};
	Connection(const Connection &conn);
	int getnodeToIdx() const;
	bool isDisable() const;
	int getnodeFromIdx() const;
	//double getWeight();
	//void updateWeight(const double &val);
	//void setWeight(double weight);
	~Connection();
	friend class Individu;
	friend class NEAT;
	bool operator ==(const Connection &obj) {
		return (disable == obj.disable) && (nodeToIdx == obj.nodeToIdx) && (nodeFromIdx == obj.nodeFromIdx) && (weight == obj.weight) && (innovationNumber == obj.innovationNumber);
	}
	friend std::ostream & operator << (std::ostream &out, const Connection &obj)
	{
		out << obj.disable << "\n";
		out << obj.weight << "\n";
		out << obj.nodeToIdx << "\n";
		out << obj.nodeFromIdx << "\n";
		out << obj.innovationNumber << "\n";
		return out;
	};

	friend std::istream & operator >> (std::istream &in, Connection &obj)
	{
		in >> obj.disable;
		in >> obj.weight;
		in >> obj.nodeToIdx;
		in >> obj.nodeFromIdx;
		in >> obj.innovationNumber;
		return in;
	};
};

#endif
