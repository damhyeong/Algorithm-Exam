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
1 초	128 MB	242698	139977	95904	58.364%

문제
---
N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.


입력
---
첫째 줄에 수의 개수 N(1 ≤ N ≤ 1,000)이 주어진다.

둘째 줄부터 N개의 줄에는 수가 주어진다.

이 수는 절댓값이 1,000보다 작거나 같은 정수이다.

수는 중복되지 않는다.


출력
---
첫째 줄부터 N개의 줄에 오름차순으로 정렬한 결과를 한 줄에 하나씩 출력한다.

예제 입력 1
5
5
2
3
4
1
예제 출력 1
1
2
3
4
5
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

void sort_quick(int* list, int start, int end);
void swap(int* list, int i, int j);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));

    int idx = 0;
    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        *(list + idx++) = parseInt(input);
    }

    sort_quick(list, 0, N - 1);

    idx = 0;
    while(idx < N) {
        char* tmpResult = intToStr(*(list + idx++));

        fputs(tmpResult, stdout); fputc('\n', stdout);

        free(tmpResult);
    }

    return 0;
}

void sort_quick(int* list, int start, int end) {
    if(start >= end) {
        return;
    }

    // pivot 은 이 메서드가 끝날 때 까지, 하나의 구심점으로서 사용된다.
    // 즉, list[pivot] 은 "선택된 중앙값" 으로서 활약한다.
    int pivot = start;
    int i = start;
    int j = end;

    while(i < j) {
        /**
        선택된 중앙값보다 크다면, 뒤에서부터 하나씩 인덱스가 내려온다.
        이 반복문의 의미는, 뒤 부분이 "중앙값보다 커야 한다" 를 의미한다.
        이 반복문이 멈춘다면, 그건 현재 pivot 인덱스의 값을 발견했거나,
        현재 pivot 인덱스(중앙값) 에 대해, 앞에 있어야 할 값을 "발견" 했을 때를 의미한다.
        */
        while(*(list + pivot) < *(list + j)) {
            j--;
        }

        /**
        교차 인덱스는 위에서 막아주고 있고,
        이 값은 앞에서부터 인덱스를 천천히 증가시키는데,
        즉, "중앙값보다 큰 값" 을 찾기 위해 반복하는 것이다.
        만약에 이 반복문이 멈추었다면,
        그것은 선택된 중앙값(pivot 인덱스) 보다 더 큰 값을 찾음을 의미한다.
        i < j 의 조건문은 i 와 j 가 교차, i > j 가 되버림을 막는다. (대신, i == j 가 될 수는 있음)
        */
        while(i < j && *(list + pivot) >= *(list + i)) {
            i++;
        }

        /**
        만약에 i >= j 상황이 아닌, 앞과 뒤에서 바꿔야 할 값을 찾아 고정시킨 상태라면,
        선택된 중앙값 pivot 에 대해, list[i] 는 pivot 보다 크기 때문에, "후반부" 로 이동해야 한다.
        선택된 중앙값 pivot 에 대해, list[j] 는 pivot 보다 작기 때문에, "전반부" 로 이동해야 한다.

        이에 대한 엘리먼트 값을 교환하면, 현재 증가되는 i, 감소되는 j 와 선택된 중앙값 pivot 인덱스에 대해 올바른 배열을 만드는 과정이다. (아직 끝나지 않음을 가정)
        */
        swap(list, i, j);
    }

    // 현재 중앙값(pivot) 에 대해 i < j 루프문이 종료되었다면, 실제로 중앙값 list[pivot] 을 중앙으로 이동시킨다.
    // 이 때, 중앙은 i 로 계산한다.
    swap(list, pivot, i);

    // 위의 i, j 즉, 선택된 중앙값 pivot 이 아닌 start, end 가 조건 (i < j) 에 따라 모두 루프되었다면,
    // 이제 선택된 중앙값인 pivot 을 기준으로 양방향으로 나누어 2 개의 재귀 메서드로 나눈다.
    sort_quick(list, start, i - 1);
    sort_quick(list, i + 1, end);
}
void swap(int* list, int i, int j) {
    int temp = *(list + i);
    *(list + i) = *(list + j);
    *(list + j) = temp;

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
