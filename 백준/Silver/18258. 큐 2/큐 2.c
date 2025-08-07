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
2 초	1024 MB	56886	21273	17594	37.531%

문제
---
정수를 저장하는 스택을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 다섯 가지이다.

1 X: 정수 X를 스택에 넣는다. (1 ≤ X ≤ 100,000)
2: 스택에 정수가 있다면 맨 위의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
3: 스택에 들어있는 정수의 개수를 출력한다.
4: 스택이 비어있으면 1, 아니면 0을 출력한다.
5: 스택에 정수가 있다면 맨 위의 정수를 출력한다. 없다면 -1을 대신 출력한다.


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
9
4
1 3
1 5
3
2
5
2
2
5
예제 출력 1
1
2
5
3
3
-1
-1
*/

/**
큐와 스택, 덱 부문은 아마 구조체를 만드는 게 가장 힘든 부분이지 않을까 싶다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

// 추상 아이템으로 정의.
typedef struct Queue {
    int size;

    void* first;
    void* last;

    // 이건 내부 node 가 가지게 될 구조체에서 정의하고, Queue 생성 시 넣어주는 걸로.
    void* (*get_next)(void* node);
    void (*set_next)(void* node, void* next);

    void* (*pop)(struct Queue* this);
    void (*push)(struct Queue* this, void* node);
} Queue;

Queue* NewQueue(void* (*get_next)(void*), void (*set_next)(void*, void*));

void* pop_queue(Queue* this);
void push_queue(Queue* this, void* new);

// 직접 정하는 아이템 구조체 - 문제에 걸맞게.
typedef struct Item {
    int value;
    struct Item* next;
} Item;

Item* NewItem(int value);

// Queue 생성 시 초기화로 넣어줄 함수.
void* get_next_item(void* item);
void set_next_item(void* currItem, void* nextItem);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int compare_str(char* s1, char* s2) {
    char* s1Ptr = s1;
    char* s2Ptr = s2;

    while(*s1Ptr && *s2Ptr) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }
    }

    return *s1Ptr ? 1 : *s2Ptr ? -1 : 0;
}

int main(void) {
    char input[255];

    Queue* queue = NewQueue(get_next_item, set_next_item);

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);
        char** tokensPtr = (char**)tokens;

        char* order = *tokensPtr++;

        if(compare_str(order, "push") == 0) {
            Item* newItem = NewItem(parseInt(*tokensPtr++));

            queue->push(queue, newItem);
        } else if(compare_str(order, "pop") == 0) {
            if(queue->size == 0) {
                fputs("-1\n", stdout);
            } else {
                Item* popItem = (Item*)queue->pop(queue);
                char* tmpResult = intToStr(popItem->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult);
                free(popItem);
            }
        } else if(compare_str(order, "size") == 0) {
            char* tmpResult = intToStr(queue->size);
            fputs(tmpResult, stdout); fputc('\n', stdout);
            free(tmpResult);
        } else if(compare_str(order, "empty") == 0) {
            if(queue->size == 0) {
                fputs("1\n", stdout);
            } else {
                fputs("0\n", stdout);
            }
        } else if(compare_str(order, "front") == 0) {
            if(queue->size == 0) {
                fputs("-1\n", stdout);
            } else {
                Item* frontItem = (Item*)queue->first;
                char* tmpResult = intToStr(frontItem->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult);
            }
        } else if(compare_str(order, "back") == 0) {
            if(queue->size == 0) {
                fputs("-1\n", stdout);
            } else {
                Item* backItem = (Item*)queue->last;
                char* tmpResult = intToStr(backItem->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult);
            }
        }


        freeTokens(tokens);
    }

    return 0;
}

Queue* NewQueue(void* (*get_next)(void*), void (*set_next)(void*, void*)) {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->size = 0;

    newQueue->first = NULL;
    newQueue->last = NULL;

    newQueue->get_next = get_next;
    newQueue->set_next = set_next;

    newQueue->pop = pop_queue;
    newQueue->push = push_queue;

    return newQueue;
}

void* pop_queue(struct Queue* this) {
    if(this->first == NULL) {
        return NULL;
    }
    void* result = this->first;
    this->first = this->get_next(this->first);

    // pop 한 엘리먼트가 애초에 마지막이었을 때.
    if(this->first == NULL) {
        this->last = NULL;
    }

    this->size--;
    return result;
}
void push_queue(struct Queue* this, void* new) {
    void* last = this->last;

    // 이건 내부에 엘리먼트가 없는 것을 의미.
    if(last == NULL) {
        this->first = new;
        this->last = new;
        this->size = 1;

        return;
    }

    this->set_next(this->last, new);
    this->last = new;
    this->size++;

    return;
}

Item* NewItem(int value) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    newItem->value = value;
    newItem->next = NULL;

    return newItem;
}

// Queue 생성 시 초기화로 넣어줄 함수. get_next_item, set_next_item 2 개.
void* get_next_item(void* item) {
    return ((Item*)item)->next;
}
void set_next_item(void* currItem, void* nextItem) {
    ((Item*)currItem)->next = (Item*)nextItem;
    return;
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
