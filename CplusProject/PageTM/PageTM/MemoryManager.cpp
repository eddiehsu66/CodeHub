#include "MemoryManager.h"
using namespace std;

MemoryManager::MemoryManager() {
    num_pages = 0;
    page_number = 0;
}
MemoryManager::~MemoryManager() {
    record(true);
    std::ofstream outputFile("disk.bin", std::ios::binary);
    outputFile.close();
}
int MemoryManager::allocatePage() {
    //简单来说就是顺序遍历一下num_pages，找到未分配的页面
    for (int i = 0; i < num_pages; i++) {
        if (pages[i].free) {
            pages[i].free = false;
            /*ss << "分配页面成功，分配了" << i << "号页面" << endl;*/
            page_queue.push(i); // 将页面编号添加到队列中
            page_map[i] = i;
            return pages[i].id;
        }
    }
    if (num_pages == MAX_PAGES) {
        ss << " 页面已满，根据LRU算法进行置换" << endl;
        int swap_page = page_queue.front();
        int position = page_map[swap_page];
        page_queue.pop();
        // 遍历并打印哈希表中的所有键值对
        /*for (const auto& pair : page_map) {
            std::ss << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }*/
        saveToDisk(pages[position]);
        ss <<"处于 "<<position<<"号位置的" << swap_page << "页表，将会被置换到磁盘中" << endl;
        Page new_page;
        new_page.id = page_number;
        new_page.free = false;
        new_page.inMemory = true;

        pages[position] = new_page;
        page_map[new_page.id] = position;

        page_queue.push(new_page.id);
        page_number++;
        ss << "调入一个新的页表" << new_page.id << endl;
        return new_page.id;
    }
    pages[num_pages].id = page_number;
    pages[num_pages].free = false;
    page_queue.push(pages[num_pages].id); // 将页面编号添加到队列中
    /*ss << "分配页面成功，分配了" << num_pages << "号页面" << endl;*/
    page_map[page_number] = page_number;
    num_pages++;
    page_number++;
    return num_pages - 1;
}

void MemoryManager::freePage(int page_id) {
    auto it = std::find(disk_page.begin(),disk_page.end(),page_id);
    if (it != disk_page.end()) {
        deleteFromDisk(page_id);
    }
    else if (page_queue.find(page_id)) {
        pages[page_id].free = true;
        ss << "释放了" << page_id << "页面" << endl;
        // 从队列中删除已释放的页面编号
        myqueue new_page_queue;
        while (!page_queue.empty()) {
            int id = page_queue.front();
            page_queue.pop();
            if (id != page_id) {
                new_page_queue.push(id);
            }
        }
        page_queue = new_page_queue;
    }
    else {
        ss << "该页面没有初始化" << endl;
        return;
    }
}

int MemoryManager::createProcess(int process_id) {
    // 当进程大小未知，手动分配或者根据需要来分配页面
    Process p;
    p.id = process_id;
    processes.push_back(p);
    ss << "创建了" << p.id << "进程" << endl;
    return p.id;
}

int MemoryManager::createProcess(int process_id,int size) {
    // 当进程大小已知，自动分配页面
    auto it = std::find_if(processes.begin(), processes.end(), [process_id](const Process& p) {
        return p.id == process_id;
        });
    if (it == processes.end()) {
        int page_num = ceil(size / PAGE_SIZE);
        if (page_num >= MAX_PAGES) {
            ss << "进程的大小过大," << process_id << "进程创建失败" << endl;
            exit(0);
            return -1;
        }
        Process p;
        p.id = process_id;
        p.size = size;
        processes.push_back(p);
        ss << "创建了" << p.id << "进程" << endl;
        for (int i = 0; i <= page_num; i++) {
            int page_id = allocatePage();
            allocatePageToProcess(p.id, page_id);
        }
        /*ss << "******************" << endl;
        Page test0 = loadFromDisk(0);
        ss << test0.id << endl;
        Page test1 = loadFromDisk(1);
        ss << test1.id << endl;
        Page test2 = loadFromDisk(2);
        ss << test2.id << endl;
        Page test3 = loadFromDisk(3);
        ss << test3.id << endl;
        Page test4 = loadFromDisk(4);
        ss << test4.id << endl;
        Page test5 = loadFromDisk(5);
        ss << test5.id << endl;
        Page test6 = loadFromDisk(6);
        ss << test6.id << endl;
        Page test7 = loadFromDisk(7);
        ss << test7.id << endl;
        Page test8 = loadFromDisk(8);
        ss << test8.id << endl;
        Page test9 = loadFromDisk(9);
        ss << test9.id << endl;
        Page test10 = loadFromDisk(10);
        ss << test10.id << endl;
        ss << "******************" << endl;*/
        ss << "进程" << p.id << "创建完毕" << endl;
        return p.id;
    }
    else {
        ss << "已有相关进程，创建失败" << endl;
        exit(0);
        return -1;
    }
}

