
#include "Individu.h"
#include "Connection.h"
#include "Node.h"
#include "HistoricalMarking.h"
#include <random>
#include <vector>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <cstdlib>



Individu::Individu(int num_input, int num_hidden, int num_output, double learning_rate)
{

	this->learning_rate = learning_rate;
	int innov = 0;
	this->num_input = num_input;
	this->num_hidden = num_hidden; //num of hidden node on initialization
	this->num_output = num_output;
	this->start_hidden = num_input;
	this->start_output = num_input + num_hidden;
	this->fitness = 0;
	sum = num_input + num_hidden + num_output;
	node.reserve(sum);
	for (int i = 0; i < sum; ++i) {
		node.push_back(Node(i));
	}
	for (int i = 0; i < num_input; ++i) {
		node[i].setIsInput(true);
	}
	for (int i = start_output; i < start_output + num_output; ++i) {
		node[i].setIsOutput(true);
	}
	int gcount = 0;
	initnum_gen = (num_input*num_hidden) + (num_hidden*num_output);
	Connection *conn;
	if (num_hidden > 0) {
		gen.reserve(initnum_gen);
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen2(rd());
		std::uniform_real_distribution<> dis(-sqrt(1.0 / (num_input + num_hidden)), sqrt(1.0 / (num_input + num_hidden)));
		std::uniform_real_distribution<> dis2(-sqrt(1.0 / (num_output + num_hidden)), sqrt(1.0 / (num_output + num_hidden)));
		for (int i = 0; i < num_hidden; ++i) {
			//node[i + start_hidden].getConn_in().reserve(num_input);
			for (int j = 0; j < num_input; ++j) {
				//Connection *newCon = new Connection(0.1, innov++, node[j], node[start_hidden + i]);
				conn = new Connection(innov++, j, start_hidden + i);
				conn->weight = dis(gen2);
				gen.push_back(conn);
				node[j].Idxconn_out.push_back(conn);
				node[start_hidden + i].Idxconn_in.push_back(conn);
				//std::cout << gen[node[j].Idxconn_out[node[j].Idxconn_out.size()-1]].getnodeFromIdx() << " " << gen[node[j].Idxconn_out[node[j].Idxconn_out.size()-1]].getnodeToIdx() << std::endl;
			}
			for (int j = 0; j < num_output; ++j) {
				//Connection *newCon = new Connection(0.1, innov++, node[start_hidden + i], node[start_output + j]);
				conn = new Connection(innov++, start_hidden + i, start_output + j);
				conn->weight = dis2(gen2);
				gen.push_back(conn);
				node[start_hidden + i].Idxconn_out.push_back(conn);
				node[start_output + j].Idxconn_in.push_back(conn);
				//node[start_hidden + i].addConnectionOut(gen[gen.size()-1]);
				//node[start_output + j].addConnectionIn(gen[gen.size()-1]);
			}
		}

	}
	else {
		gen.reserve(num_input*num_output);
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen2(rd());
		std::uniform_real_distribution<> dis(-sqrt(6 / (num_input + num_output)), sqrt(6 / (num_input + num_output)));
		for (int i = 0; i < num_input; ++i) {
			for (int j = 0; j < num_output; ++j) {
				//Connection *newCon = new Connection(-1 + ((rand() / RAND_MAX) * 2), innov++, node[i], node[start_output + j]);
				conn = new Connection(innov++, i, start_output + j);
				conn->weight = dis(gen2);
				gen.push_back(conn);
				node[i].Idxconn_out.push_back(conn);
				node[start_output + j].Idxconn_in.push_back(conn);
			}
		}
	}

}




Individu::~Individu()
{
	for (auto& gene : gen) {
		delete gene;
	}
}

