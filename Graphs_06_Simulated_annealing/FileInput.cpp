#include "FileInput.h"
#include <iostream>
#include <vector>
#include <sstream>

void FileInput::OpenFile()
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


void FileInput::GetFileNameFromUser()
{
	std::cout<<"Please enter a proper name of a file with a graph representation: ";
	std::cin>>m_fileName;
}


bool FileInput::CheckIfFileExists()
{
	if (!m_inputFile.is_open())
		return false;
	return true;
}


SimpleGraph* FileInput::GetInputFromFile()
{
	char fileType;
	m_inputFile >> fileType;
	if (fileType != 'w')
		return nullptr;
	
	std::vector<std::vector<int>> input;
	std::string lineFromFile = "";

	for (int i=0; i<2; ++i)
		getline(m_inputFile, lineFromFile);
	
	int lineNumber = 0;
	while (std::getline(m_inputFile, lineFromFile))
	{
		if (lineFromFile=="" or lineFromFile=="\n")
			break;

		input.emplace_back();

		std::stringstream stream(lineFromFile);
		while (true)
		{
			int value;
			stream>>value;
			if(!stream)
      			break;
      		input.at(lineNumber).push_back(value);
		}

		lineNumber++;
		
	}
	m_inputFile.close();

	return new SimpleGraph(input);
	
}


SimpleGraph* GetGraphFromUser()
{
	SimpleGraph* graph = nullptr;

	FileInput graphGetter;
	graphGetter.OpenFile();
	graph = graphGetter.GetInputFromFile();

	return graph;
}