/*
 *  main.h
 *  enumerations and constants for the program
 *  author: jordan sun
 */
#pragma once

// constants
// enumeration for argument indices and expected number of arguments
enum args
{
    PROGRAM_NAME,
    DAG_FILE,
    PRIORITY_FILE,
    NUM_ARGS
};

// enumeration for return values
enum return_codes
{
    SUCCESS,
    INVALID_ARGS,
    FAILED_TO_OPEN_FILE
};

// enumeration for dag parser states
enum dag_parser_states
{
    START,
    NODE,
    EDGE,
    END
};