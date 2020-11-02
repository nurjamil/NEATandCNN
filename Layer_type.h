#pragma once
#ifndef LAYER_TYPE_H
#define LAYER_TYPE_H
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <assert.h>
typedef std::vector<std::vector<double>> d2v;
typedef std::vector <d2v> d3v;
typedef std::vector<d3v> d4v;

class Layer_type
{
private:
	int x;
	int y;
	int dimensionSize;
	int sumFeatureMap;

	//typedef std::vector<std::vector<double>> filter;
	//typedef std::vector<std::vector<std::vector<double>>> dimensionFilter;
	
	std::vector<std::vector<int>> dropoutIdx;
	std::vector<double> bias, batchBias;
	d4v sumFilter;

public:
	enum type {
		convoluteRelu, maxPool, flatten, fullyConn, fullyConnSoftmax,fullyConnSigmoid,dropout
	};
	type tipe;
	double prob;
	Layer_type();
	Layer_type(type tipe) : tipe(tipe), x(0), y(0) {};
	//Layer_type(int filtersize, int sumFeatureMap,type tipe) : tipe(tipe), x(filtersize), y(filtersize), sumFeatureMap(sumFeatureMap) {};
	//Layer_type(int output, type tipe = type::fullyConn) : y(output), tipe(tipe), sumFeatureMap(1) {};
	void addFilterSize(int filtersize, int sumfeatureMap);
	void addWeightSize(int output);
	double randomNumber(double lower_bound, double upper_bound);
	~Layer_type();
	void create_filter(int dimensionSize, int x, int y, int output, bool israndom = true);
	void create_filterFC(int input, bool israndom = true);
	void init_momentum(int dimensionSize);
	std::vector<double> tempWeight(int input, bool random);
	std::vector<std::vector<std::vector<double>>> tempFilter(int dimensionSize, int x, int y, bool israndom = true);
	void create_filterSoftmax(int input, bool israndom = true);
	friend class convolution_layer;
	friend std::ostream &operator <<(std::ostream &out, const Layer_type & obj)
	{
		int tipe = static_cast<int>(obj.tipe);
		out << tipe << "\n";
		if (obj.tipe == Layer_type::maxPool || obj.tipe == Layer_type::flatten) return out;
		out << obj.x << "\n";
		out << obj.y << "\n";
		out << obj.dimensionSize << "\n";
		out << obj.sumFeatureMap << "\n";
		out << obj.bias.size() << "\n";
		for (const auto &b : obj.bias) out << b << "\n";
		assert((obj.sumFilter.size() == obj.sumFeatureMap) && (obj.sumFilter[0].size() == obj.dimensionSize) && (obj.sumFilter[0][0].size() == obj.y) && (obj.sumFilter[0][0][0].size() == obj.x));
		for (const auto &a : obj.sumFilter) {
				for (const auto &b : a) {
					for (const auto &c : b) {
						for (const auto &d : c) {
							out << d << "\n";
						}
					}
				}
		}
			
					
		return out;
	};
	friend std::istream & operator >> (std::istream &in, Layer_type &obj)
	{
		int biasSize;
		int tipe;
		in >> tipe;
		obj.tipe = static_cast<Layer_type::type>(tipe);
		if (obj.tipe == Layer_type::maxPool || obj.tipe == Layer_type::flatten) return in;
		in >> obj.x;
		in >> obj.y;
		in >> obj.dimensionSize;
		in >> obj.sumFeatureMap;
		in >> biasSize;
		obj.bias.reserve(biasSize);
		for (int i = 0; i < biasSize; ++i) {
			double temp;
			in >> temp;
			obj.bias.push_back(temp);
		}
		obj.batchBias = std::vector<double>(biasSize);
		obj.sumFilter = d4v(obj.sumFeatureMap, d3v(obj.dimensionSize, d2v(obj.y, std::vector<double>(obj.x))));
		for (int i = 0; i < obj.sumFeatureMap; ++i) {
			for (int j = 0; j < obj.dimensionSize; ++j) {
				for (int k = 0; k < obj.y; ++k) {
					for (int l = 0; l < obj.x; ++l) {
						double temp;
						in >> temp;
						obj.sumFilter[i][j][k][l] = temp;
					}
				}
			}
		}
		return in;
	};
};

#endif