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
2 초	512 MB	102597	58910	49283	56.960%
문제
요세푸스 문제는 다음과 같다.

1번부터 N번까지 N명의 사람이 원을 이루면서 앉아있고, 양의 정수 K(≤ N)가 주어진다.

이제 순서대로 K번째 사람을 제거한다.

한 사람이 제거되면 남은 사람들로 이루어진 원을 따라 이 과정을 계속해 나간다.

이 과정은 N명의 사람이 모두 제거될 때까지 계속된다.

원에서 사람들이 제거되는 순서를 (N, K)-요세푸스 순열이라고 한다.

예를 들어 (7, 3)-요세푸스 순열은 <3, 6, 2, 7, 5, 1, 4>이다.

N과 K가 주어지면 (N, K)-요세푸스 순열을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 빈 칸을 사이에 두고 순서대로 주어진다. (1 ≤ K ≤ N ≤ 1,000)

출력
예제와 같이 요세푸스 순열을 출력한다.

예제 입력 1
7 3
예제 출력 1
<3, 6, 2, 7, 5, 1, 4>
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Circular {
    int size;

    void* start;
    void* end;

    void* (*get_next)(void*);
    void (*set_next)(void*, void*);

    void* (*get_prev)(void*);
    void (*set_prev)(void*, void*);

    void (*push)(struct Circular* this, void* node);
    void* (*remove)(struct Circular* this, void* node);
} Circular;

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

Circular* NewCircular(void* (*get_next)(void*), void (*set_next)(void*, void*), void* (*get_prev)(void*), void (*set_prev)(void*, void*));
Node* NewNode(int value);

void push_node(Circular* this, void* node);
void* remove_node(Circular* this, void* node);

void* get_next_node(void* node);
void set_next_node(void* currNode, void* nextNode);

void* get_prev_node(void* node);
void set_prev_node(void* currNode, void* prevNode);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int N = parseInt(*tokensPtr++);
    int K = parseInt(*tokensPtr++);

    freeTokens(tokens);

    // 여기에 들어간 함수들은 Node 를 위한 커스텀 함수들.
    // 즉, 이러한 방식으로 추상화 구조체를 특정 아이템을 위한 자료구조로 만들 수 있다.
    // 일종의 C 에서의 메타프로그래밍 방식 중 하나라고 생각한다.
    Circular* circular = NewCircular(get_next_node, set_next_node, get_prev_node, set_prev_node);

    int idx = 1;
    while(idx <= N) {
        Node* newNode = NewNode(idx);
        circular->push(circular, newNode);

        idx++;
    }

    fputc('<', stdout);

    Node* tmpNode = circular->start;
    idx = 1;
    while(circular->size != 0) {
        if(idx % K == 0) {
            circular->remove(circular, tmpNode);

            char* tmpResult = intToStr(tmpNode->value);
            if(circular->size != 0) {
                fputs(tmpResult, stdout); fputs(", ", stdout);
            } else {
                fputs(tmpResult, stdout); fputs(">\n", stdout);
            }

            Node* freedNode = tmpNode;
            tmpNode = tmpNode->next;
            idx++;

            free(tmpResult);
            free(freedNode);
        } else {
            idx++;
            tmpNode = tmpNode->next;
        }
    }

    return 0;
}

Circular* NewCircular(void* (*get_next)(void*), void (*set_next)(void*, void*), void* (*get_prev)(void*), void (*set_prev)(void*, void*)) {
    Circular* newCircular = (Circular*)malloc(sizeof(Circular));

    newCircular->size = 0;

    newCircular->start = NULL;
    newCircular->end = NULL;

    newCircular->get_next = get_next;
    newCircular->get_prev = get_prev;

    newCircular->set_next = set_next;
    newCircular->set_prev = set_prev;

    newCircular->remove = remove_node;
    newCircular->push = push_node;

    return newCircular;
}
Node* NewNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void push_node(Circular* this, void* node) {
    if(this->start == NULL) {
        this->size = 1;
        this->start = node;
        this->end = node;

        return;
    }

    this->set_next(this->end, node);
    this->set_prev(node, this->end);
    this->end = node;
    // 순환 구조 유지
    this->set_next(this->end, this->start);
    this->set_prev(this->start, this->end);

    this->size++;

    return;
}
void* remove_node(Circular* this, void* node) {
    if(this->size == 0) {
        return NULL;
    } else if(this->size == 1) {
        this->start = NULL;
        this->end = NULL;
    }

    // 순환 자료구조라서 사이즈만을 참고해도 됨.
    if(this->get_prev(node) != NULL) {
        this->set_next(this->get_prev(node), this->get_next(node));
    }
    if(this->get_next(node) != NULL) {
        this->set_prev(this->get_next(node), this->get_prev(node));
    }

    this->size--;

    return node;
}

void* get_next_node(void* node) {
    return ((Node*)node)->next;
}
void set_next_node(void* currNode, void* nextNode) {
    ((Node*)currNode)->next = (Node*)nextNode;
    return;
}

void* get_prev_node(void* node) {
    return ((Node*)node)->prev;
}
void set_prev_node(void* currNode, void* prevNode) {
    ((Node*)currNode)->prev = (Node*)prevNode;
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
