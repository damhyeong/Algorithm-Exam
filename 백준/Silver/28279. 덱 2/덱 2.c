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
2 초	1024 MB	23282	11564	10324	50.568%

문제
---
정수를 저장하는 덱을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 여덟 가지이다.

1 X: 정수 X를 덱의 앞에 넣는다. (1 ≤ X ≤ 100,000)
2 X: 정수 X를 덱의 뒤에 넣는다. (1 ≤ X ≤ 100,000)
3: 덱에 정수가 있다면 맨 앞의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
4: 덱에 정수가 있다면 맨 뒤의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
5: 덱에 들어있는 정수의 개수를 출력한다.
6: 덱이 비어있으면 1, 아니면 0을 출력한다.
7: 덱에 정수가 있다면 맨 앞의 정수를 출력한다. 없다면 -1을 대신 출력한다.
8: 덱에 정수가 있다면 맨 뒤의 정수를 출력한다. 없다면 -1을 대신 출력한다.


입력
---
첫째 줄에 명령의 수 N이 주어진다.

(1 ≤ N ≤ 1,000,000)

둘째 줄부터 N개 줄에 명령이 하나씩 주어진다.

출력을 요구하는 명령은 하나 이상 주어진다.

출력
---
출력을 요구하는 명령이 주어질 때마다 명령의 결과를 한 줄에 하나씩 출력한다.

예제 입력 1
11
6
1 3
1 8
7
8
3
2 5
1 2
5
4
4
예제 출력 1
1
8
3
8
3
5
3
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Deck {
    int size;

    void* first;
    void* last;

    void (*set_next)(void*, void*);
    void* (*get_next)(void*);

    void (*set_prev)(void*, void*);
    void* (*get_prev)(void*);

    void (*insert_first)(struct Deck* this, void*);
    void (*insert_last)(struct Deck* this, void*);

    void* (*pop_first)(struct Deck* this);
    void* (*pop_last)(struct Deck* this);
} Deck;

Deck* NewDeck(void (*set_next)(void*, void*), void* (*get_next)(void*), void (*set_prev)(void*, void*), void* (*get_prev)(void*));

void insert_first_deck(Deck* this, void* node);
void insert_last_deck(Deck* this, void* node);

void* pop_first_deck(Deck* this);
void* pop_last_deck(Deck* this);

typedef struct Node {
    int value;
    struct Node* nextNode;
    struct Node* prevNode;
} Node;

Node* NewNode(int value);

void set_next_node(void* currNode, void* nextNode);
void* get_next_node(void* node);

void set_prev_node(void* currNode, void* prevNode);
void* get_prev_node(void* node);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    Deck* deck = NewDeck(set_next_node, get_next_node, set_prev_node, get_prev_node);

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = tokens;

        int order = parseInt(*tokensPtr++);
        if(order == 1) {
            int newNum = parseInt(*tokensPtr++);
            Node* newNode = NewNode(newNum);
            deck->insert_first(deck, newNode);
        } else if(order == 2) {
            int newNum = parseInt(*tokensPtr++);
            Node* newNode = NewNode(newNum);
            deck->insert_last(deck, newNode);
        } else if(order == 3) {
            if(deck->size != 0) {
                Node* popedNode = deck->pop_first(deck);
                char* tmpResult = intToStr(popedNode->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult); free(popedNode);
            } else {
                fputs("-1\n", stdout);
            }
        } else if(order == 4) {
            if(deck->size != 0) {
                Node* popedNode = deck->pop_last(deck);
                char* tmpResult = intToStr(popedNode->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult); free(popedNode);
            } else {
                fputs("-1\n", stdout);
            }
        } else if(order == 5) {
            int size = deck->size;
            char* tmpResult = intToStr(size);
            fputs(tmpResult, stdout); fputc('\n', stdout);
            free(tmpResult);
        } else if(order == 6) {
            if(deck->size == 0) {
                fputs("1\n", stdout);
            } else {
                fputs("0\n", stdout);
            }
        } else if(order == 7) {
            if(deck->size == 0) {
                fputs("-1\n", stdout);
            } else {
                Node* firstNode = deck->first;
                char* tmpResult = intToStr(firstNode->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult);
            }
        } else if(order == 8) {
            if(deck->size == 0) {
                fputs("-1\n", stdout);
            } else {
                Node* lastNode = deck->last;
                char* tmpResult = intToStr(lastNode->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult);
            }
        }
        freeTokens(tokens);
    }


    return 0;
}


Deck* NewDeck(void (*set_next)(void*, void*), void* (*get_next)(void*), void (*set_prev)(void*, void*), void* (*get_prev)(void*)) {
    Deck* newDeck = (Deck*)malloc(sizeof(Deck));

    newDeck->size = 0;
    newDeck->first = NULL;
    newDeck->last = NULL;

    newDeck->get_next = get_next;
    newDeck->get_prev = get_prev;

    newDeck->set_next = set_next;
    newDeck->set_prev = set_prev;

    newDeck->insert_first = insert_first_deck;
    newDeck->insert_last = insert_last_deck;

    newDeck->pop_first = pop_first_deck;
    newDeck->pop_last = pop_last_deck;

    return newDeck;
}

void insert_first_deck(Deck* this, void* node) {
    if(this->size == 0) {
        this->first = node;
        this->last = node;
        this->size = 1;
        return;
    }

    this->set_prev(this->first, node);
    this->set_next(node, this->first);
    this->first = node;

    this->size++;

    return;
}
void insert_last_deck(Deck* this, void* node) {
    if(this->size == 0) {
        this->last = node;
        this->first = node;
        this->size = 1;
        return;
    }

    this->set_next(this->last, node);
    this->set_prev(node, this->last);
    this->last = node;

    this->size++;

    return;
}

void* pop_first_deck(Deck* this) {
    if(this->size == 0) {
        return NULL;
    }

    void* poped = this->first;
    this->first = this->get_next(this->first);
    this->set_prev(this->first, NULL);
    this->size--;

    this->set_next(poped, NULL);
    return poped;
}
void* pop_last_deck(Deck* this) {
    if(this->size == 0) {
        return NULL;
    }

    void* poped = this->last;
    this->last = this->get_prev(this->last);
    this->set_next(this->last, NULL);
    this->size--;

    this->set_prev(poped, NULL);
    return poped;
}

Node* NewNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->value = value;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    return newNode;
}

void set_next_node(void* currNode, void* nextNode) {
    if(currNode == NULL) {
        return;
    }

    ((Node*)currNode)->nextNode = (Node*)nextNode;
    return;
}
void* get_next_node(void* node) {
    return ((Node*)node)->nextNode;
}

void set_prev_node(void* currNode, void* prevNode) {
    if(currNode == NULL) {
        return;
    }

    ((Node*)currNode)->prevNode = (Node*)prevNode;
    return;
}
void* get_prev_node(void* node) {
    return ((Node*)node)->prevNode;
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
            char* newTknPtr = (char*)newTkn;

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