double Individu::calculate_fitness(const std::vector<inputNEAT> &input_, bool &isLanjut) {
	fitness = 0.0;
	int size = input_.size();
	//std::vector<double> inp_;
	std::vector<double> target(num_output);
	/*
	for (auto& i : input_[0].input_data) {
		std::cout << i << " ";
	}*/

	//std::cout << std::endl;
	//std::cout << "gen size : "<<gen.size()<<std::endl;
	for (unsigned int i = 0; i < size; ++i) {
		if (isLanjut == false) {
			return -1.0;
		}
		//std::cout << "input : ";
		//std::cout << i << std::endl;
		target[input_[i].label] = 1.0;
		//for (auto in : input_[i].input_data) {
			//std::cout << in;
		//}
		//std::cout << " target : "<<input_[i].label;
			//for (auto out : target) {
				//std::cout << out;
		//}
			//std::cout << "weight bfore : " << this->gen[0]->getWeight()<<std::endl;
		backpropagate(input_[i], target);
		//std::cout << "weight after : " << this->gen[0]->getWeight() << std::endl;
		//std::cout << this->gen[0]->getNodeTo()->getDValue();
		std::fill(target.begin(), target.end(), 0.0);
	}
	std::cout << "akurasi training = " << fitness / size << std::endl;
	return fitness / (double)size;
}
int Individu::predict(const inputNEAT &input_) {
	std::vector<double> nodeValue(this->node.size() - this->num_input);
	std::size_t stop_output = start_output + num_output;
	for (std::size_t i = start_output; i < stop_output; ++i) {
		//std::cout << std::fixed;
		//std::cout << std::setprecision(3);
		//std::cout<<" Nodee Value : "<<	<<" "<<std::endl;
		if (node[i].Idxconn_in.size() == 0) {
			//std::cout << "indexmaknyus " << i;
			//std::cin.get();
		}
		calculateNodeValue(node[i].Idxconn_in, input_, nodeValue);

	}
	double max = -1;
	int classPredicted = start_output;
	for (int i = start_output; i < stop_output; ++i) {
		if (max < nodeValue[i - num_input]) {
			max = nodeValue[i - num_input];
			classPredicted = i;

		}
		//if (target[i - start_output] == 0.0) fitness = fitness + (0.0 - nodeValue[i - num_input]);
		//else fitness -= 1 - nodeValue[i - num_input];
	}
	if (input_.label == classPredicted - start_output) return 1;
	return 0;

}

int Individu::predict2(const inputNEAT &input_) {
	std::vector<double> nodeValue(this->node.size() - this->num_input);
	std::size_t stop_output = start_output + num_output;
	for (std::size_t i = start_output; i < stop_output; ++i) {
		//std::cout << std::fixed;
		//std::cout << std::setprecision(3);
		//std::cout<<" Nodee Value : "<<	<<" "<<std::endl;
		if (node[i].Idxconn_in.size() == 0) {
			//std::cout << "indexmaknyus " << i;
			//std::cin.get();
		}
		calculateNodeValue(node[i].Idxconn_in, input_, nodeValue);

	}
	double max = -1;
	int classPredicted = start_output;
	for (int i = start_output; i < stop_output; ++i) {
		if (max < nodeValue[i - num_input]) {
			max = nodeValue[i - num_input];
			classPredicted = i;

		}
		//if (target[i - start_output] == 0.0) fitness = fitness + (0.0 - nodeValue[i - num_input]);
		//else fitness -= 1 - nodeValue[i - num_input];
	}

	return classPredicted - start_output;
}

double Individu::classPredicted(const std::vector<inputNEAT> &input_, bool &isLanjut) {
	double correct = 0.0;
	fitness = 0.0;
	int size = input_.size();
	for (unsigned int i = 0; i < size; ++i) {
		if (isLanjut == false) {
			return -1.0;
		}
		//std::cout << "input : ";
		//std::cout << i << std::endl;
		//target[input_[i].label] = 1.0;
		//for (auto in : input_[i].input_data) {
			//std::cout << in;
		//}
		//std::cout << " target : "<<input_[i].label;
			//for (auto out : target) {
				//std::cout << out;
		//}
			//std::cout << "weight bfore : " << this->gen[0]->getWeight()<<std::endl;
		//backpropagate(input_[i], target);
		//std::cout << "weight after : " << this->gen[0]->getWeight() << std::endl;
		//std::cout << this->gen[0]->getNodeTo()->getDValue();
		//std::fill(target.begin(), target.end(), 0.0);
		//std::cout << "blaaaa " << predict(input_[i]);
		double isCorrect = (double)predict(input_[i]);
		correct += isCorrect;
		fitness += isCorrect;
	}
	std::cout << "test accuracy " << correct / size << std::endl;
	return correct / (double)size;
}
// predict sekaligus backpropagate
void Individu::backpropagate(const inputNEAT &input_, const std::vector<double> &target) {
	//std::cout << "test ";
	//insert input to node input
	//int size = node.size();
	std::vector<double> nodeValue(this->node.size() - this->num_input);
	std::vector<double> nodeDValue(this->node.size() - this->num_input);
	std::size_t stop_output = start_output + num_output;
	for (std::size_t i = start_output; i < stop_output; ++i) {
		if (node[i].Idxconn_in.size() == 0) {
			std::cout << "index " << i;
			std::cin.get();
		}
		calculateNodeValue(node[i].Idxconn_in, input_, nodeValue);

	}
	double ssum = 0.0;
	for (std::size_t i = start_output; i < stop_output; ++i) {
		if (node[i].Idxconn_in.size() == 0) {
			std::cout << "indexmaknyus " << i;
			std::cin.get();
		}
		nodeValue[i - num_input] = exp(nodeValue[i - num_input]);
		ssum += nodeValue[i - num_input];
		//calculateNodeValue(node[i].Idxconn_in, input_, nodeValue);

	}
	for (std::size_t i = start_output; i < stop_output; ++i) {
		if (node[i].Idxconn_in.size() == 0) {
			std::cout << "indexmaknyus" << i;
			std::cin.get();
		}
		nodeValue[i - num_input] = nodeValue[i - num_input] / ssum;
		//calculateNodeValue(node[i].Idxconn_in, input_, nodeValue);

	}
	//check predicted class
	double max = -1;
	int classPredicted = start_output;
	for (int i = start_output; i < stop_output; ++i) {
		if (max < nodeValue[i - num_input]) {
			max = nodeValue[i - num_input];
			classPredicted = i;

		}
		//if (target[i - start_output] == 0.0) fitness = fitness + (0.0 - nodeValue[i - num_input]);
		//else fitness -= 1 - nodeValue[i - num_input];
	}
	if (target[classPredicted - start_output] == 1.0)
		fitness += 1.0;

	//find delta value for every node *except input node"
	for (int i = start_output; i < stop_output; ++i) {
		//std::cout << "value = " << value<<std::endl;
		//nodeDValue[i - num_input] = (target[i - start_output] - nodeValue[i - num_input]) * ((nodeValue[i - num_input])*(1.0 - nodeValue[i - num_input]));
		nodeDValue[i - num_input] = -1 * (nodeValue[i - num_input] - target[i - start_output]);
	
	}
	for (std::size_t i = start_output; i < stop_output; ++i) {
		auto &in = node[i].Idxconn_in;
		for (auto &j : in) {
			int nodef = j->nodeFromIdx;
			if (nodef >= num_input && j->disable == false)
				calculateDValue(nodef, nodeDValue, nodeValue, input_);
		}
	}



}
void Individu::haus() {
	//int size = node[start_hidden].getConn_in().size();
	double value = 0.0;
	Connection *tempConn;
	for (int j = 0; j < num_hidden; ++j) {
		for (int i = 0; i < 0; ++i) {
			//	tempConn = node[start_hidden + j].getConn_in()[i];
				//std::cout << "alamat node dan weight  : " << node[start_hidden + j] << "   " << tempConn->getNodeTo() << std::endl;
		}
		value = 0.0;
	}


}

