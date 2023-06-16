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

const int MAX_PAGES = 3;  // ���ҳ��

class MemoryManager {
private:
    Page pages[MAX_PAGES];    // �洢����ҳ��
    int page_number;      //�½���ҳ������
    int num_pages;            // ��ǰ����ʹ�õ�ҳ����
    std::vector<Process> processes; // ���̳�
    myqueue page_queue; // �洢�ѷ����ҳ�����
    std::unordered_map<int, int> page_map;   //ά��һ��ҳ����ź�λ�õĹ�ϵ
    std::vector<int> disk_page;  //�洢�����˴����е�ҳ����ţ�
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

    void saveToDisk(); //���ǽ�������Ϣ�����ڴ�������

    void loadFromDisk();
    void deleteFromDisk(int page_id);
    void saveToDisk(Page page);
    Page loadFromDisk(int page_id);

    void record(bool clear);
};

#endif
