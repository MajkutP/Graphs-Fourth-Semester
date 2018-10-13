#ifndef UserChoiceHandlers_h
#define UserChoiceHandlers_h

#include "SimpleGraph.h"

/// This function displays all possible choices user can make
/// at the begining of a program. There are 6 exercises. Function
/// gets user choice and returns it.  
int GetExerciseChoiceFromUser();

/// This function gets user choice about the way graph will
/// be loaded to program. There are two options - from file or
/// using graphic sequences.
int ChooseGraphInputType();

SimpleGraph* GetGraphFromUser();

void FirstAndSecondOption(int userChoice);

#endif