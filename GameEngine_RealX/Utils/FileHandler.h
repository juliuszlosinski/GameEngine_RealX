#ifndef FILEHANDLER_H
#define FILEHANLDER_H

#include <string>
#include <fstream>
#include <iostream>

// Read text from file to string format.
std::string ReadTextFromFile(const std::string& pathToFile);

// Write data (string format) into file.
void WriteTextToFile(const std::string& pathToFile, const std::string& text);

#endif