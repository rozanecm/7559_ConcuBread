//
// Created by rozanecm on 5/6/20.
//

#include <iostream>
#include "DebugPrint.h"

#define DEBUG_FILE_PATH "../log_info.log"

DebugPrint::DebugPrint(){
    debug_file.open(DEBUG_FILE_PATH, std::ios::out | std::ios::trunc);
}

DebugPrint::~DebugPrint(){
    debug_file.close();
}

void DebugPrint::print(const std::string& msg) {
    debug_file << msg << std::flush;
}