double Individu::calculateNodeValue(std::vector<Connection *> &in, const inputNEAT &input_, std::vector<double> &nodeValue) {
	double value = 0.0;
	if (in.size() <= 0) {
		return 0.0;
	}
	//std::cout << in.size() << " ";
	//std::cout << "size : " << size << std::endl;
	//std::cout << "Value : " << value<<std::endl;
	for (auto &i : in) {
		int nodef = i->nodeFromIdx;
		if (i->disable == false) {
			if (nodef < num_input) {
				//std::cout << input_.input_data[i->getnodeFromIdx()] <<" ";
				//std::cout << input_.input_data[i->getnodeFromIdx()] ;
				value = value + (input_.input_data[nodef] * i->weight);
			}
			else if (nodeValue[i->getnodeFromIdx() - num_input] == 0.0) {
				//std::cout << "node value : " << tempConn->getNodeFrom()->getValue() << std::endl;
				value = value + (calculateNodeValue(node[nodef].Idxconn_in, input_, nodeValue) * i->weight);
			}
			else {
				value = value + (nodeValue[nodef - num_input] * i->weight);
			}
		}
	}
	//std::cout << "value 2 :" << value;
	if (node[in[0]->nodeToIdx].isOutput() == true);
	//value = exp(value);
	else {
		value = 1.0 / (1.0 + exp(-value));
		//if (value < 0.0) value = 0;
	}

	//value = exp(value);
	if ((in[0]->nodeToIdx - num_input) > nodeValue.size()) {
		std::cout << "ERROR " << in[0]->nodeToIdx;
		std::cin.get();
	}
	nodeValue[in[0]->getnodeToIdx() - num_input] = value;
	//std::cout << "node Value : " << value << std::endl;
	//std::cout << "value : " << nodeValue[gen[in[0]].getnodeToIdx() - num_input] << " index : "<< gen[in[0]].getnodeToIdx() - num_input<<std::endl;
	return value;
}

void Individu::calculateDValue(int node, std::vector<double> &nodeDValue, std::vector<double> &nodeValue, const inputNEAT &input_) {
	//double dValue = 0.0;
	if (nodeDValue[node - num_input] == 0.0) {
		//std::cout << "masuk";
		calcD(node, nodeDValue, nodeValue, input_);
	}
	std::vector<Connection *> &in = this->node[node].Idxconn_in;
	for (auto &i : in) {
		int nodef = i->nodeFromIdx;
		if (i->disable == false) {
			if (nodef >= num_input) {
				if (nodeDValue[nodef - num_input] != 0.0)
					calculateDValue(nodef, nodeDValue, nodeValue, input_);
			}
			else {
				i->weight = i->weight + (nodeDValue[node - num_input] * input_.input_data[nodef] * learning_rate);
			}
		}
		//if(this->node[gen[i].getnodeFromIdx()].isInput() != true || nodeDValue[gen[i].getnodeFromIdx() - num_input] != 0.0)

	}
}

