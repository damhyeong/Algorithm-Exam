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
인사성 밝은 곰곰이

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	27509	12761	10766	47.717%

문제
---
인사하는 곰곰이

알고리즘 입문방 오픈 채팅방에서는 새로운 분들이 입장을 할 때마다 곰곰티콘을 사용해 인사를 한다.

이를 본 문자열 킬러 임스는 채팅방의 기록을 수집해 그 중 곰곰티콘이 사용된 횟수를 구해 보기로 했다.

ENTER는 새로운 사람이 채팅방에 입장했음을 나타낸다.

그 외는 채팅을 입력한 유저의 닉네임을 나타낸다.

닉네임은 숫자 또는 영문 대소문자로 구성되어 있다.

새로운 사람이 입장한 이후 처음 채팅을 입력하는 사람은 반드시 곰곰티콘으로 인사를 한다.

그 외의 기록은 곰곰티콘을 쓰지 않은 평범한 채팅 기록이다.

채팅 기록 중 곰곰티콘이 사용된 횟수를 구해보자!

입력
---
첫 번째 줄에는 채팅방의 기록 수를 나타내는 정수 N 이 주어진다.

(1 <= N <= 100_000)

두 번째 줄 부터 N 개의 줄에 걸쳐 새로운 사람의 입장을 나타내는 ENTER, 혹은 채팅을 입력한 유저의 닉네임이 문자열로 주어진다.

(1 <= 문자열 길이 <= 20)

첫 번째 주어지는 문자열은 무조건 ENTER이다.

출력
---
채팅 기록 중 곰곰티콘이 사용된 횟수를 출력하시오.

예제 입력 1
9
ENTER
pjshwa
chansol
chogahui05
lms0806
pichulia
r4pidstart
swoon
tony9402
예제 출력 1
8

예제 입력 2
7
ENTER
pjshwa
chansol
chogahui05
ENTER
pjshwa
chansol
예제 출력 2
5

첫번째 새로운 사람이 들어온 뒤  pjshwa, chansol, chogahui05은 모두 곰곰티콘으로 인사했다.

두번째 새로운 사람이 들어온 뒤  pjshwa와 chansol은 다시 곰곰티콘으로 인사했다.

예제 입력 3
3
ENTER
lms0806
lms0806
예제 출력 3
1

lms0806은 새로운 사람이 들어왔으므로 처음은 곰곰티콘으로 인사하고, 그 뒤로는 일반 채팅을 했다.
*/

