#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include <vector>

struct Process {
    int id;                 // ½ø³Ì±àºÅ
    int size;
    std::vector<int> page_table; // Ò³±í
};

#endif
#pragma once
