#include <cstdio>
#include <future>
#include <vector>
#include <utility>
#include <thread>

// If using msvc DO NOT include pthread.h, since its a UNIX only header
#ifdef UNIX
#include <pthread.h>
#endif // !UNIX

#include "libcharfiller/Files/Files.h"
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
	if (parser.exists("d"))
		printf("Interpreted arguments: "
				"-f: %s\n"
				"-t: %i\n"
				"-s: %s\n"
				"-n: %s\n"
				"-d: %s\n"
				"-c: %c\n", parser.get<std::string>("f").c_str(), parser.get<int>("t"), parser.get<std::string>("s").c_str(), parser.exists("n") ? "true" : "false", parser.exists("d") ? "true" : "false", parser.get<char>("c"));

	if (parser.exists("d"))
		printf("SizeMode: %i\n", SizeMode);

	// NOTE: Everything after this point is a fucking mess. I have no idea why it segfaults
	// FIXME: This code always segfaults when reaching 'futures.push_back()'

	if (parser.exists("t")) {
		std::vector<std::future<std::pair<int, double>>> futures;
		for (int i = 0; i < parser.get<int>("t"); i++) {
			futures.push_back(std::async(std::launch::async, [&]() -> std::pair<int, double> {
				return WriteToFileN(true, i, parser.get<std::string>("n"), parser.get<std::string>("s"), !parser.exists("n"), parser.get<char>("c"));
			}));
		}
	} 
	else {
		auto op = WriteToFileN(parser.get<std::string>("f"), parser.get<std::string>("s"), !parser.exists("n"), parser.get<char>("c"));
	}

	return 0;
}