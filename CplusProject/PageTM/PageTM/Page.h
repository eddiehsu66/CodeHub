#pragma once
#ifndef PAGE_H
#define PAGE_H

const int PAGE_SIZE = 4096; // ÿҳ��С

struct Page {
    int id;           // ҳ����
    bool free;        // ҳ���Ƿ����
    bool inMemory;    //���Ƿ����ڴ���
    char data[PAGE_SIZE]; // �洢����
    int position;      //��¼����pages�е�λ��
};

#endif
