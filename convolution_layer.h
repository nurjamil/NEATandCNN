#pragma once
#ifndef CONVOLUTION_LAYER_H
#define CONVOLUTION_LAYER_H
#include <vector>
#include "Layer_type.h"
#include "inputDimension.h"
#include "InputFile.h"
#include <iostream>
class convolution_layer
{
private:
	bool isInitialized;
	double m;
	//std::vector<inputDimension> inputLayer;
	std::vector<Layer_type> layer;
	std::vector<Layer_type> Momentum;
	std::vector<Layer_type> batchDweight;
public:
	convolution_layer(double learning_rate, double m, bool isInitialized = false) : learning_rate(learning_rate), isInitialized(isInitialized), m(m) {};
	convolution_layer() : isInitialized(false),m(0.9),learning_rate(0.001) {};
	void addLayer1(int filtersize, int sumFeatureMap, Layer_type::type tipe);
	void addLayer3(Layer_type::type tipe);
	void addLayer2(int output, Layer_type::type tipe = Layer_type::fullyConn);
	double training(const std::vector<input> &input_, const int batchSize,bool &isLanjut);
	bool &getIsInitialized() { return isInitialized; };
	inputDimension convolute(int layer);
	void initializing(const input i);
	double learning_rate;
	void setInputSize(int x, int y, int z);
	void addDropout(Layer_type::type tipe, double prob);
	double test(const std::vector<input> &inp);
	int predict(const std::vector<std::vector<std::vector<double>>> &input, const std::vector<double> &output);
	void printLayer();
	void feedforward(std::vector<inputDimension> &inputLayer);
	void initialize(std::vector<inputDimension> &inputLayer);
	//void setInput(std::vector<std::vector<std::vector<double>>> &input);
	//void resetInput() { this->inputLayer.clear(); };
	void backpropagate(const std::vector<double> &output, const bool isupdated, std::vector<inputDimension> &inputLayer);
	void printWeight();
	void createDropout();
	~convolution_layer();
	friend std::ostream &operator <<(std::ostream &out, const convolution_layer & obj)
	{
		out << obj.learning_rate << "\n";
		out << obj.m << "\n";
		out << obj.isInitialized << "\n";
		out << obj.layer.size() << "\n";
		out << obj.Momentum.size() << "\n";
		out << obj.batchDweight.size() << "\n";
		for (const auto &a : obj.layer) out << a;
		for (const auto &b : obj.Momentum) out << b;
		for (const auto &c : obj.batchDweight) out << c;
		return out;
	};
	friend std::istream & operator >> (std::istream &in, convolution_layer &obj)
	{
		int layersize, momentumSize, batchDweightSize;
		in >> obj.learning_rate;
		in >> obj.m;
		in >> obj.isInitialized;
		in >> layersize;
		in >> momentumSize;
		in >> batchDweightSize;
		obj.layer.reserve(layersize);
		obj.Momentum.reserve(momentumSize);
		obj.batchDweight.reserve(batchDweightSize);
		for (int i = 0; i < layersize; ++i) {
			Layer_type temp;
			in >> temp;
			obj.layer.push_back(temp);
		}
		for (int i = 0; i < momentumSize; ++i) {
			Layer_type temp;
			in >> temp;
			obj.Momentum.push_back(temp);
		}
		for (int i = 0; i < batchDweightSize; ++i) {
			Layer_type temp;
			in >> temp;
			obj.batchDweight.push_back(temp);
		}
		return in;
	};
};

#endif