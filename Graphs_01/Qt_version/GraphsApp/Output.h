#ifndef Output_h
#define Output_h

#include <fstream> /// file handling
#include <QString> /// string handling (Qt)
#include "GraphStorage.h"

class Output 
{
public:
	/// Basic constructor of Output object
    Output(QString fileName):
        m_fileName(fileName) {}

	/// Function that saves current graph representation to file
	void SaveToFile(GraphStorage& toSave);

    /// Simple getter for output file name
    QString GetFileName() const;

private:
	/// Field storing name of output file
    QString m_fileName;

	/// Field for storing output file data
	std::ofstream m_outputFile;
};

#endif
