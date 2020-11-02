#pragma once
#ifndef HISTORICALMARKING_H
#define HISTORICALMARKING_H
#include "Connection.h"
#include "NodeH.h"
#include <vector>
class HistoricalMarking
{
private:
	int increment;
	std::vector<int> nodeNumber;
	std::vector<Connection> gen;
	std::vector<NodeH> newNode;

public:
	HistoricalMarking() { increment = 0; };
	int &getIncrement() { return increment; };
	void setIncrement(int increment) { this->increment = increment; };
	std::vector<Connection> &getGen() { return gen; };
	~HistoricalMarking();
	friend class Individu;
	friend class NEAT;
	bool operator == (const HistoricalMarking &obj) {
		bool istrue = true;
		for (int i = 0; i < nodeNumber.size(); ++i) {
			if ((nodeNumber[i] == obj.nodeNumber[i]) == false) {
				istrue = false;
				break;
			}
		}
		for (int i = 0; i < gen.size(); ++i) {
			if ((gen[i] == obj.gen[i]) == false) {
				istrue = false;
				break;
			}
		}
		for (int i = 0; i < newNode.size(); ++i) {
			if ((newNode[i] == obj.newNode[i]) == false) {
				istrue = false;
				break;
			}
		}
		return (istrue) && (increment == obj.increment);
	}
	friend std::ostream & operator << (std::ostream &out, const HistoricalMarking & obj)
	{
		out << obj.increment << "\n";
		out << obj.nodeNumber.size() << "\n";
		out << obj.gen.size() << "\n";
		out << obj.newNode.size() << "\n";
		for (const auto &nodNum : obj.nodeNumber) out << nodNum << "\n";
		for (const auto &g : obj.gen) out << g;
		for (const auto &newNod : obj.newNode) out << newNod;
		return out;
	};

	friend std::istream & operator >> (std::istream &in, HistoricalMarking &obj)
	{
		int nodeNumberSize;
		int genSize;
		int newNodeSize;
		in >> obj.increment;
		in >> nodeNumberSize;
		in >> genSize;
		in >> newNodeSize;
		obj.nodeNumber.reserve(nodeNumberSize);
		obj.gen.reserve(genSize);
		obj.newNode.reserve(newNodeSize);
		for (int i = 0; i < nodeNumberSize; ++i) {
			int temp;
			in >> temp;
			obj.nodeNumber.push_back(temp);
		}
		for (int i = 0; i < genSize; ++i) {
			Connection temp;
			in >> temp;
			obj.gen.push_back(temp);
		}
		for (int i = 0; i < newNodeSize; ++i) {
			NodeH temp;
			in >> temp;
			obj.newNode.push_back(temp);
		}
		return in;
	};
};

#endif