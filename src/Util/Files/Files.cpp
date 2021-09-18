#include "Files.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

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