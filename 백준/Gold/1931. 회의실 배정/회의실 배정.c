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
회의실 배정

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	128 MB	262618	89844	61797	31.747%

문제
---
한 개의 회의실이 있는데 이를 사용하고자 하는 N개의 회의에 대하여 회의실 사용표를 만들려고 한다.

각 회의 I에 대해 시작시간과 끝나는 시간이 주어져 있고,

각 회의가 겹치지 않게 하면서 회의실을 사용할 수 있는 회의의 최대 개수를 찾아보자.

단, 회의는 한번 시작하면 중간에 중단될 수 없으며 한 회의가 끝나는 것과 동시에 다음 회의가 시작될 수 있다.

회의의 시작시간과 끝나는 시간이 같을 수도 있다.

이 경우에는 시작하자마자 끝나는 것으로 생각하면 된다.


입력
---
첫째 줄에 회의의 수 N(1 ≤ N ≤ 100,000)이 주어진다.

둘째 줄부터 N+1 줄까지 각 회의의 정보가 주어지는데 이것은 공백을 사이에 두고 회의의 시작시간과 끝나는 시간이 주어진다.

시작 시간과 끝나는 시간은 2^31-1보다 작거나 같은 자연수 또는 0이다.


출력
---
첫째 줄에 최대 사용할 수 있는 회의의 최대 개수를 출력한다.

예제 입력 1
11
1 4
3 5
0 6
5 7
3 8
5 9
6 10
8 11
8 12
2 13
12 14
예제 출력 1
4
*/

