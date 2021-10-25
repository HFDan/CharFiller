#include "Files.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <chrono>

[[deprecated ("Old Function, from before the v2.0 rewrite")]]
void WriteToFile(int FileNum, std::string FileName, bool MultiThread,
				unsigned int& SizeMode, std::string Size, bool Random, char CharToFill) {

	std::ofstream File;

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


	// Check if multithreaded
	if (MultiThread) {
		File.open(FileNameNoExt + std::to_string(FileNum) + "." + Extension);
	}
	else
	{
		File.open(FileNameNoExt + "." + Extension);
	}

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(65, 122);

    auto start = std::chrono::high_resolution_clock::now();

        switch (SizeMode) {
            case 0:
                for (int i = 0; i < std::stoi(Size); i++) {
                    if (Random)
                        File << (char)distr(gen);
                    else
                        File << CharToFill;
                }
                File.close();
                {
                    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
                    printf("Done!\n %i B in %f seconds\n\n", std::stoi(Size), duration.count());
                    fflush(stdout);
                }
                break;

            case 1:
                for (int i = 0; i < std::stoi(Size) * 1024; i++) {
                    if (Random)
                        File << (char)distr(gen);
                    else
                        File << CharToFill;
                }
                File.close();
                {
                    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
                    printf("Done!\n %i B in %f seconds\n\n", std::stoi(Size) * 1024, duration.count());
                    fflush(stdout);
                }
                break;

            case 2:
                for (int i = 0; i < std::stoi(Size) * 1048576; i++) {
                    if (Random)
                        File << (char)distr(gen);
                    else
                        File << CharToFill;
                }

                File.close();

                {
                    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
                    printf("Done!\n %i B in %f seconds\n\n", std::stoi(Size) * 1048576, duration.count());
                    fflush(stdout);
                }
                break;

            case 3:
                for (int i = 0; i < std::stoi(Size) * 1073741824; i++) {
                    if (Random)
                        File << (char)distr(gen);
                    else
                        File << CharToFill;
                }
                File.close();

                {
                    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
                    printf("Done!\n %i B in %f seconds\n\n", std::stoi(Size) * 1073741824, duration.count());
                    fflush(stdout);
                }

                break;

            default:
                std::cerr << "\aERROR!";
                File.close();
                exit(4);
                break;
        }

}

enum class SizeMode {
	B = 1, K = 1024, M = 1048576, G = 1073741824
};

std::pair<int, double> WriteToFileN(std::string FileName, std::string Size, bool Random, char CharToFill) {
	return WriteToFileN(false, 0, FileName, Size, Random, CharToFill);
}

std::pair<int, double> WriteToFileN(bool MultiThread, int FileNum, std::string FileName, std::string Size, bool Random, char CharToFill) {

	auto FileNameParsed = ParseFileName(FileName);
	SizeMode SizeMode;
	std::ofstream File;
	if (MultiThread)
		File.open(FileNameParsed.first + std::to_string(FileNum) + "." + FileNameParsed.second);
	else
		File.open(FileNameParsed.first + FileNameParsed.second);

	std::random_device rd;
   	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(65, 122);

	// Parse Size
	switch(Size.back()) {
		case 'B':
			SizeMode = SizeMode::B;
			break;

		case 'K':
			SizeMode = SizeMode::K;
			break;

		case 'M':
			SizeMode = SizeMode::M;
			break;

		case 'G':
			SizeMode = SizeMode::G;
			break;

		default:
			fprintf(stderr, "Error when determining file size!\n");
	}
	auto StartTimepoint = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < (std::stoi(Size) * (int)SizeMode); i++) { // Write to file
		if (Random) {
			File << (char)distr(gen);
		}
		else {
			File << CharToFill;
		}
	}
	
	auto EndTimepoint = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimepoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimepoint).time_since_epoch().count();
	auto duration = end - start;



	return std::pair<int, double>(0, duration * 0.001);
}

std::pair<std::string, std::string> ParseFileName(std::string FileName) {
	std::vector<std::string> strings;
    std::istringstream f(FileName);
    std::string buff;    
    while (std::getline(f, buff, '.')) {
        strings.push_back(buff);
    }

	std::string Name;

	for (int i = 0; i < strings.size() - 1; i++) {
		Name+=strings[i];
		Name+=".";
	}

	return std::pair<std::string, std::string>(Name, strings.back());
}
