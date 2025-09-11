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
평범한 배낭

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	175438	68550	42666	36.970%

문제
---
이 문제는 아주 평범한 배낭에 관한 문제이다.

한 달 후면 국가의 부름을 받게 되는 준서는 여행을 가려고 한다.

세상과의 단절을 슬퍼하며 최대한 즐기기 위한 여행이기 때문에, 가지고 다닐 배낭 또한 최대한 가치 있게 싸려고 한다.

준서가 여행에 필요하다고 생각하는 N개의 물건이 있다.

각 물건은 무게 W와 가치 V를 가지는데, 해당 물건을 배낭에 넣어서 가면 준서가 V만큼 즐길 수 있다.

아직 행군을 해본 적이 없는 준서는 최대 K만큼의 무게만을 넣을 수 있는 배낭만 들고 다닐 수 있다.

준서가 최대한 즐거운 여행을 하기 위해 배낭에 넣을 수 있는 물건들의 가치의 최댓값을 알려주자.


입력
---
첫 줄에 물품의 수 N(1 ≤ N ≤ 100)과

준서가 버틸 수 있는 무게 K(1 ≤ K ≤ 100,000)가 주어진다.

두 번째 줄부터 N개의 줄에 거쳐

각 물건의 무게 W(1 ≤ W ≤ 100,000)와

해당 물건의 가치 V(0 ≤ V ≤ 1,000)가 주어진다.

입력으로 주어지는 모든 수는 정수이다.

출력
---
한 줄에 배낭에 넣을 수 있는 물건들의 가치합의 최댓값을 출력한다.

예제 입력 1
4 7
6 13
4 8
3 6
5 12
예제 출력 1
14
*/

/**

약 100 줄 정도의 주석을 적었는데,

GPT 에 의해 이해하게 되어 모든 주석을 삭제한다.

다음에 이 문제를 풀게 된다면, 좀 더 생각을 하길 바란다. (이전 문제에서만 규칙을 찾지 말 것.) --> 점화식이 다름

순서가 중요하지 않다는 것을 기억 할 것.

이 문제를 이해하지 못하고 풀지 못한 내 지능이 한탄스럽다고 생각한 문제이다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* calloc(size_t size, size_t byte);
extern void* realloc(void* memory, size_t byte);

int* parseTwoNumber(const char* input);
void freeArrs(void** arrs);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int* parsed = parseTwoNumber(input);

    int N = *parsed; // column
    int K = *(parsed + 1); // row

    int** dps = (int**)malloc(sizeof(int*) * (K + 2));
    int iter = 0;
    while(iter <= K) {
        *(dps + iter++) = (int*)calloc(N + 2, sizeof(int));
    }

    int** arrs = (int**)malloc(sizeof(int*) * (N + 2));
    iter = 0;
    while(iter <= N) {
        *(arrs + iter++) = (int*)calloc(2 + 1, sizeof(int));
    }

    iter = 1;
    while(iter <= N) {
        fgets(input, sizeof(input), stdin);

        parsed = parseTwoNumber(input);

        *(*(arrs + iter)) = *parsed;
        *(*(arrs + iter) + 1) = *(parsed + 1);
        iter++;
    }

    int w = 1;
    while(w <= K) {
        int i = 1;
        while(i <= N) {
            int currW = *(*(arrs + i));
            int currV = *(*(arrs + i) + 1);

            if(currW > w) {
                *(*(dps + w) + i) = *(*(dps + w) + i - 1);
                i++;
                continue;
            }

            int tempResult1 = *(*(dps + w) + i - 1);
            int tempResult2 = *(*(dps + w - currW) + i - 1) + currV;

            *(*(dps + w) + i) = tempResult1 > tempResult2 ? tempResult1 : tempResult2;

            i++;
        }
        w++;
    }

    int result = *(*(dps + K) + N);
    char* resultStr = intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    free(parsed);

    freeArrs((void**)arrs);
    freeArrs((void**)dps);

    return 0;
}

int* parseTwoNumber(const char* input) {
    const char* inputPtr = (char*)input;

    int n1 = 0;
    int n2 = 0;

    while(!isBlank(*inputPtr)) {
        n1 *= 10;
        n1 += *inputPtr++ - '0';
    }

    inputPtr++;
    while(!isBlank(*inputPtr)) {
        n2 *= 10;
        n2 += *inputPtr++ - '0';
    }

    int* result = (int*)malloc(sizeof(int) * (2 + 1));
    *result = n1;
    *(result + 1) = n2;

    return result;
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
