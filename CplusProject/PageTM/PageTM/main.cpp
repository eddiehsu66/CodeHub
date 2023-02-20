#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int PAGE_SIZE = 4096; // ÿҳ��С
const int MAX_PAGES = 100;  // ���ҳ��

// ҳ��ṹ��
struct Page {
    int id;           // ҳ����
    bool free;        // ҳ���Ƿ����
    char data[PAGE_SIZE]; // �洢����
};

// ���̽ṹ��
struct Process {
    int id;                 // ���̱��
    vector<int> page_table; // ҳ��
};

// �洢������
class MemoryManager {
private:
    Page pages[MAX_PAGES];    // �洢����ҳ��
    int num_pages;            // ��ǰҳ����
    vector<Process> processes; // ���н���
    queue<int> page_queue; // �洢�ѷ����ҳ��˳��
public:
    // ��ʼ��
    MemoryManager() {
        num_pages = 0;
    }

    // ����ҳ��
    int allocatePage() {
        for (int i = 0; i < num_pages; i++) {
            if (pages[i].free) {
                pages[i].free = false;
                cout << "����ҳ��ɹ���������" << i << "��ҳ��" << endl;
                page_queue.push(i); // ��ҳ������ӵ�������
                return pages[i].id;
            }
        }
        if (num_pages == MAX_PAGES) {
            return -1; // ҳ���������޷�����
        }
        pages[num_pages].id = num_pages;
        pages[num_pages].free = false;
        page_queue.push(num_pages); // ��ҳ������ӵ�������
        num_pages++;
        return num_pages - 1;
    }

    // �ͷ�ҳ��
    void freePage(int page_id) {
        pages[page_id].free = true;
        cout << "�ͷ���" << page_id << "ҳ��" << endl;
        // �Ӷ�����ɾ�����ͷŵ�ҳ����
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

    // ��������
    int createProcess() {
        Process p;
        p.id = processes.size();
        processes.push_back(p);
        cout << "������" << p.id << "����" << endl;
        return p.id;
    }

    // Ϊ���̷���ҳ��
    void allocatePageToProcess(int process_id, int page_id) {
        if (process_id >= processes.size()) {
            return; // ���̲�����
        }
        Process& p = processes[process_id];
        p.page_table.push_back(page_id);
        cout << "Ϊ" << p.id << "���̷�����" << page_id << "ҳ��" << endl;
    }

    // �ӽ������ͷ�ҳ��
    void freePageFromProcess(int process_id, int page_id) {
        if (process_id >= processes.size()) {
            return; // ���̲�����
        }
        Process& p = processes[process_id];
        auto it = find(p.page_table.begin(), p.page_table.end(), page_id);
        if (it != p.page_table.end()) {
            p.page_table.erase(it);
            cout << "Ϊ" << p.id << "�����ͷ���" << page_id << "ҳ��" << endl;
        }
    }
    void showPageStatus() {//��ʾ����ҳ���״̬
        for (int i = 0; i < num_pages; i++) {
            cout << "ҳ��" << i << "��";
            if (pages[i].free) {
                cout << "����" << endl;
            }
            else {
                cout << "�ѷ���" << endl;
            }
        }
        cout << endl;
    }
    // ��ʾ���н��̵�ҳ��
    void showProcessPageTable() {
        for (int i = 0; i < processes.size(); i++) {
            Process p = processes[i];
            cout << "����" << p.id << "��ҳ��";
            for (int j = 0; j < p.page_table.size(); j++) {
                cout << p.page_table[j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // ��ʾ�ѷ����ҳ��˳��
    void showPageQueue() {
        queue<int> tmp_queue = page_queue;
        cout << "�ѷ����ҳ��˳��";
        while (!tmp_queue.empty()) {
            cout << tmp_queue.front() << " ";
            tmp_queue.pop();
        }
        cout << endl;
    }

    // ���洢��Ϣ�������
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

    // �Ӵ��̶�ȡ�洢��Ϣ
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
    // ������������
    int pid1 = mm.createProcess();
    int pid2 = mm.createProcess();

    // Ϊ���̷���ҳ��
    int page1 = mm.allocatePage();
    mm.allocatePageToProcess(pid1, page1);

    int page2 = mm.allocatePage();
    mm.allocatePageToProcess(pid2, page2);

    int page3 = mm.allocatePage();
    mm.allocatePageToProcess(pid1, page3);

    int page4 = mm.allocatePage();
    mm.allocatePageToProcess(pid2, page4);

    // �ͷ�ҳ��
    mm.freePageFromProcess(pid1, page1);

    int page5 = mm.allocatePage();
    mm.allocatePageToProcess(pid1, page5);

    int page6 = mm.allocatePage();
    mm.allocatePageToProcess(pid2, page6);

    // ��ʾ״̬
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    return 0;
}
