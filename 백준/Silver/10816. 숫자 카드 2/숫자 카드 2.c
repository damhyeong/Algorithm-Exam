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
1 초	256 MB	188058	76496	54422	38.876%
문제
숫자 카드는 정수 하나가 적혀져 있는 카드이다. 상근이는 숫자 카드 N개를 가지고 있다. 정수 M개가 주어졌을 때, 이 수가 적혀있는 숫자 카드를 상근이가 몇 개 가지고 있는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 상근이가 가지고 있는 숫자 카드의 개수 N(1 ≤ N ≤ 500,000)이 주어진다. 둘째 줄에는 숫자 카드에 적혀있는 정수가 주어진다. 숫자 카드에 적혀있는 수는 -10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다.

셋째 줄에는 M(1 ≤ M ≤ 500,000)이 주어진다. 넷째 줄에는 상근이가 몇 개 가지고 있는 숫자 카드인지 구해야 할 M개의 정수가 주어지며, 이 수는 공백으로 구분되어져 있다. 이 수도 -10,000,000보다 크거나 같고, 10,000,000보다 작거나 같다.

출력
첫째 줄에 입력으로 주어진 M개의 수에 대해서, 각 수가 적힌 숫자 카드를 상근이가 몇 개 가지고 있는지를 공백으로 구분해 출력한다.

예제 입력 1
10
6 3 2 10 10 10 -10 -10 7 3
8
10 9 -5 2 3 4 5 -10
예제 출력 1
3 0 0 1 2 0 0 2
*/

/**
이 문제를 푸는 방식은, 원시값 int 배열을 사용하여 정렬 후, 이진 탐색을 통해 엘리먼트의 개수를 알아내는 방법과,

실제로 HashMap 을 구현하여 푸는 방법이 있다.

현재 시간 제한이 1초인데, 이 시간이면 HashMap 을 사용하는 것이 더 유리 할 수도 있다.

그러나, 한번 원시값 배열로 도전해 보겠다.

1. 입력된 배열 정렬 (HeapSort)

2. 입력된 검색값 이진 검색 (Binary_sort) - 중복 값 중 가장 앞 인덱스를 추출

3. 추출된 맨 앞 인덱스로부터 같은 값이 몇 번 나오는지 확인.

---

특이사항 :

하나의 줄이 최대 500 만 줄 까지 늘어날 수도 있다. (+-천만 == 8 or 9) and (N (Max) --> 500,000) and 빈칸 ==> 대략 최대가 500만?

---

1 차 시도 이후 :

62 퍼센트쯤에서 "시간 초과" 로 문제를 통과하지 못했다.

침을 삼키며 바라봤는데, 역시 커스텀으로 통과하는 것은 어렵다고 느낀다.

문제는 찾으려는 수의 첫 번째 인덱스를 가져와서, 동일한 수를 세는 과정에서 발생한 것이다.

이를 저장해서 해결한다면, 시간을 굉장히 단축 할 수 있다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

void sort_heap(int* list, int length);
void heapify(int* list, int limitIdx, int currIdx);
void swap(int* list, int i, int j);

// 중복 값 발견 시, 맨 앞의 인덱스를 전달한다.
int binary_search(int* list, int target, int i, int j);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    const int MAX_LINE = 5000000;
    const int NORMAL_LINE = 255;

    char* input = (char*)malloc(sizeof(char) * (NORMAL_LINE + 1));
    *(input + NORMAL_LINE) = 0;

    fgets(input, (int)NORMAL_LINE, stdin);

    int N = parseInt(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));
    int* record = (int*)malloc(sizeof(int) * (N + 1));

    free(input);

    input = (char*)malloc(sizeof(char) * (MAX_LINE + 1));
    *(input + MAX_LINE) = 0;

    fgets(input, (int)MAX_LINE, stdin);

    char** tokens = (char**)tokenizer(input);

    free(input);

    int idx = 0;
    while(idx < N) {
        int currNum = parseInt(*(tokens + idx));
        *(list + idx) = currNum;
        idx++;
    }

    freeTokens(tokens);

    sort_heap(list, N);

    idx = N - 1;
    int tempNum = *(list + idx);
    int totalNum = 0;
    while(idx >= 0) {
        int currNum = *(list + idx);

        if(tempNum == currNum) {
            totalNum++;
        } else {
            *(record + idx + 1) = totalNum;
            totalNum = 1;
            tempNum = currNum;
        }

        idx--;
    }
    *(record) = totalNum;

    input = (char*)malloc(sizeof(char) * (NORMAL_LINE + 1));
    *(input + NORMAL_LINE) = 0;

    fgets(input, NORMAL_LINE, stdin);

    int M = parseInt(input);

    free(input);

    input = (char*)malloc(sizeof(char) * (MAX_LINE + 1));
    *(input + MAX_LINE) = 0;

    fgets(input, MAX_LINE, stdin);

    tokens = (char**)tokenizer(input);

    free(input);

    idx = 0;
    while(idx < M) {
        int extNum = parseInt(*(tokens + idx));

        int startIdx = binary_search(list, extNum, 0, N - 1);

        if(startIdx == -1) {
            fputs("0 ", stdout);
        } else {
            // int tmpNum = *(list + startIdx);
            // int tmpTotal = 0;
            // int jdx = startIdx;
            // while(jdx < N && *(list + jdx) == tmpNum) {
            //     tmpTotal++;
            //     jdx++;
            // }

            int recordNum = *(record + startIdx);

            char* resultStr = intToStr(recordNum);

            fputs(resultStr, stdout); fputc(' ', stdout);

            free(resultStr);
        }

        idx++;
    }
    fputc('\n', stdout);

    freeTokens(tokens);

    free(list);

    return 0;
}

void sort_heap(int* list, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(list, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        swap(list, idx, 0);
        heapify(list, idx, 0);
        idx--;
    }

    return;
}
void heapify(int* list, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    if(left < limitIdx && *(list + parent) < *(list + left)) {
        parent = left;
    }
    if(right < limitIdx && *(list + parent) < *(list + right)) {
        parent = right;
    }

    if(parent != currIdx) {
        swap(list, parent, currIdx);
        heapify(list, limitIdx, parent);
    }

    return;
}
void swap(int* list, int i, int j) {
    int temp = *(list + i);
    *(list + i) = *(list + j);
    *(list + j) = temp;

    return;
}

// 중복 값 발견 시, 맨 앞의 인덱스를 전달한다.
int binary_search(int* list, int target, int i, int j) {
    if(i > j) {
        return -1;
    }

    int midIdx = (i + j) / 2;
    int midNum = *(list + midIdx);

    if(midNum < target) {
        return binary_search(list, target, midIdx + 1, j);
    } else { // midNum >= target
        int result = binary_search(list, target, i, midIdx - 1);

        if(result == -1 && target == midNum) {
            return midIdx;
        } else {
            return result;
        }
    }
}

char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = (char**)tokens;

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
            char* newTknPtr = (char*)newTkn;

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
