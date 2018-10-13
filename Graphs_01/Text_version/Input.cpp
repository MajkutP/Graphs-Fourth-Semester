#include "Input.h"
#include "GraphStorage.h"
#include <iostream>
#include <vector>
#include <sstream>

Input::Input():
	m_fileName ("") {}



void Input::OpenFile()
{
	do 
	{
		GetFileNameFromUser();
		m_inputFile.open(m_fileName.c_str());
		if (!CheckIfFileExists())
			std::cout<<"Wrong file name. Try again."<<std::endl;
		else break;

	} while (true);


}


std::string Input::GetFileName() const
{
	return m_fileName;
}

std::ifstream& Input::GetFile() 
{
	return m_inputFile;
}


void Input::GetFileNameFromUser()
{
	std::cout<<"Please enter a proper name of a file with a graph representation: ";
	std::cin>>m_fileName;
}


bool Input::CheckIfFileExists()
{
	if (!m_inputFile.is_open())
		return false;
	return true;
}



bool Input::GetInputFromFile(GraphStorage& storage)
{
	char fileType;
	m_inputFile >> fileType;
	std::cout<<fileType<<std::endl;
	
	if (fileType != 'l' and fileType != 'i' and fileType != 'a') /// check format
		return false;

	std::vector<std::vector<int>> input;
	std::string lineFromFile = "";

	/// ignore empty lines in file
	getline(m_inputFile, lineFromFile);
	getline(m_inputFile, lineFromFile);
	
	int lineNumber = 0; /// line counter
	while (std::getline(m_inputFile, lineFromFile))
	{
		if (lineFromFile=="" or lineFromFile=="\n") /// check if file has ended
			break;

		input.emplace_back();

		std::stringstream stream(lineFromFile);
		while (true) /// read values from line
		{
			int value;
			stream>>value;
			if(!stream)
      			break;
      		input.at(lineNumber).push_back(value); /// add values to vector
		}
		lineNumber++; /// increase line counter
	}

	storage.AddGraphToStorage(input, fileType);
	m_inputFile.close();

	return true; /// everything was correct
	
}

