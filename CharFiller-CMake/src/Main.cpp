#define VERSION "0.1.0"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <future>
#include <random>

// If using msvc DO NOT include pthread.h, since its a UNIX only header
#ifndef MSVC
	#include <pthread.h>
#endif // !MSVC

#include <vector>
#include <thread>

using string = std::string;

enum SizeMode {
	B = 0, KB = 1, MB = 2, GB = 3
};

#pragma region Varaibles

std::string Size = "1"; // File size
std::string FileName = "CharFiller_Output.txt"; // Name of file to write
unsigned int SizeMode; // B, KB, MB, GB
int ThreadCount = 1; // How many threads to run (How many files to generate)
std::vector<std::future<void>> futures; // Futures returned by std::async

#pragma endregion

#pragma region Functions

/*
Clears the console
*/
void clear() {
	std::cout << "\x1B[2J\x1B[H";
}


void WriteToFile(int FileNum, std::string FileName, bool MultiThread) {
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


#pragma endregion

int main(int argc, char* argv[]) {

	// Parse arguments
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "--size") == 0) {
			Size = argv[i + 1];
		}
		else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "-F") == 0 || strcmp(argv[i], "--file") == 0) {
			FileName = argv[i + 1];
		}
		else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--threads") == 0) {
			ThreadCount = atoi(argv[i + 1]);
		}
	}


	// Determine size
	if (!Size.empty()) {
		if (Size.back() == 'B') {
			SizeMode = 0;
		}
		else if (Size.back() == 'K') {
			SizeMode = 1;
		}
		else if (Size.back() == 'M') {
			SizeMode = 2;
		}
		else if (Size.back() == 'G') {
			SizeMode = 3;
		}
		else {
			SizeMode = 1;
		}
	}
	else {
		SizeMode = 1;
	}

	if (ThreadCount > 1) {
		std::cout << "Multi-Threaded\n";
		// Multi threaded code
		// Start threads

		for (int i = 0; i < ThreadCount; i++) {

			futures.push_back(std::async(std::launch::async, [i]() {

				WriteToFile(i, FileName, true);

			}));

		}
	}
	else {
		
		std::cout << "Single-threaded\n";

		WriteToFile(NULL, FileName, false);
	}

	exit(0);
}