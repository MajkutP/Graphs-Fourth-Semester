#include "OutputToFileHandler.h"
#include <fstream>

void SaveGraphToFile(SimpleGraph& toSave, std::string fileName)
{
	std::ofstream outputFile;
	outputFile.open(fileName);

	toSave.ChangeToAdjacencyMatrix();
	outputFile<<toSave.GetRepresentation()<<std::endl<<std::endl;
	
	toSave.PrintGraph(outputFile);
	outputFile.close();
}

