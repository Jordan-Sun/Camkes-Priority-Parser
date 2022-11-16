/*
 *  main.cpp
 *  entry point for the program
 *  author: jordan sun
 */

#include "main.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    // check for correct number of arguments
    if (argc != NUM_ARGS) {
        cout << "Usage: " << argv[PROGRAM_NAME] << " <dag file> <priority file>" << endl;
        return INVALID_ARGS;
    }



    return SUCCESS;
}
