#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int PAGE_SIZE = 4096; // 每页大小
const int MAX_PAGES = 100;  // 最大页数

// 页面结构体
struct Page {
    int id;           // 页面编号
    bool free;        // 页面是否空闲
    char data[PAGE_SIZE]; // 存储数据
};

// 进程结构体
struct Process {
    int id;                 // 进程编号
    vector<int> page_table; // 页表
};

// 存储管理器
class MemoryManager {
private:
    Page pages[MAX_PAGES];    // 存储所有页面
    int num_pages;            // 当前页面数
    vector<Process> processes; // 所有进程
    queue<int> page_queue; // 存储已分配的页面顺序
public:
    // 初始化
    MemoryManager() {
        num_pages = 0;
    }

    // 分配页面
    int allocatePage() {
        for (int i = 0; i < num_pages; i++) {
            if (pages[i].free) {
                pages[i].free = false;
                cout << "分配页面成功，分配了" << i << "号页面" << endl;
                page_queue.push(i); // 将页面编号添加到队列中
                return pages[i].id;
            }
        }
        if (num_pages == MAX_PAGES) {
            return -1; // 页面已满，无法分配
        }
        pages[num_pages].id = num_pages;
        pages[num_pages].free = false;
        page_queue.push(num_pages); // 将页面编号添加到队列中
        num_pages++;
        return num_pages - 1;
    }

    // 释放页面
    void freePage(int page_id) {
        pages[page_id].free = true;
        cout << "释放了" << page_id << "页面" << endl;
        // 从队列中删除已释放的页面编号
        queue<int> new_page_queue;
        while (!page_queue.empty()) {
            int id = page_queue.front();
            page_queue.pop();
            if (id != page_id) {
                new_page_queue.push(id);
            }
        }
        page_queue = new_page_queue;
    }

    // 创建进程
    int createProcess() {
        Process p;
        p.id = processes.size();
        processes.push_back(p);
        cout << "创建了" << p.id << "进程" << endl;
        return p.id;
    }

    // 为进程分配页面
    void allocatePageToProcess(int process_id, int page_id) {
        if (process_id >= processes.size()) {
            return; // 进程不存在
        }
        Process& p = processes[process_id];
        p.page_table.push_back(page_id);
        cout << "为" << p.id << "进程分配了" << page_id << "页面" << endl;
    }

    // 从进程中释放页面
    void freePageFromProcess(int process_id, int page_id) {
        if (process_id >= processes.size()) {
            return; // 进程不存在
        }
        Process& p = processes[process_id];
        auto it = find(p.page_table.begin(), p.page_table.end(), page_id);
        if (it != p.page_table.end()) {
            p.page_table.erase(it);
            cout << "为" << p.id << "进程释放了" << page_id << "页面" << endl;
        }
    }
    void showPageStatus() {//显示所有页面的状态
        for (int i = 0; i < num_pages; i++) {
            cout << "页面" << i << "：";
            if (pages[i].free) {
                cout << "空闲" << endl;
            }
            else {
                cout << "已分配" << endl;
            }
        }
        cout << endl;
    }
    // 显示所有进程的页表
    void showProcessPageTable() {
        for (int i = 0; i < processes.size(); i++) {
            Process p = processes[i];
            cout << "进程" << p.id << "的页表：";
            for (int j = 0; j < p.page_table.size(); j++) {
                cout << p.page_table[j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // 显示已分配的页面顺序
    void showPageQueue() {
        queue<int> tmp_queue = page_queue;
        cout << "已分配的页面顺序：";
        while (!tmp_queue.empty()) {
            cout << tmp_queue.front() << " ";
            tmp_queue.pop();
        }
        cout << endl;
    }

    // 将存储信息存入磁盘
    void saveToFile(string filename) {
        ofstream file(filename, ios::out | ios::binary);
        file.write((char*)&num_pages, sizeof(num_pages));
        file.write((char*)pages, sizeof(Page) * num_pages);
        int num_processes = processes.size();
        file.write((char*)&num_processes, sizeof(num_processes));
        for (int i = 0; i < num_processes; i++) {
            Process p = processes[i];
            int num_pages = p.page_table.size();
            file.write((char*)&p.id, sizeof(p.id));
            file.write((char*)&num_pages, sizeof(num_pages));
            for (int j = 0; j < num_pages; j++) {
                int page_id = p.page_table[j];
                file.write((char*)&page_id, sizeof(page_id));
            }
        }
        file.close();
    }

    // 从磁盘读取存储信息
    void loadFromFile(string filename) {
        ifstream file(filename, ios::in | ios::binary);
        file.read((char*)&num_pages, sizeof(num_pages));
        file.read((char*)pages, sizeof(Page) * num_pages);
        int num_processes;
        file.read((char*)&num_processes, sizeof(num_processes));
        processes.clear();
        for (int i = 0; i < num_processes; i++) {
            Process p;
            int num_pages;
            file.read((char*)&p.id, sizeof(p.id));
            file.read((char*)&num_pages, sizeof(num_pages));
            for (int j = 0; j < num_pages; j++) {
                int page_id;
                file.read((char*)&page_id, sizeof(page_id));
                p.page_table.push_back(page_id);
            }
            processes.push_back(p);
        }
        file.close();
    }
};
int main() {
    MemoryManager mm;
    // 创建两个进程
    int pid1 = mm.createProcess();
    int pid2 = mm.createProcess();

    // 为进程分配页面
    int page1 = mm.allocatePage();
    mm.allocatePageToProcess(pid1, page1);

    int page2 = mm.allocatePage();
    mm.allocatePageToProcess(pid2, page2);

    int page3 = mm.allocatePage();
    mm.allocatePageToProcess(pid1, page3);

    int page4 = mm.allocatePage();
    mm.allocatePageToProcess(pid2, page4);

    // 释放页面
    mm.freePageFromProcess(pid1, page1);

    int page5 = mm.allocatePage();
    mm.allocatePageToProcess(pid1, page5);

    int page6 = mm.allocatePage();
    mm.allocatePageToProcess(pid2, page6);

    // 显示状态
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    return 0;
}
