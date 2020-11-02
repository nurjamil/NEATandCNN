
#include "convolution_layer.h"
#include <iostream>
#include <math.h>
//#include <amp.h>

convolution_layer::~convolution_layer()
{
}

void convolution_layer::addLayer1(int filtersize, int sumFeatureMap, Layer_type::type tipe) {
	Layer_type kampret(tipe);
	kampret.addFilterSize(filtersize, sumFeatureMap);
	kampret.bias = std::vector<double>(sumFeatureMap);
	kampret.batchBias = std::vector<double>(sumFeatureMap);
	layer.push_back(kampret);
	Momentum.push_back(kampret);
	batchDweight.push_back(kampret);
}
void convolution_layer::addLayer2(int output, Layer_type::type tipe) {
	Layer_type kampret(tipe);
	kampret.addWeightSize(output);
	kampret.bias = std::vector<double>(output);
	kampret.batchBias = std::vector<double>(output);
	layer.push_back(kampret);
	Momentum.push_back(kampret);
	batchDweight.push_back(kampret);
}
void convolution_layer::addLayer3(Layer_type::type tipe) {
	Layer_type kampret(tipe);
	layer.push_back(Layer_type(tipe));
	Momentum.push_back(Layer_type(tipe));
	batchDweight.push_back(Layer_type(tipe));

}

void convolution_layer::addDropout(Layer_type::type tipe, double prob) {
	Layer_type kampret(tipe);
	kampret.prob = prob;
	layer.push_back(kampret);
	Momentum.push_back(Layer_type(tipe));
	batchDweight.push_back(Layer_type(tipe));
}

void convolution_layer::initializing(const input i) {
	std::vector<inputDimension> inputLayer;
	inputLayer.push_back(inputDimension(i.inputData));
	//inputDimension start(input_[0].inputData);
	//std::cout << "hai";
	//this->inputLayer.push_back(start);
	initialize(inputLayer);
	isInitialized = true;
}

