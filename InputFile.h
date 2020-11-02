#pragma once
#ifndef INPUTFILE_H
#define INPUTFILE_H
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
typedef unsigned char BYTE;
//typedef std::vector<std::vector<double>> file;
struct input {
	std::vector<double> output;
	std::vector<std::vector<std::vector<double>>> inputData;

};

struct input2 {
	int label;
	std::vector<double> input_data;

};
class InputFile
{
private:

public:
	double mean;
	double std;
	std::vector<input> data;
	InputFile();
	std::vector<input2> data2;
	std::vector<input> &getData() { return data; };
	void readFolder(std::string folder, int indexPredicted, int count = -1);
	~InputFile();
	std::string type2str(int type);
	void print1();
	void print();
	void transfer();
	void normalize();
	void loadImage(std::string path);
	std::vector<std::string> get_directories(const std::string& s);
	void LoadFromOneFolder(const std::string str);
	void normalizeTest();
	std::vector<BYTE> openfile(std::string filename);
	void prepareInput();
	std::vector<std::vector<double>> filetoVector(std::string file);
	bool operator==(const InputFile &in2);
};

#endif