
#include "InputFile.h"
#include <filesystem>
#include <fstream>

InputFile::InputFile()
{

}
void InputFile::readFolder(std::string folder, int indexPredicted, int count) {
	//int count = 0;
	//#pragma loop(hint_parallel(4))
	size_t size = std::distance(std::filesystem::directory_iterator(folder), std::filesystem::directory_iterator{});
	data.reserve(size);
	for (auto & entry : std::filesystem::directory_iterator(folder)) {
		//std::cout << entry.path() << std::endl;
		//std::vector<file> in(1);
		//in.push_back(filetoVector(entry.path().string()));
		//input.push_back(in);
		//output.push_back(std::vector<double>(10));
		//output[output.size() - 1][indexPredicted] = 1.0;
		input i;
		i.inputData.push_back(filetoVector(entry.path().string()));
		i.output = std::vector<double>(10);
		i.output[indexPredicted] = 1.0;
		data.push_back(i);
		--count;
		if (count == 1) break;

	}
	//std::cout << input.size();
}

std::vector<std::string> InputFile::get_directories(const std::string& s)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::recursive_directory_iterator(s))
		if (p.is_directory())
			r.push_back(p.path().string());
	return r;
}

void InputFile::LoadFromOneFolder(const std::string str) {
	std::vector<std::string> dir = get_directories(str);
	for (size_t i = 0; i < dir.size();++i) {
		readFolder(dir[i], (int)i);
	}
}



void InputFile::print() {
	for (auto &a : data) {
		for (auto &b : a.inputData) {
			for (auto &c : b) {
				for (auto &d : c) {
					std::cout << d << " ";
				}
			}
		}
	}
}