/**
이건 다이나믹 프로그래밍 기법 중에, Flex 배열을 사용하면 될 것 같다. (Stack 이랑 비슷하게.)

배열 마지막의 x1, y1 이 존재 할 때,

새로운 비교 엘리먼트 x2, y2 를 비교해야 한다면,

비교 조건에 따라 뒤에 붙거나, 내부의 엘리먼트들을 검색하여 대체하는 방식으로.

---

혹은, 100,000 길이의 2차원 배열을 만드는 것도 방법일 것 같다.

그런데, 십만 * 십만 수준의 크기라서, 안된다.

기준이

1. 최대 회의의 수
2. 포함시킬 수 있는 모든 엘리먼트의 수

이기 때문이다.

만약에 두 기준 중 하나를 "시간" 기준으로 대체한다고 하면, 그건 몇천배 메모리를 증가시키는 상황일 것이다.

---

그렇다면, 문제를 기준으로 "앞" 과 "뒤" 로 구분될 수 있는 기준을 세워보자.

그 전에, 맨 앞의 "시작 시간" 을 기준으로 정렬해야 한다. --> 엘리먼트 배열을 앞으로 전부 한칸씩 옮기는 불필요 계산을 방지.

예를 들어, 현재 flex 배열 내부에 { [0, 0], [1, 6], ... } 이 있을 때, [1, 1] 을 비교 및 추가해야 한다면,

{ [0, 0], [1, 1], [1, 6], ... } 배열이 되어야 한다.

그런데, 이 과정에서 [1, 1] 앞의 무수한 정보들은 전부 인덱스 상으로 +1 로 이동해야 한다는 것이다.

이를 방지하기 위해 오름차순 정렬 후 시작한다. (시작 시작 비교 && 끝나는 시간 비교)

---
0 6
1 4
2 13
3 5
3 8
5 7
5 9
6 10
8 11
8 12
12 14
---

입력을 정렬한 위의 상태에서, "앞" 그리고 "뒤" 가 존재하는 Flexible 배열을 만들자.

이 배열이 완성된다면, 배열의 길이는 사용할 수 있는 회의의 "최대 개수" 가 된다.

주어진 시간에 대해서 하나씩 배열에 추가할 때,

어떤 시간이 "앞" 이고, "뒤" 이어야 하는지 구해보자.

마지막 엘리먼트를 x1, y1 으로 가정하고, 현재 비교 엘리먼트를 x2, y2 라고 가정한다.

flex 누적 배열은 초기화로 [0, 0] 을 기본으로 포함하고 시작한다.

###

현재 누적 배열 : { [0, 0] } --> 현재 비교 엘리먼트 [0, 6]

x1 : 0, y1 : 0
x2 : 0, y2 : 6

--> y1 <= x2 이므로, 뒤에 새로 붙는다.

(회의가 끝난 후, 회의가 정상적으로 시작될 수 있으므로.)

결과 : { [0, 0], [0, 6] }

###

현재 누적 배열 : { [0, 0], [0, 6] } --> 현재 비교 엘리먼트 [1, 4]

x1 : 0, y1 : 6
x2 : 1, y2 : 4

x1 < x2 && y1 > y2 이므로, 내부에서 탐색을 통해 엘리먼트를 교체한다.

--> 마지막 엘리먼트인 [0, 6] 보다, [1, 4] 가 더 효율적인 시간대를 가지고 있다.

x1 : 0, y1 : 0
x2 : 1, y2 : 4
현재 비교 : [1, 4] --> [0, 0] 뒤에 붙을 수 있는 시간대이다.

따라서, [0, 0] 앞에 있는 엘리먼트를 [1, 4] 로 교체한다.

결과 : { [0, 0], [1, 4] }

###

현재 누적 배열 : { [0, 0], [1, 4] } --> 현재 비교 엘리먼트 [2, 13]

x1 : 1, y1 : 4
x2 : 2, y2 : 13 --> x1 <= x2 && y1 < y2 라서, 무시한다.

결과 : { [0, 0], [1, 4] }

###

현재 누적 배열 : { [0, 0], [1, 4] } --> 현재 비교 엘리먼트 [3, 5]

x1 : 1, y1 : 4
x2 : 3, y2 : 5 --> x1 <= x2 && y1 < y2 이기에, 무시한다.

결과 : { [0, 0], [1, 4] }

###

현재 누적 배열 : { [0, 0], [1, 4] } --> 현재 비교 엘리먼트 [3, 8]

x1 : 1, y1 : 4
x2 : 3, y2 : 8 --> x1 <= x2 && y1 < y2 이기 때문에 무시한다.

결과 : { [0, 0], [1, 4] }

###

현재 누적 배열 : { [0, 0], [1, 4] } --> 현재 비교 엘리먼트 [5, 7]

x1 : 1, y1 : 4
x2 : 5, y2 : 7 --> y1 <= x2 이기 때문에, 뒤에 추가한다. (회의 추가 가능)

결과 : { [0, 0], [1, 4], [5, 7] }

###

현재 누적 배열 : { [0, 0], [1, 4], [5, 7] } --> 현재 비교 엘리먼트 [5, 9]

x1 : 5, y1 : 7
x2 : 5, y2 : 9 --> x x1 <= x2 && y1 < y2 이기 때문에, 무시한다.

결과 : { [0, 0], [1, 4], [5, 7] }

###

현재 누적 배열 : { [0, 0], [1, 4], [5, 7] } --> 현재 비교 엘리먼트 [6, 10]

x1 : 5, y1 : 7
x2 : 6, y2 : 10 --> y1 > x2 상황에서, x1 <= x2 && y1 < y2 이기 때문에 무시한다.

결과 : { [0, 0], [1, 4], [5, 7] }

###

현재 누적 배열 : { [0, 0], [1, 4], [5, 7] } --> 현재 비교 엘리먼트 [8, 11]

x1 : 5, y1 : 7
x2 : 8, y2 : 11 --> y1 <= x2 이기 때문에, 뒤에 추가한다.

결과 : { [0, 0], [1, 4], [5, 7], [8, 11] }

###

현재 누적 배열 : { [0, 0], [1, 4], [5, 7], [8, 11] } --> 현재 비교 엘리먼트 [8, 12]

x1 : 8, y1 : 11
x2 : 8, y2 : 12 --> y1 > x2 이며,  x1 <= x2 && y1 < y2 이기 때문에, 무시한다.

결과 : { [0, 0], [1, 4], [5, 7], [8, 11] }

###

현재 누적 배열 : { [0, 0], [1, 4], [5, 7], [8, 11] } --> 현재 비교 엘리먼트 [12, 14]

x1 : 8, y1 : 11
x2 : 12, y2 : 14 --> y1 <= x2 이기 때문에, 뒤에 추가한다.

결과 : { [0, 0], [1, 4], [5, 7], [8, 11], [12, 14] }

---

최종 누적 배열의 길이는, 4 가 된다. ( [0, 0] 은 누적 배열의 초기화용이기 때문에 뺀다.)

---

그런데, 이런 생각이 들었다.

"굳이 Flex 누적 배열로 풀 이유가 있을까?"

다른 입력들을 고려해 보았을 때,

입력을 정렬 후, 위와 같은 알고리즘으로 최대 길이를 구한다고 하면,

x1 : 0, y1 : 0 으로 변수를 설정 해 둔 후,

정렬된 입력들을 하나씩 꺼내어 비교했을 때, (x2, y2)

조건에 맞는다면, x1, y1 만 변경하여, 변경 된 횟수를 측정하면 되지 않나? 생각이 들었다.

(만약, [5, 5], [5, 5] 상황이라면, 이것도 변경 된 횟수로 인정한다는 가정.)

---

x, y 가 변하는 조건에 따라, 그 횟수를 측정하는 방식이라면,

"정렬" 에만 시간을 쏟고, 정렬된 입력들을 순회하며 측정하는 방식으로 길이를 알아낼 수 있다.

초기 변수 x, y 를 둘다 0 으로 두고, 비교하면 된다.

단, [3, 3], [3, 3] 을 비교할 경우, [3, 3] --> [3, 3] 으로 변경하는 로직을 추가하여 측정한다.

1. x1 == x2 && y1 == y2 일 경우 변경.
2. x2 <= y1 일 경우 변경 (뒤에 추가한다는 로직.)
3. x1 <= x2 && y1 >= y2 일 경우, 변경 --> 하지만, 횟수는 추가하지 않음.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void sort_heap(int** arrs, int length);
void heapify(int** arrs, int limitIdx, int currIdx);
void swap_elem(int** arrs, int i, int j);
int compare_elem(int* e1, int* e2);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(int target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {
    int N = parseInt(NULL, stdin);

    int** arrs = (int**)malloc(sizeof(int*) * (N + 1));
    int idx = 0;
    while(idx < N){
        *(arrs + idx) = (int*)malloc(sizeof(int) * (2 + 1));

        char** tokens = tokenizer(stdin);

        // fputs(*tokens, stdout); fputc(' ', stdout); fputs(*(tokens + 1), stdout); fputc('\n', stdout);

        *(*(arrs + idx)) = parseInt(*tokens, NULL);
        *(*(arrs + idx) + 1) = parseInt(*(tokens + 1), NULL);

        freeArrs((void**)tokens);
        idx++;
    }

    sort_heap(arrs, N);

    int result = 0;
    int x1 = 0, y1 = 0;
    idx = 0;
    while(idx < N) {
        int x2 = *(*(arrs + idx));
        int y2 = *(*(arrs + idx) + 1);

        _Bool isOptimize = (x1 <= x2 && y1 >= y2) ? 1 : 0;
        _Bool isNext = (y1 <= x2) ? 1 : 0;
        if(y1 == x2 && x2 == y2) {
            result++;
        } else if(isOptimize) {
            x1 = x2; y1 = y2;
        } else if(isNext) {
            x1 = x2; y1 = y2;
            result++;
        }

        idx++;
    }

    char buf[32];
    char* resultStr = intToStr(result, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

void sort_heap(int** arrs, int length) {
    int idx = (length / 2) - 1;
    while(idx >= 0)
        heapify(arrs, length, idx--);

    idx = length - 1;
    while(idx > 0) {
        swap_elem(arrs, 0, idx);
        heapify(arrs, idx--, 0);
    }

    return;
}
void heapify(int** arrs, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    if(left < limitIdx && compare_elem(*(arrs + parent), *(arrs + left)) > 0)
        parent = left;

    if(right < limitIdx && compare_elem(*(arrs + parent), *(arrs + right)) > 0)
        parent = right;

    if(parent != currIdx) {
        swap_elem(arrs, parent, currIdx);
        heapify(arrs, limitIdx, parent);
    }

    return;
}
void swap_elem(int** arrs, int i, int j) {
    int* temp = *(arrs + i);
    *(arrs + i) = *(arrs + j);
    *(arrs + j) = temp;
    return;
}
int compare_elem(int* e1, int* e2) {
    int x1 = *e1;
    int y1 = *(e1 + 1);
    int x2 = *e2;
    int y2 = *(e2 + 1);

    if(x1 != x2)
        return x1 < x2 ? 1 : -1;

    if(y1 != y2)
        return y1 < y2 ? 1 : -1;

    return 0;
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    int tknSize = 0;
    char ch;
    int bufSize = 100;
    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    *(buf + bufSize) = 0;
    char* bufPtr = buf;

    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0) {
                continue;
            }

            *bufPtr = 0;
            *tokensPtr++ = realloc(buf, sizeof(char) * (tknSize + 1));
            curr++;

            bufSize = 100;
            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            bufPtr = buf; tknSize = 0;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch;
            tknSize++;

            if(tknSize == bufSize) {
                bufSize *= 2;
                buf = (char*)realloc(buf, sizeof(char) * (bufSize + 1));
                bufPtr = (char*)(buf + tknSize);
            }
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

char* intToStr(int target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long temp = target;
    if(target < 0) {
        temp *= -1;
    }

    do {
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0) {
        *--bufPtr = '-';
    }

    return bufPtr;
}
int parseInt(const char* str, FILE* stream) {
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

        while(!isBlank(ch) && ch != -1) {
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
