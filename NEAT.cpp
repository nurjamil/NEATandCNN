
#include "NEAT.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>


NEAT::NEAT(int num_input, int num_hidden, int num_output, int number_population, double c1, double c2, double c3, double compatible_distance, double mutation_node_rate, double mutation_weight_rate,
	double interspecies_crossover_rate) : num_input(num_input), num_hidden(num_hidden), num_output(num_output), number_population(number_population), c1(c1), c2(c2), c3(c3), compatible_distance(compatible_distance), mutation_node_rate(mutation_node_rate),
	mutation_weight_rate(mutation_weight_rate), interspecies_crossover_rate(interspecies_crossover_rate)
{
	Individu *newInd;
	for (std::size_t i = 0; i < number_population; ++i) {
		newInd = new Individu(num_input, num_hidden, num_output, 0.01);
		population.push_back(newInd);
	}
	history_mark.increment = 0;
	for (auto &gen : population[0]->gen)
		history_mark.gen.push_back(Connection(history_mark.increment++, gen->nodeFromIdx, gen->nodeToIdx));
	std::cout << "history_mark increment " << history_mark.increment << std::endl;
	for (auto &node : population[0]->node)
		history_mark.nodeNumber.push_back(node.nodeNumber());
}
NEAT::NEAT() {

}

NEAT::~NEAT()
{
	for (auto &pop : population) {
		delete pop;
	}
}
void NEAT::start() {
	//std::cout << "mutation rate " << mutation_node_rate << std::endl;
	std::vector<std::string> str;
	bool isLanjut;
		//std::cout << "generation " << i + 1 << std::endl;
		std::cout << "calculate fitness " << std::endl;
		std::cout << "population size" << population.size() << std::endl;
		int count = 0;
		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(training.data), std::end(training.data), rng);
		for (auto &ind : population) {
			std::cout << "individu gen size" << ind->gen.size() << std::endl;
			ind->calculate_fitness(training.data,isLanjut);
			ind->classPredicted(validation.data,isLanjut);
		}

		//std::cout << "species size : " << list_species.size() << std::endl;
		std::cout << "speciation  " << std::endl; speciation();
		std::cout << "species size : " << list_species.size() << std::endl;
		//std::cout << "adjust fitness  " << std::endl; adjust_fitness();
		//std::cout << "species size : " << list_species.size() << std::endl;
		//std::cout << "kill the last  " << std::endl; kill_the_last();
		//std::cout << "crossover" << std::endl; crossover();
		//std::cout << "mutation " << std::endl; mutation();

	
	


}
void NEAT::speciation() {
	species a;
	a.push_back(population[0]);
	list_species.push_back(a);
	for (std::size_t i = 1; i < number_population; ++i) {
		//std::cout << "population ke " << i << std::endl;
		bool isNew = true;
		for (auto &list : list_species) {
			if (population[i]->gen[0]->innovationNumber)std::cout << "yes";
			if (list[0]->gen[(list[0])->gen.size() - 1]->innovationNumber) {
				std::cout << "yes";
			}

			if (population[i]->gen[population[i]->gen.size() - 1]->innovationNumber > (list[0])->gen[(list[0])->gen.size() - 1]->innovationNumber) {
				if (compare(population[i], list[0], true) == true) {
					list.push_back(population[i]);
					isNew = false;
				}
			}
			else if (population[i]->gen[population[i]->gen.size() - 1]->innovationNumber < (list[0])->gen[(list[0])->gen.size() - 1]->innovationNumber) {
				if (compare(list[0], population[i], true) == true) {
					list.push_back(population[i]);
					isNew = false;
				}
			}
			else {
				if (compare(population[i], list[0], false) == true) {
					list.push_back(population[i]);
					isNew = false;
				}
			}
		}
		if (isNew == true) {
			species b;
			b.push_back(population[i]);
			list_species.push_back(b);
		}
		/*
		int nextIndex = population[excessIndex]->gen.size() - 1;
		//find excess
		if (excessIndex != -1)
			for (int j = population[excessIndex]->gen.size() - 1; j >= population[i]->initnum_gen; --j) {
			int c = population[notExcess]->gen.size() - 1;
			if (population[excessIndex]->gen[j]->innovationNumber < population[notExcess]->gen[c]->innovationNumber) {
				nextIndex = j;
				break;
			}
			++excess;
		}
		for (int j = nextIndex, c = population[notExcess]->gen.size() - 1; j >= population[i]->initnum_gen && c>= population[i]->initnum_gen;) {
			if (population[excessIndex]->gen[j]->innovationNumber > population[notExcess]->gen[c]->innovationNumber) {
				++disjoint;
				--j;
			}
			else if (population[excessIndex]->gen[j]->innovationNumber < population[notExcess]->gen[c]->innovationNumber) {
				++disjoint;
				--c;
			}
			else {
				dweight += abs(population[excessIndex]->gen[j]->weight - population[notExcess]->gen[c]->innovationNumber);
				--j;
				--c;
			}
		}*/
		//speciate

	}
}
void NEAT::calculate_fitness_and_backprop() {
	for (auto &pop : population) {
		//population[i].calculate_fitness()
		//pop->calculate_fitness();
	}
}

