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
2 초	256 MB	382940	120149	84283	31.675%

문제
---
N개의 수가 주어졌을 때, 이를 오름차순으로 정렬하는 프로그램을 작성하시오.

입력
---
첫째 줄에 수의 개수 N(1 ≤ N ≤ 1,000,000)이 주어진다.

둘째 줄부터 N개의 줄에는 수가 주어진다.

이 수는 절댓값이 1,000,000보다 작거나 같은 정수이다.

수는 중복되지 않는다.


출력
---
첫째 줄부터 N개의 줄에 오름차순으로 정렬한 결과를 한 줄에 하나씩 출력한다.

예제 입력 1
5
5
4
3
2
1
예제 출력 1
1
2
3
4
5
*/
/**
 * 이번에는 시간복잡도를 고려하여 Merge Sort 로 진행.
 */

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

void sort_merge(int* list, int length);
void swap(int* list, int i, int j);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));
    int* listPtr = list;

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        *listPtr++ = parseInt(input);
    }

    sort_merge(list, N);

    idx = 0;
    listPtr = list;
    while(idx++ < N) {
        char* tmpStr = intToStr(*listPtr++);

        fputs(tmpStr, stdout); fputc('\n', stdout);

        free(tmpStr);
    }

    free(list);

    return 0;
}

void sort_merge(int* list, int length) {
    if(length <= 1) {
        return;
    }

    int leftLen = length / 2;
    int rightLen = length - (length / 2);

    int* leftList = (int*)malloc(sizeof(int) * (leftLen + 1));
    int* rightList = (int*)malloc(sizeof(int) * (rightLen + 1));

    int idx = 0;

    int i = 0;
    while(i < leftLen) {
        *(leftList + i++) = *(list + idx++);
    }
    i = 0;
    while(i < rightLen) {
        *(rightList + i++) = *(list + idx++);
    }

    sort_merge(leftList, leftLen);
    sort_merge(rightList, rightLen);

    i = 0; idx = 0;
    int j = 0;
    while(i < leftLen && j < rightLen) {
        if(*(leftList + i) <= *(rightList + j)) {
            *(list + idx++) = *(leftList + i++);
        } else {
            *(list + idx++) = *(rightList + j++);
        }
    }

    while(i < leftLen) {
        *(list + idx++) = *(leftList + i++);
    }
    while(j < rightLen) {
        *(list + idx++) = *(rightList + j++);
    }

    free(leftList); free(rightList);

    return;
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
