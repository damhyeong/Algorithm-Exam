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
2 초	512 MB	124873	53893	40327	40.327%

문제
---
수직선 위에 N개의 좌표 X1, X2, ..., XN이 있다.

이 좌표에 좌표 압축을 적용하려고 한다.

Xi를 좌표 압축한 결과 X'i의 값은 Xi > Xj를 만족하는 서로 다른 좌표 Xj의 개수와 같아야 한다.

X1, X2, ..., XN에 좌표 압축을 적용한 결과

X'1, X'2, ..., X'N를 출력해보자.


입력
---
첫째 줄에 N이 주어진다.

둘째 줄에는 공백 한 칸으로 구분된 X1, X2, ..., XN이 주어진다.


출력
---
첫째 줄에 X'1, X'2, ..., X'N을 공백 한 칸으로 구분해서 출력한다.


제한
---
1 ≤ N ≤ 1,000,000
-10^9 ≤ X_i ≤ 10^9


예제 입력 1
5
2 4 -10 4 -9
예제 출력 1
2 3 0 3 1
예제 입력 2
6
1000 999 1000 999 1000 999
예제 출력 2
1 0 1 0 1 0
*/

/**
이 문제는 어떤 방법론을 적용할 것인지에 달려 있다.

이전에 Java 를 사용 할 때는 비교적 쉽게 사용했는데,

이번엔 이분 탐색을 적용해야 할 것 같다는 생각이 든다.

문제는, 정렬 후 중복값을 제거함에 있다.

1. 주어진 값을 정렬한다.

2. 토큰을 파싱하고 삭제하지 않는다. 즉, 마지막에 삭제한다. (출력에 이용할 예정)

3. 정렬된 값을 순회하며, 이전 값을 참조하여 삭제한다.

4. 삭제하는 과정은 "새로운 배열" 을 만들 것인지, "기존 배열" 내에서 해결 할 것인지 선택해야 한다.

5. 메모리 해제하지 않은 토큰을 다시 순회하며, 이분 탐색을 통해 미중복 배열의 인덱스를 찾는다.

6. 해당 인덱스를 하나씩 출력하며 결과물을 완성한다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

int binary_search_for_index(int* list, int target, int start, int end);

int* remove_same(int* list, int length);

void sort_heap(int* list, int length);
void heapify(int* list, int limitIdx, int currIdx);
void swap(int* list, int i, int j);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int length = 0; // 전역 변수 선언.

int main(void) {
    size_t inputSize = 200;
    char* input = (char*)malloc(sizeof(char) * (inputSize));

    fgets(input, (int)inputSize, stdin);

    int N = parseInt(input);

    inputSize = 20000000;
    input = (char*)malloc(sizeof(char) * (inputSize));
    fgets(input, inputSize, stdin);

    char** tokens = (char**)tokenizer(input);

    free(input);

    int* list = (int*)malloc(sizeof(int) * (N + 1));
    int idx = 0;
    while(idx < N) {
        char* currTkn = *(tokens + idx);
        *(list + idx) = parseInt(currTkn);
        idx++;
    }

    sort_heap(list, N);

    list = remove_same(list, N);

    idx = 0;
    while(idx < N) {
        int target = parseInt(*(tokens + idx));

        int findIdx = binary_search_for_index(list, target, 0, length - 1);

        char* tempStr = intToStr(findIdx);

        fputs(tempStr, stdout); fputc(' ', stdout);
        free(tempStr);

        idx++;
    }
    fputc('\n', stdout);

    return 0;
}

int binary_search_for_index(int* list, int target, int start, int end) {
    int middle = (start + end) / 2;

    if(start >= end) {
        return *(list + middle) == target ? middle : -1;
    }

    int midNum = *(list + middle);
    if(midNum == target) {
        return middle;
    } else if(midNum < target) {
        return binary_search_for_index(list, target, middle + 1, end);
    } else {
        return binary_search_for_index(list, target, start, middle - 1);
    }

}

int* remove_same(int* list, int len) {
    int prevNum = -100000100; // 초기화
    int idx = 0; // 순회용
    int i = 0; // 중복 제거용 인덱스
    while(idx < len) {
        int currNum = *(list + idx);

        if(prevNum != currNum) {
            swap(list, i, idx);
            i++;
            prevNum = currNum;
        }

        idx++;
    }

    int* newList = (int*)realloc(list, sizeof(int) * (i));
    length = i;

    return newList;
}

void sort_heap(int* list, int length) {
    int i = length / 2 - 1;
    while(i >= 0) {
        heapify(list, length, i--);
    }

    i = length - 1;
    while(i > 0) {
        swap(list, 0, i);
        heapify(list, i, 0);
        i--;
    }
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
}
void swap(int* list, int i, int j) {
    int temp = *(list + i);
    *(list + i) = *(list + j);
    *(list + j) = temp;

    return;
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