double convolution_layer::training(const std::vector<input> &input_, const int batchSize, bool &isLanjut) {
	//std::cout << input_.size() << std::endl;
	//std::cout << input_[0].inputData.size();

	if (isInitialized == false) {
		std::vector<inputDimension> inputLayer;
		inputLayer.push_back(inputDimension(input_[0].inputData));
		//inputDimension start(input_[0].inputData);
		//std::cout << "hai";
		//this->inputLayer.push_back(start);
		initialize(inputLayer);
		isInitialized = true;
		//this->inputLayer.push_back(start);
		//feedforward();
	}
	//setInputSize(input_[0].inputData[0][0].size(), input_[0].inputData[0].size(), input_[0].inputData.size());
	const int size = input_.size();
	double correct = 0.0;
	//std::vector<inputDimension> inputLayer;
	//inputLayer.push_back(inputDimension(input_[0].inputData));
	//feedforward(inputLayer);

	for (int i = 0; i < size; ++i) {//input_.size(); ++i) {
	
		if (isLanjut == false) {
			return -1.0;
		}
		//std::cout <<"file ke = "<< i << " ";
		//createDropout();
		std::vector<inputDimension> inputLayer;
		inputLayer.push_back(inputDimension(input_[i].inputData));
		//std::cout << "feed forward" << std::endl; 
		feedforward(inputLayer);
		//std::cout << "back prop" << std::endl;
		if ((i + 1) % batchSize == 0) {
			backpropagate(input_[i].output, true, inputLayer);
		}
		else if (i == size - 1) {
			backpropagate(input_[i].output, true, inputLayer);
		}
		else {
			backpropagate(input_[i].output, false, inputLayer);
		}
		int predicted = -1;
		double max = -1.0;

		for (int i = 0; i < inputLayer[inputLayer.size() - 1].inputD[0][0].size(); ++i) {
			//std::cout << inputLayer[inputLayer.size() - 1].inputD[0][0][i] << ": : ";
			if (inputLayer[inputLayer.size() - 1].inputD[0][0][i] > max) {
				max = inputLayer[inputLayer.size() - 1].inputD[0][0][i];
				predicted = i;
			}
		}
		if (input_[i].output[predicted] == 1.0) {
			++correct;
		}
		//std::vector<inputDimension>().swap(inputLayer);
		//inputLayer.clear();
		//dropout.clear();
	}
	//std::cout << "bener " << correct << std::endl;
	std::cout << "akurasi  = " << correct / input_.size() << std::endl;
	return (correct / input_.size());
}
double convolution_layer::test(const std::vector<input> &inp) {
	if (isInitialized == false) {
		initializing(inp[0]);
	}
	double correct = 0.0;
	for (size_t i = 0; i < inp.size(); ++i) {
		if (inp[i].output[predict(inp[i].inputData, inp[i].output)] == 1.0) ++correct;
	}
	std::cout << "test accuration = " << correct / inp.size();
	return correct/inp.size();
}
int convolution_layer::predict(const std::vector<std::vector<std::vector<double>>> &input, const std::vector<double> &output) {
	std::vector<inputDimension> inputLayer;
	inputLayer.push_back(inputDimension(input));
	feedforward(inputLayer);
	double max = -1;
	int predicted = -1;
	int size = inputLayer.size() - 1;
	for (int i = 0; i < inputLayer[size].x; ++i) {
		if (inputLayer[size].inputD[0][0][i] > max) {
			max = inputLayer[size].inputD[0][0][i];
			predicted = i;
		}
	}
	return predicted;
}
void convolution_layer::feedforward(std::vector<inputDimension> &inputLayer) {

	int startDropout = 0;
	int size2 = layer.size();
	for (int layerDimension = 0; layerDimension < size2; ++layerDimension) {
		//inputDimension newInput;


		if (layer[layerDimension].tipe == Layer_type::convoluteRelu) {
			// for every feature map generated
			//std::cout << "convolute layer "<<layerDimension;
			int size = layer[layerDimension].sumFilter.size();
			inputDimension newInput;
			newInput.input_Dimension = size;
			for (int i = 0; i < size; ++i) {
				if (inputLayer[layerDimension].input_Dimension != layer[layerDimension].dimensionSize) std::cout << "error" << std::endl;
				else {
					int ix = inputLayer[layerDimension].x;
					int iy = inputLayer[layerDimension].y;
					int lx = layer[layerDimension].x;
					int ly = layer[layerDimension].y;
					newInput.y = iy - (ly - 1);
					newInput.x = ix - (lx - 1);
					int offset = (layer[layerDimension].y - 1) / 2;
					int filtersize = layer[layerDimension].y;
					std::vector<std::vector<double>> newIn(newInput.y, std::vector<double>(newInput.x, 0.0));
					// every dimension
					//#pragma loop(hint_parallel(4))
					for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
						for (int y = 0; y < newInput.y; ++y) {
							for (int x = 0; x < newInput.x; ++x) {
								double value = 0;
								for (int y1 = y, yf = 0; y1 < y + filtersize; ++y1, ++yf) {
									for (int x1 = x, xf = 0; x1 < x + filtersize; ++x1, ++xf) {
										
										value += (inputLayer[layerDimension].inputD[j][y1][x1] * layer[layerDimension].sumFilter[i][j][yf][xf]);
									}
								}
								newIn[y][x] += value;
								//	std::cout << newIn[y][x] << " ";

							}
							//	std::cout << std::endl;
						}
						//std::cout << std::endl;
						//std::cout << std::endl;
					}
					newInput.inputD.push_back(newIn);

					std::vector<std::vector<double>>().swap(newIn);
				}
				//RELU
				for (int y = 0; y < newInput.y; ++y) {
					//#pragma loop(hint_parallel(4))
					for (int x = 0; x < newInput.x; ++x) {
						newInput.inputD[i][y][x] += layer[layerDimension].bias[i];
						if (newInput.inputD[i][y][x] < 0)
							newInput.inputD[i][y][x] = 0;
					}
				}

			}
			inputLayer.push_back(newInput);

		}
		else if (layer[layerDimension].tipe == Layer_type::dropout) {
			inputDimension newInput(inputLayer[layerDimension]);
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd());
			std::uniform_real_distribution<double> dis(0.0, 1.0);
			for (int i = 0; i < newInput.inputD.size(); ++i) {
				for (int j = 0; j < newInput.inputD[0].size(); ++j) {
					for (int k = 0; k < newInput.inputD[0][0].size(); ++k) {
						if (dis(gen) <= layer[layerDimension].prob) {
							newInput.inputD[i][j][k] = 0.0;
							std::vector<int> idx(3);
							idx[0] = i;
							idx[1] = j;
							idx[2] = k;
							layer[layerDimension].dropoutIdx.push_back(idx);
						}
							
					}
				}
			}
			inputLayer.push_back(newInput);
		}
		else if (layer[layerDimension].tipe == Layer_type::maxPool) {
			//std::cout << "maxpool layer "<<layerDimension;
			inputDimension newInput;
			if (inputLayer[layerDimension].inputD[0].size() % 2 != 0) {
				//std::cin.get();
				for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
					inputLayer[layerDimension].inputD[j].push_back(std::vector<double>(inputLayer[layerDimension].inputD[j][0].size()));
				}
			}
			if (inputLayer[layerDimension].x % 2 != 0) {
				//std::cin.get();
				for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
					for (int k = 0; k < inputLayer[layerDimension].y; ++k) {
						inputLayer[layerDimension].inputD[j][k].push_back(0.0);
					}
				}
			}

			newInput.input_Dimension = inputLayer[layerDimension].input_Dimension;
			newInput.inputD.reserve(inputLayer[layerDimension].input_Dimension);
			for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
				int ix = inputLayer[layerDimension].x;
				int iy = inputLayer[layerDimension].y;
				newInput.y = iy / 2;
				newInput.x = ix / 2;
				std::vector<std::vector<double>> newIn(iy / 2, std::vector<double>(ix / 2, 0.0));
				for (int y = 0; y < newInput.y; ++y) {
					for (int x = 0; x < newInput.x; ++x) {
						double max = inputLayer[layerDimension].inputD[j][y * 2][x * 2];
						for (int y1 = y * 2; y1 < (y * 2) + 2; ++y1) {
							for (int x1 = x * 2; x1 < (x * 2) + 2; ++x1) {
								if (inputLayer[layerDimension].inputD[j][y1][x1] > max) max = inputLayer[layerDimension].inputD[j][y1][x1];
							}
						}
						newIn[y][x] = max;
						//std::cout << newIn[y][x] << " ";
					}
					//std::cout << std::endl;
				}
				//std::cout << std::endl;
				newInput.inputD.push_back(newIn);
				//std::vector<std::vector<double>>().swap(newIn);
			}
			inputLayer.push_back(newInput);

		}
		else if (layer[layerDimension].tipe == Layer_type::flatten) {
			//std::cout << "flatten";
			inputDimension newInput;
			int ix = inputLayer[layerDimension].x;
			int iy = inputLayer[layerDimension].y;
			int id = inputLayer[layerDimension].input_Dimension;

			newInput.input_Dimension = 1;
			newInput.y = 1;
			newInput.x = ix * iy * id;
			std::vector<std::vector<double>> newIn(1, std::vector<double>(newInput.x));
			//newIn[0].reserve(newInput.x);
			int count = 0;
			for (int j = 0; j < id; ++j) {
				for (int y = 0; y < iy; ++y) {
					//#pragma loop(hint_parallel(4))
					for (int x = 0; x < ix; ++x) {
						//newIn[0].push_back(inputLayer[layerDimension].inputD[j][y][x]);
						newIn[0][count++] = inputLayer[layerDimension].inputD[j][y][x];
					}
				}
			}
			newInput.inputD.push_back(newIn);
			inputLayer.push_back(newInput);
			//std::vector<std::vector<double>>().swap(newIn);

		}
		else if (layer[layerDimension].tipe == Layer_type::fullyConn) {
			//std::cout << "fullycon" << "x = " << inputLayer[layerDimension].inputD[0][0].size() << " " << layer[layerDimension].sumFilter[0][0][0].size();
			inputDimension newInput;
			newInput.input_Dimension = 1;
			newInput.y = 1;
			newInput.x = layer[layerDimension].y;
			//std::cout << "output : ";
			std::vector<std::vector<double>> newIn(1, std::vector<double>(layer[layerDimension].y));
			//#pragma loop(hint_parallel(4))
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				double value = 0.0;
				for (int x = 0; x < inputLayer[layerDimension].x; ++x) {
					value = value + (inputLayer[layerDimension].inputD[0][0][x] * layer[layerDimension].sumFilter[0][0][y][x]);
				}
				value += layer[layerDimension].bias[y];
				//value = 1.0 / (1.0 + exp((-(value))));
				//if (value < 0) value = 0;
				/*if (isnan(value)) {
					std::cout << "ERROR 2";
					std::cin.get();
				}*/
				if (value > 0) newIn[0][y] = value;
					//newIn[0][y] = 1.0 / (1.0 + exp((-(value))));
				//if (layer[layerDimension].randomNumber(0.0, 1.0) <= 0.5)
					//newIn[0][y] = 0;
			}
			//std::cout << std::endl;
			newInput.inputD.push_back(newIn);
			std::vector<std::vector<double>>().swap(newIn);
			inputLayer.push_back(newInput);
			++startDropout;
		}
		else if (layer[layerDimension].tipe == Layer_type::fullyConnSigmoid) {
		//std::cout << "fullycon" << "x = " << inputLayer[layerDimension].inputD[0][0].size() << " " << layer[layerDimension].sumFilter[0][0][0].size();
		inputDimension newInput;
		newInput.input_Dimension = 1;
		newInput.y = 1;
		newInput.x = layer[layerDimension].y;
		//std::cout << "output : ";
		std::vector<std::vector<double>> newIn(1, std::vector<double>(layer[layerDimension].y));
		//#pragma loop(hint_parallel(4))
		for (int y = 0; y < layer[layerDimension].y; ++y) {
			double value = 0.0;
			for (int x = 0; x < inputLayer[layerDimension].x; ++x) {
				value = value + (inputLayer[layerDimension].inputD[0][0][x] * layer[layerDimension].sumFilter[0][0][y][x]);
			}
			value += layer[layerDimension].bias[y];
			//value = 1.0 / (1.0 + exp((-(value))));
			//if (value < 0) value = 0;
			/*if (isnan(value)) {
				std::cout << "ERROR 2";
				std::cin.get();
			}*/
			//if (value > 0) newIn[0][y] = value;
			newIn[0][y] = 1.0 / (1.0 + exp((-(value))));
		//if (layer[layerDimension].randomNumber(0.0, 1.0) <= 0.5)
			//newIn[0][y] = 0;
		}
		//std::cout << std::endl;
		newInput.inputD.push_back(newIn);
		std::vector<std::vector<double>>().swap(newIn);
		inputLayer.push_back(newInput);
		++startDropout;
		}
		else if (layer[layerDimension].tipe == Layer_type::fullyConnSoftmax) {
			inputDimension newInput;
			//layer[layerDimension].create_filterFC(inputLayer[layerDimension].x);
			//Momentum[layerDimension].create_filterFC(inputLayer[layerDimension].x, false);
			//batchDweight[layerDimension].create_filterFC(inputLayer[layerDimension].x, false);
			newInput.input_Dimension = 1;
			newInput.y = 1;
			newInput.x = layer[layerDimension].y;
			std::vector<std::vector<double>> newIn(1, std::vector<double>(layer[layerDimension].y));
			//#pragma loop(hint_parallel(4))
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				//std::cout << "y " << y;
				double value = 0.0;
			
				for (int x = 0; x < inputLayer[layerDimension].x; ++x) {
					//std::cout << "x " << x << std::endl;
					value += inputLayer[layerDimension].inputD[0][0][x] * layer[layerDimension].sumFilter[0][0][y][x];
				}
				//if(layerDimension == layer.size()-1)
				//std::cout << "output : "<<value<<" ";
				//value = 1.0 / (1.0 + exp((value - (2.0*value))));
				//value = exp(value);
				//if (value < 0) value = 0;
				value += layer[layerDimension].bias[y];
				newIn[0][y] = value;
			}
			double sum = 0;
			double max = newIn[0][0];
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				if (newIn[0][y] > max) max = newIn[0][y];
			}
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				newIn[0][y] = exp(newIn[0][y] - max);
			}
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				sum += newIn[0][y];
			}
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				newIn[0][y] = newIn[0][y] / sum;
			}
			//std::cout << std::endl;
			newInput.inputD.push_back(newIn);
			inputLayer.push_back(newInput);
			std::vector<std::vector<double>>().swap(newIn);

		}
		//inputLayer.push_back(newInput);
		//std::vector<std::vector<std::vector<double>>>().swap(newInput.inputD);
	}

}


