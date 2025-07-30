
/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	256 MB	145317	54410	41040	35.583%


오박사 : 그럼 다솜아 이제 진정한 포켓몬 마스터가 되기 위해 도감을 완성시키도록 하여라.

일단 네가 현재 가지고 있는 포켓몬 도감에서 포켓몬의 이름을 보면 포켓몬의 번호를 말하거나,

포켓몬의 번호를 보면 포켓몬의 이름을 말하는 연습을 하도록 하여라.

나의 시험을 통과하면, 내가 새로 만든 도감을 주도록 하겠네.


입력
---
첫째 줄에는 도감에 수록되어 있는 포켓몬의 개수 N이랑 내가 맞춰야 하는 문제의 개수 M이 주어져.

N과 M은 1보다 크거나 같고, 100,000보다 작거나 같은 자연수인데,

자연수가 뭔지는 알지? 모르면 물어봐도 괜찮아.

나는 언제든지 질문에 답해줄 준비가 되어있어.

둘째 줄부터 N개의 줄에 포켓몬의 번호가 1번인 포켓몬부터 N번에 해당하는 포켓몬까지 한 줄에 하나씩 입력으로 들어와.

포켓몬의 이름은 모두 영어로만 이루어져있고, 또, 음... 첫 글자만 대문자이고, 나머지 문자는 소문자로만 이루어져 있어.

아참! 일부 포켓몬은 마지막 문자만 대문자일 수도 있어.

포켓몬 이름의 최대 길이는 20, 최소 길이는 2야.

그 다음 줄부터 총 M개의 줄에 내가 맞춰야하는 문제가 입력으로 들어와.

문제가 알파벳으로만 들어오면 포켓몬 번호를 말해야 하고, 숫자로만 들어오면, 포켓몬 번호에 해당하는 문자를 출력해야해.

입력으로 들어오는 숫자는 반드시 1보다 크거나 같고, N보다 작거나 같고,

입력으로 들어오는 문자는 반드시 도감에 있는 포켓몬의 이름만 주어져. 그럼 화이팅!!!


출력
---
첫째 줄부터 차례대로 M개의 줄에 각각의 문제에 대한 답을 말해줬으면 좋겠어!!!.

입력으로 숫자가 들어왔다면 그 숫자에 해당하는 포켓몬의 이름을,

문자가 들어왔으면 그 포켓몬의 이름에 해당하는 번호를 출력하면 돼. 그럼 땡큐~

이게 오박사님이 나에게 새로 주시려고 하는 도감이야. 너무 가지고 싶다ㅠㅜ. 꼭 만점을 받아줬으면 좋겠어!! 파이팅!!!

예제 입력 1
26 5
Bulbasaur
Ivysaur
Venusaur
Charmander
Charmeleon
Charizard
Squirtle
Wartortle
Blastoise
Caterpie
Metapod
Butterfree
Weedle
Kakuna
Beedrill
Pidgey
Pidgeotto
Pidgeot
Rattata
Raticate
Spearow
Fearow
Ekans
Arbok
Pikachu
Raichu
25
Raichu
3
Pidgey
Kakuna
예제 출력 1
Pikachu
26
Venusaur
16
14
*/

