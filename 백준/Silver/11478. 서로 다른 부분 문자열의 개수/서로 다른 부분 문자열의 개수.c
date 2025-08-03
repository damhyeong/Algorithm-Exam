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
1 초	512 MB	40971	26145	21163	64.165%

문제
---
문자열 S가 주어졌을 때, S의 서로 다른 부분 문자열의 개수를 구하는 프로그램을 작성하시오.

부분 문자열은 S에서 연속된 일부분을 말하며, 길이가 1보다 크거나 같아야 한다.


예를 들어,

ababc의 부분 문자열은 a, b, a, b, c, ab, ba, ab, bc, aba, bab, abc, abab, babc, ababc가 있고,

서로 다른것의 개수는 12개이다.


입력
---
첫째 줄에 문자열 S가 주어진다.

S는 알파벳 소문자로만 이루어져 있고, 길이는 1,000 이하이다.


출력
---
첫째 줄에 S의 서로 다른 부분 문자열의 개수를 출력한다.

예제 입력 1
ababc
예제 출력 1
12
*/

/**
이번에는 "중복되지 않은" 원소의 개수가 보장되지 않는다.

오히려, 내가 "중복되지 않은" 원소의 개수를 보장해야 한다.

이 때는 직접 Tree 를 구현해야 한다.

---

어디까지 구현할까 고민이 되는데,

1 단계 : Tree + Element

2 단계 : Tree + Element + Node

3 단계 : HashSet + Tree + Element + Node --> 선택함.

이렇게 존재한다.

이 문제는 트리 속에 존재하는 모든 엘리먼트를 꺼내서 사용할 필요는 없다.

단순히 "중복되지 않은 원소의 개수" 를 구하는 것이기 때문에,

1 단계로도 충분히 풀 수 있다.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

typedef struct HashSet {
    int size;
    int treeSize;

    struct Tree** trees;
    _Bool (*add)(struct HashSet* this, const char* target, int length);
    struct Element* (*get)(struct HashSet* this, int length, const char* target);
    int (*get_size)(struct HashSet* this);
    int (*hashing)(const char* target, int length, int limit);
} HashSet; // Tree** trees, int size, functions..
struct HashSet* NewHashSet(void);
_Bool add_hashset(struct HashSet* this, const char* target, int length);
struct Element* get_hashset(struct HashSet* this, int length, const char* target);
int size_hashset(struct HashSet* this);
int hasing_hashset(const char* target, int length, int limit);

typedef struct Tree {
    int size;

    struct LinkedNode* linkedNode;

    struct Element* topElem;

    struct Element* (*add)(struct Tree* this, struct Element* currElem, char* newStr, int length);
    struct Element* (*get)(struct Tree* this, struct Element* currElem, const char* targetStr);

    struct Element* (*left_rotate)(struct Tree* this, struct Element* currElem);
    struct Element* (*right_rotate)(struct Tree* this, struct Element* currElem);

    int (*get_height)(struct Element* e);
} Tree; // LinkedNode* linkedNode, Element* topElem, int size, functions..
struct Tree* NewTree(void);
struct Element* add_tree(struct Tree* this, struct Element* currElem, char* newStr, int length);
struct Element* get_tree(struct Tree* this, struct Element* currElem, const char* targetStr);
struct Element* left_rotate(struct Tree* this, struct Element* currElem);
struct Element* right_rotate(struct Tree* this, struct Element* currElem);
int get_height(struct Element* e);

typedef struct LinkedNode { // int size, Node* headNode, Node* tailNode, .. fucntions..
    int size;

    struct Node* headNode;
    struct Node* tailNode;

    _Bool (*add)(struct LinkedNode* this, struct Element* addTargetElem);
    void (*freeLinkedNode)(struct LinkedNode* this);
} LinkedNode; // int size, Node* headNode, Node* tailNode, .. fucntions..
struct LinkedNode* NewLinkedNode(void);
_Bool add_linkedNode(struct LinkedNode* this, struct Element* addTargetElem);
void freeLinkedNode(struct LinkedNode* this);

typedef struct Node { // Element* chained_elem, Node* prevNode, Node* nextNode, fn freeNode
    struct Element* chained_elem;

    struct Node* prevNode;
    struct Node* nextNode;

    void (*freeNode)(struct Node* this);
} Node; // Element* chained_elem, Node* prevNode, Node* nextNode, fn freeNode
struct Node* NewNode(void);
void freeNode_node(struct Node* this);

typedef struct Element { // int height, char* str, fn compare
    int height;
    char* str;
    int length;

    struct Element* leftElem;
    struct Element* rightElem;

    Node* chained_node;

    int (*compare)(struct Element* e1, struct Element* e2);
    int (*compare_str)(struct Element* elem, const char* str);
    void (*freeElement)(struct Element* this);
} Element; // int height, char* str, fn compare
struct Element* NewElement(char* str, int length);
int compare_element(struct Element* e1, struct Element* e2);
int compare_str_element(struct Element* elem, const char* str);
void freeElement_element(struct Element* this);

char* parsePureStr(const char* str);
char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


// char* slice(char* str, int i, int j) {
//     int size = j - i;
//     char* newStr = (char*)malloc(sizeof(char) * (size + 1));
//     *(newStr + size) = 0;

//     int idx = i;
//     while(idx < j) {
//         *(newStr + idx - i) = *(str + idx);
//         idx++;
//     }

//     return newStr;
// }

int main(void) {
    HashSet* hashSet = NewHashSet();

    char input[1200];

    fgets(input, sizeof(input), stdin);

    // wordLen 이 결정됨.
    char* origin = parsePureStr(input);
    char* originPtr = origin;

    int wordLen = 0;
    while(*originPtr++) {
        wordLen++;
    }

    int idx = 0;
    while(idx < wordLen) {
        int jdx = idx + 1;
        while(jdx <= wordLen) {
            char memo = *(origin + jdx);

            *(origin + jdx) = 0;

            int length = jdx - idx;

            hashSet->add(hashSet, origin + idx, length);

            *(origin + jdx) = memo;

            jdx++;
        }
        idx++;
    }

    char* result = intToStr(hashSet->size);
    fputs(result, stdout); fputc('\n', stdout);
    free(result);

    return 0;
}

HashSet* NewHashSet(void) {
    HashSet* newHashSet = (HashSet*)malloc(sizeof(HashSet));

    newHashSet->size = 0;
    newHashSet->treeSize = 1048589;

    newHashSet->add = add_hashset;
    newHashSet->get = get_hashset;
    newHashSet->get_size = size_hashset;
    newHashSet->hashing = hasing_hashset;

    // Tree** trees = (Tree**)malloc(sizeof(Tree*) * (newHashSet->treeSize + 1));
    Tree** trees = (Tree**)calloc(sizeof(Tree*), (newHashSet->treeSize + 1));
    // *(trees + newHashSet->treeSize) = NULL;

    // int idx = 0;
    // while(idx < newHashSet->treeSize) {
    //     *(trees + idx) = NewTree();
    //     idx++;
    // }

    newHashSet->trees = trees;

    return newHashSet;
}
_Bool add_hashset(HashSet* this, const char* target, int length) {
    int hash = this->hashing(target, length, this->treeSize);
    if(*(this->trees + hash) == NULL) {
        *(this->trees + hash) = NewTree();
    }
    Tree* selectedTree = *(this->trees + hash);

    int prevSize = selectedTree->size;
    selectedTree->topElem = selectedTree->add(selectedTree, selectedTree->topElem, (char*)target, length);
    int nextSize = selectedTree->size;

    if(prevSize == nextSize) {
        return 0;
    } else {
        this->size++;
        return 1;
    }
}
Element* get_hashset(HashSet* this, int length, const char* target) {
    int hash = this->hashing(target, length, this->treeSize);
    if(*(this->trees + hash) == NULL) {
        return NULL;
    }
    Tree* selectedTree = *(this->trees + hash);

    Element* findElem = selectedTree->get(selectedTree, selectedTree->topElem, target);

    return findElem; // Element* or NULL.
}
int size_hashset(HashSet* this) {
    return this->size;
}
// 문자열에 따른 해싱. (랜덤 시드를 이용하지 않았음.)
int hasing_hashset(const char* target, int length, int limit) {

    // char* targetPtr = (char*)target;

    // int total = 0;

    int total = (*target + 131 + length) * 777777;

    // while(*targetPtr) {
    //     char currCh = *targetPtr++;
    //     total += (currCh + 131) * 777777;
    //     total %= limit;
    // }

    // fputs(intToStr(total), stdout); fputc('\n', stdout);
    return total % limit;
}

Tree* NewTree(void) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));

    // newTree->linkedNode = NewLinkedNode();
    newTree->linkedNode = NULL;
    newTree->topElem = NULL;

    newTree->add = add_tree;
    newTree->get = get_tree;

    newTree->left_rotate = left_rotate;
    newTree->right_rotate = right_rotate;

    newTree->get_height = get_height;

    return newTree;
}
Element* add_tree(Tree* this, Element* currElem, char* newStr, int length) {
    if(currElem == NULL) {
        Element* newElem = NewElement(newStr, length);
        // Node* newNode = NewNode();

        // newElem->chained_node = newNode;
        newElem->chained_node = NULL;
        // newNode->chained_elem = newElem;

        // LinkedNode* manageNodes = this->linkedNode;

        // 엘리먼트를 넣어서 체이닝 된 노드를 등록한다.
        // manageNodes->add(manageNodes, newElem);

        // HashSet 은 Tree 의 add 전후 사이즈를 비교하여 스스로의 사이즈를 알아낸다.
        // 이건 위험한 방식이지만, 직관적이여서 선택함.
        //
        // 안전한 방식은, HashSet 에 등록된 트리 목록의 사이즈를 전부 다시 참조하여 계산하는 것.
        this->size++;

        return newElem;
    }

    int diffResult = currElem->compare_str(currElem, newStr);

    if(diffResult == 0) {
        return currElem;
    } else if(diffResult < 0) {
        currElem->rightElem = add_tree(this, currElem->rightElem, newStr, length);
    } else {
        currElem->leftElem = add_tree(this, currElem->leftElem, newStr, length);
    }

    int leftHeight = this->get_height(currElem->leftElem);
    int rightHeight = this->get_height(currElem->rightElem);

    int heightDiff = leftHeight - rightHeight;

    // LL
    if(
        heightDiff > 1 &&
        this->get_height(currElem->leftElem->leftElem) > this->get_height(currElem->leftElem->rightElem)
    ) {
        currElem = this->right_rotate(this, currElem);
    }
    // RR
    if(
        heightDiff < -1 &&
        this->get_height(currElem->rightElem->rightElem) > this->get_height(currElem->rightElem->leftElem)
    ) {
        currElem = this->left_rotate(this, currElem);
    }
    // LR
    if(
        heightDiff > 1 &&
        this->get_height(currElem->leftElem->rightElem) > this->get_height(currElem->leftElem->leftElem)
    ) {
        currElem->leftElem = this->left_rotate(this, currElem->leftElem);
        currElem = this->right_rotate(this, currElem);
    }
    // RL
    if(
        heightDiff < -1 &&
        this->get_height(currElem->rightElem->leftElem) > this->get_height(currElem->rightElem->rightElem)
    ) {
        currElem->rightElem = this->right_rotate(this, currElem->rightElem);
        currElem = this->left_rotate(this, currElem);
    }

    leftHeight = this->get_height(currElem->leftElem);
    rightHeight = this->get_height(currElem->rightElem);

    currElem->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    return currElem;
}
Element* get_tree(Tree* this, Element* currElem, const char* targetStr) {
    if(currElem == NULL) {
        return NULL;
    }

    int diffResult = currElem->compare_str(currElem, targetStr);

    if(diffResult == 0) {
        return currElem;
    } else if(diffResult < 0) {
        return get_tree(this, currElem->rightElem, targetStr);
    } else {
        return get_tree(this, currElem->leftElem, targetStr);
    }
}
Element* left_rotate(Tree* this, Element* currElem) {
    Element* newRoot = currElem->rightElem;
    currElem->rightElem = newRoot->leftElem;
    newRoot->leftElem = currElem;

    newRoot->height++;
    currElem->height--;

    return newRoot;
}
Element* right_rotate(Tree* this, Element* currElem) {
    Element* newRoot = currElem->leftElem;
    currElem->leftElem = newRoot->rightElem;
    newRoot->rightElem = currElem;

    newRoot->height++;
    currElem->height--;

    return newRoot;
}
int get_height(Element* e) {
    return e == NULL ? 0 : e->height;
}


LinkedNode* NewLinkedNode(void) {
    LinkedNode* newLinkedNode = (LinkedNode*)malloc(sizeof(LinkedNode));

    newLinkedNode->size = 0;

    newLinkedNode->headNode = NULL;
    newLinkedNode->tailNode = NULL;

    newLinkedNode->add = add_linkedNode;
    newLinkedNode->freeLinkedNode = freeLinkedNode;

    return newLinkedNode;
}
_Bool add_linkedNode(LinkedNode* this, Element* addTargetElem) {

    Node* newNode = addTargetElem->chained_node;

    if(this->size == 0) {
        this->headNode = newNode;
        this->tailNode = newNode;
    } else {
        this->tailNode->nextNode = newNode;
        newNode->prevNode = this->tailNode;
        this->tailNode = newNode;
    }

    this->size++;

    return 1;
}
// 이 메서드는 Node 를 순회하지만, Element 의 free 전용 메서드를 통해 Node 스스로를 해제한다.
// 또한, 이 메서드를 실행하면 트리를 구성하는 모든 엘리먼트가 해제된다. Element <--> Node (1 : 1)
void freeLinkedNode(LinkedNode* this) {
    Node* currNode = this->headNode;

    while(currNode) {
        Node* freedNode = currNode;
        currNode = currNode->nextNode;

        // Element 를 통해 현재 Node 를 해제.
        Element* freedElem = freedNode->chained_elem;
        freedElem->freeElement(freedElem);
    }

    free(this);

    return;
}


Node* NewNode(void) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->chained_elem = NULL;

    newNode->prevNode = NULL;
    newNode->nextNode = NULL;

    newNode->freeNode = freeNode_node;

    return newNode;
}
void freeNode_node(Node* this) {
    if(this->prevNode) {
        this->prevNode->nextNode = this->nextNode;
    }
    if(this->nextNode) {
        this->nextNode->prevNode = this->prevNode;
    }

    this->chained_elem = NULL;

    free(this);

    return;
}

Element* NewElement(char* str, int length) {
    Element* newElem = (Element*)malloc(sizeof(Element));

    newElem->height = 1;
    newElem->str = str;
    newElem->length = length;

    newElem->leftElem = NULL;
    newElem->rightElem = NULL;

    newElem->chained_node = NULL;

    newElem->compare = compare_element;
    newElem->compare_str = compare_str_element;
    newElem->freeElement = freeElement_element;

    return newElem;
}
int compare_element(Element* e1, Element* e2) {
    char* s1Ptr = e1->str;
    char* s2Ptr = e2->str;

    int s1Len = e1->length;
    int s2Len = e2->length;

    int idx = 0;
    while(idx < s1Len && idx < s2Len) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }

        idx++;
    }

    return idx == s1Len ? idx == s2Len ? 0 : -1 : 1;
}
int compare_str_element(struct Element* elem, const char* str) {
    char* s1Ptr = elem->str;
    char* s2Ptr = (char*)str;

    int s1Len = elem->length;

    int idx = 0;
    while(idx < s1Len && *s2Ptr) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }
        idx++;
    }

    return idx == s1Len ? *s2Ptr == 0 ? 0 : -1 : 1;
}
void freeElement_element(Element* this) {
    free(this->str);
    Node* node = this->chained_node;
    // Element 에서 Node 를 free
    node->freeNode(node);

    this->chained_node = NULL;
    this->leftElem = NULL;
    this->rightElem = NULL;

    free(this);

    return;
}

char* parsePureStr(const char* str) {
    int len = 0;
    char* strPtr = (char*)str;
    while(isBlank(*strPtr++) != 1) {
        len++;
    }

    char* pureStr = (char*)malloc(sizeof(char) * (len + 1));
    *(pureStr + len) = 0;

    int idx = 0;
    while(idx < len) {
        *(pureStr + idx) = *(str + idx);
        idx++;
    }

    return pureStr;
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
