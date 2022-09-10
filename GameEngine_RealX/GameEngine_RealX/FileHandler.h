#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef FSTREAM_H
#define FSTREAM_H
#include <fstream>
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

// Read text from file to string format.
std::string ReadTextFromFile(const std::string& pathToFile);

// Write data (string format) into file.
void WriteTextToFile(const std::string& pathToFile, const std::string& text);