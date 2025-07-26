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
2 초 (하단 참고)	1536 MB	70214	38612	29597	54.573%
문제
총 N개의 문자열로 이루어진 집합 S가 주어진다.

입력으로 주어지는 M개의 문자열 중에서 집합 S에 포함되어 있는 것이 총 몇 개인지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 문자열의 개수 N과 M (1 ≤ N ≤ 10,000, 1 ≤ M ≤ 10,000)이 주어진다.

다음 N개의 줄에는 집합 S에 포함되어 있는 문자열들이 주어진다.

다음 M개의 줄에는 검사해야 하는 문자열들이 주어진다.

입력으로 주어지는 문자열은 알파벳 소문자로만 이루어져 있으며, 길이는 500을 넘지 않는다. 집합 S에 같은 문자열이 여러 번 주어지는 경우는 없다.

출력
첫째 줄에 M개의 문자열 중에 총 몇 개가 집합 S에 포함되어 있는지 출력한다.

예제 입력 1
5 11
baekjoononlinejudge
startlink
codeplus
sundaycoding
codingsh
baekjoon
codeplus
codeminus
startlink
starlink
sundaycoding
codingsh
codinghs
sondaycoding
startrink
icerink
예제 출력 1
4
*/

/**

--어떻게 풀 것인가?--

바로 이전 문제에서 원시값 배열 + heap_sort + binary_search 를 통해 Set 을 모방할 수 있었다.

HashSet 은 사용이 간단하며, 검증이 완료된 라이브러리이다.

원시배열 + heap_sort 보다 HashSet 이 더 우수할 수 밖에 없는 이유가 있는데,

바로 HashSet 은 랜덤 시드를 통해 여러개의 트리에 추가된 엘리먼트를 배치하기 때문이다.

즉, 원시 배열은 "1개의 tree" 이지만, HashSet 은 내가 직접 몇 개의 트리를 만들지 설정 할 수 있다.

이전 문제에서는 heap_sort + binary_search 를 이용하여 풀었으므로,

이번 문제는 HashSet + Tree + Element 구조로 만들 것이다. (heap_sort 로 푸는 게 훨씬 쉬움)

이러한 방식으로 푸는 것은 Java 로 구현 할 때도 몇백줄은 우습게 넘었는데,

C 와 stdio.h 만 사용하는 제약조건 속에서 몇 줄의 코드가 나올지 예상 못하겠다.

첫 줄의 수들을 파싱하기 위해 tokenizer 를 사용하지만, 다음 줄들부터는 단순 문자열에 불과하다.

그래도, 코드의 수를 줄이기 위해 tokenizer 를 다시 이용하여 트리에 추가 할 것이다.

---

우려되는 것은, 만들어진 HashSet + Tree + Element 의 메모리 해제 부분이다.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct HashSet {
    int tree_size; // 트리 개수
    int size; // 전체 엘리먼트 개수

    struct Tree** trees;
    struct Tree* (*get_tree)(struct HashSet* this, int idx);

    int (*hashed_idx)(struct HashSet* this, const char* str);

    struct Element* (*get)(struct HashSet* this, const char* targetStr);
    _Bool (*add)(struct HashSet* this, const char* targetStr);
} HashSet;

typedef struct Tree {
    struct Element* topElement;
    int size;

    struct Element* (*get)(struct Tree* this, struct Element* currElem, const char* targetStr);
    struct Element* (*add)(struct Tree* this, struct Element* currElem, const char* targetStr);

    struct Element* (*leftRotate)(struct Tree* this, struct Element* element);
    struct Element* (*rightRotate)(struct Tree* this, struct Element* element);
    int (*get_height)(struct Element* element);
} Tree;

typedef struct Element {
    struct Element* leftElement;
    struct Element* rightElement;

    char* str;
    int height;

    int (*compare)(struct Element* e1, struct Element* e2);
    int (*compare_str)(struct Element* e1, const char* str);
} Element;

HashSet* NewHashSet(void);
Tree* get_tree_hashset(HashSet* this, int idx);
int hashed_idx_hashset(HashSet* this, const char* str);
Element* get_hashset(HashSet* this, const char* targetStr);
_Bool add_hashset(HashSet* this, const char* targetStr);

Tree* NewTree(void);
Element* get_tree(Tree* this, Element* currElem, const char* targetStr);
Element* add_tree(Tree* this, Element* currElem, const char* targetStr);

Element* leftRotate_tree(Tree* this, Element* element);
Element* rightRotate_tree(Tree* this, Element* element);
int get_height_tree(Element* element);

Element* NewElement(const char* newStr);
int compare_element(Element* e1, Element* e2);
int compare_str_element(Element* e1, const char* str);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[1000];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);

    int N = parseInt(*tokens);
    int M = parseInt(*(tokens + 1));

    freeTokens(tokens);

    HashSet* hashSet = NewHashSet();

    int idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        tokens = (char**)tokenizer(input);

        char* str = *tokens;

        hashSet->add(hashSet, str);

        freeTokens(tokens);
    }

    int total = 0;
    idx = 0;
    while(idx++ < M) {
        fgets(input, sizeof(input), stdin);

        tokens = (char**)tokenizer(input);

        char* str = *tokens;

        Element* checkElem = hashSet->get(hashSet, str);

        freeTokens(tokens);

        if(checkElem != NULL) {
            total++;
        }
    }

    char* resultStr = intToStr(total);

    fputs(resultStr, stdout); fputc('\n', stdout);

    free(resultStr);

    return 0;
}

HashSet* NewHashSet(void) {
    HashSet* newHashSet = (HashSet*)malloc(sizeof(HashSet));

    newHashSet->tree_size = 20;
    newHashSet->size = 0;

    newHashSet->trees = (Tree**)malloc(sizeof(Tree*) * (newHashSet->tree_size + 1));
    *(newHashSet->trees + newHashSet->tree_size) = NULL;

    int idx = 0;
    while(idx < newHashSet->tree_size) {
        *(newHashSet->trees + idx++) = NewTree();
    }

    newHashSet->get_tree = get_tree_hashset;

    newHashSet->hashed_idx = hashed_idx_hashset;

    newHashSet->get = get_hashset;
    newHashSet->add = add_hashset;

    return newHashSet;
}
Tree* get_tree_hashset(HashSet* this, int idx) {
    Tree* selectTree = *(this->trees + idx);

    return selectTree;
}
int hashed_idx_hashset(HashSet* this, const char* str) {
    char* strPtr = (char*)str;
    int total = 0;

    while(*strPtr) {
        total += *strPtr++;
    }

    return total % this->tree_size;
}
Element* get_hashset(HashSet* this, const char* targetStr) {
    int hashedIdx = this->hashed_idx(this, targetStr);
    Tree* selectedTree = this->get_tree(this, hashedIdx);

    return selectedTree->get(selectedTree, selectedTree->topElement, targetStr);
}
_Bool add_hashset(HashSet* this, const char* targetStr) {
    int hashIdx = this->hashed_idx(this, targetStr);
    Tree* selectedTree = this->get_tree(this, hashIdx);

    int previousSize = selectedTree->size;

    selectedTree->topElement
        = selectedTree->add(selectedTree, selectedTree->topElement, targetStr);

    int afterSize = selectedTree->size;

    // 이미 존재
    if(previousSize != afterSize) {
        this->size++;
        return 1;
    } else {
        return 0;
    }
}

Tree* NewTree(void) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));

    newTree->topElement = NULL;
    newTree->size = 0;

    newTree->get = get_tree;
    newTree->add = add_tree;

    newTree->leftRotate = leftRotate_tree;
    newTree->rightRotate = rightRotate_tree;

    newTree->get_height = get_height_tree;

    return newTree;
}
Element* get_tree(Tree* this, Element* currElem, const char* targetStr) {
    if(currElem == NULL) {
        return NULL;
    }

    int compare_result = currElem->compare_str(currElem, targetStr);

    if(compare_result == 0) {
        return currElem;
    } else if(compare_result < 0) {
        return get_tree(this, currElem->leftElement, targetStr);
    } else {
        return get_tree(this, currElem->rightElement, targetStr);
    }
}
// 머릿속에 트리 구조의 그래프를 생성해야 이해 가능.
Element* add_tree(Tree* this, Element* currElem, const char* targetStr){
    if(currElem == NULL) {
        this->size++;

        return NewElement(targetStr);
    }

    int compareResult = currElem->compare_str(currElem, targetStr);

    // 동일한 값을 가진 엘리먼트가 존재하면, 추가하지 못하므로 그대로 바로 반환.
    if(compareResult == 0) {
        return currElem;
    } else if(compareResult < 0) {
        currElem->leftElement
            = this->add(this, currElem->leftElement, targetStr);
    } else { // compareResult > 0
        currElem->rightElement
            = this->add(this, currElem->rightElement, targetStr);
    }

    int left_height = this->get_height(currElem->leftElement);
    int right_height = this->get_height(currElem->rightElement);

    currElem->height = left_height < right_height ? right_height + 1 : left_height + 1;

    int balance = left_height - right_height;

    // LL
    if(
        balance > 1 &&
        this->get_height(currElem->leftElement->leftElement) > this->get_height(currElem->leftElement->rightElement)
    ) {
        currElem = this->rightRotate(this, currElem);
    }
    // RR
    if(
        balance < -1 &&
        this->get_height(currElem->rightElement->rightElement) > this->get_height(currElem->rightElement->leftElement)
    ) {
        currElem = this->leftRotate(this, currElem);
    }
    // LR
    if(
        balance > 1 &&
        this->get_height(currElem->leftElement->leftElement) < this->get_height(currElem->leftElement->rightElement)
    ) {
        // LL 상태로 만든다.
        currElem->leftElement = this->leftRotate(this, currElem->leftElement);
        // 이후 오른쪽으로 회전.
        currElem = this->rightRotate(this, currElem);
    }
    // RL
    if(
        balance < -1 &&
        this->get_height(currElem->rightElement->leftElement) > this->get_height(currElem->rightElement->rightElement)
    ) {
        // RR 상태로 만든다.
        currElem->rightElement = this->rightRotate(this, currElem->rightElement);
        // 이후 왼쪽으로 회전.
        currElem = this->leftRotate(this, currElem);
    }

    return currElem;
}

// 이는 element(== root) 와, element->right 가 NULL 이 아니라는 전제 하에 진행된다.
// 반환되는 root-element 는 인자로 주어진 element->right 라는 것을 명심.
Element* leftRotate_tree(Tree* this, Element* element) {
    /**
    트리 구조를 바꾸는 것은 단순히 로직만 생각하기보다, 은유적으로 생각하는 것도 좋다.

    나의 경우, 나뭇가지를 왼쪽으로 꺾는다는 생각을 한다.
    현재 이 메서드에 들어왔다는 것은, "\" 이 상태이다.

    왼쪽으로 회전하고 나면, " ^ " 로 형태가 변한다.

    그러나, 단순히 꺾는다고 생각하면 안되고, 꺾이는 과정에서 재배치해야 할 엘리먼트들이 존재한다.

    이를 이해하기 위해서는, 트리가 펼쳐졌을 때, x 축으로 내부 엘리먼트들을 펼쳐놓는다 가정 할 때,
    오름차순을 유지한다.
    */

    // 왼쪽으로 꺾는 과정에서 중간 엘리먼트의 데이터를 훼손하지 않는 과정(유지)
    Element* rootElement = element->rightElement;
    element->rightElement = rootElement->leftElement;
    rootElement->leftElement = element;

    int newLeftHeight = this->get_height(rootElement->leftElement);
    int newRightHeight = this->get_height(rootElement->rightElement);

    rootElement->height =
        newLeftHeight > newRightHeight ? newLeftHeight + 1 : newRightHeight + 1;

    return rootElement;
}
Element* rightRotate_tree(Tree* this, Element* element) {
    // 이번엔 " / " 상태의 가지를 오른쪽으로 꺾는다고 상상.
    // 그 과정에서 손실되는 데이터가 없도록 조치하는 과정.

    Element* rootElement = element->leftElement;
    element->leftElement = rootElement->rightElement;
    rootElement->rightElement = element;

    int newLeftHeight = this->get_height(rootElement->leftElement);
    int newRightHeight = this->get_height(rootElement->rightElement);

    rootElement->height
        = newLeftHeight > newRightHeight ? newLeftHeight + 1 : newRightHeight + 1;

    return rootElement;
}
int get_height_tree(Element* element) {
    if(element == NULL) {
        return 0;
    } else {
        return element->height;
    }
}

