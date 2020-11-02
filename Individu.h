#pragma once
#include <vector>
#include <random>
#include "Node.h"
#include "Connection.h"
#include "PrepareInput.h"
#include "HistoricalMarking.h"
class Individu
{
private:
	friend class ThreadNEAT;
	friend class cMain;
	int num_input, num_hidden, num_output; //num_hidden = number of hidden node on initialization
	int start, start_hidden, start_output, sum, initnum_gen;
	double fitness;
	std::vector<Node> node;
	std::vector<Connection *> gen;
public:
	double learning_rate;
	Individu();
	Individu(int num_input, int num_hidden, int num_output, double learning_rate);
	Individu(Individu *individu, Individu *individu2);
	Individu(const Individu &individu);
	double calculate_fitness(const std::vector<inputNEAT> &input_, bool &isLanjut);
	double calculateNodeValue(std::vector<Connection *> &in, const inputNEAT &input_, std::vector<double> &nodeValue);
	int predict(const inputNEAT &input_);
	int predict2(const inputNEAT &input_);
	void backpropagate(const inputNEAT &input_, const std::vector<double> &target);
	std::vector<Node> &getNode();
	std::vector<Connection*> &getGen();
	double calcD(int node, std::vector<double> &nodeDValue, std::vector<double> &nodeValue, const inputNEAT &input_);
	void calculateDValue(int node, std::vector<double> &nodeDValue, std::vector<double> &nodeValue, const inputNEAT &input_);
	double getFitness() const;
	double classPredicted(const std::vector<inputNEAT> &input_, bool &isLanjut);
	void haus();
	void mutate(double node_mutation_rate, double weight_mutation_rate, HistoricalMarking &h);
	double randomNumber(double lower_bound, double upper_bound);
	int randomNumberInt(int lower_bound, int upper_bound);
	int level(int node);
	bool checkStackOverflow(int node, int node_from);
	~Individu();
	friend class NEAT;
	bool operator ==(const Individu &obj) {
		bool istrue = true;
		for (int i = 0; i < node.size(); ++i) {
			if ((node[i] == obj.node[i]) == false) {
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
		return (istrue) && (num_input == obj.num_input) && (num_hidden == obj.num_hidden) && (num_output == obj.num_output) && (fitness == obj.fitness) && (start == obj.start)
			&& (start_hidden == obj.start_hidden) && (start_output == obj.start_output) && (learning_rate == obj.learning_rate) && (initnum_gen == obj.initnum_gen)
			&& (sum == obj.sum) && (node.size() == obj.node.size()) && (gen.size() == obj.gen.size());
	}
	friend std::ostream &operator <<(std::ostream &out, const Individu & obj)
	{
		out << obj.num_input << "\n";
		out << obj.num_hidden << "\n";
		out << obj.num_output << "\n";
		out << obj.fitness << "\n";
		out << obj.start << "\n";
		out << obj.start_hidden << "\n";
		out << obj.start_output << "\n";
		out << obj.learning_rate << "\n";
		out << obj.initnum_gen << "\n";
		out << obj.sum << "\n";
		out << obj.node.size() << "\n";
		out << obj.gen.size() << "\n";
		for (size_t i = 0; i < obj.node.size(); ++i) {
			out << obj.node[i];
		}
		for (const auto &con : obj.gen) out << *con;
		return out;
	};
	friend std::istream & operator >> (std::istream &in, Individu &obj)
	{
		size_t nodesize;
		size_t gensize;
		in >> obj.num_input;
		in >> obj.num_hidden;
		in >> obj.num_output;
		in >> obj.fitness;
		in >> obj.start;
		in >> obj.start_hidden;
		in >> obj.start_output;
		in >> obj.learning_rate;
		in >> obj.initnum_gen;
		in >> obj.sum;
		in >> nodesize;
		in >> gensize;
		obj.node.reserve(nodesize);
		obj.gen.reserve(gensize);
		for (size_t i = 0; i < nodesize; ++i) {
			Node no;
			in >> no;
			obj.node.push_back(no);
		}
		for (size_t i = 0; i < gensize; ++i) {
			Connection *newCon = new Connection();
			in >> *newCon;
			//std::cout << obj.node.size() << " " << newCon->getnodeFromIdx() << std::endl;
			obj.node[newCon->getnodeFromIdx()].Idxconn_out.push_back(newCon);
			obj.node[newCon->getnodeToIdx()].Idxconn_in.push_back(newCon);
			obj.gen.push_back(newCon);
		}
		return in;
	};
};