void NEAT::mutation() {
	for (int i = 0; i < population.size() - 2; ++i) population[i]->mutate(mutation_node_rate, mutation_weight_rate, history_mark);
}
void NEAT::adjust_fitness() {
	for (auto &ind : population) {
		int count = 0;
		for (auto &ind2 : population) {
			if (ind->gen[ind->gen.size() - 1] > ind2->gen[ind2->gen.size() - 1]) {
				if (ind2 != ind) {
					if (compare(ind, ind2, true) == true)
						++count;
				}
			}
			else if (ind->gen[ind->gen.size() - 1] < ind2->gen[ind2->gen.size() - 1]) {
				if (ind != ind2) {
					if (compare(ind2, ind, true) == true)
						++count;
				}
			}
			else {
				if (ind != ind2) {
					if (compare(ind, ind2, false) == true)
						++count;
				}
			}
		}
		ind->fitness = ind->fitness / count;
		//ind->fitness = ind->fitness * 1000;
	}
}
void NEAT::kill_the_last() {
	for (auto &spec : list_species) {
		if (spec.size() > 2) {
			delete spec[spec.size() - 1];
			spec.erase(spec.begin() + spec.size() - 1);
		}
	}
}
void NEAT::crossover() {
	std::vector<Individu *> newPopulation;
	double sumPop = 0;
	double sum = 0;
	for (auto &pop : population) sumPop = sumPop + pop->fitness;
	for (std::size_t i = 0; i < number_population - 2; ++i) {
		//std::cout << i << std::endl;
		double random1 = population[0]->randomNumber(0.0, sumPop);
		double random2;
		//int count = 0;
		double low = 0;
		std::vector<Individu *> ind;
		bool interspecies = false;
		if (population[0]->randomNumber(0.0, 1.0) <= interspecies_crossover_rate) interspecies = true;
		for (auto &spec : list_species) {
			for (auto &id : spec) {
				if (random1 >= low && random1 <= (low + (id)->fitness)) {
					//++count;
					ind.push_back(id);
					if (interspecies == true) break;
				}
				low = low + (id)->fitness;
				/*
				if (random2 >= low && random2 <= (low + id->fitness)) {
					//++count;
					ind.push_back(id);
					low = low + id->fitness;
					if (ind.size() > 2)
						break;
				}*/

			}
			if (ind.size() == 1 && interspecies == false && spec.size() > 1) {
				for (auto &id : spec) sum = sum + (id)->fitness;
				low = 0;
				random2 = population[0]->randomNumber(0.0, sum);
				for (auto &id : spec) {
					if (random2 >= low && random2 <= (low + (id)->fitness)) {
						//++count;
						ind.push_back(id);
						break;
					}
					low = low + (id)->fitness;
				}
				sum = 0;
			}

		}
		if (interspecies == true) {
			random2 = population[0]->randomNumber(0.0, sumPop);
			low = 0;
			for (auto & pop : population) {
				if (random2 >= low && random2 <= (low + pop->fitness)) {
					//++count;
					ind.push_back(pop);
					low = low + pop->fitness;
					break;
				}
			}
			/*
			if (random2 >= low && random2 <= (low + id->fitness)) {
				//++count;
				ind.push_back(id);
				low = low + id->fitness;
				if (ind.size() > 2)
					break;
			}*/
		}
		if (ind.size() > 1) {
			if (ind[0]->gen[ind[0]->gen.size() - 1]->innovationNumber >= ind[1]->gen[ind[1]->gen.size() - 1]->innovationNumber) {
				newPopulation.push_back(new Individu(ind[0], ind[1]));
				/*for (auto &g :  newPopulation[newPopulation.size() - 1]->gen) {
					std::cout << g->weight;
				}*/
			}
			else if (ind[0]->gen[ind[0]->gen.size() - 1]->innovationNumber < ind[1]->gen[ind[1]->gen.size() - 1]->innovationNumber) {
				newPopulation.push_back(new Individu(ind[1], ind[0]));
				/*for (auto &g : newPopulation[newPopulation.size() - 1]->gen) {
					std::cout << g->weight;
				}*/
			}
		}
		else {
			//std::cout << ind.size()<<" "<<i<<" ";
			newPopulation.push_back(new Individu(*ind[0]));
		}
	}
	/*
	for (int i = 0; i < list_species.size();++i) {
		Individu **maxId = NULL;
		double max = -1.0;
		for (int j = 0; j < list_species[i].size();++j) {
			if ((*list_species[i][j])->fitness > max) {
				max = (*list_species[i][j])->fitness;
				maxId = list_species[i][j];
			}
		}
		newPopulation.push_back(*maxId);
		*maxId = NULL;
	}*/
	std::vector<Individu *> max12(2);
	max12[0] = NULL;
	max12[1] = NULL;
	for (int i = 0; i < 2; ++i) {
		double max = -1.0;
		max12[i] = population[0];
		int index = 0;
		for (int j = 0; j < population.size(); ++j) {
			if (population[j]->fitness > max) {
				max12[i] = population[j];
				index = j;
				max = population[j]->fitness;
			}
		}
		population.erase(population.begin() + index);
	}
	newPopulation.push_back(new Individu(*max12[0]));
	newPopulation.push_back(new Individu(*max12[1]));
	delete max12[0];
	delete max12[1];
	for (auto &pop : population) {
		delete pop;
	}
	population.clear();
	list_species.clear();
	population = newPopulation;
	std::cout << "new population size " << population.size();
}