double Individu::calcD(int node, std::vector<double> &nodeDValue, std::vector<double> &nodeValue, const inputNEAT &input_) {
	double dValue = 0.0;
	std::vector<Connection *> &out = this->node[node].Idxconn_out;
	for (auto &i : out) {
		int nodet = i->nodeToIdx;
		if (i->disable == false) {
			if (this->node[nodet].isOutput() != true && nodeDValue[nodet - num_input] == 0.0) {
				//std::cout << "masuk";
				dValue += calcD(nodet, nodeDValue, nodeValue, input_) * i->weight;
			}
			else {
				dValue += i->weight * nodeDValue[nodet - num_input];
			}
		}
	}
	dValue = dValue * (nodeValue[node - num_input] * (1.0 - nodeValue[node - num_input]));
	nodeDValue[node - num_input] = dValue;
	for (auto &i : this->node[node].Idxconn_out) {
		int nodef = i->nodeFromIdx;
		int nodet = i->nodeToIdx;
		if (i->disable == false) {
			if (nodef >= num_input) {
				i->weight = i->weight + (nodeDValue[nodet - num_input] * nodeValue[nodef - num_input] * learning_rate);
			}
			else {
				i->weight = i->weight + (nodeDValue[nodet - num_input] * input_.input_data[nodef] * learning_rate);
			}
		}
	}
	//std::cout << "node number : " << node ;0.12
	//std::cout << "dValue hidden : "<< dValue << std::endl;
	//std::cout << dValue << std::endl;
	return dValue;
}

std::vector<Node> &Individu::getNode() {
	return node;
}

std::vector<Connection*> &Individu::getGen() {
	return gen;
}

double Individu::randomNumber(double lower_bound, double upper_bound) {


	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(lower_bound, upper_bound);
	return dis(gen);
}

int Individu::randomNumberInt(int lower_bound, int upper_bound) {


	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(lower_bound, upper_bound);
	return dis(gen);
}

double Individu::getFitness() const {
	return this->fitness;
}

