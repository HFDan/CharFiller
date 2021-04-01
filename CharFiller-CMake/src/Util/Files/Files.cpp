#include "Files.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>

void WriteToFile(int FileNum, std::string FileName, bool MultiThread, unsigned int& SizeMode, std::string& Size, bool Random, char CharToFill) {
	std::ofstream File;

#pragma region Tokenisation

	std::string FileNameTemp = FileName;
	std::string delimiter = ".";
	size_t pos = 0;
	std::string token;
	std::vector<std::string> StringVect;

	while ((pos = FileNameTemp.find(delimiter)) != std::string::npos) {
		token = FileNameTemp.substr(0, pos);
		StringVect.push_back(token);
		FileNameTemp.erase(0, pos + delimiter.length());
	}
	std::string Extension = FileNameTemp;

	std::string FileNameNoExt;
	for (auto i : StringVect) {
		FileNameNoExt = FileNameNoExt + i;
	}

#pragma endregion

	// Check if multithreaded
	if (MultiThread) {
		File.open(FileNameNoExt + std::to_string(FileNum) + "." + Extension);
	}
	else
	{
		File.open(FileNameNoExt + Extension);
	}


	// Generate random number for file name
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(65, 122);

	switch (SizeMode)
	{

	case 0:
		for (int i = 0; i < std::stoi(Size); i++) {
			File << (char)distr(gen);
		}

		std::cout << "Done!\n" << std::stoi(Size) << " B\n\n";
		File.close();
		break;

	case 1:
		for (int i = 0; i < std::stoi(Size) * 1024; i++) {
			File << (char)distr(gen);
		}

		std::cout << "Done!\n" << std::stoi(Size) * 1024 << " B\n\n";
		File.close();
		break;

	case 2:
		for (int i = 0; i < std::stoi(Size) * 1048576; i++) {
			File << (char)distr(gen);
		}

		std::cout << "Done!\n" << std::stoi(Size) * 1048576 << " B\n\n";
		File.close();
		break;

	case 3:
		for (int i = 0; i < std::stoi(Size) * 1073741824; i++) {
			File << (char)distr(gen);
		}

		std::cout << "Done!\n" << std::stoi(Size) * 1073741824 << " B\n\n";
		File.close();
		break;

	default:
		std::cerr << "\aERROR!";
		File.close();
		exit(4);
		break;
	}

}