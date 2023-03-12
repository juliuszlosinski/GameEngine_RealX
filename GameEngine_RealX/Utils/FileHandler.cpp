#include "FileHandler.h"

// Read text from file to string format.
std::string ReadTextFromFile(const std::string& pathToFile) {
	std::string currentLine, allLines;
	std::fstream file(pathToFile);
	if (file.is_open()) {
		while (std::getline(file, currentLine)) {
			allLines += currentLine + "\n";
		}
		file.close();
		return allLines;
	}
	else {
		std::cout << "Unable to open file with path: " << pathToFile << std::endl;
		return std::string();
	}
}

// Write data (string format) into file.
void WriteTextToFile(const std::string& pathToFile, const std::string& text) {
	std::ofstream file(pathToFile);
	if (file.is_open()) {
		file << text;
		file << "\n";
		file.close();
	}
	else {
		std::cout << "Unable to open file with path: " << pathToFile << std::endl;
	}
}