void Individu::mutate(double node_mutation_rate, double weight_mutation_rate, HistoricalMarking &h) {
	// for every gen/link
	//std::cout << "mutaion " << std::endl;
	Connection *newCon;
	int size = gen.size();
	int rand = randomNumberInt(100, 150);
	for (int j = 0; j < rand; ++j) {
		if (randomNumber(0.0, 1.0) <= node_mutation_rate) {
			if (randomNumber(0.0, 1.0) > 0.5) {
				//add node
				//std::cout << "stuck here 1?" << std::endl;
				bool isnewNode = true;
				int randomLink = randomNumberInt(0, gen.size() - 1);
				if (gen[randomLink]->disable == false) {
					for (auto &b : h.newNode) {
						//is newnode or not check from historical marking
						if (b.createFrom == gen[randomLink]->innovationNumber) {
							//not a newnode, push this node and its new connection from historical marking to the individu
							isnewNode = false;
							this->node.push_back(Node(b.nodeNumber));
							newCon = new Connection(b.innovationCreated, gen[randomLink]->nodeFromIdx, node.size() - 1);
							newCon->weight = 1.0;
							this->gen.push_back(newCon);
							this->node[gen[randomLink]->nodeFromIdx].Idxconn_out.push_back(newCon);
							this->node[node.size() - 1].Idxconn_in.push_back(newCon);
							newCon = new Connection(b.innovationCreated + 1, node.size() - 1, gen[randomLink]->nodeToIdx);
							newCon->weight = randomNumber(-1.0, 1.0);
							//std::cout << newCon->weight ;
							this->gen.push_back(newCon);
							this->node[node.size() - 1].Idxconn_out.push_back(newCon);
							this->node[gen[randomLink]->nodeToIdx].Idxconn_in.push_back(newCon);
							gen[randomLink]->disable = true;
							break;

						}

					}
					if (isnewNode == true) {
						//create new node, and create its connection then push it to historicalmarking and the individu itself
						h.nodeNumber.push_back(h.nodeNumber[h.nodeNumber.size() - 1] + 1);
						this->node.push_back(Node(h.nodeNumber[h.nodeNumber.size() - 1]));
						h.newNode.push_back(NodeH(gen[randomLink]->innovationNumber, h.nodeNumber[h.nodeNumber.size() - 1], h.increment));
						h.gen.push_back(Connection(h.increment, this->node[gen[randomLink]->nodeFromIdx].nodeNumber(), h.nodeNumber[h.nodeNumber.size() - 1]));
						newCon = new Connection(h.increment++, gen[randomLink]->nodeFromIdx, this->node.size() - 1);
						newCon->weight = 1.0;
						this->gen.push_back(newCon);
						this->node[gen[randomLink]->nodeFromIdx].Idxconn_out.push_back(newCon);
						this->node[node.size() - 1].Idxconn_in.push_back(newCon);
						h.gen.push_back(Connection(h.increment, h.nodeNumber[h.nodeNumber.size() - 1], this->node[gen[randomLink]->nodeToIdx].nodeNumber()));
						newCon = new Connection(h.increment++, this->node.size() - 1, gen[randomLink]->nodeToIdx);
						newCon->weight = randomNumber(-1.0, 1.0);
						this->gen.push_back(newCon);
						this->node[this->node.size() - 1].Idxconn_out.push_back(newCon);
						this->node[gen[randomLink]->nodeToIdx].Idxconn_in.push_back(newCon);
						gen[randomLink]->disable = true;
					}
					//sort the connection
					for (int k = 0; k < 2; k++) {
						for (std::size_t j = gen.size() - (2 - k); j >= initnum_gen + 1; --j) {
							if (this->gen[j]->innovationNumber > this->gen[j - 1]->innovationNumber) {
								Connection *temp2 = this->gen[j - 1];
								this->gen[j - 1] = this->gen[j];
								this->gen[j] = temp2;
							}
							else {
								break;
							}
						}
					}
				}
			}

			else {
				//add link
				// connect it to random node, and check if its new connection from historicalmarking , and push it with its innovationnumber if its already in historicalmarking
				// if its newconnection in historicalmarking, create new connection in historicalmarking and ++ the increment and put it in the new connection
				int randomfrom = randomNumberInt(0, node.size() - 1);
				int randomto = randomNumberInt(num_input, this->node.size() - 1);
				bool isAllowed = true;
				//check if the randomnumber already connected to its fromnode
				for (auto &ccd : this->node[randomfrom].Idxconn_out) {
					if (randomto == ccd->nodeToIdx)
						isAllowed = false;
				}
				if (level(randomfrom) >= level(randomto)) isAllowed = false;
				if (randomto == randomfrom) isAllowed = false;
				//if itsnot already connected then create the newconncetion to the individu or historicalmarking to the individu
				if (isAllowed == true) {
					bool isNewConnection = true;
					//std::cout << "random " << random << "nodefrom  " << gen[i]->nodeFromIdx << std::endl;
					for (std::size_t j = initnum_gen; j < h.gen.size(); ++j) {
						if (this->node[randomfrom].nodeNumber() == h.gen[j].nodeFromIdx && this->node[randomto].nodeNumber() == h.gen[j].nodeToIdx) {
							//its not a new connection from historicalmarking, put the connection from that historicalmarking to this individu
							newCon = new Connection(h.gen[j].innovationNumber, randomfrom, randomto);
							newCon->weight = randomNumber(-1.0, 1.0);
							this->gen.push_back(newCon);
							this->node[randomfrom].Idxconn_out.push_back(newCon);
							this->node[randomto].Idxconn_in.push_back(newCon);
							isNewConnection = false;
							break;
						}
					}
					if (isNewConnection == true) {
						//a new connection from historicalmarking, add it to historicalmarking and ++increment, and then push it to this individu
						h.gen.push_back(Connection(h.increment, this->node[randomfrom].nodeNumber(), this->node[randomto].node_number));
						newCon = new Connection(h.increment++, randomfrom, randomto);
						newCon->weight = randomNumber(-1.0, 1.0);
						this->gen.push_back(newCon);
						this->node[randomfrom].Idxconn_out.push_back(newCon);
						this->node[randomto].Idxconn_in.push_back(newCon);
					}
				}
				//sort the connection;

				for (std::size_t j = gen.size() - 1; j >= initnum_gen + 1; --j) {
					if (this->gen[j]->innovationNumber > this->gen[j - 1]->innovationNumber) {
						Connection *temp2 = this->gen[j - 1];
						this->gen[j - 1] = this->gen[j];
						this->gen[j] = temp2;
					}
					else
					{
						break;
					}
				}
			}
		}
	}


	for (int i = 0; i < size; ++i) {
		

		if (randomNumber(0.0, 1.0) <= weight_mutation_rate) {
			/*mutate weight to random number*/
			gen[i]->weight = randomNumber(-1.0, 1.0);
		}
	}
	//std::cout << "gen size 2: " << gen.size() << std::endl;




}

