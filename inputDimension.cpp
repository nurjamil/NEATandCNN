
#include "inputDimension.h"


inputDimension::inputDimension(const std::vector<std::vector<std::vector<double>>> &input)
{
	this->x = input[0][0].size();
	this->y = input[0].size();
	this->input_Dimension = input.size();
	inputD = input;
}


inputDimension::~inputDimension()
{
}

inputDimension::inputDimension(const inputDimension &id) {
	inputD = id.inputD;
	input_Dimension = id.input_Dimension;
	y = id.y;
	x = id.x;
}

inputDimension::inputDimension() {

}