void MemoryManager::allocatePageToProcess(int process_id, int page_id) {
    auto it = std::find_if(processes.begin(), processes.end(), [process_id](const Process& p) {
        return p.id == process_id;
        });
    if (it != processes.end()) {
        it->page_table.push_back(page_id);
        ss << "为" << process_id << "进程分配了" << page_id << "页面" << endl;
    }
    else {
        ss << "进程" << process_id << "不存在" << endl;
        return;
    }
}
void MemoryManager::WakeUpPage(int process_id, int page_id) {
    auto it = std::find_if(processes.begin(), processes.end(), [process_id](const Process& p) {
        return p.id == process_id;
        });
    if (it != processes.end()) {
        auto it2 = std::find(it->page_table.begin(), it->page_table.end(), page_id);

        if (it2 != it->page_table.end()) {
            if (page_queue.find(page_id)) {
                page_queue.used(page_id);
            }
            else {
                int swap_page = page_queue.front();
                page_queue.pop();
                saveToDisk(pages[page_map[swap_page]]);
                ss << "处于 " << page_map[swap_page] << "号位置的" << swap_page << "页表，将会被置换到磁盘中" << endl;
                Page new_page = loadFromDisk(page_id);
                page_queue.push(new_page.id);
                page_map[new_page.id] = page_queue.size() - 1;
                ss << "将磁盘中的" << new_page.id << "号页表转移进内存中来" << endl;
            }
        }
        else {
            ss << "页表" << page_id << "不属于进程"<<process_id <<endl;
            return;
        }
    }
    else {
        ss << "进程" << process_id << "不存在" << endl;
        return;
    }
}

void MemoryManager::killProcess(int process_id) {
    if (process_id >= processes.size()) {
        ss << "无" << process_id << "进程" << endl;
        return;
    }
    int index = 0;
    for (Process &p : processes) {
        if (p.id == process_id) {
            Process temp = p;
            processes.erase(processes.begin() + index);
            ss << "杀死" << temp.id << "进程" << endl;
            for (int i : temp.page_table) {
                /*pages[i].free = true;
                ss << "为" << temp.id << "进程释放了" << i << "页面" << endl;*/
                freePage(i);
            }
        }
        index++;
    }
}
void MemoryManager::freePageFromProcess(int process_id, int page_id) {
    if (process_id >= processes.size()) {
        return; // 进程不存在
    }
    Process& p = processes[process_id];
    auto it = find(p.page_table.begin(), p.page_table.end(), page_id);
    if (it != p.page_table.end()) {
        p.page_table.erase(it);
        freePage(page_id);
    }
}

void MemoryManager::showPageStatus() {
    for (int i = 0; i < num_pages; i++) {
        ss << "页面" << i << "：";
        if (pages[i].free) {
            ss << "空闲" << endl;
        }
        else {
            ss << "已分配" << endl;
        }
    }
    ss << endl;
}

void MemoryManager::showProcessPageTable() {
    for (Process p : processes) {
        ss << "进程" << p.id << "的页表:";
        for (int i : p.page_table) {
            ss << i << " ";
        }
        ss << endl;
    }
    ss << endl;
}

void MemoryManager::showPageQueue() {
    myqueue tmp_queue = page_queue;
    ss << "已分配的页面顺序：";
    while (!tmp_queue.empty()) {
        ss << tmp_queue.front() << " ";
        tmp_queue.pop();
    }
    ss << endl;
}

void MemoryManager::saveToDisk() {
    //snapshot，针对当发生异常的时候将当前状态转储到磁盘
    ofstream file("snapshot.bin", ios::out | ios::binary);
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
void MemoryManager::saveToDisk(Page page) {
    std::streamoff offset = page.id * sizeof(Page);

    std::ofstream outputFile("disk.bin", std::ios::binary | std::ios::in);
    this->disk_page.push_back(page.id);
    if (outputFile.is_open()) {
        outputFile.seekp(offset,std::ios_base::beg);
        page.inMemory = false;
        outputFile.write(reinterpret_cast<const char*>(&page), sizeof(Page));

        outputFile.close();
    }
    else {
        ss << "文件打开失败" << endl;
    }
}



Page MemoryManager::loadFromDisk(int page_id) {
    Page page;
    this->disk_page.erase(std::remove(disk_page.begin(), disk_page.end(), page_id), disk_page.end());
    std::streamoff offset = page_id * sizeof(Page);

    std::ifstream inputFile("disk.bin", std::ios::binary | std::ios::out);

    if (inputFile.is_open()) {
        inputFile.seekg(offset, std::ios_base::beg);

        inputFile.read(reinterpret_cast<char*>(&page), sizeof(Page));

        inputFile.close();
    }
    else {
        ss << "文件打开失败" << endl;
    }
    page.inMemory = true;
    return page;
}

void MemoryManager::deleteFromDisk(int page_id) {
    std::streamoff offset = page_id * sizeof(Page);

    std::fstream file("disk.bin", std::ios::binary | std::ios::in | std::ios::out);

    if (file.is_open()) {
        file.seekp(offset);

        // 创建一个无效的页面
        Page invalidPage;
        invalidPage.id = -1;
        invalidPage.free = true;
        invalidPage.inMemory = false;
        std::fill(std::begin(invalidPage.data), std::end(invalidPage.data), '\0');

        // 将无效页面写入文件中，替换要删除的页面信息
        file.write(reinterpret_cast<const char*>(&invalidPage), sizeof(Page));

        file.close();
    }
    else {
        ss << "文件打开失败" << endl;
    }
}



void MemoryManager::loadFromDisk() {
    //snapshot恢复，从磁盘中恢复
    ifstream file("snapshot.bin", std::ios::binary | std::ios::in | std::ios::out);
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

void MemoryManager::record(bool clear) {
    if (clear) {
        std::ofstream file("ptm.log", std::ios::trunc);
        file.close();
    }
    std::ofstream file("ptm.log", std::ios::app);
    std::string log = ss.str(); 
    file << log;
    ss.str("");

    file.close();
}