Individu::Individu(Individu *individu, Individu *individu2) {
	learning_rate = individu->learning_rate;
	std::cout << "BRAAAH" << std::endl;
	int nextIndex = individu->gen.size() - 1;
	std::vector<Connection *> excess;
	int count = 0;
	for (int j = nextIndex; j >= individu->initnum_gen; --j) {
		if (individu->gen[j]->innovationNumber <= individu2->gen[individu2->gen.size() - 1]->innovationNumber) {
			nextIndex = j;
			break;
		}
		++count;
	}
	int innov = 0;
	start = individu->start;
	this->num_input = individu->num_input;//num_input;
	this->num_hidden = individu->num_hidden; //num of hidden node on initialization
	this->num_output = individu->num_output;
	this->start_hidden = individu->num_input;
	this->start_output = num_input + num_hidden;
	this->fitness = 0;
	sum = num_input + num_hidden + num_output;
	node.reserve(sum);
	for (int i = 0; i < sum; ++i) {
		node.push_back(Node(i));
	}
	for (int i = 0; i < num_input; ++i) {
		node[i].setIsInput(true);
	}
	for (int i = start_output; i < start_output + num_output; ++i) {
		node[i].setIsOutput(true);
	}
	int gcount = 0;
	initnum_gen = (num_input*num_hidden) + (num_hidden*num_output);
	//Connection *conn;
	if (num_hidden > 0) {
		gen.reserve(initnum_gen);
		for (int i = 0; i < num_hidden; ++i) {
			//node[i + start_hidden].getConn_in().reserve(num_input);
			for (int j = 0; j < num_input; ++j) {
				//Connection *newCon = new Connection(0.1, innov++, node[j], node[start_hidden + i]);
				Connection *conn = new Connection(innov++, j, start_hidden + i);
				if (individu->gen[innov - 1]->disable == true || individu2->gen[innov - 1]->disable == true) {
					conn->disable = true;
				}
				else {
					if (individu->randomNumber(0.0,1.0)<= 0.5) {
						conn->weight = individu->gen[innov - 1]->weight;

						//conn->weight = randomNumber(-1.0, 1.0);
					}
					else {
						conn->weight = individu2->gen[innov - 1]->weight;

					}
				}
				//
				//conn->weight = randomNumber(-1.0, 1.0);
				gen.push_back(conn);
				node[j].Idxconn_out.push_back(conn);
				node[start_hidden + i].Idxconn_in.push_back(conn);
				//std::cout << gen[node[j].Idxconn_out[node[j].Idxconn_out.size()-1]].getnodeFromIdx() << " " << gen[node[j].Idxconn_out[node[j].Idxconn_out.size()-1]].getnodeToIdx() << std::endl;
			}
			for (int j = 0; j < num_output; ++j) {
				//Connection *newCon = new Connection(0.1, innov++, node[start_hidden + i], node[start_output + j]);
				Connection *conn = new Connection(innov++, start_hidden + i, start_output + j);
				//conn->weight = randomNumber(-1.0, 1.0);
				if (individu->gen[innov - 1]->disable == true || individu2->gen[innov - 1]->disable == true) {
					conn->disable = true;
				}
				else {
					if (individu->randomNumber(0.0, 1.0) <= 0.5) {
						conn->weight = individu->gen[innov - 1]->weight;

						//conn->weight = randomNumber(-1.0, 1.0);
					}
					else {
						conn->weight = individu2->gen[innov - 1]->weight;

						//conn->weight = randomNumber(-1.0, 1.0);
					}
				}
				gen.push_back(conn);
				node[start_hidden + i].Idxconn_out.push_back(conn);
				node[start_output + j].Idxconn_in.push_back(conn);
				//node[start_hidden + i].addConnectionOut(gen[gen.size()-1]);
				//node[start_output + j].addConnectionIn(gen[gen.size()-1]);
			}
		}

	}
	else {
		gen.reserve(num_input*num_output);
		for (int i = 0; i < num_input; ++i) {
			for (int j = 0; j < num_output; ++j) {
				//Connection *newCon = new Connection(-1 + ((rand() / RAND_MAX) * 2), innov++, node[i], node[start_output + j]);
				Connection *conn = new Connection(innov++, i, start_output + j);
				if (individu->gen[innov - 1]->disable == true || individu2->gen[innov - 1]->disable == true) {
					conn->disable = true;
				}
				else {
					if (individu->randomNumber(0.0, 1.0) <= 0.5) {
						conn->weight = individu->gen[innov - 1]->weight;
					}
					else {
						conn->weight = individu2->gen[innov - 1]->weight;
					}
				}
				//
				//conn->weight = randomNumber(-1.0, 1.0);
				gen.push_back(conn);
				node[i].Idxconn_out.push_back(conn);
				node[start_output + j].Idxconn_in.push_back(conn);
			}
		}
	}
	for (int i = sum; i < individu->node.size(); ++i) {
		node.push_back(Node(individu->node[i].node_number));
	}
	for (int i = sum; i < individu2->node.size(); ++i) {
		bool duplicate = false;
		for (int j = sum; j < node.size(); ++j) {
			if (individu2->node[i].node_number == node[j].node_number) {
				duplicate = true;
				break;
			}
		}
		if (duplicate == false) {
			node.push_back(Node(individu2->node[i].node_number));
		}
	}
	//push the non init gen from both individu to this new individu
	int size = individu->gen.size();
	auto i = individu->gen.begin() + initnum_gen;
	auto j = individu2->gen.begin() + initnum_gen;
	int size2 = individu2->gen.size();
	while (i != individu->gen.end() && j != individu2->gen.end()) {
		/*if (i > size || j > size2) {
			std::cout << "ERROR";
			std::cin.get();
		}*/
		if (j == individu2->gen.end() && i != individu->gen.end()) {
			int idx_nodefrom, idx_nodeto;
			if ((*i)->nodeFromIdx < sum) {
				idx_nodefrom = (*i)->nodeFromIdx;
			}
			else {
				int number = individu->node[(*i)->nodeFromIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodefrom = c;
						break;
					}
				}
			}
			if ((*i)->nodeToIdx < sum) {
				idx_nodeto = (*i)->nodeToIdx;
			}
			else {
				int number = individu->node[(*i)->nodeToIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodeto = c;
						break;
					}
				}
			}
			//if (checkStackOverflow(idx_nodefrom,idx_nodeto) == false) {
			Connection *conn = new Connection((*i)->innovationNumber, idx_nodefrom, idx_nodeto, (*i)->disable);
			conn->weight = (*i)->weight;
			gen.push_back(conn);
			node[idx_nodefrom].Idxconn_out.push_back(conn);
			node[idx_nodeto].Idxconn_in.push_back(conn);
			//}
			++i;
		}
		else if (i == individu->gen.end() && j != individu2->gen.end()) {
			int idx_nodefrom, idx_nodeto;
			if ((*j)->nodeFromIdx < sum) {
				idx_nodefrom = (*j)->nodeFromIdx;
			}
			else {
				int number = individu2->node[(*j)->nodeFromIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodefrom = c;
						break;
					}
				}
			}
			if ((*j)->nodeToIdx < sum) {
				idx_nodeto = (*j)->nodeToIdx;
			}
			else {
				int number = individu2->node[(*j)->nodeToIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodeto = c;
						break;
					}
				}
			}
			//if (checkStackOverflow(idx_nodefrom, idx_nodeto) == false) {
			Connection *conn = new Connection((*j)->innovationNumber, idx_nodefrom, idx_nodeto, (*j)->disable);
			conn->weight = (*j)->weight;
			gen.push_back(conn);
			node[idx_nodefrom].Idxconn_out.push_back(conn);
			node[idx_nodeto].Idxconn_in.push_back(conn);
			//}
			++j;
		}
		else if ((*j)->innovationNumber < (*i)->innovationNumber) {
			//conn = new Connection(individu2->gen[j]->innovationNumber, )
			int idx_nodefrom, idx_nodeto;
			if ((*j)->nodeFromIdx < sum) {
				idx_nodefrom = (*j)->nodeFromIdx;
			}
			else {
				int number = individu2->node[(*j)->nodeFromIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodefrom = c;
						break;
					}
				}
			}
			if ((*j)->nodeToIdx < sum) {
				idx_nodeto = (*j)->nodeToIdx;
			}
			else {
				int number = individu2->node[(*j)->nodeToIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodeto = c;
						break;
					}
				}
			}
			//if (checkStackOverflow(idx_nodefrom, idx_nodeto) == false) {
			Connection *conn = new Connection((*j)->innovationNumber, idx_nodefrom, idx_nodeto, (*j)->disable);
			conn->weight = (*j)->weight;
			gen.push_back(conn);
			node[idx_nodefrom].Idxconn_out.push_back(conn);
			node[idx_nodeto].Idxconn_in.push_back(conn);
			//}
			++j;
		}
		else if ((*i)->innovationNumber < (*j)->innovationNumber) {
			//gen.push_back(individu->gen[i]);
			int idx_nodefrom, idx_nodeto;
			if ((*i)->nodeFromIdx < sum) {
				idx_nodefrom = (*i)->nodeFromIdx;
			}
			else {
				int number = individu->node[(*i)->nodeFromIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodefrom = c;
						break;
					}
				}
			}
			if ((*i)->nodeToIdx < sum) {
				idx_nodeto = (*i)->nodeToIdx;
			}
			else {
				int number = individu->node[(*i)->nodeToIdx].node_number;
				for (int c = sum; c < node.size(); ++c) {
					if (node[c].node_number == number) {
						idx_nodeto = c;
						break;
					}
				}
			}
			//if (checkStackOverflow(idx_nodefrom, idx_nodeto) == false) {
			Connection *conn = new Connection((*i)->innovationNumber, idx_nodefrom, idx_nodeto, (*i)->disable);
			conn->weight = (*i)->weight;
			gen.push_back(conn);
			node[idx_nodefrom].Idxconn_out.push_back(conn);
			node[idx_nodeto].Idxconn_in.push_back(conn);
			//}
			++i;
		}
		else if ((*i)->innovationNumber == (*j)->innovationNumber) {
			if (individu->fitness >= individu2->fitness) {
				//gen.push_back(individu->gen[i]);
				int idx_nodefrom, idx_nodeto;
				if ((*i)->nodeFromIdx < sum) {
					idx_nodefrom = (*i)->nodeFromIdx;
				}
				else {
					int number = individu->node[(*i)->nodeFromIdx].node_number;
					for (int c = sum; c < node.size(); ++c) {
						if (node[c].node_number == number) {
							idx_nodefrom = c;
							break;
						}
					}
				}
				if ((*i)->nodeToIdx < sum) {
					idx_nodeto = (*i)->nodeToIdx;
				}
				else {
					int number = individu->node[(*i)->nodeToIdx].node_number;
					for (int c = sum; c < node.size(); ++c) {
						if (node[c].node_number == number) {
							idx_nodeto = c;
							break;
						}
					}
				}
				//if (checkStackOverflow(idx_nodefrom, idx_nodeto) == false) {
				Connection *conn = new Connection((*i)->innovationNumber, idx_nodefrom, idx_nodeto, (*i)->disable);
				conn->weight = (*i)->weight;
				gen.push_back(conn);
				node[idx_nodefrom].Idxconn_out.push_back(conn);
				node[idx_nodeto].Idxconn_in.push_back(conn);
				//}
			}
			else {
				//gen.push_back(individu2->gen[j]);
				int idx_nodefrom, idx_nodeto;
				if ((*j)->nodeFromIdx < sum) {
					idx_nodefrom = (*j)->nodeFromIdx;
				}
				else {
					int number = individu2->node[(*j)->nodeFromIdx].node_number;
					for (int c = sum; c < node.size(); ++c) {
						if (node[c].node_number == number) {
							idx_nodefrom = c;
							break;
						}
					}
				}
				if ((*j)->nodeToIdx < sum) {
					idx_nodeto = (*j)->nodeToIdx;
				}
				else {
					int number = individu2->node[(*j)->nodeToIdx].node_number;
					for (int c = sum; c < node.size(); ++c) {
						if (node[c].node_number == number) {
							idx_nodeto = c;
							break;
						}
					}
				}
				//if (checkStackOverflow(idx_nodefrom, idx_nodeto) == false) {
				Connection *conn = new Connection((*j)->innovationNumber, idx_nodefrom, idx_nodeto, (*j)->disable);
				conn->weight = (*j)->weight;
				gen.push_back(conn);
				node[idx_nodefrom].Idxconn_out.push_back(conn);
				node[idx_nodeto].Idxconn_in.push_back(conn);
				//}
			}
			++i;
			++j;
		}
	}

}

