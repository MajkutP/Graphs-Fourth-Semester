#ifndef Input_h
#define Input_h

#include <fstream> /// file handling
#include <QString> /// string handling (Qt)
#include "GraphStorage.h"


class Input 
{
public:
    /// Basic constructor - it sets name of file
    Input(QString& name):
        m_fileName (name) {}

    /// This function only opens file
	void OpenFile();

	/// Parser that gets input from file and saves it 
	/// If file has a proper format it returns true
	/// Otherwise it returns false
	bool GetInputFromFile(GraphStorage& storage);

	/// Getter that returns stored file 
	std::ifstream& GetFile();

private:
	/// This field operates on given input file
	std::ifstream m_inputFile;

	/// This filed stores 
    QString m_fileName;

};

#endif
