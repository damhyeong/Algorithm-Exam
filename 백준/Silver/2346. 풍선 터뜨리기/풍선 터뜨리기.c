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
2 초	4 MB	45903	19653	15956	44.454%

문제
---
1번부터 N번까지 N개의 풍선이 원형으로 놓여 있고.

i번 풍선의 오른쪽에는 i+1번 풍선이 있고, 왼쪽에는 i-1번 풍선이 있다.

단, 1번 풍선의 왼쪽에 N번 풍선이 있고, N번 풍선의 오른쪽에 1번 풍선이 있다.

각 풍선 안에는 종이가 하나 들어있고, 종이에는 -N보다 크거나 같고, N보다 작거나 같은 정수가 하나 적혀있다.

이 풍선들을 다음과 같은 규칙으로 터뜨린다.

우선, 제일 처음에는 1번 풍선을 터뜨린다.

다음에는 풍선 안에 있는 종이를 꺼내어 그 종이에 적혀있는 값만큼 이동하여 다음 풍선을 터뜨린다.

양수가 적혀 있을 경우에는 오른쪽으로, 음수가 적혀 있을 때는 왼쪽으로 이동한다.

이동할 때에는 이미 터진 풍선은 빼고 이동한다.

예를 들어 다섯 개의 풍선 안에 차례로 3, 2, 1, -3, -1이 적혀 있었다고 하자.

이 경우 3이 적혀 있는 1번 풍선, -3이 적혀 있는 4번 풍선, -1이 적혀 있는 5번 풍선, 1이 적혀 있는 3번 풍선, 2가 적혀 있는 2번 풍선의 순서대로 터지게 된다.


입력
---
첫째 줄에 자연수 N(1 ≤ N ≤ 1,000)이 주어진다.

다음 줄에는 차례로 각 풍선 안의 종이에 적혀 있는 수가 주어진다.

종이에 0은 적혀있지 않다.


출력
---
첫째 줄에 터진 풍선의 번호를 차례로 나열한다.

예제 입력 1
5
3 2 1 -3 -1
예제 출력 1
1 4 5 3 2
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Node {
    int index;
    int value;
    struct Node* nextNode;
    struct Node* prevNode;
} Node;

Node* NewNode(int index, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->index = index;
    newNode->value = value;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    return newNode;
}

Node* get_next(Node* node) {
    return node->nextNode;
}
void set_next(Node* currNode, Node* nextNode) {
    if(!currNode) {
        return;
    }

    currNode->nextNode = nextNode;
    return;
}

Node* get_prev(Node* node) {
    return node->prevNode;
}
void set_prev(Node* currNode, Node* prevNode) {
    if(!currNode) {
        return;
    }

    currNode->prevNode = prevNode;
    return;
}

Node* remove_node(Node* node) {
    node->prevNode->nextNode = node->nextNode;
    node->nextNode->prevNode = node->prevNode;

    return node;
}

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[5000];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    fgets(input, sizeof(input), stdin);

    char** tokens = tokenizer(input);
    char** tokensPtr = tokens;

    Node* startNode = NewNode(1, parseInt(*tokensPtr++));
    Node* lastNode = startNode;

    lastNode->nextNode = startNode;
    startNode->prevNode = lastNode;

    int size = N;
    int idx = 2;
    while(idx <= N) {
        Node* node = NewNode(idx, parseInt(*tokensPtr++));
        lastNode->nextNode = node;
        node->prevNode = lastNode;
        lastNode = node;

        lastNode->nextNode = startNode; startNode->prevNode = lastNode;

        idx++;
    }

    Node* currNode = startNode;

    while(size != 0) {
        int index = currNode->index;
        int value = currNode->value;
        size--;
        char* indexStr = intToStr(index);
        fputs(indexStr, stdout); fputc(' ', stdout);
        free(indexStr);

        Node* freedNode = remove_node(currNode);

        if(value > 0) {
            int idx = 0;
            while(idx < value) {
                currNode = currNode->nextNode;

                idx++;
            }
        } else {
            int idx = 0;
            while(idx > value) {
                currNode = currNode->prevNode;

                idx--;
            }
        }

        free(freedNode);
    }
    fputc('\n', stdout);


    return 0;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    char* inputPtr = (char*)input;
    int tknIdx = 0;
    int currIdx = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch) == 1) {
            if(tknIdx == currIdx) {
                tknIdx = ++currIdx;
                continue;
            }

            int tknSize = currIdx - tknIdx;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(tknIdx != currIdx) {
                *newTknPtr++ = input[tknIdx++];
            }
            *tokensPtr++ = newTkn; currSize++;

            tknIdx = ++currIdx;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            currIdx++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = (char**)tokens;

    while(*tokensPtr) {
        free(*tokensPtr++);
    }
    free(tokens);

    return;
}

char* intToStr(int target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
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
