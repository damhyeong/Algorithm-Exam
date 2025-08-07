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
2 초	1024 MB	56917	21288	17608	37.540%
문제
정수를 저장하는 스택을 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 다섯 가지이다.

1 X: 정수 X를 스택에 넣는다. (1 ≤ X ≤ 100,000)
2: 스택에 정수가 있다면 맨 위의 정수를 빼고 출력한다. 없다면 -1을 대신 출력한다.
3: 스택에 들어있는 정수의 개수를 출력한다.
4: 스택이 비어있으면 1, 아니면 0을 출력한다.
5: 스택에 정수가 있다면 맨 위의 정수를 출력한다. 없다면 -1을 대신 출력한다.
입력
첫째 줄에 명령의 수 N이 주어진다. (1 ≤ N ≤ 1,000,000)

둘째 줄부터 N개 줄에 명령이 하나씩 주어진다.

출력을 요구하는 명령은 하나 이상 주어진다.

출력
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
자료구조는 추상화.

그리고, 들어갈 값과 적용되야 할 함수는 커스텀하는 방식.
*/
#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Stack {
    int size;

    void* bottom;
    void* top;

    void* (*get_next)(void*);
    void* (*get_prev)(void*);
    void (*set_next)(void*, void*);
    void (*set_prev)(void*, void*);

    void (*push)(struct Stack* this, void*);
    void* (*pop)(struct Stack* this);
} Stack;

Stack* NewStack(void* (*get_next)(void*), void* (*get_prev)(void*), void (*set_next)(void*, void*), void (*set_prev)(void*, void*));
void push_stack(Stack* this, void* node);
void* pop_stack(Stack* this);

typedef struct Item {
    int value;
    struct Item* next;
    struct Item* prev;
} Item;

Item* NewItem(int value);

void* get_next(void* item);
void* get_prev(void* item);
void set_next(void* currItem, void* nextItem);
void set_prev(void* currItem, void* prevItem);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    Stack* stack = NewStack(get_next, get_prev, set_next, set_prev);

    int N = parseInt(input);

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = tokens;

        int order = parseInt(*tokensPtr++);

        if(order == 1) {
            Item* newItem = NewItem(parseInt(*tokensPtr++));
            stack->push(stack, newItem);
        } else if(order == 2) {
            if(stack->size == 0) {
                fputs("-1\n", stdout);
            } else {
                Item* topItem = (Item*)stack->pop(stack);
                char* tmpResult = intToStr(topItem->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult); free(topItem);
            }
        } else if(order == 3) {
            char* tmpResult = intToStr(stack->size);
            fputs(tmpResult, stdout); fputc('\n', stdout);
            free(tmpResult);
        } else if(order == 4) {
            if(stack->size == 0) {
                fputs("1\n", stdout);
            } else {
                fputs("0\n", stdout);
            }
        } else if(order == 5) {
            if(stack->size == 0) {
                fputs("-1\n", stdout);
            } else {
                Item* topItem = (Item*)stack->top;
                char* tmpResult = intToStr(topItem->value);
                fputs(tmpResult, stdout); fputc('\n', stdout);
                free(tmpResult);
            }
        }


        freeTokens(tokens);
    }

    // 내부에 Item이 없다는 전제 하.
    free(stack);

    return 0;
}

Stack* NewStack(void* (*get_next)(void*), void* (*get_prev)(void*), void (*set_next)(void*, void*), void (*set_prev)(void*, void*)) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));

    newStack->size = 0;

    newStack->top = NULL;
    newStack->bottom = NULL;

    newStack->get_next = get_next;
    newStack->get_prev = get_prev;
    newStack->set_next = set_next;
    newStack->set_prev = set_prev;

    newStack->pop = pop_stack;
    newStack->push = push_stack;

    return newStack;
}
void push_stack(Stack* this, void* node) {
    if(this->size == 0) {
        this->bottom = node;
        this->top = node;

        this->size++;

        return;
    }

    this->set_next(this->top, node);
    this->set_prev(node, this->top);
    this->top = node;
    this->size++;

    return;
}
void* pop_stack(Stack* this) {
    if(this->size == 0) {
        return NULL;
    }

    void* result = this->top;
    this->top = this->get_prev(this->top);
    this->size--;

    // 사이즈가 하나 일 경우.
    if(this->top == NULL) {
        this->bottom = NULL;
    } else {
        this->set_next(this->top, NULL);
    }

    // 혹시 모를 참조 에러를 방지. - 순수 값만을 방출
    this->set_next(result, NULL);
    this->set_prev(result, NULL);

    return result;
}

Item* NewItem(int value) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    newItem->value = value;
    newItem->next = NULL;
    newItem->prev = NULL;

    return newItem;
}

void* get_next(void* item) {
    return ((Item*)item)->next;
}
void* get_prev(void* item) {
    return ((Item*)item)->prev;
}
void set_next(void* currItem, void* nextItem) {
    ((Item*)currItem)->next = (Item*)nextItem;
    return;
}
void set_prev(void* currItem, void* prevItem) {
    ((Item*)currItem)->prev = (Item*)prevItem;
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
