#pragma once
#ifndef PAGE_H
#define PAGE_H

const int PAGE_SIZE = 4096; // 每页大小

struct Page {
    int id;           // 页面编号
    bool free;        // 页面是否空闲
    bool inMemory;    //其是否在内存中
    char data[PAGE_SIZE]; // 存储数据
    int position;      //记录其在pages中的位置
};

#endif
