#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include <vector>

struct Process {
    int id;                 // ���̱��
    int size;
    std::vector<int> page_table; // ҳ��
};

#endif
#pragma once