bool NEAT::compare(Individu *excess, Individu *notExcess, bool isExcess) {
	int excessValue = 0;
	int disjoint = 0;
	double dweight = 0.0;
	int nextIndex = excess->gen.size() - 1;
	//find excess
	if (isExcess == true)
		for (int j = excess->gen.size() - 1; j >= excess->initnum_gen; --j) {
			if (excess->gen[j]->innovationNumber <= notExcess->gen[notExcess->gen.size() - 1]->innovationNumber) {
				nextIndex = j;
				break;
			}
			++excessValue;
		}
	/*
	for (int j = nextIndex, c = notExcess->gen.size() - 1; j >= excess->initnum_gen && c >= notExcess->initnum_gen;) {
		if (excess->gen[j]->innovationNumber > notExcess->gen[c]->innovationNumber) {
			++disjoint;
			if (j == excess->initnum_gen && c != excess->initnum_gen) {
				--c;
			}
			else {
				--j;
			}

		}
		else if (excess->gen[j]->innovationNumber < notExcess->gen[c]->innovationNumber) {
			++disjoint;
			if (c == excess->initnum_gen && j != excess->initnum_gen) {
				--j;
			}
			else {
				--c;
			}
		}
		else {
			dweight += abs(excess->gen[j]->weight - notExcess->gen[c]->innovationNumber);
			if (j == excess->initnum_gen && c != excess->initnum_gen) {
				--c;
			}
			else if (c == excess->initnum_gen && j != excess->initnum_gen) {
				--j;
			}
			else {
				--j;
				--c;
			}

		}
	}*/
	int size = excess->gen.size();
	int numinit = excess->initnum_gen;
	for (int i = numinit, start = numinit; i < size; ++i) {
		for (int j = start; j < notExcess->gen.size(); ++j) {
			if (excess->gen[i] > notExcess->gen[j]) {
				++disjoint;
				if (j == notExcess->gen.size() - 1) start = ++j;
			}
			else if (excess->gen[i] < notExcess->gen[j]) {
				++disjoint;
				start = j;
				break;
			}
			else {
				dweight += abs(excess->gen[i]->weight - notExcess->gen[j]->innovationNumber);
				if (j == notExcess->gen.size() - 1) start = j;
				else start = j + 1;
				break;
			}
		}
	}
	double val = ((c1*excessValue) / number_population) + ((c2*disjoint) / number_population);
	//std::cout << "distance value : " << val << std::endl;
	//std::cout << "excess value : " << excessValue << std::endl;
	if (val <= 4.0) {
		return true;
	}
	return false;
}

void NEAT::set_inputTraining(const PrepareInput &pre) {
	this->training = pre;
}


void NEAT::set_inputValidation(const PrepareInput &pre) {
	this->validation = pre;
}


void NEAT::copyPop(const NEAT &neat) {
	population.clear();
	population.shrink_to_fit();
	for (size_t i = 0; i < neat.population.size(); ++i) {
		population.push_back(new Individu(*neat.population[i]));
	}
}

