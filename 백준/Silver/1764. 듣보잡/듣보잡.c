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
2 초	256 MB	143329	62938	49413	42.169%

문제
---
김진영이 듣도 못한 사람의 명단과, 보도 못한 사람의 명단이 주어질 때, 듣도 보도 못한 사람의 명단을 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 듣도 못한 사람의 수 N, 보도 못한 사람의 수 M이 주어진다.

이어서 둘째 줄부터 N개의 줄에 걸쳐 듣도 못한 사람의 이름과, N+2째 줄부터 보도 못한 사람의 이름이 순서대로 주어진다.

이름은 띄어쓰기 없이 알파벳 소문자로만 이루어지며, 그 길이는 20 이하이다.

N, M은 500,000 이하의 자연수이다.

듣도 못한 사람의 명단에는 중복되는 이름이 없으며, 보도 못한 사람의 명단도 마찬가지이다.


출력
---
듣보잡의 수와 그 명단을 사전순으로 출력한다.

예제 입력 1
3 4
ohhenrie
charlie
baesangwook
obama
baesangwook
ohhenrie
clinton
예제 출력 1
2
baesangwook
ohhenrie
*/

/**
이것도 딱히 remove 기능이 필요하지 않고, heap_sort 와 binary_search 만으로도 충분히 풀 수 있는 문제이다.

듣도 못한 사람들을 정렬하고,

보도 못한 사람들을 binary_search 하여 교집합에 속하는 사람들을 저장 이후 출력하면 된다.

단, 이 교집합의 수를 저장한 이후 첫 번째로 출력해야 하기 때문에,

이를 struct 로 만들어 저장했다가 출력할지,

아니면 그냥 따로 원시적으로 저장했다가 출력할지 선택하면 된다.

---

선택 --> 구조체를 사용하면 편하긴 하지만, 원시적으로 값을 저장했다가 출력하자. (실력 향상을 위함)
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char* copy_str(const char* str);
int compare_each_str(const char* s1, const char* s2);

void sort_heap(char** strList, int length);
void heapify(char** strList, int limitIdx, int currIdx);
void swap(char** strList, int i, int j);

int binary_search(char** strList, char* target, int i, int j);

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
    int M = parseInt(*tokensPtr++);

    freeTokens(tokens);

    char** strList = (char**)malloc(sizeof(char*) * (N + 1));
    *(strList + N) = NULL;

    int idx = 0;

    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        tokens = tokenizer(input);

        *(strList + idx) = copy_str(*tokens);

        freeTokens(tokens);

        idx++;
    }

    sort_heap(strList, N);

    int size = 4;
    int currSize = 0;

    // 길이 재조정은 루프 내에서.
    char** findStrs = (char**)malloc(sizeof(char*) * (size + 1));
    char** findStrsPtr = (char**)findStrs;

    idx = 0;
    while(idx++ < M) {
        fgets(input, sizeof(input), stdin);

        tokens = tokenizer(input);

        char* findStr = copy_str(*tokens);

        freeTokens(tokens);

        int findIdx = binary_search(strList, findStr, 0, N - 1);

        if(findIdx != -1) {
            *findStrsPtr++ = findStr; currSize++;

            if(size == currSize) {
                size *= 2;
                findStrs = (char**)realloc(findStrs, sizeof(char*) * (size + 1));
                findStrsPtr = (char**)(findStrs + currSize);
            }
        }
    }
    *findStrsPtr = NULL;

    sort_heap(findStrs, currSize);

    char* lenStr = intToStr(currSize);
    fputs(lenStr, stdout); fputc('\n', stdout);
    free(lenStr);

    findStrsPtr = (char**)findStrs;
    while(*findStrsPtr) {
        fputs(*findStrsPtr, stdout); fputc('\n', stdout);
        free(*findStrsPtr++);
    }
    free(findStrs);

    char** strListPtr = (char**)strList;
    while(*strListPtr) {
        free(*strListPtr++);
    }
    free(strList);

    return 0;
}

char* copy_str(const char* str) {
    char* strPtr = (char*)str;

    int len = 0;
    while(*strPtr++) {
        len++;
    }

    char* newStr = (char*)malloc(sizeof(char) * (len + 1));
    *(newStr + len) = 0;

    int idx = 0;
    while(idx < len) {
        *(newStr + idx) = *(str + idx);
        idx++;
    }

    return newStr;
}
int compare_each_str(const char* s1, const char* s2) {
    char* s1Ptr = (char*)s1;
    char* s2Ptr = (char*)s2;

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

void sort_heap(char** strList, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(strList, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        swap(strList, 0, idx);
        heapify(strList, idx--, 0);
    }

    return;
}
void heapify(char** strList, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    if(left < limitIdx && compare_each_str(*(strList + parent), *(strList + left)) < 0) {
        parent = left;
    }
    if(right < limitIdx && compare_each_str(*(strList + parent), *(strList + right)) < 0) {
        parent = right;
    }

    if(parent != currIdx) {
        swap(strList, parent, currIdx);
        heapify(strList, limitIdx, parent);
    }

    return;
}
void swap(char** strList, int i, int j) {
    char* tempStr = *(strList + i);
    *(strList + i) = *(strList + j);
    *(strList + j) = tempStr;

    return;
}

int binary_search(char** strList, char* target, int i, int j) {
    if(i > j) {
        return -1;
    }

    int midIdx = (i + j) / 2;

    int diffResult = compare_each_str(*(strList + midIdx), target);

    if(diffResult == 0) {
        return midIdx;
    } else if(diffResult < 0) {
        return binary_search(strList, target, midIdx + 1, j);
    } else {
        return binary_search(strList, target, i, midIdx - 1);
    }
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
