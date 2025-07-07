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
1 초	128 MB	60167	28295	25672	47.468%
문제
삼각형의 세 변의 길이가 주어질 때 변의 길이에 따라 다음과 같이 정의한다.

Equilateral :  세 변의 길이가 모두 같은 경우
Isosceles : 두 변의 길이만 같은 경우
Scalene : 세 변의 길이가 모두 다른 경우
단 주어진 세 변의 길이가 삼각형의 조건을 만족하지 못하는 경우에는 "Invalid" 를 출력한다. 예를 들어 6, 3, 2가 이 경우에 해당한다. 가장 긴 변의 길이보다 나머지 두 변의 길이의 합이 길지 않으면 삼각형의 조건을 만족하지 못한다.

세 변의 길이가 주어질 때 위 정의에 따른 결과를 출력하시오.

입력
각 줄에는 1,000을 넘지 않는 양의 정수 3개가 입력된다. 마지막 줄은 0 0 0이며 이 줄은 계산하지 않는다.

출력
각 입력에 맞는 결과 (Equilateral, Isosceles, Scalene, Invalid) 를 출력하시오.

예제 입력 1
7 7 7
6 5 4
3 2 5
6 2 6
0 0 0
예제 출력 1
Equilateral
Scalene
Invalid
Isosceles
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

_Bool isValid(const int* list);
int sameCount(const int* list);
_Bool isEqual(const char* s1, const char* s2);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    while(isEqual(fgets(input, sizeof(input), stdin), "0 0 0") != 1) {
        int size = 3;
        int* intList = (int*)malloc(sizeof(int) * (size + 1));
        *(intList + size) = 0;

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        int idx = 0;
        while(idx < size) {
            int num = parseInt(*tokensPtr++);
            *(intList + idx++) = num;
        }

        freeTokens(tokens);

        int same = sameCount(intList);

        _Bool valid = isValid(intList);

        if(valid == 1) {
            if(same == 3) {
                fputs("Equilateral\n", stdout);
            } else if(same == 2) {
                fputs("Isosceles\n", stdout);
            } else {
                fputs("Scalene\n", stdout);
            }
        } else {
            fputs("Invalid\n", stdout);
        }
    }

    return 0;
}

_Bool isValid(const int* list) {
    int biggest = -1;
    int biggestIdx = 0;
    int idx = 0;
    while(idx < 3) {
        int num = *(list + idx);
        if(biggest < num) {
            biggest = num;
            biggestIdx = idx;
        }

        ++idx;
    }

    idx = 0;
    int tempTotal = 0;
    while(idx < 3) {
        if(biggestIdx != idx) {
            tempTotal += *(list + idx);
        }
        idx++;
    }

    if(biggest < tempTotal) {
        return 1;
    } else {
        return 0;
    }
}

int sameCount(const int* list) {

    int same = 1;
    int currNum = 0;

    int idx = 0;
    while(idx < 3) {
        int num = *(list + idx++);

        if(currNum == num) {
            same++;
        } else {
            currNum = num;
        }
    }

    if(same == 1 && *list == *(list + 2)) {
        same = 2;
    }

    return same;
}

_Bool isEqual(const char* s1, const char* s2) {
    char* s1Ptr = (char*)s1;
    char* s2Ptr = (char*)s2;

    _Bool isSame = 1;

    while(*s2Ptr) {
        char ch1 = *s1Ptr++; char ch2 = *s2Ptr++;

        if(ch1 != ch2) {
            isSame = 0;
            break;
        }
    }

    return isSame;
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

int parseInt(const char* str) {
    int result = 0;
    int sign = 1;

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
