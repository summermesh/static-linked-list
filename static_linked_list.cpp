#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 11
typedef struct {
    string data;
    int cur; // 游标
}Component, staticLinkList[MAXSIZE];
void initList(staticLinkList &L);
void printList(const staticLinkList &L);
int getListLength(const staticLinkList &L);
bool insertElem(staticLinkList &L, int location, const string str);
bool deleteElem(staticLinkList &L, int location, string &str);
int main() {
    // 初始化静态链表
    staticLinkList L;
    initList(L);
    // 打印静态链表
    printList(L);
    // 插值
    int location = 3;
    string str = "test";
    if (!insertElem(L, location, str)) {
        cout << "insert element error" << endl;
    } else {
        cout << "insert " + str << " located at " << location << " success" << endl;
    }
    printList(L);
    // 删除
    location = 7;
    if (!deleteElem(L, location, str)) {
        cout << "delete node failed" << endl;
    } else {
        cout << "delete location at" << location << " success, string is " + str << endl;
    }
    printList(L);
    system("pause");
    return 0;
}
void initList(staticLinkList &L) {
    // 按照以下形式初始化 MAXSIZE = 11
    /* ZHAO QIAN SUN LI ZHOU WU
    i    data     cur
    0     ""       2   // 备用链表的头结点 cur是第一个备用链表索引
    1   "ZHAO"     5
    2              4
    3    "LI"      7
    4              8
    5   "QIAN"     9
    6    "WU"      0
    7   "ZHOU"     6
    8              0
    9   "SUN"      3
    10             1   // 数据链表的头结点，cur存储的是第一个元素的索引
    */
    L[0].cur = 2;
    L[1].data = "ZHAO";L[1].cur = 5;
    L[2].cur = 4;
    L[3].data = "LI";L[3].cur = 7;
    L[4].cur = 8;
    L[5].data = "QIAN";L[5].cur = 9;
    L[6].data = "WU";L[6].cur = 0;
    L[7].data = "ZHOU";L[7].cur = 6;
    L[8].cur = 0;
    L[9].data = "SUN";L[9].cur = 3;
    L[10].cur = 1;
}
void printList(const staticLinkList &L) {
    int cur = L[MAXSIZE - 1].cur; // 数据头结点的游标
    while (cur != 0) {
        // 根据游标，获取data
        cout << L[cur].data << " ";
        cur = L[cur].cur;
    }
    cout << endl;
}
int getListLength(const staticLinkList &L) {
    int nodeCount = 0;
    int cur = L[MAXSIZE - 1].cur;
    while (cur != 0) {
        // 根据游标，获取data
        nodeCount++;
        cur = L[cur].cur;
    }
    return nodeCount;
}
bool insertElem(staticLinkList &L, int location, const string str) {
    if (location<1 || location > getListLength(L) + 1 || location > MAXSIZE) {
        return false;
    }
    // 首先根据备用链表处的游标，找到备用链表的第一个结点
    // 将数据放入到该节点，并且将该结点原来的游标赋值给头结点
    // 下一步是修改该节点逻辑上的上一个结点的游标，并将原游标赋给插入的结点
    int insertIndex = L[0].cur; // insertIndex是插入结点的索引
    L[insertIndex].data = str;
    L[0].cur = L[insertIndex].cur;

    // 寻找第location - 1个结点
    int temp = MAXSIZE - 1; // 获取第一个数据结点索引
    int count = location - 1;
    while (count > 0) {
        // 根据游标，获取data
        count--;
        temp = L[temp].cur;
    }
    // 将前一个数据节点的游标赋给插入节点游标，并且将插入结点的索引赋给该数据结点的游标
    L[insertIndex].cur = L[temp].cur;
    L[temp].cur = insertIndex;
    return true;
}
bool deleteElem(staticLinkList &L, int location, string &str) {
    if (location <1 || location>getListLength(L)) {
        return false;
    }
    // 寻找第location - 1个结点
    int temp = MAXSIZE - 1; // 获取第一个数据结点索引
    int count = location - 1;
    while (count > 0) {
        // 根据游标，获取data
        count--;
        temp = L[temp].cur;
    }
    // temp是第location - 1个数据结点的索引
    // 将被删除上一个结点和下一个结点通过cur链接
    int deleteNodeIndex = L[temp].cur;
    str = L[deleteNodeIndex].data;
    L[temp].cur = L[deleteNodeIndex].cur;
    // 处理被删除数据结点 
    // 遍历备用链表到最后一个结点，将最后一个结点的cur赋为deleteNodeIndex
    int spareNodeIndex = 0; // 获取第一个数据结点索引
    while (L[spareNodeIndex].cur != 0) {
        // 根据游标，获取data
        spareNodeIndex = L[spareNodeIndex].cur;
    }
    // 游标修改
    L[spareNodeIndex].cur = deleteNodeIndex;
    L[deleteNodeIndex].cur = 0;
    return true;
}
