#include "Output.h"
#include <iostream>
#include <cstdlib>
#include <QFileDialog>

void Output::SaveToFile(GraphStorage& toSave)
{
    m_outputFile.open(m_fileName.toStdString());
    m_outputFile<<toSave->GetRepresentation()<<std::endl<<std::endl;
    for (unsigned i = 0; i < toSave->getNumberOfVertices(); ++i)
    {
        for (unsigned j = 0; j < toSave->GetRepresentationVector().at(i).size(); ++j)
            m_outputFile<<toSave->GetRepresentationVector().at(i).at(j)<<" ";
        m_outputFile<<std::endl;
    }
	m_outputFile.close();
}

QString Output::GetFileName() const
{
    return m_fileName;
}
