//
// Created by rozanecm on 5/6/20.
//

#ifndef CONCUBREAD_DEBUGPRINT_H
#define CONCUBREAD_DEBUGPRINT_H


#include <string>
#include <fstream>

class DebugPrint {
public:
    DebugPrint();
    ~DebugPrint();
    void print(const std::string&);

private:
    std::ofstream debug_file;
};


#endif //CONCUBREAD_DEBUGPRINT_H