bool Individu::checkStackOverflow(int node, int node_from) {
	if (node == node_from) return true;
	for (auto &conn : this->node[node].Idxconn_in) {
		if (checkStackOverflow(conn->nodeFromIdx, node_from) == true) {
			return true;
			//break;
		}
	}
	return false;
}

int Individu::level(int node) {
	int max = 0;
	for (auto &conn : this->node[node].Idxconn_in) {
		int val = 1 + level(conn->nodeFromIdx);
		if (val > max) max = val;
	}
	return max;
}

Individu::Individu(const Individu &individu) {
	learning_rate = individu.learning_rate;
	node = individu.node;
	for (auto &nod : node) {
		nod.Idxconn_in.clear();
		nod.Idxconn_out.clear();
	}
	int size = individu.gen.size();
	gen.reserve(size);
	for (int i = 0; i < size; ++i) {
		gen.push_back(new Connection(*individu.gen[i]));
	}
	for (int i = 0; i < size; ++i) {
		node[gen[i]->nodeFromIdx].Idxconn_out.push_back(gen[i]);
		node[gen[i]->nodeToIdx].Idxconn_in.push_back(gen[i]);

	}
	num_input = individu.num_input;
	num_hidden = individu.num_hidden;
	num_output = individu.num_output;
	start = individu.start;
	start_hidden = individu.start_hidden;
	start_output = individu.start_output;
	sum = individu.sum;
	initnum_gen = individu.initnum_gen;
	fitness = individu.fitness;
}
Individu::Individu() {

}