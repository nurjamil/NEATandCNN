#pragma once
#ifndef NEAT_H
#define NEAT_H
#include "HistoricalMarking.h"
#include "Individu.h"
#include <vector>
#include <iostream>
#include <fstream>
class NEAT
{
private:
	friend class cMain;
	friend class ThreadNEAT;
	int num_input, num_hidden, num_output;
	int start_output;
	int number_population, timeout_generation, minimum_generation;
	double c1, c2, c3, compatible_distance;
	double mutation_node_rate, mutation_weight_rate, interspecies_crossover_rate;
	HistoricalMarking history_mark;
	PrepareInput training,validation;
	std::vector<Individu *> population;
	typedef std::vector<Individu *> species;
	std::vector<species> list_species;
public:
	NEAT(int num_input, int num_hidden, int num_output, int number_population, double c1 = 0.1, double c2 = 0.1, double c3 = 0.6, double compatible_distance = 4.0, double mutation_node_rate = 0.1, double mutation_weight_rate = 0.005,
		double interspecies_crossover_rate = 0.35);
	NEAT();
	const PrepareInput &getTraining() const { return training; };
	const PrepareInput &getValidation() const { return validation; };
	PrepareInput &TrainData() { return training; };
	PrepareInput &ValidationData() { return validation; };
	void speciation();
	void calculate_fitness_and_backprop();
	void adjust_fitness();
	void kill_the_last();
	void set_inputTraining(const PrepareInput &pre);
	void set_inputValidation(const PrepareInput &pre);
	int predict();
	void crossover();
	void start();
	void mutation();
	HistoricalMarking &historyMark() { return history_mark; };
	double Getmutation_node_rate() { return mutation_node_rate; };
	double Getmutation_weight_rate() { return mutation_weight_rate; };
	std::vector<Individu *> &getPopulation() { return population; };
	void copyPop(const NEAT &neat);
	void setNodeMutationRate(double node_mutation_rate) { this->mutation_node_rate = node_mutation_rate; };
	//Individu *mate(Individu *excess, Individu *notExcess);
	bool compare(Individu *excess, Individu *notExcess, bool isExcess);
	bool operator ==(const NEAT&obj) {
		bool istrue = true;
		for (int i = 0; i < population.size(); ++i) {
			if ((population[i] == obj.population[i]) == false) {
				istrue = false;
					break;
			}
		}
		return (istrue) && (population.size() == obj.population.size()) && (num_input == obj.num_input) && (num_hidden == obj.num_hidden) && (num_output == obj.num_output)
			&& (number_population == obj.number_population) && (start_output == obj.start_output) && (c1 == obj.c1) && (c2 == obj.c2) && (c3 == obj.c3) && (compatible_distance == obj.compatible_distance)
			&& (mutation_node_rate == obj.mutation_node_rate) && (mutation_weight_rate == obj.mutation_weight_rate) && (interspecies_crossover_rate == obj.interspecies_crossover_rate)
			&& (history_mark == obj.history_mark);
	};
	friend std::ostream & operator << (std::ostream &out, const NEAT&obj) {
		out << obj.num_input << "\n";
		out << obj.num_hidden << "\n";
		out << obj.num_output << "\n";
		out << obj.number_population << "\n";
		out << obj.start_output << "\n";
		out << obj.c1 << "\n";
		out << obj.c2 << "\n";
		out << obj.c3 << "\n";
		out << obj.compatible_distance << "\n";
		out << obj.mutation_node_rate << "\n";
		out << obj.mutation_weight_rate << "\n";
		out << obj.interspecies_crossover_rate << "\n";
		out << obj.population.size() << "\n";
		out << obj.history_mark;
		for (const auto &pop : obj.population) out << *pop;
		return out;
	};
	friend std::istream & operator >> (std::istream &in, NEAT &obj)
	{
		int size;
		in >> obj.num_input;
		in >> obj.num_hidden;
		in >> obj.num_output;
		in >> obj.number_population;
		in >> obj.start_output;
		in >> obj.c1;
		in >> obj.c2;
		in >> obj.c3;
		in >> obj.compatible_distance;
		in >> obj.mutation_node_rate;
		in >> obj.mutation_weight_rate;
		in >> obj.interspecies_crossover_rate;
		in >> size;
		in >> obj.history_mark;
		for (int i = 0; i < size; ++i) {
			Individu *newInd = new Individu();
			in >> *newInd;
			obj.population.push_back(newInd);
		}
	
		return in;
	};
	~NEAT();
};

#endif