/**
이번에는 remove 가 필요 없다.

상황에 따른 get 도 필요 없고 결과만 필요 하므로,

index, name 두 속성을 가진 Element 와,

index 순으로 만들어진 Elememt*, name 순으로 만들어진 Element* 를 만들면 된다.

그리고, 들어오는 숫자의 1 번째 글자가 숫자인지, 아닌지에 따라 결과를 출력한다.

---

요약 :

1. Heap_sort 사용한다. + Element(커스텀)

2. binary_search 사용한다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Element {
    int index;
    char* name;

    int (*compare)(struct Element* e1, struct Element* e2);
    int (*compare_str)(struct Element* e, const char* str);
}Element;

Element* NewElement(int index, const char* name);
int compare_element(Element* e1, Element* e2);
int compare_str_element(Element* e, const char* str);

Element* search_binary_str(Element** eList, const char* findName, int i, int j);

void sort_heap(Element** eList, int length);
void heapify(Element** eList, int limitIdx, int currIdx);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);
    char** tokensPtr = (char**)tokens;

    int N = parseInt(*tokensPtr++);
    int M = parseInt(*tokensPtr++);

    freeTokens(tokens);

    Element** originElemList = (Element**)malloc(sizeof(Element*) * (N + 1));
    *(originElemList + N) = NULL;
    Element** strOrderedElemList = (Element**)malloc(sizeof(Element*) * (N + 1));
    *(strOrderedElemList + N) = NULL;

    int idx = 1;
    while(idx <= N) {
        fgets(input, sizeof(input), stdin);

        tokens = (char**)tokenizer(input);

        char* name = *tokens;

        *(originElemList + idx - 1) = NewElement(idx, name);
        *(strOrderedElemList + idx - 1) = NewElement(idx, name);

        freeTokens(tokens);

        idx++;
    }

    sort_heap(strOrderedElemList, N);

    idx = 0;
    while(idx < M) {
        fgets(input, sizeof(input), stdin);

        tokens = (char**)tokenizer(input);

        char* inputStr = *tokens;

        char ch = *inputStr;

        if(ch >= '0' && ch <= '9') {
            int index = parseInt(inputStr);

            index -= 1;

            Element* findElem = *(originElemList + index);

            char* result = findElem->name;

            fputs(result, stdout); fputc('\n', stdout);
        } else {
            Element* findElem = search_binary_str(strOrderedElemList, inputStr, 0, N - 1);

            int resultIndex = findElem->index;

            char* result = intToStr(resultIndex);

            fputs(result, stdout); fputc('\n', stdout);

            free(result);
        }

        freeTokens(tokens);

        idx++;
    }
}

Element* NewElement(int index, const char* name) {
    Element* newElem = (Element*)malloc(sizeof(Element));

    newElem->index = index;

    newElem->compare = compare_element;
    newElem->compare_str = compare_str_element;

    int len = 0;
    char* namePtr = (char*)name;
    while(*namePtr++) {
        len++;
    }

    newElem->name = (char*)malloc(sizeof(char) * (len + 1));
    *(newElem->name) = 0;

    int idx = 0;
    while(idx < len) {
        *(newElem->name + idx) = *(name + idx);

        idx++;
    }

    return newElem;
}
int compare_element(Element* e1, Element* e2) {
    char* s1Ptr = (char*)e1->name;
    char* s2Ptr = (char*)e2->name;

    while(*s1Ptr && *s2Ptr) {
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
int compare_str_element(Element* e, const char* str) {
    char* s1Ptr = (char*)e->name;
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

    return *s1Ptr ? 1 : *s2Ptr ? -1 : 0;
}

Element* search_binary_str(Element** eList, const char* findName, int i, int j) {
    int midIdx = (i + j) / 2;
    Element* midElem = *(eList + midIdx);

    if(i > j) {
        return NULL;
    }

    int diffResult = midElem->compare_str(midElem, findName);

    if(diffResult == 0) {
        return midElem;
    } else if(diffResult < 0) {
        return search_binary_str(eList, findName, midIdx + 1, j);
    } else {
        return search_binary_str(eList, findName, i, midIdx - 1);
    }
}

void sort_heap(Element** eList, int length) {
    int idx = length / 2 - 1;
    while(idx >= 0) {
        heapify(eList, length, idx--);
    }

    idx = length - 1;
    while(idx > 0) {
        Element* tempElem = *(eList + idx);
        *(eList + idx) = *(eList + 0);
        *(eList + 0) = tempElem;

        heapify(eList, idx, 0);
        idx--;
    }
    return;
}
void heapify(Element** eList, int limitIdx, int currIdx) {
    int parent = currIdx;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;

    Element* parentElem = *(eList + parent);

    if(left < limitIdx && parentElem->compare(parentElem, *(eList + left)) < 0) {
        parent = left;
        parentElem = *(eList + left);
    }

    if(right < limitIdx && parentElem->compare(parentElem, *(eList + right)) < 0) {
        parent = right;
    }

    if(parent != currIdx) {
        Element* tempElem = *(eList + parent);
        *(eList + parent) = *(eList + currIdx);
        *(eList + currIdx) = tempElem;

        heapify(eList, limitIdx, parent);
    }

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