std::vector<std::vector<double>> InputFile::filetoVector(const std::string file) {
	cv::Mat mat = cv::imread(file, 0);
	//std::cout << "mat type" << type2str(mat.type());
	cv::Mat dst;
	//dst.convertTo(mat, CV_64F, 1, 0);
	//std::cin.get();

	//std::string windowName = "ori";
	//cv::namedWindow(windowName);
	//cv::imshow(windowName, dst);
	//cv::waitKey(0); // Wait for any keystroke in the window
	//std::cin.get();
	//cv::destroyWindow(windowName);
	//std::cin.get();

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
	int rows = mat.rows;
	int column = mat.cols;
	int offset = 0;

	std::vector<std::vector<double>> array2(mat.rows, std::vector<double>(mat.cols));
	std::vector<float> array;
	std::vector<BYTE> vec;
	if (mat.isContinuous()) {
		// array.assign((float*)mat.datastart, (float*)mat.dataend); // <- has problems for sub-matrix like mat = big_mat.row(i)
		//for (int i = 0; i < rows; ++i) {
			//array2[i].assign((float*)mat.data + offset, (float*)mat.data + column * (i + 1));
			//offset = column * (i + 1);
		//}
		vec.assign(mat.data, mat.data + mat.total());
		//std::cout << "true";
	}
	else {
		std::cout << "false";
		for (int i = 0; i < mat.rows; ++i) {
			array2[i].insert(array2[i].end(), mat.ptr<float>(i), mat.ptr<float>(i) + mat.cols);
		}
	}
	//std::cout << vec.size();
	//std::cin.get();
	//std::cout << "row " << rows << " column " << column;
	//std::cout << "mat type" << type2str(mat.type());
	int count = 0;
	/*double mean = 0.0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < column; ++j) {
			mean += (static_cast<double>(vec[count++]));

		}
	}
	count = 0;
	mean = mean / (double)vec.size();
	double std = 0.0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < column; ++j) {
			std += pow(((static_cast<double>(vec[count++])) - mean),2);

		}
	}
	count = 0;
	std = sqrt(std / (double)vec.size());
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < column; ++j) {
			 array2[i][j]= ((static_cast<double>(vec[count++])) - mean) / (std + 0.0000001);
		}
	}*/
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < column; ++j) {
			//array2[i][j] = (255 - static_cast<double>(vec[count++])) / 255.0;
			array2[i][j] = (255.0 - static_cast<double>(vec[count++])) / 255.0;
			//mean += array2[i][j];
		}
	}

	return array2;
}
void InputFile::loadImage(std::string path) {
	input i;
	i.inputData.push_back(filetoVector(path));
	i.output = std::vector<double>(10);
	if (data.empty()) {
		data.push_back(i);
	}
	else {
		data[0] = i;
	}
}
InputFile::~InputFile()
{
}
void InputFile::prepareInput() {
	input2 in;
	std::vector<BYTE> vec;
	vec = openfile("D:\\cats1000.bin");
	std::cout << vec.size() / 784 << std::endl;
	//input in;
	int stop = 783;
	int offset = 0;
	in.input_data.resize(784);
	in.label = 0;
	int size = vec.size();
	//std::cout << size << std::endl;
	for (int i = 0; i < size; ++i) {
		if (i == stop) {
			in.input_data[i - offset] = static_cast<double>(vec[i]) / 255.0;
			this->data2.push_back(in);
			stop += 784;
			offset += 784;
		}
		else {
			in.input_data[i - offset] = static_cast<double>(vec[i]) / 255.0;
		}

	}
	vec = openfile("D:\\trains1000.bin");
	in.label = 1;
	stop = 783;
	size = vec.size();
	offset = 0;
	for (int i = 0; i < size; ++i) {
		if (i == stop) {
			in.input_data[i - offset] = static_cast<double>(vec[i]) / 255.0;
			this->data2.push_back(in);
			stop += 784;
			offset += 784;
		}
		else {
			in.input_data[i - offset] = static_cast<double>(vec[i]) / 255.0;
		}
	}


	vec = openfile("D:\\rainbows1000.bin");
	in.label = 2;
	stop = 783;
	offset = 0;
	size = vec.size();
	for (int i = 0; i < size; ++i) {
		if (i == stop) {
			in.input_data[i - offset] = static_cast<double>(vec[i]) / 255.0;
			this->data2.push_back(in);
			stop += 784;
			offset += 784;
		}
		else {
			in.input_data[i - offset] = static_cast<double>(vec[i]) / 255.0;
		}
	}

}
void InputFile::transfer() {
	for (int i = 0; i < data2.size(); ++i) {
		std::vector<std::vector<std::vector<double>>> anu;
		std::vector<std::vector<double>> semane(28, std::vector<double>(28));
		for (int y = 0, count = 0; y < 28; ++y) {
			for (int x = 0; x < 28; ++x) {
				semane[y][x] = data2[i].input_data[count++];
			}
		}
		anu.push_back(semane);
		input in;
		in.inputData = anu;
		in.output = std::vector<double>(10);
		//int la = data2[i].
		in.output[data2[i].label] = 1.0;
		data.push_back(in);
	}
}
std::vector<BYTE> InputFile::openfile(std::string filename) {
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

void InputFile::print1() {
	for (auto &b : data[0].inputData) {
		for (auto &c : b) {
			for (auto &d : c) {
				std::cout << d << " ";
			}
			std::cout << std::endl;
		}
	}

}
std::string InputFile::type2str(int type) {
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

void InputFile::normalize() {
	mean = mean / (data.size() * 784);
	for (auto &a : data) {
		for (auto &b : a.inputData) {
			for (auto &c : b) {
				for (auto &d : c) {
					std += pow((d - mean), 2);
				}
			}
		}
	}
	std = sqrt(std / (data.size() * 784));
	for (auto &a : data) {
		for (auto &b : a.inputData) {
			for (auto &c : b) {
				for (auto &d : c) {
					d = (d - mean) / (std + 0.000000001);
				}
			}
		}
	}

}

void InputFile::normalizeTest() {
	for (auto &a : data) {
		for (auto &b : a.inputData) {
			for (auto &c : b) {
				for (auto &d : c) {
					d = (d - mean) / (std + 0.000000001);
				}
			}
		}
	}

}

bool InputFile::operator==(const InputFile &in2) {
	for (size_t i = 0; i < data.size(); ++i) {
		if (data[i].inputData != in2.data[i].inputData || data[i].output != in2.data[i].output) return false;
	}
	return true;
}