/**
문제를 찬찬히 읽고, 이는 "ENTER" 문자열이 들어올 때,

그 다음 "ENTER" 입력이 들어 올 때 까지, HashSet 에 유저의 이름들을 집어넣고,

사이즈를 측정하여 지속적으로 누적하여 푸는 문제라는 것을 인지했다.

즉, "ENTER" 이후에 출력된, 중복되지 않은 이름의 수는 몇 개인지 파악해야 한다는 것이다.

---

이 문제의 대체 풀이법을 생각해 보니까, 유연한 char** 배열을 마련하고,

"ENTER" 문자를 입력받거나, 프로그램이 종료 했을 때,

1. 들어온 배열을 정렬한다.
2. 중복되지 않은 이름의 개수를 구한다.

이러한 방식으로도 누적하여 구할 수 있다는 것을 캐치했다.

즉, 구조체가 아닌 원시값 2차원 배열로도 해결할 수 있다.

---

그러나, 근본적으로 HashSet 보다 논리가 최적화 되는 것은 아니다.

HashSet 은 중복값을 자체적으로 없애주며, 결과 사이즈도 내장되어 있다.

그러나, 원시값 배열을 자체적으로 정렬하여 비중복 크기를 계산 할 경우,

중복값들이 들어있는 상태에서 정렬 할 뿐만 아니라, 다시 비중복 크기를 계산하기 위해 루프를 돌려야 한다.

이 때, 내 생각에 스치는 것이, 두 문자열의 비교 과정을 굉장히 간소화 시키며, 유니크화 시킨다면 최적화가 가능하다는 것이다.

물론, 이것이 가능해 질 경우, HashSet + 비교 최적화가 훨씬 더 최적화 논리에 해당하긴 한다.

---

그렇다면, 문자열 간의 비교 최적화는 어떻게 진행해야 하는가?

기존의 문자열 비교는 이러한 방식으로 진행되었다.

1. 비교 함수는 두 문자열의 포인터를 가져와서, 두 포인터를 옮기며 차례로 하나씩 비교한다.
2. 이 때, 부가적인 메타 데이터는 존재하지 않는다. - 진짜 문자열만 비교하여 앞뒤를 비교해야 한다.
3. 컨벤션적으로 정해져 있는 정렬 방식을 선택하며, 이는 전적으로 문자열 포인터에 의존한다. (값 비교)
4. 만약에, 비교 대상이 서로 다르다면 빠르지만, 비교 대상이 일치한다면 긴 문자열이더라도, 비교를 위해 모든 문자열을 비교해야 한다.

나는 그런 생각이 들었다.

서로 다른 문자열을 가진 상황에서는 빠른 비교가 가능하다.

그러나, 같은 문자열을 가진 상황에서는 빠른 비교가 불가능하므로,

이를 계산할 수 있는 특수 메타데이터를 주입하는 것은 어떨까?

---

주소는 메타데이터가 될 수 없다. 그 이유는 내용물이 동일하더라도, 서로 다른 주소를 가지기 때문이다.

그렇다면, 서로 같은 데이터를 가진 메타데이터를 어떻게 생성해 내야 할까?

나는 문자열이 동일하기 위한 조건을 나열해 보았다.

1. 길이
2. 각 인덱스와 배치된 문자

그렇다면, 길이와 더불어, 각 인덱스에 배치된 문자들을 조합하여 큰 숫자로 곱하고,

그것을 나머지 연산을 수행하면 정수로 판가름 할 수 있는 메타데이터가 될 수 있을 것이라고 생각했다.

순서는 상관이 없다. 그저, 메타데이터의 Unique 함을 보장할 수 있으며, 내용물이 완벽히 동일할 경우,

그 메타데이터가 동일함을 보장해야 한다.

C 에서는 Language Virtual Machine 처럼, 메모리 주소에 할당된 값들의 메타데이터를 저장하지 않으므로,

이것을 직접 구조체로 구현해야 한다.

완벽한 메타데이터의 독립성을 보장하기 위해, 256 * 256 * 256 * ..... * 256 정도의 아주 큰 수가 메타데이터가 되어야 한다고도 생각한다.

하지만, 그 정도의 입력이 들어올 거라고 생각하지 않는다. EX - 21 억 개 이상의 천문학 적인 개수

이건 물론 경우에 따른 것이긴 하지만, 나는 이를 이용하여 정렬을 하려고 한다. (동일 입력만 걸러내면 되기 때문.)
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct String {
    int len;
    // int metadata;

    char* str;
    int (*compare)(struct String* s1, struct String* s2);
} String;

String* NewString(char* str);
int compare_str(String* s1, String* s2);

void freeStrList(String** strList);

long createMeta(const char* str);

void sort_heap(String** strList, int length);
void heapify(String** strList, int limitIdx, int currIdx);

void swap(void** arr, int i, int j);

char* parseStr(const char* input);
char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int isEnter(const char* str) {
    char s1[] = "ENTER";
    char* s1Ptr = s1;
    char* s2Ptr = (char*)str;

    while(*s1Ptr && *s2Ptr) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }
    }

    int result = *s1Ptr ? 1 : *s2Ptr ? -1 : 0;

    return result;
}

int getDiff(String** strList) {
    if(*strList == NULL) {
        return 0;
    }

    int result = 1;
    String* currStr = *strList;
    strList++;

    while(*strList) {
        int tmpResult = ((String*)*strList)->compare(currStr, *strList);

        if(tmpResult == 0){
            strList++;
            continue;
        } else {
            result++;
            currStr = ((String*)*strList);
        }
        strList++;
    }

    return result;
}

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);
    int total = 0;

    _Bool enterMode = 0;

    int size = 5;
    int currSize = 0;
    String** strList = (String**)malloc(sizeof(String*) * (size + 1));
    String** strListPtr = strList;
    *strList = NULL;

    int idx = 0;
    while(idx++ < N) {

        fgets(input, sizeof(input), stdin);
        char* new = parseStr(input);

        if(isEnter(new) == 0) {

            enterMode = 1;

            *strListPtr = NULL;

            sort_heap(strList, currSize);

            total += getDiff(strList);

            freeStrList(strList);

            size = 5;
            currSize = 0;
            strList = (String**)malloc(sizeof(String*) * (size + 1));
            strListPtr = strList;
            *strListPtr = NULL;

            continue;
        }

        if(enterMode != 1) {
            continue;
        }

        String* newStr = NewString(new);
        *strListPtr++ = newStr; currSize++;

        if(size == currSize) {
            size *= 2;
            strList = (String**)realloc(strList, sizeof(String*) * (size + 1));
            strListPtr = (String**)(strList + currSize);
        }
    }
    *strListPtr = NULL;

    if(currSize != 0) {
        sort_heap(strList, currSize);

        total += getDiff(strList);
    }


    char* resultStr = intToStr(total);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    freeStrList(strList);

    return 0;
}

String* NewString(char* str) {
    String* newStr = (String*)malloc(sizeof(String));

    int len = 0;
    char* strPtr = (char*)str;
    while(*strPtr++) {
        len++;
    }

    newStr->str = str;
    newStr->len = len;
    // newStr->metadata = createMeta(newStr->str);
    newStr->compare = compare_str;

    return newStr;
}
int compare_str(String* s1, String* s2) {
    char* s1Ptr = s1->str;
    char* s2Ptr = s2->str;

    while(*s1Ptr && s2Ptr) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }
    }

    return *s1Ptr ? 1 : *s2Ptr ? -1 : 0;
}

void freeStrList(String** strList) {
    String** strListPtr = strList;

    while(*strListPtr) {
        free(((String*)*strListPtr)->str);
        free(*strListPtr++);
    }
    free(strList);

    return;
}

// 걍 외움 - 추후 쓸 데가 많아 보여서.
// 오버플로를 사용한 방법 (최대값을 명시하지 않고, 결국 정수의 최대값으로 나머지 연산을 하는 것과 동일하다.)
long createMeta(const char* str) {
    int seed = 1664525;
    long mul = 1139143;

    char* strPtr = (char*)str;

    long result = seed;
    while(*strPtr) {
        result = (result * mul + *strPtr++) % 2113242;
    }

    return result;
}

void sort_heap(String** strList, int length) {
    if(length == 0) {
        return;
    }

    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(strList, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        swap((void**)strList, 0, idx);
        heapify(strList, idx, 0);
        idx--;
    }

    return;
}
void heapify(String** strList, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    int (*compare)(String* s1, String* s2) = ((String*)*strList)->compare;

    if(left < limitIdx && compare(*(strList + parent), *(strList + left)) < 0) {
        parent = left;
    }
    if(right < limitIdx && compare(*(strList + parent), *(strList + right)) < 0) {
        parent = right;
    }

    if(parent != currIdx) {
        swap((void**)strList, parent, currIdx);
        heapify(strList, limitIdx, parent);
    }

    return;
}

void swap(void** arr, int i, int j) {
    void* elem = *(arr + i);
    *(arr + i) = *(arr + j);
    *(arr + j) = elem;

    return;
}

char* parseStr(const char* input) {
    int len = 0;
    char* inputPtr = (char*)input;

    while(isBlank(*inputPtr++) != 1) {
        len++;
    }

    char* newStr = (char*)malloc(sizeof(char) * (len + 1));
    *(newStr + len) = 0;

    char* newStrPtr = newStr;
    inputPtr = (char*)input;

    int idx = 0;
    while(idx++ < len) {
        *newStrPtr++ = *inputPtr++;
    }

    return newStr;
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