Element* NewElement(const char* newStr) {
    Element* newElem = (Element*)malloc(sizeof(Element));

    newElem->leftElement = NULL;
    newElem->rightElement = NULL;

    newElem->height = 1; // 0 은 NULL 을 위함.

    int len = 0;
    char* newStrPtr = (char*)newStr;
    while(*newStrPtr++) {
        len++;
    }

    newElem->str = (char*)malloc(sizeof(char) * (len + 1));
    *(newElem->str + len) = 0;

    int idx = 0;
    while(idx < len) {
        *(newElem->str + idx) = *(newStr + idx);
        idx++;
    }

    newElem->compare = compare_element;
    newElem->compare_str = compare_str_element;

    return newElem;
}
int compare_element(Element* e1, Element* e2) {
    const char* e1Str = e1->str;
    const char* e2Str = e2->str;

    char* e1StrPtr = (char*)e1Str;
    char* e2StrPtr = (char*)e2Str;

    while(*e1StrPtr && *e2StrPtr) {
        char ch1 = *e1StrPtr++;
        char ch2 = *e2StrPtr++;

        if(ch1 == ch2) {
            continue;
        } else if(ch1 < ch2) {
            return -1;
        } else {
            return 1;
        }
    }

    return (*e1StrPtr == 0 && *e2StrPtr == 0) ? 0 : (*e1StrPtr == 0) ? -1 : 1;
}
int compare_str_element(Element* e1, const char* str) {
    const char* e1Str = e1->str;
    const char* e2Str = (char*)str;

    char* e1StrPtr = (char*)e1Str;
    char* e2StrPtr = (char*)e2Str;

    while(*e1StrPtr && *e2StrPtr) {
        char ch1 = *e1StrPtr++;
        char ch2 = *e2StrPtr++;

        if(ch1 == ch2) {
            continue;
        } else if(ch1 < ch2) {
            return -1;
        } else {
            return 1;
        }
    }

    return (*e1StrPtr == 0 && *e2StrPtr == 0) ? 0 : (*e1StrPtr == 0) ? -1 : 1;
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
    while(*strPtr == '-') {
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
