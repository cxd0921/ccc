#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxSize 100

typedef struct RingBuffer {
    char *data;
    int write;
    int read;
    int size;
} RingBuffer;

void INIT(RingBuffer *rb) {
    rb->data = (char *)malloc(MaxSize);
    rb->read = 0;
    rb->write = 0;
    rb->size = 0;
}

bool isFull(RingBuffer *rb) {
    return (rb->write + 1) % MaxSize == rb->read;
}

bool isEmpty(RingBuffer *rb) {
    return rb->write == rb->read;
}

bool w_data(RingBuffer *rb, char data) {
    if (isFull(rb)) {
        printf("is full\n");
        return false;
    }
    rb->data[rb->write] = data;
    rb->write = (rb->write + 1) % MaxSize;
    rb->size++;
    return true;
}


void w_s_data(RingBuffer *rb, char *data) {
    while (*data != '\0') {
        w_data(rb, *data);
        data++;
    }
}

char r_data(RingBuffer *rb) {
    if (isEmpty(rb)) {
        printf("Buffer is empty\n");
        return '\0'; // 返回空字符表示缓冲区为空
    }
    char data = rb->data[rb->read];
    rb->read = (rb->read + 1) % MaxSize;
    rb->size--;
    return data;
}

void r_s_data(RingBuffer *rb, char *buffer, int maxSize) {
    int count = 0;
    while (!isEmpty(rb) && count < maxSize) {
        buffer[count] = r_data(rb);
        count++;
    }

    buffer[count] = '\0';
}

void ptr(RingBuffer *rb) {
    printf("data: ");
    int count = rb->size;
    for (int i = 0; i < count; ++i) {
        printf("%c", rb->data[(rb->read + i) % MaxSize]);
    }
    printf("\n");
}


void FreeBuf(RingBuffer*rb){
    if(rb==NULL){
        return;
    }
    if(rb->data!=NULL){
        free(rb->data);
        rb->data=NULL;
    }
    free(rb);
    rb=NULL;
}
int main() {
    RingBuffer rb;
    INIT(&rb);
    w_data(&rb, '1');
    w_s_data(&rb, "567");
    w_s_data(&rb, "333");
    ptr(&rb);

    char buffer[MaxSize];
    r_s_data(&rb, buffer, 2);
    printf("Read data: %s\n", buffer);

    ptr(&rb);

    free(rb.data);
    return 0;
}