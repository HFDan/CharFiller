#define VERSION "0.0.1"

#include <iostream>
#include <string>
#include <fstream>

using string = std::string;

enum SizeMode {
	B = 0, KB = 1, MB = 2, GB = 3
};

std::string Size;
std::string FileName;
std::ofstream File;
unsigned int SizeMode;

void clear() {
	std::cout << "\x1B[2J\x1B[H";
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
		for (int i = 0; i < std::stoi(Size); i++) {
			File << "a";
		}
		File.close();
		exit(0);
		break;

	default:
		exit(4);
		break;
	}

}