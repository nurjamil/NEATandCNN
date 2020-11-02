#pragma once
#ifndef INPUTDIMENSION_H
#define INPUTDIMENSION_H
#include <vector>
class inputDimension
{
private:
	int x;
	int y;
	int input_Dimension;
	//typedef std::vector<std::vector<double>> input;
	std::vector<std::vector<std::vector<double>>> inputD;
public:
	inputDimension();
	inputDimension(const std::vector<std::vector<std::vector<double>>> &input);
	//inputDimension(std::vector<input> inputD) : inputD(inputD) {};
	inputDimension(const inputDimension &id);
	~inputDimension();
	friend class convolution_layer;
};

#endif