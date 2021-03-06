#define VERSION "0.1.0"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <future>
#include <chrono>
#include <random>

// If using msvc DO NOT include pthread.h, since its a UNIX only header
#ifdef UNIX
	#include <pthread.h>
#endif // !UNIX

#include <vector>
#include <thread>
#include "Util/Files/Files.h"

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
bool Random = true; // Should fill with random characters or not
std::string Char = "a"; // Char to fill with

#pragma endregion

#pragma region Functions

/*
Clears the console
*/
void clear() {
	std::cout << "\x1B[2J\x1B[H";
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
		else if (strcmp(argv[i], "-nr") == 0 || strcmp(argv[i], "-NR") == 0 || strcmp(argv[i], "--no-random") == 0) {
			Random = false;
		}
		else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-C") == 0 || strcmp(argv[i], "--character") == 0) {
			Char = argv[i + 1];
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
		std::cout << "Multi-Threaded\n\n";
		// Multi threaded code
		// Start threads

		for (int i = 0; i < ThreadCount; i++) {

			futures.push_back(std::async(std::launch::async, [i]() {

				WriteToFile(i, FileName, true, SizeMode, Size, Random, Char[0]);

			}));

		}
	}
	else {
		
		std::cout << "Single-threaded\n\n";

		WriteToFile(NULL, FileName, false, SizeMode, Size, Random, Char[0]);
	}

	exit(0);
}