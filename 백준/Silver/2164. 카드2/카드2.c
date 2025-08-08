/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.

    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!

    참고로, AI 작성 글이 아니라, 진짜 공식문서 뒤져가면서 힘들게 얻은 지식을 나눠보려고 합니다.
*/

/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초 (추가 시간 없음)	128 MB	161214	84354	65270	51.077%

문제
---
N장의 카드가 있다.

각각의 카드는 차례로 1부터 N까지의 번호가 붙어 있으며,

1번 카드가 제일 위에, N번 카드가 제일 아래인 상태로 순서대로 카드가 놓여 있다.

이제 다음과 같은 동작을 카드가 한 장 남을 때까지 반복하게 된다.

우선, 제일 위에 있는 카드를 바닥에 버린다.

그 다음, 제일 위에 있는 카드를 제일 아래에 있는 카드 밑으로 옮긴다.

예를 들어 N=4인 경우를 생각해 보자.

카드는 제일 위에서부터 1234 의 순서로 놓여있다.

1을 버리면 234가 남는다.

여기서 2를 제일 아래로 옮기면 342가 된다.

3을 버리면 42가 되고, 4를 밑으로 옮기면 24가 된다.

마지막으로 2를 버리고 나면, 남는 카드는 4가 된다.

N이 주어졌을 때, 제일 마지막에 남게 되는 카드를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 정수 N(1 ≤ N ≤ 500,000)이 주어진다.

출력
---
첫째 줄에 남게 되는 카드의 번호를 출력한다.

예제 입력 1
6
예제 출력 1
4
*/

/**
1 2 3 4 5 6
3 4 5 6 2
5 6 2 4
2 4 6
6 4
4


1 2 3 4 5 6 7 8 9 10
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

typedef struct Queue {
    int size;

    void* first;
    void* last;

    void (*set_next)(void*, void*);
    void* (*get_next)(void*);

    void* (*pop)(struct Queue* this);
    void (*push)(struct Queue* this, void*);
} Queue;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Queue* NewQueue(void* (*get_next)(void*), void (*set_next)(void*, void*));
Node* NewNode(int value);

void* pop(Queue* this);
void push(Queue* this, void* node);

void set_next(void* currNode, void* nextNode);
void* get_next(void* node);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    Queue* queue = NewQueue(get_next, set_next);

    int idx = 1;
    while(idx <= N) {
        Node* newNode = NewNode(idx);

        queue->push(queue, newNode);

        idx++;
    }

    while(queue->size != 1) {
        Node* freeNode = queue->pop(queue);
        free(freeNode);
        Node* tmpNode = queue->pop(queue);
        queue->push(queue, tmpNode);
    }

    Node* resultNode = queue->pop(queue);
    int result = resultNode->value;
    free(resultNode);

    char* resultStr = intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    free(queue);

    return 0;
}

Queue* NewQueue(void* (*get_next)(void*), void (*set_next)(void*, void*)) {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->size = 0;
    newQueue->first = NULL;
    newQueue->last = NULL;
    newQueue->get_next = get_next;
    newQueue->set_next = set_next;
    newQueue->pop = pop;
    newQueue->push = push;

    return newQueue;
}
Node* NewNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

void* pop(Queue* this) {
    if(this->first == NULL) {
        return NULL;
    }

    void* result = this->first;
    this->first = this->get_next(result);
    this->set_next(result, NULL);
    this->size--;

    return result;
}
void push(Queue* this, void* node) {
    if(this->first == NULL) {
        this->first = node;
        this->last = node;
        this->size = 1;

        return;
    }

    this->set_next(this->last, node);
    this->last = node;
    this->size++;

    return;
}

void set_next(void* currNode, void* nextNode) {
    ((Node*)currNode)->next = (Node*)nextNode;
    return;
}
void* get_next(void* node) {
    return ((Node*)node)->next;
}

char* intToStr(int target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        target *= -1;
        sign = -1;
    }

    int temp = target;
    do {
        temp /= 10;
        len++;
    } while(temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    *(result + size) = 0;

    int idx = endIdx;
    while(idx >= startIdx) {
        *(result + idx--) = (target % 10) + '0';
        target /= 10;
    }
    if(sign == -1) {
        *result = '-';
    }

    return result;
}
int parseInt(const char* str) {
    int sign = 1;
    int result = 0;

    char* strPtr = (char*)str;
    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    while(isBlank(*strPtr) != 1) {
        result *= 10;
        result += *strPtr++ - '0';
    }

    return result * sign;
}
_Bool isBlank(char ch) {
    if(ch == 32 || ch == 0) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
