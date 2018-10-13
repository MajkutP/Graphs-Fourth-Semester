#include <vector> /// std::vector
#include <sstream> /// std::stringstream
#include "Input.h"
#include "GraphStorage.h"


void Input::OpenFile()
{
    m_inputFile.open(m_fileName.toStdString().c_str());
}

std::ifstream& Input::GetFile() 
{
	return m_inputFile;
}

bool Input::GetInputFromFile(GraphStorage& storage)
{
	char fileType;
	m_inputFile >> fileType;

    if (fileType != 'l' and fileType != 'i' and fileType != 'a') /// check format
		return false;

	std::vector<std::vector<int>> input;
    std::string lineFromFile;

    /// Ignore empty lines in file
    getline(m_inputFile, lineFromFile);
    getline(m_inputFile, lineFromFile);
	
    int lineNumber = 0; /// Line counter
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

