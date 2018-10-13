#ifndef OutputToFileHandler_h
#define OutputToFileHandler_h

#include <string>
#include "SimpleGraph.h"

/// This function saves graph to text file. It always uses adjacency matrix representation
/// Because of that, if graph is represented in any other way, proper conversion
/// function is called. 
void SaveGraphToFile(SimpleGraph& toSave, std::string fileName);

#endif