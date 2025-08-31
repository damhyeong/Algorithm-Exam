
/**
정수 삼각형

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	112202	66881	50714	60.271%

문제
---
        7
      3   8
    8   1   0
  2   7   4   4
4   5   2   6   5

위 그림은 크기가 5인 정수 삼각형의 한 모습이다.

맨 위층 7부터 시작해서 아래에 있는 수 중 하나를 선택하여 아래층으로 내려올 때, 이제까지 선택된 수의 합이 최대가 되는 경로를 구하는 프로그램을 작성하라.

아래층에 있는 수는 현재 층에서 선택된 수의 대각선 왼쪽 또는 대각선 오른쪽에 있는 것 중에서만 선택할 수 있다.

삼각형의 크기는 1 이상 500 이하이다.

삼각형을 이루고 있는 각 수는 모두 정수이며, 범위는 0 이상 9999 이하이다.


입력
---
첫째 줄에 삼각형의 크기 n(1 ≤ n ≤ 500)이 주어지고, 둘째 줄부터 n+1번째 줄까지 정수 삼각형이 주어진다.

출력
---
첫째 줄에 합이 최대가 되는 경로에 있는 수의 합을 출력한다.

예제 입력 1
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
예제 출력 1
30
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(const char* input);
void freeArrs(void** arrs);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[5000];

    fgets(input, sizeof(input), stdin);

    int n = parseInt(input);

    int** arrs = (int**)malloc(sizeof(int*) * (n + 1));
    int** dps = (int**)malloc(sizeof(int*) * (n + 1));

    int i = 0;
    while(i < n) {
        *(arrs + i) = (int*)malloc(sizeof(int) * (i + 2));
        *(dps + i) = (int*)malloc(sizeof(int) * (i + 2));

        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);
        char** tokensPtr = tokens;

        int j = 0;
        while(j <= i) {
            *(*(arrs + i) + j) = parseInt(*tokensPtr++);

            j++;
        }
        i++;
        freeArrs((void**)tokens);
    }

    *(*(dps)) = *(*(arrs));

    i = 1;
    while(i < n) {

        int j = 0;
        while(j <= i) {
            int curr = *(*(arrs + i) + j);

            int leftUpper = j == 0 ? -1 : *(*(dps + i - 1) + j - 1);
            int rightUpper = j == i ? -1 : *(*(dps + i - 1) + j);

            *(*(dps + i) + j) = (leftUpper > rightUpper ? leftUpper : rightUpper) + curr;
            j++;
        }
        i++;
    }

    int max = -1;
    int idx = 0;
    while(idx < n) {
        max = max < *(*(dps + n - 1) + idx) ? *(*(dps + n - 1) + idx) : max;
        idx++;
    }

    char* resultStr = intToStr(max);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    freeArrs((void**)arrs); freeArrs((void**)dps);


    return 0;
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
