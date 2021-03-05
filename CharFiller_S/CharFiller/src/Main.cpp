#define VERSION "0.1.0-beta-multithreading"

#include <iostream>
#include <string>
#include <fstream>
#include <future>
#include <mutex>
#include <thread>

using string = std::string;

enum SizeMode {
	B = 0, KB = 1, MB = 2, GB = 3
};

std::string Size;
std::string FileName;
std::ofstream File;
unsigned int SizeMode;
static std::mutex FileMutex;
std::vector<std::future<void>> futures;


/*
Clears the console
*/
void clear() {
	std::cout << "\x1B[2J\x1B[H";
}

/*
Writes asynchronously to a file using mutexes
@param	std::mutex&	mut:	mutex reference
@param	std::ofstream&	file:	file to write to
@param	std::string	write:	string to write in file
*/
static void WriteToFile_Async(std::mutex& mut, std::ofstream& file, std::string write) {
	std::lock_guard<std::mutex> lock(mut);
	file << write;
}

int main(int argc, char* argv[]) {

	// Parse arguments
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-S") == 0) {
			Size = argv[i + 1];
		}
		else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "-F") == 0) {
			FileName = argv[i + 1];
		}
	}

	

	if (Size != "" || Size != " ") {
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
			SizeMode = 2;
		}
	}
	else {
		SizeMode = 2;
	}


	File.open(FileName);
	
	switch (SizeMode)
	{

	case 0:
		/*for (int i = 0; i < std::stoi(Size); i++) { // Not Multithreaded!
			File << "a";
		}*/

		for (int i = 0; i < std::stoi(Size); i++) {
			futures.push_back(std::async(std::launch::async, []() {
				
				WriteToFile_Async(FileMutex, File, "a");

			}));
		}

		std::cout << "Done!\n" << std::stoi(Size) << " B\n";
		File.close();
		break;

	case 1:
		/*for (int i = 0; i < std::stoi(Size)*1024; i++) { // Not Multithreaded!
			File << "a";
		}*/

		for (int i = 0; i < std::stoi(Size) * 1024; i++) {
			futures.push_back(std::async(std::launch::async, []() {

				WriteToFile_Async(FileMutex, File, "a");

			}));
		}

		std::cout << "Done!\n" << std::stoi(Size)*1024 << " B\n";
		File.close();
		break;

	case 2:
		/*for (int i = 0; i < std::stoi(Size) * 1048576; i++) { // Not Multithreaded!
			File << "a";
		}*/

		for (int i = 0; i < std::stoi(Size) * 1048576; i++) {
			futures.push_back(std::async(std::launch::async, []() {

				WriteToFile_Async(FileMutex, File, "a");

			}));
		}

		std::cout << "Done!\n" << std::stoi(Size) * 1048576 << " B\n";
		File.close();
		break;

	case 3:
		/*for (int i = 0; i < std::stoi(Size) * 1073741824; i++) { // Not Multithreaded
			File << "a";
		}*/

		for (int i = 0; i < std::stoi(Size) * 1073741824; i++) {
			futures.push_back(std::async(std::launch::async, []() {

				WriteToFile_Async(FileMutex, File, "a");

			}));
		}

		std::cout << "Done!\n" << std::stoi(Size) * 1073741824 << " B\n";
		File.close();
		break;

	default:
		std::cerr << "\aERROR!";
		exit(4);
		break;
	}
	exit(0);
}