#ifndef FileInput_h
#define FileInput_h

#include <fstream> // file handling
#include <string> // string handling

#include "SimpleGraph.h"

class FileInput
{
public:
	/// This function gets file name from user and checks if file exists
	/// If file does not exists (opened file is empty), then it asks user to try again
	void OpenFile();

	/// Parser that gets input from file and saves it 
	/// If file has a proper format it returns true
	/// Otherwise it returns false
	SimpleGraph* GetInputFromFile();

private:
	/// Function that asks user to enter name of file that stores graph representation
	/// It saves the name in class field m_fileName
	void GetFileNameFromUser();

	/// Function that checks if file with name provided by user exists
	/// It returns true if it does, and false if it does not 
	bool CheckIfFileExists();

	/// This field operates on given input file
	std::ifstream m_inputFile;

	/// This filed stores 
	std::string m_fileName;

};

SimpleGraph* GetGraphFromUser();

#endif