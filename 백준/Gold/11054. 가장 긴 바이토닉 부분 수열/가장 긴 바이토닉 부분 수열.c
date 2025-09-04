/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "코드를 보다가 궁금하시면 EMAIL 로 연락 주셔도 괜찮습니다!"

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.


    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!

    참고로, AI 작성 글이 아니라, 진짜 공식문서 뒤져가면서 힘들게 얻은 지식을 나눠보려고 합니다.
*/

/**
가장 긴 바이토닉 부분 수열

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	65570	34142	26691	51.580%

문제
---
수열 S가 어떤 수 Sk를 기준으로 S1 < S2 < ... Sk-1 < Sk > Sk+1 > ... SN-1 > SN을 만족한다면,

그 수열을 바이토닉 수열이라고 한다.

예를 들어,

{10, 20, 30, 25, 20}과 {10, 20, 30, 40}, {50, 40, 25, 10} 은 바이토닉 수열이지만,

{1, 2, 3, 2, 1, 2, 3, 2, 1} 과 {10, 20, 30, 40, 20, 30} 은 바이토닉 수열이 아니다.

수열 A가 주어졌을 때, 그 수열의 부분 수열 중 바이토닉 수열이면서 가장 긴 수열의 길이를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 수열 A의 크기 N이 주어지고, 둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다.

(1 ≤ N ≤ 1,000, 1 ≤ A_i ≤ 1,000)

출력
---
첫째 줄에 수열 A의 부분 수열 중에서 가장 긴 바이토닉 수열의 길이를 출력한다.


예제 입력 1
10
1 5 2 1 4 3 4 5 2 1
예제 출력 1
7

힌트
---
예제의 경우 {1 5 2 1 4 3 4 5 2 1}이 가장 긴 바이토닉 부분 수열이다.
*/

/**
이번에는 바로 직전 문제인, 가장 긴 증가 부분 수열 문제의 연장선이라고 생각한다.



*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void binary_and_insert(int* list, int start, int end, int newNum);

char** tokenizer(const char* input);
void freeArrs(void** arrs);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main(void) {
    char input[10000];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (N + 2));

    // 리스트와 같은 길이지만, 단순하게 flexible 배열을 의미한다. (up, down)
    int* up = (int*)malloc(sizeof(int) * (N + 2));
    int upSize = 0;
    int* down = (int*)malloc(sizeof(int) * (N + 2));
    int downSize = 0;

    int* upDp = (int*)malloc(sizeof(int) * (N + 2));
    int* downDp = (int*)malloc(sizeof(int) * (N + 2));

    fgets(input, sizeof(input), stdin);
    char** tokens = tokenizer(input);
    char** tokensPtr = tokens;


    int idx = 1;
    while(idx <= N) {
        *(list + idx++) = parseInt(*tokensPtr++);
    }

    freeArrs((void**)tokens);

    // up 리스트 - 오름차순 감지
    idx = 1;
    while(idx <= N) {
        int num = *(list + idx);

        if(*(up + upSize) < num) {
            upSize++;
            *(up + upSize) = num;
        } else {
            binary_and_insert(up, 0, upSize, num);
        }

        *(upDp + idx) = upSize;

        idx++;
    }

    idx = N;
    while(idx >= 1) {
        int num = *(list + idx);

        if(*(down + downSize) < num) {
            downSize++;
            *(down + downSize) = num;
        } else {
            binary_and_insert(down, 0, downSize, num);
        }

        *(downDp + idx) = downSize;

        idx--;
    }

    int max = -1;
    idx = 1;
    while(idx <= N) {
        int upVal = *(upDp + idx);
        int downVal = *(downDp + idx);

        max = (upVal + downVal) > max ? (upVal + downVal) : max;

        idx++;
    }

    char* resultStr = intToStr(max - 1);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    free(list); free(up); free(down);
    free(upDp); free(downDp);

    return 0;
}

void binary_and_insert(int* list, int start, int end, int newNum) {
    int mid = (start + end) / 2;

    if(start > end) {
        *(list + end + 1) = newNum;

        return;
    }

    int midNum = *(list + mid);

    if(midNum == newNum) {
        return;
    } else if(midNum > newNum) {
        binary_and_insert(list, 0, mid - 1, newNum);
    } else { // midNum < newNum
        binary_and_insert(list, mid + 1, end, newNum);
    }

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
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
    free(arrs);

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
    *result = sign == 1 ? *result : '-';

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