void convolution_layer::initialize(std::vector<inputDimension> &inputLayer) {
	for (int layerDimension = 0; layerDimension < layer.size(); ++layerDimension) {
		inputDimension newInput;
		// for every feature map generated
		//std::cout << layerDimension;
		//std::cout << inputLayer[layerDimension].input_Dimension << " " << inputLayer[layerDimension].y << " " << inputLayer[layerDimension].x << std::endl;
		//std::cout << layer[layerDimension].x << " " << layer[layerDimension].y << std::endl;
		if (layer[layerDimension].tipe == Layer_type::convoluteRelu) {
			
			layer[layerDimension].create_filter(inputLayer[layerDimension].input_Dimension, inputLayer[layerDimension].x, inputLayer[layerDimension].y, layer[layerDimension].sumFeatureMap * ((inputLayer[layerDimension].x - layer[layerDimension].x + 1) * 2));
			Momentum[layerDimension].create_filter(inputLayer[layerDimension].input_Dimension, inputLayer[layerDimension].x, inputLayer[layerDimension].y, layer[layerDimension].y, false);
			batchDweight[layerDimension].create_filter(inputLayer[layerDimension].input_Dimension, inputLayer[layerDimension].x, inputLayer[layerDimension].y, layer[layerDimension].y, false);
			newInput.input_Dimension = layer[layerDimension].sumFilter.size();
			for (int i = 0; i < layer[layerDimension].sumFilter.size(); ++i) {
				if (inputLayer[layerDimension].input_Dimension != layer[layerDimension].dimensionSize) std::cout << "error" << std::endl;
				else {
					newInput.y = inputLayer[layerDimension].y - (layer[layerDimension].y - 1);
					newInput.x = inputLayer[layerDimension].x - (layer[layerDimension].x - 1);
					std::vector<std::vector<double>> newIn(inputLayer[layerDimension].y - (layer[layerDimension].y - 1), std::vector<double>(inputLayer[layerDimension].x - (layer[layerDimension].x - 1)));
					int offset = (layer[layerDimension].y - 1) / 2;
					int filtersize = layer[layerDimension].y;
					// every dimension
					for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
						for (int y = 0; y < newInput.y; ++y) {
							for (int x = 0; x < newInput.x; ++x) {
								for (int y1 = y, yf = 0; y1 < y + filtersize; ++y1, ++yf) {
									for (int x1 = x, xf = 0; x1 < x + filtersize; ++x1, ++xf) {
										newIn[y][x] += inputLayer[layerDimension].inputD[j][y1][x1] * layer[layerDimension].sumFilter[i][j][yf][xf];
									}
								}
								//std::cout << newIn[y][x] << " ";

							}
							//std::cout<<std::endl;
						}
					
					}
					newInput.inputD.push_back(newIn);
				}
				//RELU
				//std::cout << "RELU";
				for (int y = 0; y < newInput.y; ++y) {
					for (int x = 0; x < newInput.x; ++x) {
						if (newInput.inputD[i][y][x] < 0)
							newInput.inputD[i][y][x] = 0;
					}
				}
			}

		}
		else if (layer[layerDimension].tipe == Layer_type::dropout) {
			inputDimension newInput2(inputLayer[layerDimension]);
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0.0, 1.0);
			for (int i = 0; i < newInput.inputD.size(); ++i) {
				for (int j = 0; j < newInput.inputD[0].size(); ++j) {
					for (int k = 0; k < newInput.inputD[0][0].size(); ++k) {
						if (dis(gen) <= layer[layerDimension].prob) {
							newInput.inputD[i][j][k] = 0.0;
							std::vector<int> idx(3);
							idx[0] = i;
							idx[1] = j;
							idx[2] = k;
							layer[layerDimension].dropoutIdx.push_back(idx);
						}

					}
				}
			}
			newInput = newInput2;
		}
		else if (layer[layerDimension].tipe == Layer_type::maxPool) {
			//std::cout << "maxpool" << std::endl;
			if (inputLayer[layerDimension].inputD[0].size() % 2 != 0) {
				for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
					inputLayer[layerDimension].inputD[j].push_back(std::vector<double>(inputLayer[layerDimension].inputD[j][0].size()));
				}
			}
			if (inputLayer[layerDimension].x % 2 != 0) {
				for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
					for (int k = 0; k < inputLayer[layerDimension].y; ++k) {
						inputLayer[layerDimension].inputD[j][k].push_back(0.0);
					}
				}
			}
			newInput.input_Dimension = inputLayer[layerDimension].input_Dimension;
			newInput.inputD.reserve(newInput.input_Dimension);
			for (int j = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
				newInput.y = inputLayer[layerDimension].y / 2;
				newInput.x = inputLayer[layerDimension].x / 2;
				std::vector<std::vector<double>> newIn(inputLayer[layerDimension].y / 2, std::vector<double>(inputLayer[layerDimension].x / 2));
				for (int y = 0; y < newInput.y; ++y) {
					for (int x = 0; x < newInput.x; ++x) {
						double max = -1.0;
						for (int y1 = y * 2; y1 < (y * 2) + 2; ++y1) {
							for (int x1 = x * 2; x1 < (x * 2) + 2; ++x1) {
								if (inputLayer[layerDimension].inputD[j][y1][x1] > max) max = inputLayer[layerDimension].inputD[j][y1][x1];
							}
						}
						newIn[y][x] = max;
						//std::cout << newIn[y][x] << " ";
					}
					//std::cout << std::endl;
				}
				//std::cout << std::endl;
				newInput.inputD.push_back(newIn);
			}
		}
		else if (layer[layerDimension].tipe == Layer_type::flatten) {
			//std::cout << "flatten" << std::endl;
			newInput.input_Dimension = 1;
			newInput.y = 1;
			newInput.x = inputLayer[layerDimension].x * inputLayer[layerDimension].y * inputLayer[layerDimension].input_Dimension;
			std::vector<std::vector<double>> newIn(1, std::vector<double>(newInput.x));
			for (int j = 0, count = 0; j < inputLayer[layerDimension].input_Dimension; ++j) {
				for (int y = 0; y < inputLayer[layerDimension].y; ++y) {
					for (int x = 0; x < inputLayer[layerDimension].x; ++x) {
						newIn[0][count++] = inputLayer[layerDimension].inputD[j][y][x];
						//std::cout << newIn[0][newIn[0].size() - 1]<<" ";
					}
				}
			}
			//std::cout << std::endl;
			newInput.inputD.push_back(newIn);
		}
		else if (layer[layerDimension].tipe == Layer_type::fullyConn || layer[layerDimension].tipe == Layer_type::fullyConnSigmoid) {
			//std::cout << "fullyconn" << std::endl;
			layer[layerDimension].create_filterFC(inputLayer[layerDimension].x);
			Momentum[layerDimension].create_filterFC(inputLayer[layerDimension].x, false);
			batchDweight[layerDimension].create_filterFC(inputLayer[layerDimension].x, false);
			newInput.input_Dimension = 1;
			newInput.y = 1;
			newInput.x = layer[layerDimension].y;
			std::vector<std::vector<double>> newIn(1, std::vector<double>(layer[layerDimension].y));
			//#pragma loop(hint_parallel(4))
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				//std::cout << "y " << y;
				double value = 0.0;
				for (int x = 0; x < inputLayer[layerDimension].x; ++x) {
					//std::cout << "x " << x << std::endl;
					//if (inputLayer[layerDimension].inputD[0][0][x] > 0)std::cin.get();
					value += inputLayer[layerDimension].inputD[0][0][x] * layer[layerDimension].sumFilter[0][0][y][x];
				}
				//if(layerDimension == layer.size()-1)
				//std::cout << "output : "<<value<<" ";
				value = 1.0 / (1.0 + exp((value - (2.0*value))));
				//if (value < 0) value = 0;
				newIn[0][y] = value;
			}
			std::cout << std::endl;
			newInput.inputD.push_back(newIn);
		}
		else if (layer[layerDimension].tipe == Layer_type::fullyConnSoftmax) {
			layer[layerDimension].create_filterFC(inputLayer[layerDimension].x);
			Momentum[layerDimension].create_filterFC(inputLayer[layerDimension].x, false);
			batchDweight[layerDimension].create_filterFC(inputLayer[layerDimension].x, false);
			newInput.input_Dimension = 1;
			newInput.y = 1;
			newInput.x = layer[layerDimension].y;
			std::vector<std::vector<double>> newIn(1, std::vector<double>(layer[layerDimension].y));
			//#pragma loop(hint_parallel(4))
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				//std::cout << "y " << y;
				double value = 0.0;
				for (int x = 0; x < inputLayer[layerDimension].x; ++x) {
					//std::cout << "x " << x << std::endl;
					value += inputLayer[layerDimension].inputD[0][0][x] * layer[layerDimension].sumFilter[0][0][y][x];
				}
				//if(layerDimension == layer.size()-1)
				//std::cout << "output : "<<value<<" ";
				//value = 1.0 / (1.0 + exp((value - (2.0*value))));
				value = exp(value);
				//if (value < 0) value = 0;
				newIn[0][y] = value;
			}
			double sum = 0;
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				sum += newIn[0][y];
			}
			for (int y = 0; y < layer[layerDimension].y; ++y) {
				newIn[0][y] = newIn[0][y] / sum;
			}
			//std::cout << std::endl;
			newInput.inputD.push_back(newIn);

		}
		inputLayer.push_back(newInput);
	}
	std::vector<inputDimension>().swap(inputLayer);
	//inputLayer.clear();

}
void convolution_layer::backpropagate(const std::vector<double> &output, const bool isupdated, std::vector<inputDimension> &inputLayer) {
	inputDimension dValue;
	//std::cout << "x last layer size " << inputLayer[inputLayer.size() - 1].x;
	std::vector<std::vector<double>> dv(1, std::vector<double>(inputLayer[inputLayer.size() - 1].x));
	//std::cout << "output error : ";
	for (int i = 0; i < inputLayer[inputLayer.size() - 1].x; ++i) {
		//double dval =   (-1.0 *(output[i] - inputLayer[inputLayer.size() - 1].inputD[0][0][i])) * (inputLayer[inputLayer.size() - 1].inputD[0][0][i] * (1.0 - inputLayer[inputLayer.size() - 1].inputD[0][0][i]));
		//std::cout << inputLayer[inputLayer.size() - 1].inputD[0][0][i] << " ";
		double dval = inputLayer[inputLayer.size() - 1].inputD[0][0][i] - output[i];
		dv[0][i] = dval;
	}
	//std::cout << std::endl;
	dValue.inputD.push_back(dv);
	for (int i = layer.size() - 1; i >= 0; --i) {
		//std::cout << "Backprop " << layer[i].tipe << std::endl;
		if (layer[i].tipe == Layer_type::fullyConn || layer[i].tipe == Layer_type::fullyConnSoftmax) {
			//std::cout << "fullyconn" << std::endl;
			inputDimension tempDValue;
			std::vector<std::vector<double>> vec(1, std::vector<double>(inputLayer[i].x));
			//std::cout << "here?" << std::endl;
			//#pragma loop(hint_parallel(4))
			for (int x = 0; x < inputLayer[i].x; ++x) { //inputLayer[i].x
				//std::cout << "x"<<x<<std::endl;
				double value = 0.0;
		

				for (int y = 0; y < layer[i].y; ++y) {
					//std::cout << "y" << y << std::endl;
					value += layer[i].sumFilter[0][0][y][x] * dValue.inputD[0][0][y];
				}
				//value = ;
				//if (value < 0) value = 0;
				vec[0][x] = value;// *(inputLayer[i].inputD[0][0][x] * (1.0 - inputLayer[i].inputD[0][0][x]));
			}
			//std::cout << "or here?" << std::endl;
			tempDValue.inputD.push_back(vec);
			tempDValue.input_Dimension = 1;
			tempDValue.y = 1;
			tempDValue.x = inputLayer[i].x;
			if (isupdated == false) {
				for (int y = 0; y < layer[i].y; ++y) {
					//#pragma loop(hint_parallel(4))
					layer[i].batchBias[y] += dValue.inputD[0][0][y];
					for (int x = 0; x < layer[i].x; ++x) {
					
						
						batchDweight[i].sumFilter[0][0][y][x] += (dValue.inputD[0][0][y] * inputLayer[i].inputD[0][0][x]);
						//Momentum[i].sumFilter[0][0][y][x] = (dValue.inputD[0][0][y] * inputLayer[i].inputD[0][0][x] * m) + ((1.0 - m) * Momentum[i].sumFilter[0][0][y][x]);
					}
				}
			}
			else {
				for (int y = 0; y < layer[i].y; ++y) {
					//	#pragma loop(hint_parallel(4))
					layer[i].batchBias[y] += dValue.inputD[0][0][y];
					layer[i].bias[y] = layer[i].bias[y] - (layer[i].batchBias[y] * learning_rate);
					layer[i].batchBias[y] = 0.0;
					for (int x = 0; x < layer[i].x; ++x) {
						batchDweight[i].sumFilter[0][0][y][x] += (dValue.inputD[0][0][y] * inputLayer[i].inputD[0][0][x]);
						//if(batchDweight[i].sumFilter[0][0][y][x]!= 0.0)
						Momentum[i].sumFilter[0][0][y][x] = (batchDweight[i].sumFilter[0][0][y][x] * m) + ((1.0 - m) * Momentum[i].sumFilter[0][0][y][x]);
						//double value = (batchDweight[i].sumFilter[0][0][y][x]*m) + ((1.0-m) * Momentum[i].sumFilter[0][0][y][x]);
						layer[i].sumFilter[0][0][y][x] = layer[i].sumFilter[0][0][y][x] - (Momentum[i].sumFilter[0][0][y][x] * learning_rate);// -(0.00001 * layer[i].sumFilter[0][0][y][x]);
						//Momentum[i].sumFilter[0][0][y][x] = value;
						batchDweight[i].sumFilter[0][0][y][x] = 0;
					}
				}
			}
			dValue = tempDValue;
			//if(layer[i-1].tipe!= Layer_type::flatten)
		}
		else if (layer[i].tipe == Layer_type::dropout) {
			inputDimension tempDValue(dValue);
			for (auto &a : layer[i].dropoutIdx) {
				tempDValue.inputD[a[0]][a[1]][a[2]] = 0.0;
			}
			dValue = tempDValue;
		}
		else if (layer[i].tipe == Layer_type::fullyConnSigmoid) {
			//std::cout << "fullyconn" << std::endl;
			inputDimension tempDValue;
			std::vector<std::vector<double>> vec(1, std::vector<double>(inputLayer[i].x));
			//std::cout << "here?" << std::endl;
			//#pragma loop(hint_parallel(4))
			for (int x = 0; x < inputLayer[i].x; ++x) { //inputLayer[i].x
				//std::cout << "x"<<x<<std::endl;
				double value = 0.0;
				

				for (int y = 0; y < layer[i].y; ++y) {
					//std::cout << "y" << y << std::endl;
					value += layer[i].sumFilter[0][0][y][x] * dValue.inputD[0][0][y];
				}
				//value = ;
				//if (value < 0) value = 0;
				vec[0][x] = value  *(inputLayer[i].inputD[0][0][x] * (1.0 - inputLayer[i].inputD[0][0][x]));
			}
			//std::cout << "or here?" << std::endl;
			tempDValue.inputD.push_back(vec);
			tempDValue.input_Dimension = 1;
			tempDValue.y = 1;
			tempDValue.x = inputLayer[i].x;
			if (isupdated == false) {
				for (int y = 0; y < layer[i].y; ++y) {
					//#pragma loop(hint_parallel(4))
					layer[i].batchBias[y] += dValue.inputD[0][0][y];
					for (int x = 0; x < layer[i].x; ++x) {
						

						batchDweight[i].sumFilter[0][0][y][x] += (dValue.inputD[0][0][y] * inputLayer[i].inputD[0][0][x]);
						//Momentum[i].sumFilter[0][0][y][x] = (dValue.inputD[0][0][y] * inputLayer[i].inputD[0][0][x] * m) + ((1.0 - m) * Momentum[i].sumFilter[0][0][y][x]);
					}
				}
			}
			else {
				for (int y = 0; y < layer[i].y; ++y) {
					//	#pragma loop(hint_parallel(4))
					layer[i].batchBias[y] += dValue.inputD[0][0][y];
					layer[i].bias[y] = layer[i].bias[y] - (layer[i].batchBias[y] * learning_rate);
					layer[i].batchBias[y] = 0.0;
					for (int x = 0; x < layer[i].x; ++x) {
						batchDweight[i].sumFilter[0][0][y][x] += (dValue.inputD[0][0][y] * inputLayer[i].inputD[0][0][x]);
						Momentum[i].sumFilter[0][0][y][x] = (batchDweight[i].sumFilter[0][0][y][x] * m) + ((1.0 - m) * Momentum[i].sumFilter[0][0][y][x]);
						//double value = (batchDweight[i].sumFilter[0][0][y][x]*m) + ((1.0-m) * Momentum[i].sumFilter[0][0][y][x]);
						layer[i].sumFilter[0][0][y][x] = layer[i].sumFilter[0][0][y][x] - (Momentum[i].sumFilter[0][0][y][x] * learning_rate);// -(0.00001 * layer[i].sumFilter[0][0][y][x]);
						//Momentum[i].sumFilter[0][0][y][x] = value;
						batchDweight[i].sumFilter[0][0][y][x] = 0;
					}
				}
			}
			dValue = tempDValue;
			//if(layer[i-1].tipe!= Layer_type::flatten)
		}
		else if (layer[i].tipe == Layer_type::flatten) {
			inputDimension tempDValue(inputLayer[i]);
			for (int j = 0, count = 0; j < tempDValue.input_Dimension; ++j) {
				for (int y = 0; y < tempDValue.y; ++y) {
					for (int x = 0; x < tempDValue.x; ++x) {
						tempDValue.inputD[j][y][x] = dValue.inputD[0][0][count++];
					}
				}
			}
			dValue = tempDValue;
		}
		else if (layer[i].tipe == Layer_type::maxPool) {
			inputDimension tempDValue;
			tempDValue.x = inputLayer[i].x;
			tempDValue.input_Dimension = inputLayer[i].input_Dimension;
			tempDValue.y = inputLayer[i].y;
			//for (int j = 0; j < tempDValue.input_Dimension; ++i) {
				//tempDValue.inputD.push_back(std::vector<std::vector<double>>(tempDValue.y, std::vector<double>(tempDValue.x)));
			//}
			tempDValue.inputD = std::vector<std::vector<std::vector<double>>>(tempDValue.input_Dimension, std::vector<std::vector<double>>(tempDValue.y, std::vector<double>(tempDValue.x, 0.0)));
			for (int j = 0, count = 0; j < tempDValue.input_Dimension; ++j) {
				//std::vector<std::vector<double>> tempvector(tempDValue.y, std::vector<double>(tempDValue.x,0.0));
				for (int y = 0; y < dValue.y; ++y) {
					for (int x = 0; x < dValue.x; ++x) {
						int yoff = y * 2;
						int xoff = x * 2;
						double max = inputLayer[i].inputD[j][yoff][xoff];
						int xIndex = yoff;
						int yIndex = xoff;
						for (int yf = yoff; yf < yoff + 2; ++yf) {
							for (int xf = xoff; xf < xoff + 2; ++xf) {
								if (inputLayer[i].inputD[j][yf][xf] > max) {
									max = inputLayer[i].inputD[j][yf][xf];
									xIndex = xf;
									yIndex = yf;
								}
								//tempDValue.inputD[j][yf][xf] = dValue.inputD[j][y][x];
							}
						}
					
						tempDValue.inputD[j][yIndex][xIndex] = dValue.inputD[j][y][x];
						//tempDValue.inputD[j][y][x] = tempDValue.inputD[j][y][x]
					}
				}
				//tempDValue.inputD.push_back(tempvector);
			}
			dValue = tempDValue;
		}
		else if (layer[i].tipe == Layer_type::convoluteRelu) {
			inputDimension tempDValue(inputLayer[i]);
			int filtersize = layer[i].x;
			if (i > 0) {
				std::vector<std::vector<std::vector<double>>>().swap(tempDValue.inputD);
				//tempDValue.inputD.clear();
				tempDValue.inputD = std::vector<std::vector<std::vector<double>>>(tempDValue.input_Dimension, std::vector<std::vector<double>>(tempDValue.y, std::vector<double>(tempDValue.x, 0.0)));
				for (int j = 0; j < dValue.input_Dimension; ++j) {
					//#pragma loop(hint_parallel(4))
					//std::vector<std::vector<double>> tempvector(tempDValue.y, std::vector<double>(tempDValue.x, 0.0));
					for (int d = 0; d < inputLayer[i].input_Dimension; ++d) {

						for (int y = 0; y < dValue.y; ++y) {
							for (int x = 0; x < dValue.x; ++x) {
								for (int yf = y, filY = 0; yf < y + (filtersize); ++yf, ++filY) {
									for (int xf = x, filX = 0; xf < x + (filtersize); ++xf, ++filX) {
										if (dValue.inputD[j][y][x] != 0.0)
											tempDValue.inputD[d][yf][xf] += (dValue.inputD[j][y][x] * layer[i].sumFilter[j][d][filY][filX]);
									}
								}
							}
						}

					}
				}
			}
			if (isupdated == false) {
				for (int j = 0; j < dValue.input_Dimension; ++j) {
					for (int y = 0; y < dValue.y; ++y) {
						for (int x = 0; x < dValue.x; ++x) {
							for (int d = 0; d < inputLayer[i].input_Dimension; ++d) {
								for (int yf = y, filY = 0; yf < y + (filtersize); ++yf, ++filY) {
									for (int xf = x, filX = 0; xf < x + (filtersize); ++xf, ++filX) {
										//double value = (inputLayer[i].inputD[d][yf][xf] * dValue.inputD[j][y][x] * m) + ((1.0-m)* Momentum[i].sumFilter[j][d][filY][filX]);
										//layer[i].sumFilter[j][d][filY][filX] = layer[i].sumFilter[j][d][filY][filX];
										if (dValue.inputD[j][y][x] != 0.0)
											batchDweight[i].sumFilter[j][d][filY][filX] += (inputLayer[i].inputD[d][yf][xf] * dValue.inputD[j][y][x]);
									}
								}
							}
							layer[i].batchBias[j] += dValue.inputD[j][y][x];
						}
					}
				}
			}
			else {
				for (int j = 0; j < dValue.input_Dimension; ++j) {
					for (int y = 0; y < dValue.y; ++y) {
						for (int x = 0; x < dValue.x; ++x) {
							for (int d = 0; d < inputLayer[i].input_Dimension; ++d) {
								for (int yf = y, filY = 0; yf < y + (filtersize); ++yf, ++filY) {
									for (int xf = x, filX = 0; xf < x + (filtersize); ++xf, ++filX) {
										if (y == dValue.y - 1 && x == dValue.x - 1) {
											if (dValue.inputD[j][y][x] != 0.0)
											batchDweight[i].sumFilter[j][d][filY][filX] += (inputLayer[i].inputD[d][yf][xf] * dValue.inputD[j][y][x]);
											Momentum[i].sumFilter[j][d][filY][filX] = ((batchDweight[i].sumFilter[j][d][filY][filX]) * m) + ((1.0 - m)* Momentum[i].sumFilter[j][d][filY][filX]);
											layer[i].sumFilter[j][d][filY][filX] = layer[i].sumFilter[j][d][filY][filX] - (Momentum[i].sumFilter[j][d][filY][filX] * learning_rate) - (0.00001 *layer[i].sumFilter[j][d][filY][filX]);
											//Momentum[i].sumFilter[j][d][filY][filX] = value;
											batchDweight[i].sumFilter[j][d][filY][filX] = 0.0;
										}
										else {
											if (dValue.inputD[j][y][x] != 0.0)
												batchDweight[i].sumFilter[j][d][filY][filX] += (inputLayer[i].inputD[d][yf][xf] * dValue.inputD[j][y][x]);
										}
									}
								}
							}
							if (y == dValue.y - 1 && x == dValue.x - 1) {
								layer[i].batchBias[j] += dValue.inputD[j][y][x];
								layer[i].bias[j] = layer[i].bias[j] - (layer[i].batchBias[j] * learning_rate);
								layer[i].batchBias[j] = 0.0;
							}
							else {
								layer[i].batchBias[j] += dValue.inputD[j][y][x];
							}

						}
					}
				}
			}
			dValue = tempDValue;
		}
	}

}

void convolution_layer::printLayer() {
	for (auto &a : layer) {
		std::cout << a.tipe;
	}
}

inputDimension convolution_layer::convolute(int layer) {
	inputDimension y;
	return y;
}

/*void convolution_layer::setInput(std::vector < std::vector < std::vector < double >> > &input) {
	inputDimension start(input);
	//std::cout << "hai";
	this->inputLayer.push_back(start);
}*/

void convolution_layer::printWeight() {
	for (int i = 0; i < layer.size(); ++i) {
		for (int j = 0; j < layer[i].sumFeatureMap; ++j) {
			for (int k = 0; k < layer[i].dimensionSize; ++k) {
				for (int y = 0; y < layer[i].y; ++y) {
					for (int x = 0; x < layer[i].x; ++x) {
						std::cout << "layer " << i << " dimension" << j << "  y " << y << "x " << x << std::endl;
						std::cout << layer[i].sumFilter[j][k][y][x] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
		}
	}
}

