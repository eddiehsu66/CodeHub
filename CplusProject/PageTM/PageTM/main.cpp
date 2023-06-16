#include "MemoryManager.h"
using namespace std;

int main() {
    MemoryManager mm;
    int pid0 = mm.createProcess(0,7906);
    int pid1 = mm.createProcess(1);
    int page = mm.allocatePage();
    mm.allocatePageToProcess(pid1, page);
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    int pid2 = mm.createProcess(2, 10000);
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    mm.killProcess(0);
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    int pid3 = mm.createProcess(3, 10000);
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    int pid4 = mm.createProcess(4, 10000);
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    mm.killProcess(pid3);
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    mm.WakeUpPage(pid2, 4);
    mm.showPageStatus();
    mm.showProcessPageTable();
    mm.showPageQueue();

    return 0;


}