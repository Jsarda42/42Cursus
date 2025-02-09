#pragma once

#include "Lib.hpp"
#include "ParsedData.hpp"

#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include <sys/types.h>
#include <cerrno>

class Php
{
private:
	std::map<std::string, std::string> env_;

public:
    Php();
    ~Php();
        
    void createEnv(ParsedData &parsedData, std::string &filePath);
    char **getEnv();
    std::string askPhp();
};


