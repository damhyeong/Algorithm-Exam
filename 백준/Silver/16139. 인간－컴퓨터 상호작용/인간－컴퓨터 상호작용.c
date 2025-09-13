
/**
인간-컴퓨터 상호작용

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초 (추가 시간 없음)	256 MB	32182	9239	7341	29.987%

문제
---
승재는 인간-컴퓨터 상호작용에서 생체공학 설계를 공부하다가 키보드 자판이 실용적인지 궁금해졌다.

이를 알아보기 위해 승재는 다음과 같은 생각을 했다.

'문자열에서 특정 알파벳이 몇 번 나타나는지 알아봐서

자주 나타나는 알파벳이 중지나 검지 위치에 오는 알파벳인지 확인하면 실용적인지 확인할 수 있을 것이다.'


승재를 도와 특정 문자열 S, 특정 알파벳 a 와 문자열의 구간 [l, r] 이 주어지면,

S 의 l 번째 문자부터 r 번째 문자 사이에 a 가 몇 번 나타나는지 구하는 프로그램을 작성하여라.

승재는 문자열의 문자는 0 번째부터 세며, l 번째와 r 번째 문자를 포함해서 생각한다.

주의할 점은 승재는 호기심이 많기에, (통계적으로 크게 무의미하지만) 같은 문자열을 두고 질문을 q 번 할 것이다.


입력
---
첫 줄에 문자열 S 가 주어진다.

문자열의 길이는 200,000 자 이하이며, 알파벳 소문자로만 구성되었다.

두 번째 줄에는 질문의 수 q 가 주어지며, 문제의 수는 1 <= q <= 200,000 을 만족한다.

세 번째 줄부터 (q + 2) 번째 줄에는 질문이 주어진다.

각 질문은 알파벳 소문자 a_i 와 0 <= l_i <= r_i < |S| 를 만족하는

정수 l_i, r_i 가 공백으로 구분되어 주어진다.


서브태스크 1 (50점)
---
문자열의 길이는 2,000 자 이하, 질문의 수는 2,000 개 이하이다.


서브태스크 2 (50점)
---
추가 제한 조건이 없다.

예제 입력 1
seungjaehwang
4
a 0 5
a 0 6
a 6 10
a 7 10
예제 출력 1
0
1
2
1
*/

/**
각 알파벳에 대해 누적값을 조회하려 한다면 분명히 시간초과 에러가 나는 문제이다.

즉, a ~ z 까지의 누적값을 담을 2 차원 배열을 만들어야 한다.

주소는 a ~ z , 내부의 누적값을 담을 배열은 최대 200,000 개여야 한다.

즉, 약 23? * 200,000 이 만들어질 수 있는 최대 2차원 배열이다. --> O(N^2) 에 해당하긴 한다. 그러나, 최대 460 만 번 계산한다는 의미.

---

질문의 수도 최대 200,000 개 인데,

각 질문은 2차원 배열에 쌓인 누적합을 단순히 한 번 계산하면 되는 문제라서, 여기는 O(N) 에 해당한다.

---

즉, 최대 문자열과, 최대 질문의 개수가 주어졌을 때,

총 계산양은 460만 + 20 만 (동적 할당 및 조건절 비교 등등을 제외하고. 넣으면 끝이 없을 듯)

480만 정도가 된다.

*/

#include <stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* parseStr(FILE* stream, int* lenStat);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(FILE* stream, const char* str);
_Bool isBlank(char ch);

int main(void) {
    int len;
    char* str = parseStr(stdin, &len);

    int** alphabetList = (int**)malloc(sizeof(int*) * ('z' - 'a' + 2));

    int idx = 0;
    while(idx < ('z' - 'a' + 1))
        *(alphabetList + idx++) = (int*)calloc(len + 2, sizeof(int));

    idx = 0;
    while(idx < len) {
        // 자연스럽게 1 번째를 노리도록 ++.
        char ch = *(str + idx++);

        int jdx = 0;
        while(jdx < ('z' - 'a' + 1)) {
            if(jdx == (ch - 'a'))
                *(*(alphabetList + jdx) + idx) = *(*(alphabetList + jdx) + idx - 1) + 1;
            else
                *(*(alphabetList + jdx) + idx) = *(*(alphabetList + jdx) + idx - 1);
            jdx++;
        }
    }

    int loop = parseInt(stdin, NULL);

    idx = 0;
    while(idx++ < loop) {
        char** tokens = tokenizer(stdin);

        int a = **tokens - 'a';
        int l = parseInt(NULL, *(tokens + 1)) + 1;
        int r = parseInt(NULL, *(tokens + 2)) + 1;

        freeArrs((void**)tokens);

        int* tmpLine = *(alphabetList + a);

        int tmpResult = *(tmpLine + r) - *(tmpLine + l - 1);

        char buf[32];
        char* result = intToStr(tmpResult, sizeof(buf), buf);
        fputs(result, stdout); fputc('\n', stdout);
    }

    free(str); freeArrs((void**)alphabetList);


    return 0;
}

// 하나의 토큰(단어) 는 최대 100 자를 가질 수 있으며, 그 이상 가질 시 Buffer Overflow 에러가 난다.
char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* buf = (char*)malloc(sizeof(char) * (100 + 1));
    char* bufPtr = buf;
    int tknSize = 0;

    char ch = 0;
    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0) {
                continue;
            }
            *bufPtr = 0;

            buf = (char*)realloc(buf, sizeof(char) * (tknSize + 1));

            *tokensPtr++ = buf;

            buf = (char*)malloc(sizeof(char) * (100 + 1));
            bufPtr = buf;
            tknSize = 0;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            tknSize++;
            *bufPtr++ = ch;
        }

        if(ch == '\n') {
            break;
        }
    }

    free(buf);

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

char* parseStr(FILE* stream, int* lenStat) {
    int size = 5;
    int curr = 0;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    char* resultPtr = result;

    char ch = -1;
    while(!isBlank(ch = fgetc(stream))) {
        *resultPtr++ = ch; curr++;

        if(size == curr) {
            size *= 2;
            result = (char*)realloc(result, sizeof(char) * (size + 1));
            resultPtr = (char*)(result + curr);
        }
    }
    *resultPtr = 0;

    *lenStat = curr;

    return result;
}

char* intToStr(int target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long temp = target;
    if(target < 0)
        temp *= -1;


    do {
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0)
        *--bufPtr = '-';

    return bufPtr;
}
int parseInt(FILE* stream, const char* str) {
    int sign = 1;
    int result = 0;

    if(stream == NULL) {
        char* strPtr = (char*)str;
        if(*strPtr == '-') {
            sign = -1;
            strPtr++;
        }

        while(!isBlank(*strPtr)) {
            result *= 10;
            result += *strPtr++ - '0';
        }
    } else {
        char ch = fgetc(stream);
        if(ch == '-') {
            sign = -1;
            ch = fgetc(stream);
        }

        while(!isBlank(ch)) {
            result *= 10;
            result += ch - '0';
            ch = fgetc(stream);
        }
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
