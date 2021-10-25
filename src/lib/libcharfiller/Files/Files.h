#pragma once

#include <fstream>
#include <variant>
#include <string>
#include <utility>
#include <chrono>

// enum class SizeMode {
// 	B=0, K=1, M=2, G=3
// };

[[deprecated ("Old Function, from before the v2.0 rewrite")]]void WriteToFile(int FileNum, std::string FileName, bool MultiThread, unsigned int& SizeMode, std::string Size, bool Random, char CharToFill);


/**
 * @brief Writes to a file
 * 
 * @param FileName Name of the file
 * @param Size Size of the file
 * @param Random Should the file be filled with random characters?
 * @param CharToFill If Random is false, fill the file with this char
 * @return std::pair<int, double> error code+milliseconds
 */
[[maybe_unused]] std::pair<int, double> WriteToFileN(std::string FileName, std::string Size, bool Random, char CharToFill);

/**
 * @brief Writes to a file
 * 
 * @param MultiThread Is the workload multithreaded?
 * @param FileNum Number of the file. Will be appended after the name, before the extrension. Ignored if not MultiThreaded
 * @param FileName Name of the file
 * @param Size Size of the file
 * @param Random Should the file be filled with random characters?
 * @param CharToFill If Random is false, fill the file with this char
 * @return std::pair<int ,double> error code+milliseconds
 */
[[maybe_unused]] std::pair<int ,double> WriteToFileN(bool MultiThread, int FileNum, std::string FileName, std::string Size, bool Random, char CharToFill);

/**
 * @brief Parses a file name
 * 
 * @param FileName Name of the file
 * @return std::pair<std::string, std::string> name+extension
 */
[[maybe_unused]] std::pair<std::string, std::string> ParseFileName(std::string FileName);