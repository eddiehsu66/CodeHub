#pragma once
#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include <String>
#include <unordered_map>
#include <sstream>
#include "Page.h"
#include "Process.h"
#include "myqueue.h"

const int MAX_PAGES = 3;  // 最大页数

class MemoryManager {
private:
    Page pages[MAX_PAGES];    // 存储所有页面
    int page_number;      //新建的页面的序号
    int num_pages;            // 当前正在使用的页面数
    std::vector<Process> processes; // 进程池
    myqueue page_queue; // 存储已分配的页面队列
    std::unordered_map<int, int> page_map;   //维护一个页面序号和位置的关系
    std::vector<int> disk_page;  //存储放入了磁盘中的页面序号；
    std::stringstream ss;
public:
    MemoryManager();
    ~MemoryManager();

    int allocatePage();

    void freePage(int page_id);

    int createProcess(int process_id);
    int createProcess(int process_id, int size);

    void allocatePageToProcess(int process_id, int page_id);

    void WakeUpPage(int process_id, int page_id);

    void killProcess(int process_id);

    void freePageFromProcess(int process_id, int page_id);

    //int virtualToPhysical(int process_id, int virtual_address);

    void showPageStatus();

    void showProcessPageTable();

    void showPageQueue();

    void saveToDisk(); //其是将所有信息保存在磁盘中了

    void loadFromDisk();
    void deleteFromDisk(int page_id);
    void saveToDisk(Page page);
    Page loadFromDisk(int page_id);

    void record(bool clear);
};

#endif
