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
2 초	256 MB	232931	99608	74492	40.974%

문제
---
알파벳 소문자로 이루어진 N개의 단어가 들어오면 아래와 같은 조건에 따라 정렬하는 프로그램을 작성하시오.

길이가 짧은 것부터
길이가 같으면 사전 순으로
단, 중복된 단어는 하나만 남기고 제거해야 한다.

입력
첫째 줄에 단어의 개수 N이 주어진다. (1 ≤ N ≤ 20,000) 둘째 줄부터 N개의 줄에 걸쳐 알파벳 소문자로 이루어진 단어가 한 줄에 하나씩 주어진다. 주어지는 문자열의 길이는 50을 넘지 않는다.

출력
조건에 따라 정렬하여 단어들을 출력한다.

예제 입력 1
13
but
i
wont
hesitate
no
more
no
more
it
cannot
wait
im
yours
예제 출력 1
i
im
it
no
but
more
wait
wont
yours
cannot
hesitate
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

typedef struct String {
    char* str;
    int length;

    void (*print)(struct String* this);
    int (*compare_to)(struct String* s1, struct String* s2);
} String;

void sort_heap(String** strList, int length);
void heapify(String** strList, int limitIdx, int currIdx);

void print_str(String* this);
int compare_to_str(String* s1, String* s2);

void freeStrList(String** strList);

String* parseString(const char* input);

int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    String** strList = (String**)malloc(sizeof(String*) * (N + 1));
    String** strListPtr = (String**)strList;

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        *strListPtr = parseString(input);

        strListPtr++;
    }

    sort_heap(strList, N);

    strListPtr = (String**)strList;

    String* prevStr = (String*)malloc(sizeof(String));
    prevStr->str = "1";
    prevStr->length = 1;
    prevStr->compare_to = compare_to_str;
    prevStr->print = print_str;

    while(*strListPtr) {
        String* tempStr = *strListPtr;

        if(prevStr->compare_to(prevStr, *strListPtr) == 0) {
            strListPtr++;
            continue;
        }

        prevStr = *strListPtr;

        strListPtr++;

        tempStr->print(tempStr);
    }

    freeStrList(strList);

    return 0;
}

void sort_heap(String** strList, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(strList, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        String* tempStr = *strList;
        *strList = *(strList + idx);
        *(strList + idx) = tempStr;

        heapify(strList, idx--, 0);
    }

    return;
}
void heapify(String** strList, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    if(left < limitIdx && compare_to_str(*(strList + parent), *(strList + left)) < 0) {
        parent = left;
    }
    if(right < limitIdx && compare_to_str(*(strList + parent), *(strList + right)) < 0) {
        parent = right;
    }

    if(parent != currIdx) {
        String* tempStr = *(strList + parent);
        *(strList + parent) = *(strList + currIdx);
        *(strList + currIdx) = tempStr;

        heapify(strList, limitIdx, parent);
    }
}


void print_str(String* this) {
    fputs(this->str, stdout); fputc('\n', stdout);

    return;
}
int compare_to_str(String* s1, String* s2) {
    int s1Len = s1->length;
    int s2Len = s2->length;

    char* str1 = s1->str;
    char* str1Ptr = str1;
    char* str2 = s2->str;
    char* str2Ptr = str2;

    if(s1Len == s2Len) {
        int result = 0;

        while(*str1Ptr) {
            char ch1 = *str1Ptr++;
            char ch2 = *str2Ptr++;

            if(ch1 < ch2) {
                result = -1;
                break;
            } else if(ch1 > ch2) {
                result = 1;
                break;
            }
        }
        return result;
    } else {
        return s1Len < s2Len ? -1 : 1;
    }
}

void freeStrList(String** strList) {
    String** strListPtr = (String**)strList;

    while(*strListPtr) {
        free(*strListPtr++);
    }
    free(strList);

    return;
}

String* parseString(const char* input) {
    char* inputPtr = (char*)input;

    int len = 0;
    while(isBlank(*inputPtr++) != 1) {
        len++;
    }

    char* result = (char*)malloc(sizeof(char) * (len + 1));
    *(result + len) = 0;

    inputPtr = (char*)input;
    char* resultPtr = (char*)result;

    int idx = 0;
    while(idx++ < len) {
        *resultPtr++ = *inputPtr++;
    }

    String* newStr = (String*)malloc(sizeof(String));
    newStr->str = result;
    newStr->length = len;

    newStr->print = print_str;
    newStr->compare_to = compare_to_str;

    return newStr;
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
