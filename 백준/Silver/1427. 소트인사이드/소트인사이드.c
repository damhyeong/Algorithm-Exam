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
2 초	128 MB	117383	77240	63467	66.064%

문제
---
배열을 정렬하는 것은 쉽다.

수가 주어지면, 그 수의 각 자리수를 내림차순으로 정렬해보자.


입력
---
첫째 줄에 정렬하려고 하는 수 N이 주어진다.

N은 1,000,000,000보다 작거나 같은 자연수이다.

출력
---
첫째 줄에 자리수를 내림차순으로 정렬한 수를 출력한다.

예제 입력 1
2143
예제 출력 1
4321
예제 입력 2
999998999
예제 출력 2
999999998
예제 입력 3
61423
예제 출력 3
64321
예제 입력 4
500613009
예제 출력 4
965310000
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);

void sort_heap(int* list, int length);
void heapify(int* list, int limitIdx, int currIdx);
void swap(int* list, int i, int j);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int number = parseInt(input);

    char* numStr = intToStr(number);
    char* numStrPtr = numStr;

    int length = 0;
    while(*numStrPtr++) {
        length++;
    }

    int* list = (int*)malloc(sizeof(int) * (length + 1));
    int* listPtr = list;

    numStrPtr = numStr;
    while(*numStrPtr) {
        *listPtr++ = *numStrPtr++ - '0';
    }

    free(numStr);

    sort_heap(list, length);

    int idx = length - 1;
    while(idx >= 0) {
        char* tmpNumStr = intToStr(*(list + idx--));
        fputs(tmpNumStr, stdout);
        free(tmpNumStr);
    }

    fputc('\n', stdout);

    return 0;
}

/**
 * 먼저 배열 자체를 트리로 치환한다. 이는 i 라는 인덱스에 대해 왼쪽, 오른쪽 자식을 2(i) + 1, 2(i) + 2 로 치환할 수 있다.
 * 내가 사용하는 힙 정렬은, 중간 단계와 마지막 단계가 존재한다.
 *
 * 중간 단계 : 자식을 가지는 최소 인덱스 (length / 2 - 1) 에서부터 0 까지 순회하며,
 *          list[0] 이 항상 가장 큰 값을 가진다. 그리고, 힙 트리 상 최대 힙을 만족한다.
 *          그러나, 이 상황은 정렬이 된 상태가 아니며, "list[0]" 이 항상 "가장 큰 값" 을 가지게 하는 데 초점을 둔다.
 *
 * 마지막 단계 : 중간 단계를 통해 힙 트리는 항상 자식보다 "더 큰 값" 을 가지게 되었다.
 *            그러나, 오름차순 정렬을 위해 실행하는 단계이다.
 *            length - 1 부터 1 까지 실행되며, 가장 큰 값을 가진 arr[0] 을, 현재 순회중인 i 에 넣는다.
 *            가장 큰 값을 "제한된 인덱스" 인 topIdx == i 이므로, heapify 를 통해 length - 1 EX == i 에 도달할 수 없다.
 *            즉, 마지막 단계는 순회 시 마다, 힙 트리의 정상을 "가장 큰 값" 으로 만들고, 이를 후미에 배치하는 것이다.
 */
void sort_heap(int* list, int length) {

    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(list, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        swap(list, 0, idx);

        heapify(list, idx--, 0);
    }

    return;
}
void heapify(int* list, int limitIdx, int currIdx) {
    // 인덱스가 벗어나는 것은 sort_heap 에서 관리한다.


    // 주어진 현재 인덱스는 하위 2 개의 인덱스 값을 참조해야 하므로, 부모 인덱스라고 말할 수 있다.
    int parent = currIdx;

    // 힙 트리 상, 왼쪽에 해당하는 인덱스. (0 : 부모, 1 : 왼쪽 자식, 2 : 오른쪽 자식)
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    /**
     * 선정된 왼쪽, 오른쪽 자식 인덱스는 우리가 지정해 놓은 인덱스 이상이 되면 안되며,
     * 자식 노드 중 더 큰 값이 있다면, 해당 값은 현재 인자로 들어온 currIdx 가 되어야 한다.
     * 그리고, 다시 heapify 로 재귀한다.
     */
    if(left < limitIdx && *(list + parent) < *(list + left)) {
        parent = left;
    }
    if(right < limitIdx && *(list + parent) < *(list + right)) {
        parent = right;
    }

    // 왼쪽 혹은 오른쪽 노드가 부모 노드보다 더 크기 때문에, 이를 바꾼 후 재귀를 통해 또 다시 계산한다.
    // 만약 상단에 비교적 아주 작은 값이 들어가 있다면, 이 재귀함수는 빈번하게 일어날 수 있다.
    // 만약 currIdx 가 하위 자식인 left, right 보다 더 큰 수라면, 부모 값이 맞으므로, 이 분기는 실행되지 않는다.
    if(parent != currIdx) {
        swap(list, parent, currIdx);

        heapify(list, limitIdx, parent);
    }
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
