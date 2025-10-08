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
행렬 제곱

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	50448	18499	14631	35.066%

문제
---
크기가 N*N인 행렬 A가 주어진다.

이때, A의 B제곱을 구하는 프로그램을 작성하시오.

수가 매우 커질 수 있으니, A^B의 각 원소를 1,000으로 나눈 나머지를 출력한다.

입력
---
첫째 줄에 행렬의 크기 N과 B가 주어진다.

(2 ≤ N ≤  5, 1 ≤ B ≤ 100,000,000,000)

둘째 줄부터 N개의 줄에 행렬의 각 원소가 주어진다.

행렬의 각 원소는 1,000보다 작거나 같은 자연수 또는 0이다.

출력
---
첫째 줄부터 N개의 줄에 걸쳐 행렬 A를 B제곱한 결과를 출력한다.

예제 입력 1
2 5
1 2
3 4
예제 출력 1
69 558
337 406
예제 입력 2
3 3
1 2 3
4 5 6
7 8 9
예제 출력 2
468 576 684
62 305 548
656 34 412
예제 입력 3
5 10
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
1 0 0 0 1
예제 출력 3
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
512 0 0 0 512
*/

/**
이번에는 단순 수의 제곱을 구하는 것이 아니라, 행렬에 대한 거대한 제곱을 구하는 문제가 나왔다.

다행히도 크기는 N * N 으로 제한되기 때문에, 크기가 동적인가 에 대해 걱정할 필요는 없어졌다.

이전에 사용했던 방식을 사용하면 되는데,

5^1000000 이라고 가정 할 때,

A = 5, B = 1000000, C= 1000 (A 는 기반 수, B 는 제곱 수, C = 나머지 계산 수)

여기서 재귀를 통해, 양 갈래로 나누어 지는 것이 아니라,

B 를 절반으로 나누었을 때, 홀수인지, 짝수인지에 따라 다른 return 문을 작성하면 된다.

따라서, 만약에 제곱수가 21 억 쯤 된다 하면, 재귀를 수십번만 하면 된다는 것이다.

---

여기서 문제는, "행렬" 이라는 부분에 있다.

내가 현재 진행하는 방식은 모든 메모리의 통제 및 유틸리티 작성에 있으므로,

무엇이 필요할지 예측하여 미리 함수들을 작성해야 한다.

---

이번에는 A 에 해당하는 값이 단순 수가 아니라, "행렬" 이다.

B / 2 가 짝수 일 경우, 재귀결과 * 재귀결과 이며,
B / 2 가 홀수 일 경우, 재귀결과 * 재귀결과 * A 이다.

A 는 재귀로 주소가 전달되어 "재사용" 할 수 있지만,

재귀 결과는 재사용 하기 어렵다. (가능한 방식이 있겠지만 조금 더 생각해 봐야 할 듯)

N * N 배열이므로, 따로 재귀 결과 보관용 배열을 만들어 전달하면 어떨까? 생각이 든다.

그렇다면, 인자로 A = 원래 행렬 배열, B = 제곱수(정수), C = 나머지 계산 수, D = 재귀 결과 보관용

이렇게 하면 괜찮을 것 같다는 생각이 들었다.

그래도, 하나의 함수 내에서 결국 동적 2 차원 배열을 생성해야 한다.

이유는, 행렬의 계산 과정 상, D = D * .. 하기가 어렵다. 계산 과정에 아직 있는 행렬을 변경하면 계산 결과가 틀리기 때문이다.

---

그렇다면, 결국 계산 결과를 담기 위한 행렬을 생성해야 한다는 결과에 이르른다.

D 로 재귀 결과를 보관하는 것이 아니라, 그냥 2차원 동적 배열을 생성 한 후, return 하면 된다는 결과에 이른다.

그나마 다행인 것은, 양방향 재귀가 아니기 때문에, 수십만 이상의 동적 다차원 배열을 만들 필요는 없다는 것이다.

다시 돌아온다면, A, B, C 로 실행 할 수 있다.


*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

long** newArrs(long i, long j, long** dest);
long getCellResult(long** arrs1, long** arrs2, long i, long j, long N);
long** mulMatrix(long** arrs1, long** arrs2, long N, long** target);
long** divAndConquer(long** A, long B, long C, long N);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* longToStr(long target, long bufSize, char* buf);
long parselong(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {
    char** tokens = tokenizer(stdin);
    long N = parselong(*tokens, NULL);
    long B = parselong(*(tokens + 1), NULL);

    freeArrs((void**)tokens);

    long** A = newArrs(N, N, NULL);

    long idx = 0;
    while(idx < N) {
        tokens = tokenizer(stdin);

        long jdx = 0;
        while(jdx < N) {
            *(*(A + idx) + jdx) = parselong(*(tokens + jdx), NULL);

            jdx++;
        }
        freeArrs((void**)tokens);

        idx++;
    }

    long** resultArrs = divAndConquer(A, B, 1000, N);

    char buf[32];
    idx = 0;
    while(idx < N) {
        long jdx = 0;
        while(jdx < N) {
            char* tmpStr = longToStr(*(*(resultArrs + idx) + jdx), sizeof(buf), buf);
            fputs(tmpStr, stdout); fputc(' ', stdout);

            jdx++;
        }
        fputc('\n', stdout);
        idx++;
    }

    freeArrs((void**)resultArrs);

    return 0;
}

long** newArrs(long i, long j, long** dest) {
    long** tmpArrs = (long**)malloc(sizeof(long*) * (i + 1));
    *(tmpArrs + i) = NULL;
    long idx = 0;
    while(idx < i) {
        *(tmpArrs + idx++) = (long*)calloc(j + 1, sizeof(long));
    }

    if(dest == NULL)
        return tmpArrs;

    idx = 0;
    while(idx < i) {
        long jdx = 0;
        while(jdx < j) {
            *(*(tmpArrs + idx) + jdx) = *(*(dest + idx) + jdx) % 1000;
            jdx++;
        }
        idx++;
    }

    return tmpArrs;
}
long getCellResult(long** arrs1, long** arrs2, long i, long j, long N) {
    long result = 0;

    long idx = 0;
    while(idx < N) {
        long n1 = *(*(arrs1 + i) + idx);
        long n2 = *(*(arrs2 + idx) + j);

        result += n1 * n2;
        idx++;
    }

    return result % 1000;
}

long** mulMatrix(long** arrs1, long** arrs2, long N, long** target) {

    long idx = 0;
    while(idx < N) {
        long jdx = 0;
        while(jdx < N) {
            *(*(target + idx) + jdx) = getCellResult(arrs1, arrs2, idx, jdx, N);

            jdx++;
        }
        idx++;
    }

    return target;
}
long** divAndConquer(long** A, long B, long C, long N) {
    if(B == 0 || B == 1) {
        if(B == 1) {
            return newArrs(N, N, A);
        }
        long** newArr = newArrs(N, N, NULL);

        long i = 0;
        while(i < N) {
            *(*(newArr + i) + i) = 1;

            i++;
        }
    }

    long** tmpResult = divAndConquer(A, B / 2, C, N);

    long** newArr = newArrs(N, N, NULL);
    if(B % 2 == 0) {
        long** tempArrs = mulMatrix(tmpResult, tmpResult, N, newArr);
        freeArrs((void**)tmpResult);

        return tempArrs; // tempArrs == newArr 주소 동일
    } else {
        long** temp1Arr = mulMatrix(tmpResult, tmpResult, N, newArr);

        freeArrs((void**)tmpResult);

        newArr = newArrs(N, N, NULL);

        long** temp2Arr = mulMatrix(temp1Arr, A, N, newArr);
        freeArrs((void**)temp1Arr);

        // temp2Arr == newArr 주소 동일
        return temp2Arr;
    }
}

char** tokenizer(FILE* stream) {
    long size = 5;
    long curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

    long tknSize = 0;
    char ch;

    long bufSize = 20;
    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    *(buf + bufSize) = 0;
    char* bufPtr = buf;

    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(!tknSize)
                continue;

            *bufPtr = 0;
            *tokensPtr++ = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            curr++;

            tknSize = 0;
            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            *(buf + bufSize) = 0;
            bufPtr = buf;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch; tknSize++;
        }


        if(ch == '\n')
            break;
    }
    free(buf);

    *tokensPtr = NULL;

    return tokens;
}
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr)
        free(*arrsPtr++);
    free(arrs);

    return;
}

char* longToStr(long target, long bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long temp = target;
    temp = target < 0 ? -temp : temp;

    do {
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0)
        *--bufPtr = '-';

    return bufPtr;
}
long parselong(const char* str, FILE* stream) {
    long sign = 1;
    long result = 0;

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
    if(ch == 32 || ch == 0)
        return 1;
    else if(ch >= 9 && ch <= 13)
        return 1;
    else
        return 0;
}
