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
영단어 암기는 괴로워

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (추가 시간 없음)	1024 MB	32142	14889	11848	45.761%

문제
---
화은이는 이번 영어 시험에서 틀린 문제를 바탕으로 영어 단어 암기를 하려고 한다.

그 과정에서 효율적으로 영어 단어를 외우기 위해 영어 단어장을 만들려 하고 있다.

화은이가 만들고자 하는 단어장의 단어 순서는 다음과 같은 우선순위를 차례로 적용하여 만들어진다.

1. 자주 나오는 단어일수록 앞에 배치한다.
2. 해당 단어의 길이가 길수록 앞에 배치한다.
3. 알파벳 사전 순으로 앞에 있는 단어일수록 앞에 배치한다

M 보다 짧은 길이의 단어의 경우 읽는 것만으로도 외울 수 있기 때문에

길이가 M 이상인 단어들만 외운다고 한다.

화은이가 괴로운 영단어 암기를 효율적으로 할 수 있도록 단어장을 만들어 주자.

입력
---
첫째 줄에는 영어 지문에 나오는 단어의 개수 N 과 외울 단어의 길이 기준이 되는 M 이 공백으로 구분되어 주어진다.

(1 <= N <= 100_000, 1 <= M <= 10)

둘째 줄 부터 N + 1 번째 줄 까지 외울 단어를 입력받는다.

이 때의 입력은 알파벳 소문자로만 주어지며 단어의 길이는 10 을 넘지 않는다.

단어장에 단어가 반드시 1개 이상 존재하는 입력만 주어진다.


출력
---
화은이의 단어장에 들어 있는 단어를 단어장의 앞에 위치한 단어부터 한 줄에 한 단어씩 순서대로 출력한다.

예제 입력 1
7 4
apple
ant
sand
apple
append
sand
sand
예제 출력 1
sand
apple
append
예제 입력 2
12 5
appearance
append
attendance
swim
swift
swift
swift
mouse
wallet
mouse
ice
age
예제 출력 2
swift
mouse
appearance
attendance
append
wallet
*/

#include<stdio.h>


extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct String String;

struct String {
    int len;
    int times;
    char* str;

    int (*compare)(String* s1, String* s2);
};

String* NewString(const char* str, int times);
int compare_string(String* s1, String* s2);

void sort_heap(String** strList, int length);
void heapify(String** strList, int limitIdx, int currIdx);
void swap(String** strList, int i, int j);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    char** tokens = tokenizer(input);
    char** tokensPtr = tokens;

    int N = parseInt(*tokensPtr++);
    int M = parseInt(*tokensPtr++);

    freeTokens(tokens);

    // flexible arr 를 만들기 위함.
    int size = 5;
    int currSize = 0;

    String** strList = (String**)malloc(sizeof(String*) * (size + 1));
    String** strListPtr = strList;

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);

        char* str = *tokens;
        char* strPtr = str;

        int len = 0;
        while(*strPtr++) {
            len++;
        }

        if(len < M) {
            freeTokens(tokens);
            continue;
        }

        String* newStr = NewString(str, len);

        *strListPtr++ = newStr; currSize++;

        if(size == currSize) {
            size *= 2;
            strList = (String**)realloc(strList, sizeof(String*) * (size + 1));
            strListPtr = (String**)(strList + currSize);
        }
    }
    *strListPtr = NULL;

    sort_heap(strList, currSize);

    // 재사용
    currSize = 0;
    int currTimes = 1;
    strListPtr = strList;
    String* currStr = *strListPtr++;

    while(*strListPtr) {
        String* str = *strListPtr++;

        if(!compare_string(currStr, str)) {
            currTimes++;
        } else {
            *(strList + currSize++) = currStr;
            currStr->times = currTimes;

            currStr = str;
            currTimes = 1;
        }
    }
    *(strList + currSize++) = currStr;
    currStr->times = currTimes;


    sort_heap(strList, currSize);

    idx = 0;
    while(idx < currSize) {
        String* tmpStr = *(strList + idx++);

        fputs(tmpStr->str, stdout); fputc('\n', stdout);
    }


    return 0;
}

String* NewString(const char* str, int times) {
    String* newStr = (String*)malloc(sizeof(String));

    newStr->str = (char*)str;
    newStr->times = times;
    newStr->compare = compare_string;
    newStr->len = 0;

    char* strPtr = (char*)str;
    while(*strPtr++) {
        newStr->len++;
    }

    return newStr;
}
int compare_string(String* s1, String* s2) {
    char* s1Ptr = s1->str;
    char* s2Ptr = s2->str;

    if(s1->times == s2->times) {
        if(s1->len == s2->len) {
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
        } else {
            return s1->len > s2->len ? -1 : 1;
        }
    } else {
        return s1->times > s2->times ? -1 : 1;
    }
}

void sort_heap(String** strList, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(strList, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        swap(strList, 0, idx);
        heapify(strList, idx, 0);
        idx--;
    }

    return;
}
void heapify(String** strList, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    int (*compare)(String* s1, String* s2) = ((String*)*strList)->compare;

    if(left < limitIdx && compare(*(strList + parent), *(strList + left)) < 0) {
        parent = left;
    }
    if(right < limitIdx && compare(*(strList + parent), *(strList + right)) < 0) {
        parent = right;
    }

    if(parent != currIdx) {
        swap(strList, parent, currIdx);
        heapify(strList, limitIdx, parent);
    }

    return;
}
void swap(String** strList, int i, int j) {
    String* tmpStr = *(strList + i);
    *(strList + i) = *(strList + j);
    *(strList + j) = tmpStr;

    return;
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* inputPtr = (char*)input;
    int start = 0;
    int end = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch)) {
            if(start == end) {
                start = ++end;
                continue;
            }

            int tknSize = end - start;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(start != end) {
                *newTknPtr++ = input[start++];
            }
            *tokensPtr++ = newTkn; currSize++;

            start = ++end;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = tokens;
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
        sign =-1;
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

    while(!isBlank(*strPtr)) {
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
