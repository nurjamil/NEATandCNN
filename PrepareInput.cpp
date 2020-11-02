
#include "PrepareInput.h"
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <filesystem>

PrepareInput::PrepareInput()
{

	
}


PrepareInput::~PrepareInput()
{
}

std::vector<BYTE> PrepareInput::openfile(std::string filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "fail";
	}
	//std::cout<<ind.randomNumber(-1, 1)<<std::endl;

	// Stop eating new lines in binary mode!!!
	file.unsetf(std::ios::skipws);

	// get its size:
	std::streampos fileSize;

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// reserve capacity
	std::vector<BYTE> vec;
	vec.reserve(fileSize);

	// read the data:
	vec.insert(vec.begin(),
		std::istream_iterator<BYTE>(file),
		std::istream_iterator<BYTE>());

	return vec;
}

void PrepareInput::convertData() {
	for (auto &dat : data2) {
		inputNEAT in;
		for (int i = 0, count = 0; i < dat.inputData[0].size(); ++i) {
			for (int j = 0; j < dat.inputData[0][i].size(); ++j) {
				in.input_data.push_back(dat.inputData[0][i][j]);
			}
		}
		for (int i = 0; i < dat.output.size(); ++i) if (dat.output[i] == 1.0) in.label = i;
		data.push_back(in);
	}
}
void PrepareInput::loadImg(std::string path) {
	inputNEAT i;
	i.input_data = (filetoVector(path));
	i.label = 0;
	if (data.empty())
		data.push_back(i);
	else
		data[0] = i;
}
void PrepareInput::readFolder(std::string folder, int indexPredicted, int count) {
	for (auto & entry : std::filesystem::directory_iterator(folder)) {
		//std::cout << entry.path() << std::endl;
		//std::vector<file> in(1);
		//in.push_back(filetoVector(entry.path().string()));
		//input.push_back(in);
		//output.push_back(std::vector<double>(10));
		//output[output.size() - 1][indexPredicted] = 1.0;
		inputNEAT i;
		i.input_data = (filetoVector(entry.path().string()));
		i.label = indexPredicted;
		data.push_back(i);
		--count;
		if (count == 0) {
			break;
		}
		
	}
	//std::cout << input.size();
}

std::vector<double> PrepareInput::filetoVector(std::string file) {
	cv::Mat mat = cv::imread(file, 0);
	//std::cout << "mat type" << type2str(mat.type());
	cv::Mat dst;

	if (mat.empty()) // Check for failure
	{
		std::cout << "Could not open or find the image" << std::endl;
		system("pause"); //wait for any key press
		//return -1;
	}
	else {
		//std::cout << "sukses" << std::endl;
	}

	//cv::imshow("kw", dst);
	//std::cin.get();
	std::vector<std::vector<double>> array2(mat.rows, std::vector<double>(mat.cols));
	std::vector<double> array;
	std::vector<BYTE> vec;
	int rows = mat.rows;
	int column = mat.cols;
	int offset = 0;
	if (mat.isContinuous()) {
		vec.assign(mat.data, mat.data + mat.total());
		//std::cout << "true";
	}
	else {
		//std::cout << "false";
		for (int i = 0; i < mat.rows; ++i) {
			array2[i].insert(array2[i].end(), mat.ptr<float>(i), mat.ptr<float>(i) + mat.cols);
		}
	}
	//std::cout << vec.size();
	//std::cin.get();
	//std::cout << "row " << rows << " column " << column;
	//std::cout << "mat type" << type2str(mat.type());
	int count = 0;
	array.reserve(rows*column);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < column; ++j) {
			array.push_back((255 - static_cast<double>(vec[count++])) / 255.0);
			//array2[i][j] = (255 - static_cast<double>(vec[count++])) / 255.0;
			
		}
	}

	return array;
}
std::vector<std::string> PrepareInput::get_directories(const std::string& s)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::recursive_directory_iterator(s))
		if (p.is_directory())
			r.push_back(p.path().string());
	return r;
}

void PrepareInput::LoadFromOneFolder(const std::string str) {
	std::vector<std::string> dir = get_directories(str);
	for (size_t i = 0; i < dir.size(); ++i) {
		readFolder(dir[i], (int)i);
	}
}