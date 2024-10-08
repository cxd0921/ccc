#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义双向循环链表节点结构体
typedef struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
} Node;

// 创建新节点
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！");
        exit(1);
    }
    newNode->data = (char*)malloc(strlen(data) + 1);

    strcpy(newNode->data, data);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


Node* initList() {
    Node* head = createNode("");
    head->prev = head;
    head->next = head;
    return head;
}


void insertTail(Node* head, const char* data) {
    Node* newNode = createNode(data);
    Node* tail = head->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
}


void insertHead(Node* head, const char* data) {
    Node* newNode = createNode(data);
    Node* first = head->next; // 找到首节点
    head->next = newNode;
    newNode->prev = head;
    newNode->next = first; // 新节点的后继指向原首节点
    first->prev = newNode; // 原首节点的前驱指向新节点
}

void deleteNode(Node* head, Node* target) {
    if (target == NULL || head == target) {
        printf("目标节点为空或为头节点，无法删除！");
        return;
    }
    Node* prev = target->prev;
    Node* next = target->next;
    prev->next = next;
    next->prev = prev;
    if (head->next == target) { // 如果删除的是首节点，需要更新头节点的后继
        head->next = next;
    }
    if (head->prev == target) { // 如果删除的是尾节点，需要更新头节点的前驱
        head->prev = prev;
    }
    free(target->data); // 释放数据
    free(target); // 释放节点
}

// 打印双向循环链表
void printList(Node* head) {
    Node* current = head->next; // 从首节点开始遍历
    while (current != head) { // 遍历到头节点为止
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 释放整个双向循环链表
void freeList(Node* head) {
    Node* current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(head);
}

int main() {
    Node* list = initList();
    insertTail(list, "Hello");
    insertTail(list, "World");
    insertHead(list, "Welcome");
    printList(list);

    Node* target = list->next; // 找到要删除的节点"Hello"
    deleteNode(list, target); // 删除节点"Hello"
    printList(list); // 打印链表：Welcome World

    // 释放链表
    freeList(list);

    return 0;
}