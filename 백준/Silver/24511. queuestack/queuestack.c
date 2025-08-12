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
1 초 (추가 시간 없음)	1024 MB (추가 메모리 없음)	27653	9435	7991	33.160%

문제
---
한가롭게 방학에 놀고 있던 도현이는 갑자기 재밌는 자료구조를 생각해냈다.

그 자료구조의 이름은 queuestack이다.

queuestack의 구조는 다음과 같다.
1번, 2번, ... , N번의 자료구조(queue 혹은 stack)가 나열되어있으며,

각각의 자료구조에는 한 개의 원소가 들어있다.

queuestack의 작동은 다음과 같다.

* x_0 을 입력받는다.
* x_0을 1번 자료구조에 삽입한 뒤 1번 자료구조에서 원소를 pop한다. 그때 pop된 원소를 x_1이라 한다.
* x_1을 2번 자료구조에 삽입한 뒤 2번 자료구조에서 원소를 pop한다. 그때 pop된 원소를 x_2이라 한다.
...
* x_{N-1}을 N번 자료구조에 삽입한 뒤 N번 자료구조에서 원소를 pop한다. 그때 pop된 원소를 x_N이라 한다.
* x_N을 리턴한다.

도현이는 길이 M 의 수열 C 를 가져와서 수열의 원소를 앞에서부터 차례대로 queuestack에 삽입할 것이다.

이전에 삽입한 결과는 남아 있다. (예제 1 참고)

queuestack에 넣을 원소들이 주어졌을 때, 해당 원소를 넣은 리턴값을 출력하는 프로그램을 작성해보자.

입력
---
첫째 줄에 queuestack 을 구성하는 자료구조의 개수 N 이 주어진다. (1 <= N <= 100_000)

둘째 줄에 길이 N 의 수열 A 가 주어진다. i 번 자료구조가 큐라면 A_i = 0, 스택이라면 A_i = 1 이다.

셋째 줄에 길이 N 의 수열 B 가 주어진다. B_i 는 i 번 자료구조에 들어 있는 원소이다. (1 <= B_i <= 1_000_000_000)

넷째 줄에 삽입할 수열의 길이 M 이 주어진다. (1 <= M <= 100_000)

다섯째 줄에 queuestack 에 삽입할 원소를 담고 있는 길이 M 의 수열 C 가 주어진다. (1 <= C_i <= 1_000_000_000)

입력으로 주어지는 모든 수는 정수이다.

출력
---
수열 C 의 원소를 차례대로 queuestack에 삽입했을 때의 리턴값을 공백으로 구분하여 출력한다.

예제 입력 1
4
0 1 1 0
1 2 3 4
3
2 4 7
예제 출력 1
4 1 2


각 상태에 대한 큐스택 내부를 표현하면 다음과 같다.

초기 상태 : [1, 2, 3, 4]
첫 번째 원소 삽입 : [2, 2, 3, 1]
두 번째 원소 삽입 : [4, 2, 3, 2]
세 번째 원소 삽입 : [7, 2, 3, 4]

예제 입력 2
5
1 1 1 1 1
1 2 3 4 5
3
1 3 5
예제 출력 2
1 3 5
*/

/**
문제를 잘 읽어봐야 하는 항목이다.

하나의 원소를 가진 각 자료구조는 어떤 행동을 하는지 조사해보면,

스택을 의미하는 "1" 은 구현해도 되고, 구현하지 않아도 된다. - 당연히 구현하지 않았을 때 어떤 로직으로 대체 할 것인지 생각해야 한다.

하지만, 큐를 의미하는 "0" 은 구현해야 한다.

스택은 소유한 엘리먼트를 뱉어내는 일이 없지만,

큐는 항상 소유한 엘리먼트를 뱉어내고, 입력된 데이터로 수정한다.

그렇다면, "0" 에 해당하는 자료구조들만 엮어서 큐로 만들어도 된다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Node {
    int value;
    struct Node* nextNode;
} Node;

Node* NewNode(int value);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    const int NORMAL_SIZE = 255;
    const int MAX_SIZE = 1000000;

    char* input = (char*)malloc(sizeof(char) * (NORMAL_SIZE + 1));
    *(input + NORMAL_SIZE) = 0;

    fgets(input, NORMAL_SIZE, stdin);

    int N = parseInt(input);

    free(input);

    input = (char*)malloc(sizeof(char) * (MAX_SIZE + 1));
    *(input + MAX_SIZE) = 0;

    fgets(input, MAX_SIZE, stdin);

    char** structTokens = tokenizer(input);
    char** structTokensPtr = structTokens;

    free(input);

    int queueSize = 0;
    while(*structTokensPtr) {
        char ch = *(*structTokensPtr++);

        if(ch == '0') {
            queueSize++;
        }
    }

    int* numList = (int*)malloc(sizeof(int) * (queueSize + 1));

    input = (char*)malloc(sizeof(char) * (MAX_SIZE + 1));
    *(input + MAX_SIZE) = 0;
    fgets(input, MAX_SIZE, stdin);

    char** elemTokens = tokenizer(input);
    char** elemTokensPtr = (char**)elemTokens;
    structTokensPtr = structTokens;

    free(input);

    int fix = 0;
    while(*elemTokensPtr) {
        int currNumber = parseInt(*elemTokensPtr++);
        char ch = *(*structTokensPtr++);

        if(ch == '0') {
            *(numList + fix++) = currNumber;
        }
    }

    freeTokens(structTokens);
    freeTokens(elemTokens);

    // 입력을 그대로 출력하면 됨. - 맨 마지막에 구현.
    if(queueSize == 0) {
        input = (char*)malloc(sizeof(char) * (NORMAL_SIZE + 1));
        *(input + NORMAL_SIZE) = 0;
        fgets(input, NORMAL_SIZE, stdin);
        free(input);


        input = (char*)malloc(sizeof(char) * (MAX_SIZE + 1));
        *(input + MAX_SIZE) = 0;
        fgets(input, MAX_SIZE, stdin);
        fputs(input, stdout);

        free(input);

        return 0;
    }

    int idx = queueSize - 1;
    Node* startNode = NewNode(*(numList + idx--));
    Node* endNode = startNode;

    while(idx >= 0) {
        int currVal = *(numList + idx--);

        Node* currNode = NewNode(currVal);
        endNode->nextNode = currNode;
        endNode = currNode;
    }

    input = (char*)malloc(sizeof(char) * (NORMAL_SIZE + 1));
    *(input + NORMAL_SIZE) = 0;
    fgets(input, NORMAL_SIZE, stdin);

    int M = parseInt(input);

    free(input);

    input = (char*)malloc(sizeof(char) * (MAX_SIZE + 1));
    *(input + MAX_SIZE) = 0;
    fgets(input, MAX_SIZE, stdin);

    char** insertTokens = tokenizer(input);
    char** insertTokensPtr = insertTokens;

    free(input);

    idx = 0;
    while(idx++ < M) {
        int insertNum = parseInt(*insertTokensPtr++);

        Node* insertNode = NewNode(insertNum);

        endNode->nextNode = insertNode;
        endNode = insertNode;

        Node* tmpNode = startNode;
        int tmpNum = tmpNode->value;
        char* tmpResult = intToStr(tmpNum);
        fputs(tmpResult, stdout); fputc(' ', stdout);
        free(tmpResult);

        startNode = startNode->nextNode;
        free(tmpNode);
    }
    fputc('\n', stdout);

    return 0;
}

Node* NewNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->value = value;
    newNode->nextNode = NULL;

    return newNode;
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
