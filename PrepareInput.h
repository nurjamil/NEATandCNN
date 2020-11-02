#pragma once
#ifndef PREPAREINPUT_H
#define PREPAREINPUT_H
#include <vector>
#include <opencv2/opencv.hpp>
typedef unsigned char BYTE;
typedef std::vector<std::vector<double>> file;
struct inputNEAT2 {
	std::vector<double> output;
	std::vector<file> inputData;

};

struct inputNEAT {
	int label;
	std::vector<double> input_data;

};
class PrepareInput
{
public:
	PrepareInput();
	std::vector<inputNEAT> data;
	std::vector<inputNEAT2> data2;
	void convertData();
	void loadImg(std::string path);
	std::vector<std::string> get_directories(const std::string& s);
	void readFolder(std::string folder, int indexPredicted, int count = -1);
	void LoadFromOneFolder(const std::string str);
	std::vector<double> filetoVector(std::string file);
	std::vector<BYTE> openfile(std::string filename);
	~PrepareInput();
};

#endif

