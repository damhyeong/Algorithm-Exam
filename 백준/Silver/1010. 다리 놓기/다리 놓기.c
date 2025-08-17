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
다리 놓기 성공

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
0.5 초 (추가 시간 없음)	128 MB	127426	60175	48794	48.279%

문제
---
재원이는 한 도시의 시장이 되었다.

이 도시에는 도시를 동쪽과 서쪽으로 나누는 큰 일직선 모양의 강이 흐르고 있다.

하지만 재원이는 다리가 없어서 시민들이 강을 건너는데 큰 불편을 겪고 있음을 알고 다리를 짓기로 결심하였다.

강 주변에서 다리를 짓기에 적합한 곳을 사이트라고 한다.

재원이는 강 주변을 면밀히 조사해 본 결과 강의 서쪽에는 N개의 사이트가 있고 동쪽에는 M개의 사이트가 있다는 것을 알았다.

(N ≤ M)

재원이는 서쪽의 사이트와 동쪽의 사이트를 다리로 연결하려고 한다.

(이때 한 사이트에는 최대 한 개의 다리만 연결될 수 있다.)

재원이는 다리를 최대한 많이 지으려고 하기 때문에 서쪽의 사이트 개수만큼 (N개) 다리를 지으려고 한다.

다리끼리는 서로 겹쳐질 수 없다고 할 때 다리를 지을 수 있는 경우의 수를 구하는 프로그램을 작성하라.


입력
---
입력의 첫 줄에는 테스트 케이스의 개수 T가 주어진다. 그 다음 줄부터 각각의 테스트케이스에 대해 강의 서쪽과 동쪽에 있는 사이트의 개수 정수 N, M (0 < N ≤ M < 30)이 주어진다.

출력
---
각 테스트 케이스에 대해 주어진 조건하에 다리를 지을 수 있는 경우의 수를 출력한다.

예제 입력 1
3
2 2
1 5
13 29
예제 출력 1
1
5
67863915
*/
/**
    0   1   2   3   4   5   6 - 선택 수
1   1   1
2   1   2   1
3   1   3   3   1
4   1   4   6   4   1
5   1   5   10  10  5   1
6   1   6   15  20  15  6   1
-
최대 수

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(long long target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main(void) {
    int max_size = 30;
    long** ansList = (long**)malloc(sizeof(long*) * (max_size + 1));

    int i = 0;
    while(i <= max_size) {
        *(ansList + i++) = (long*)calloc(max_size + 1, sizeof(long));
    }

    i = 0;
    while (i <= max_size) {
        ansList[i][0] = 1;
        ansList[i][i] = 1;
        i++;
    }

    i = 2;
    int j;
    while(i <= max_size) {
        j = 1;
        while(j < i) {
            long left = *(*(ansList + i - 1) + j - 1);
            long right = *(*(ansList + i - 1) + j);

            *(*(ansList + i) + j) = left + right;

            j++;
        }
        i++;
    }


    char input[255];

    fgets(input, sizeof(input), stdin);

    int T = parseInt(input);
    int idx = 0;
    while(idx++ < T) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);
        char** tokensPtr = tokens;

        int N = parseInt(*tokensPtr++);
        int M = parseInt(*tokensPtr++);

        if(N > (M / 2)) {
            N = M - N;
        }

        freeTokens(tokens);

        fputs(intToStr(*(*(ansList + M) + N)), stdout); fputc('\n', stdout);
    }
    
    

    return 0;
}


char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

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
            char* newTknPtr = newTkn;

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

char* intToStr(long long target) {
    int sign = 1;
    int len = 0;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    long long temp = target;
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
