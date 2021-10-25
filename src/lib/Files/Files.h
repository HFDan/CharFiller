#pragma once

#include <fstream>

/**
Writes to a file
@param	int		FileNum:	The number of the file, to prevent duplicates. Can be set to NULL if workload is not multithreaded.
@param	std::string	FileName:	Name of the file. Extension gets parsed automatically.
@param	bool	MultiThread:	Is the workload multithreaded?
@param	int&	SizeMode:	0 = Bytes, 1 = KB, 2 = MB, 3 = GB
@param	std::string& Size:	The size of the file
@param	bool	Random:	Should the file be filled with random chars?
@param	char	CharToFill:	If Random is false, what should the char be filled with? Otherwise set to NULL
*/
[[deprecated ("Old Function, from before the v2.0 rewrite")]]void WriteToFile(int FileNum, std::string FileName, bool MultiThread, unsigned int& SizeMode, std::string Size, bool Random, char CharToFill);