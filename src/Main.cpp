#include <cstdio>
#include <future>
#include <vector>
#include <thread>

// If using msvc DO NOT include pthread.h, since its a UNIX only header
#ifdef UNIX
#include <pthread.h>
#endif // !UNIX

#include "Files/Files.h"
#include "thirdparty/argparse/argparse.h"

using namespace argparse;

int main(int argc, const char **argv) {
	unsigned int SizeMode = 0; // To make clang-tidy shut up

	ArgumentParser parser("CharFiller", "A console app to create files");
	parser.add_argument("-f", "--file", "The name of the file", true);
	parser.add_argument("-t", "--threads", "Amount of *IDENTICAL FILES* to create", false);
	parser.add_argument("-s", "--size", "Desired file-size", true);
	parser.add_argument("-n", "--norandom", "Generate the file without random contents", false);
	parser.add_argument("-d", "--debug", "Enables debug mode", false);
	parser.add_argument("-c", "--char", "*ONLY USABLE WITH -n*, the character to fill the file with", false);
	parser.enable_help();

	auto parseError = parser.parse(argc, argv);

	if (parseError) {
		fprintf(stderr, "%s\n", parseError.what().c_str());
		return -1;
	}

	if (parser.exists("h")) {
		parser.print_help();
		return 0;
	}

	// NOTE: ONLY FOR DEBUGGING PURPOSES!
	printf("-f: %s\n"
			"-t: %i\n"
			"-s: %s\n"
			"-nR: %i\n"
			"-d: %i\n"
			"-c: %c\n", parser.get<std::string>("f").c_str(), parser.get<int>("t"), parser.get<std::string>("s").c_str(), parser.exists("n"), parser.exists("d"), parser.get<char>("c"));

	switch(parser.get<std::string>("s").back()) {
		case 'B':
			SizeMode = 0;
			break;

		case 'K':
			SizeMode = 1;
			break;

		case 'M':
			SizeMode = 2;
			break;

		case 'G':
			SizeMode = 3;
			break;

		default:
			fprintf(stderr, "Error when determining file size!\n");
	}

	printf("SizeMode: %i\n", SizeMode);

	// NOTE: Everything after this point is a fucking mess. I have no idea what it does so i will
	// rewrite it when i have the time.
	// if (parser.exists("t")) {
	// 	std::vector<std::future<void>> futures;
	// 	for (int i = 0; i < parser.get<int>("t"); i++) {
	// 		futures.push_back(std::async(std::launch::async, [&]() -> void {
	// 			WriteToFile(i, parser.get<std::string>("f"), true,
	// 					   SizeMode, parser.get<std::string>("s"), !parser.exists("n"), parser.get<char>("c"));
	// 		}));
	// 	}
	// } else {
	// 	printf("ST\n");
	// 	WriteToFile(NULL, parser.get<std::string>("f"), parser.exists("t"),
	// 				SizeMode, parser.get<std::string>("s"), !parser.exists("nR"), parser.get<char>("c"));
	// }

	return 0;
}