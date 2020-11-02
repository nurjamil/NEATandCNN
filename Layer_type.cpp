
#include "Layer_type.h"
#include <iostream>



void Layer_type::addFilterSize(int filtersize, int sumfeatureMap) {
	x = filtersize;
	y = filtersize;
	this->sumFeatureMap = sumfeatureMap;
}
void Layer_type::addWeightSize(int output) {
	y = output;
	sumFeatureMap = 1;
}
Layer_type::~Layer_type()
{
}
double Layer_type::randomNumber(double lower_bound, double upper_bound) {


	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(lower_bound, upper_bound);
	//std::normal_distribution<double> dis(lower_bound, upper_bound);
	return dis(gen);
}

void Layer_type::create_filter(int dimensionSize, int x, int y, int output, bool israndom) {
	//this->sumFeatureMap = sumFeatureMap;
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937_64 gen(rd());
	//std::uniform_real_distribution<double> dis(-sqrt(6.0 / (x*y*dimensionSize + output)), sqrt(6.0 / (x*y*dimensionSize + output)));
	std::normal_distribution<double> dis(0.0, sqrt(6.0 / (x*y*dimensionSize + output)));
	this->dimensionSize = dimensionSize;
	//this->x = x;
	//this->y = y;
	for (int i = 0; i < sumFeatureMap; ++i) {
		std::vector<std::vector<std::vector<double>>> f;
		for (int j = 0; j < dimensionSize; ++j) {
			std::vector<std::vector<double>> newIn(this->y, std::vector<double>(this->x));
			for (int k = 0; k < this->y; ++k) {
				for (int l = 0; l < this->x; ++l) {
					if (israndom == true) {
						//newIn[k][l] = 0.5 - double(rand()) / double(RAND_MAX);
						//newIn[k][l] = randomNumber(-1.0, 1.0);
						//newIn[k][l] = newIn[k][l] * sqrt(1 / (x*y));
						newIn[k][l] = dis(gen);
					}
					else newIn[k][l] = 0;
					//newIn[k][l] = 0.1;
				}
			}
			f.push_back(newIn);
		}
		sumFilter.push_back(f);
	}
}

void Layer_type::create_filterFC(int input, bool israndom) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937_64 gen(rd());
	//std::uniform_real_distribution<double> dis(-sqrt(6.0 / (input + y)), sqrt(6.0 / (input + y)));
	std::normal_distribution<double> dis(0.0, sqrt(1.0 / (input + y)));
	std::vector<std::vector<double>> newIn(y, std::vector<double>(input));
	this->dimensionSize = 1;
	this->x = input;
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < input; ++j) {
			if (israndom == true) {
				//newIn[i][j] = randomNumber(-1.0, 1.0);
				//newIn[i][j] = newIn[i][j] * sqrt(1/input);
				//if (newIn[i][j] == 0.0) std::cout << "ERROR";
				//newIn[i][j] = 0.5 - double(rand()) / double(RAND_MAX);
				newIn[i][j] = dis(gen); //* sqrt(1/input);
			}
			else newIn[i][j] = 0;
			//newIn[y][x] = 0.1;
		}
		//newIn.push_back(tempWeight(input, israndom));
	}
	std::vector<std::vector<std::vector<double>>>  dim;
	dim.push_back(newIn);
	sumFilter.push_back(dim);
}

void Layer_type::init_momentum(int dimensionSize) {

}

std::vector<std::vector<std::vector<double>>> Layer_type::tempFilter(int dimensionSize, int x, int y, bool israndom) {
	std::vector<std::vector<std::vector<double>>> temp(dimensionSize, std::vector<std::vector<double>>(y, std::vector<double>(x)));
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-sqrt(6.0 / (x*y*dimensionSize)), sqrt(6.0 / (x*y*dimensionSize)));
	for (int j = 0; j < dimensionSize; ++j) {
		std::vector<std::vector<double>> newIn(y, std::vector<double>(x));
		for (int k = 0; k < y; ++k) {
			for (int l = 0; l < x; ++l) {
				if (israndom == true) {
					//newIn[k][l] = 0.5 - double(rand()) / double(RAND_MAX);
					//newIn[k][l] = randomNumber(-1.0, 1.0);
					//newIn[k][l] = newIn[k][l] * sqrt(1 / (x*y));
					newIn[k][l] = dis(gen);
				}
				else newIn[k][l] = 0;
				//newIn[k][l] = 0.1;
			}
		}
		temp.push_back(newIn);
	}
	return temp;
}

std::vector<double> Layer_type::tempWeight(int input, bool israndom) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-sqrt(1.0 / input + y), sqrt(1.0 / input + y));
	std::vector<double> temp(input);
	for (int j = 0; j < input; ++j) {
		if (israndom == true) {
			//newIn[i][j] = randomNumber(-1.0, 1.0);
			//newIn[i][j] = newIn[i][j] * sqrt(1/input);
			//if (newIn[i][j] == 0.0) std::cout << "ERROR";
			//newIn[i][j] = 0.5 - double(rand()) / double(RAND_MAX);
			temp[j] = dis(gen); //* sqrt(1/input);
		}
		else temp[j] = 0;
		//newIn[y][x] = 0.1;
	}

	return temp;
}

void Layer_type::create_filterSoftmax(int input, bool israndom) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-sqrt(1.0 / (input + y)), sqrt(1.0 / (input + y)));
	//std::normal_distribution<double> dis(0.0, 1);
	std::vector<std::vector<double>> newIn(y, std::vector<double>(input));
	this->dimensionSize = 1;
	this->x = input;
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < input; ++j) {
			if (israndom == true) {
				//newIn[i][j] = randomNumber(-1.0, 1.0);
				//newIn[i][j] = newIn[i][j] * sqrt(1/input);
				//if (newIn[i][j] == 0.0) std::cout << "ERROR";
				//newIn[i][j] = 0.5 - double(rand()) / double(RAND_MAX);
				newIn[i][j] = dis(gen); //* sqrt(1/input);
			}
			else newIn[i][j] = 0;
			//newIn[y][x] = 0.1;
		}
		//newIn.push_back(tempWeight(input, israndom));
	}
	std::vector<std::vector<std::vector<double>>> dim;
	dim.push_back(newIn);
	sumFilter.push_back(dim);
}

Layer_type::Layer_type() {

}