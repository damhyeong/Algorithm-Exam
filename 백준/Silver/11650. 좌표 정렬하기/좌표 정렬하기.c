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
1 초	256 MB	175428	86202	67261	49.002%

문제
---
2차원 평면 위의 점 N개가 주어진다.

좌표를 x좌표가 증가하는 순으로,

x좌표가 같으면 y좌표가 증가하는 순서로 정렬한 다음

출력하는 프로그램을 작성하시오.


입력
---
첫째 줄에 점의 개수 N (1 ≤ N ≤ 100,000)이 주어진다.

둘째 줄부터 N개의 줄에는 i번점의 위치 xi와 yi가 주어진다.

(-100,000 ≤ xi, yi ≤ 100,000) 좌표는 항상 정수이고, 위치가 같은 두 점은 없다.


출력
---
첫째 줄부터 N개의 줄에 점을 정렬한 결과를 출력한다.

예제 입력 1
5
3 4
1 1
1 -1
2 2
3 3
예제 출력 1
1 -1
1 1
2 2
3 3
3 4

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);


typedef struct Vector {
    int x; int y;

    int (*get_x)(struct Vector* this);
    int (*get_y)(struct Vector* this);
    void (*print)(struct Vector* this);
} Vector;

Vector* NewVector(int x, int y);
void freeVectorList(Vector** vecList);

int get_x_vec(Vector* this);
int get_y_vec(Vector* this);
void print_vec(Vector* this);
int compare_vec(Vector* this, Vector* another);

Vector** sort_merge_with_vector(Vector** vecList, int length);
Vector* copy_vector(Vector* target);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    Vector** vecList = (Vector**)malloc(sizeof(Vector*) * (N + 1));
    *(vecList + N) = NULL;

    int idx = 0;
    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = tokens;

        int x = parseInt(*tokensPtr++);
        int y = parseInt(*tokensPtr++);

        *(vecList + idx) = NewVector(x, y);

        freeTokens(tokens);

        idx++;
    }
    // 검증 완료

    vecList = sort_merge_with_vector(vecList, N);

    Vector** vecListPtr = (Vector**)vecList;
    idx = 0;
    while(*vecListPtr) {
        print_vec(*vecListPtr++);
    }

    freeVectorList(vecList);

    return 0;
}

Vector* NewVector(int x, int y) {
    Vector* vector = (Vector*)malloc(sizeof(Vector));

    vector->x = x;
    vector->y = y;

    vector->get_x = get_x_vec;
    vector->get_y = get_y_vec;
    vector->print = print_vec;

    return vector;
}
void freeVectorList(Vector** vecList) {
    Vector** vecListPtr = vecList;
    while(*vecListPtr) {
        free(*vecListPtr++);
    }
    free(vecList);
}

int get_x_vec(Vector* this) {
    return this->x;
}
int get_y_vec(Vector* this) {
    return this->y;
}
void print_vec(Vector* this) {
    char* xStr = intToStr(this->x);
    char* yStr = intToStr(this->y);

    fputs(xStr, stdout); fputc(' ', stdout); fputs(yStr, stdout); fputc('\n', stdout);

    free(xStr); free(yStr);

    return;
}
int compare_vec(Vector* this, Vector* another) {
    int thisX = this->x;
    int thisY = this->y;

    int diffX = another->x;
    int diffY = another->y;

    if(thisX == diffX) {
        if(thisY == diffY) {
            return 0;
        } else {
            return thisY < diffY ? -1 : 1;
        }
    } else {
        return thisX < diffX ? -1 : 1;
    }
}
Vector* copy_vector(Vector* target) {
    int x = target->get_x(target);
    int y = target->get_y(target);

    Vector* newVector = NewVector(x, y);

    return newVector;
}

Vector** sort_merge_with_vector(Vector** vecList, int length) {
    if(length <= 1) {
        return vecList;
    }

    int leftLen = length / 2;
    int rightLen = length - leftLen;

    Vector** leftVecList = (Vector**)malloc(sizeof(Vector*) * (leftLen + 1));
    *(leftVecList + leftLen) = NULL;
    Vector** rightVecList = (Vector**)malloc(sizeof(Vector*) * (rightLen + 1));
    *(rightVecList + rightLen) = NULL;

    int i = 0;
    int idx = 0;
    while(i < leftLen) {
        *(leftVecList + i++) = copy_vector(*(vecList + idx++));
    }
    i = 0;
    while(i < rightLen) {
        *(rightVecList + i++) = copy_vector(*(vecList + idx++));
    }

    freeVectorList(vecList);

    vecList = (Vector**)malloc(sizeof(Vector*) * (length + 1));
    *(vecList + length) = NULL;

    leftVecList = sort_merge_with_vector(leftVecList, leftLen);
    rightVecList = sort_merge_with_vector(rightVecList, rightLen);

    i = 0; idx = 0; int j = 0;

    while(i < leftLen && j < rightLen) {
        if(compare_vec(*(leftVecList + i), *(rightVecList + j)) < 0) {
            *(vecList + idx++) = copy_vector(*(leftVecList + i++));
        } else {
            *(vecList + idx++) = copy_vector(*(rightVecList + j++));
        }
    }

    while(i < leftLen) {
        *(vecList + idx++) = copy_vector(*(leftVecList + i++));
    }
    while(j < rightLen) {
        *(vecList + idx++) = copy_vector(*(rightVecList + j++));
    }

    freeVectorList(leftVecList); freeVectorList(rightVecList);

    return vecList;
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
