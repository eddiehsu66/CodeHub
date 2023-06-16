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
    //����˵����˳�����һ��num_pages���ҵ�δ�����ҳ��
    for (int i = 0; i < num_pages; i++) {
        if (pages[i].free) {
            pages[i].free = false;
            /*ss << "����ҳ��ɹ���������" << i << "��ҳ��" << endl;*/
            page_queue.push(i); // ��ҳ������ӵ�������
            page_map[i] = i;
            return pages[i].id;
        }
    }
    if (num_pages == MAX_PAGES) {
        ss << " ҳ������������LRU�㷨�����û�" << endl;
        int swap_page = page_queue.front();
        int position = page_map[swap_page];
        page_queue.pop();
        // ��������ӡ��ϣ���е����м�ֵ��
        /*for (const auto& pair : page_map) {
            std::ss << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }*/
        saveToDisk(pages[position]);
        ss <<"���� "<<position<<"��λ�õ�" << swap_page << "ҳ�����ᱻ�û���������" << endl;
        Page new_page;
        new_page.id = page_number;
        new_page.free = false;
        new_page.inMemory = true;

        pages[position] = new_page;
        page_map[new_page.id] = position;

        page_queue.push(new_page.id);
        page_number++;
        ss << "����һ���µ�ҳ��" << new_page.id << endl;
        return new_page.id;
    }
    pages[num_pages].id = page_number;
    pages[num_pages].free = false;
    page_queue.push(pages[num_pages].id); // ��ҳ������ӵ�������
    /*ss << "����ҳ��ɹ���������" << num_pages << "��ҳ��" << endl;*/
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
        ss << "�ͷ���" << page_id << "ҳ��" << endl;
        // �Ӷ�����ɾ�����ͷŵ�ҳ����
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
        ss << "��ҳ��û�г�ʼ��" << endl;
        return;
    }
}

int MemoryManager::createProcess(int process_id) {
    // �����̴�Сδ֪���ֶ�������߸�����Ҫ������ҳ��
    Process p;
    p.id = process_id;
    processes.push_back(p);
    ss << "������" << p.id << "����" << endl;
    return p.id;
}

int MemoryManager::createProcess(int process_id,int size) {
    // �����̴�С��֪���Զ�����ҳ��
    auto it = std::find_if(processes.begin(), processes.end(), [process_id](const Process& p) {
        return p.id == process_id;
        });
    if (it == processes.end()) {
        int page_num = ceil(size / PAGE_SIZE);
        if (page_num >= MAX_PAGES) {
            ss << "���̵Ĵ�С����," << process_id << "���̴���ʧ��" << endl;
            exit(0);
            return -1;
        }
        Process p;
        p.id = process_id;
        p.size = size;
        processes.push_back(p);
        ss << "������" << p.id << "����" << endl;
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
        ss << "����" << p.id << "�������" << endl;
        return p.id;
    }
    else {
        ss << "������ؽ��̣�����ʧ��" << endl;
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
        ss << "Ϊ" << process_id << "���̷�����" << page_id << "ҳ��" << endl;
    }
    else {
        ss << "����" << process_id << "������" << endl;
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
                ss << "���� " << page_map[swap_page] << "��λ�õ�" << swap_page << "ҳ�����ᱻ�û���������" << endl;
                Page new_page = loadFromDisk(page_id);
                page_queue.push(new_page.id);
                page_map[new_page.id] = page_queue.size() - 1;
                ss << "�������е�" << new_page.id << "��ҳ��ת�ƽ��ڴ�����" << endl;
            }
        }
        else {
            ss << "ҳ��" << page_id << "�����ڽ���"<<process_id <<endl;
            return;
        }
    }
    else {
        ss << "����" << process_id << "������" << endl;
        return;
    }
}

void MemoryManager::killProcess(int process_id) {
    if (process_id >= processes.size()) {
        ss << "��" << process_id << "����" << endl;
        return;
    }
    int index = 0;
    for (Process &p : processes) {
        if (p.id == process_id) {
            Process temp = p;
            processes.erase(processes.begin() + index);
            ss << "ɱ��" << temp.id << "����" << endl;
            for (int i : temp.page_table) {
                /*pages[i].free = true;
                ss << "Ϊ" << temp.id << "�����ͷ���" << i << "ҳ��" << endl;*/
                freePage(i);
            }
        }
        index++;
    }
}
void MemoryManager::freePageFromProcess(int process_id, int page_id) {
    if (process_id >= processes.size()) {
        return; // ���̲�����
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
        ss << "ҳ��" << i << "��";
        if (pages[i].free) {
            ss << "����" << endl;
        }
        else {
            ss << "�ѷ���" << endl;
        }
    }
    ss << endl;
}

void MemoryManager::showProcessPageTable() {
    for (Process p : processes) {
        ss << "����" << p.id << "��ҳ��:";
        for (int i : p.page_table) {
            ss << i << " ";
        }
        ss << endl;
    }
    ss << endl;
}

void MemoryManager::showPageQueue() {
    myqueue tmp_queue = page_queue;
    ss << "�ѷ����ҳ��˳��";
    while (!tmp_queue.empty()) {
        ss << tmp_queue.front() << " ";
        tmp_queue.pop();
    }
    ss << endl;
}

void MemoryManager::saveToDisk() {
    //snapshot����Ե������쳣��ʱ�򽫵�ǰ״̬ת��������
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
        ss << "�ļ���ʧ��" << endl;
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
        ss << "�ļ���ʧ��" << endl;
    }
    page.inMemory = true;
    return page;
}

void MemoryManager::deleteFromDisk(int page_id) {
    std::streamoff offset = page_id * sizeof(Page);

    std::fstream file("disk.bin", std::ios::binary | std::ios::in | std::ios::out);

    if (file.is_open()) {
        file.seekp(offset);

        // ����һ����Ч��ҳ��
        Page invalidPage;
        invalidPage.id = -1;
        invalidPage.free = true;
        invalidPage.inMemory = false;
        std::fill(std::begin(invalidPage.data), std::end(invalidPage.data), '\0');

        // ����Чҳ��д���ļ��У��滻Ҫɾ����ҳ����Ϣ
        file.write(reinterpret_cast<const char*>(&invalidPage), sizeof(Page));

        file.close();
    }
    else {
        ss << "�ļ���ʧ��" << endl;
    }
}



void MemoryManager::loadFromDisk() {
    //snapshot�ָ����Ӵ����лָ�
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



