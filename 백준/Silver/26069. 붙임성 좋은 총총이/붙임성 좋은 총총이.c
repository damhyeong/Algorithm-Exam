
/**
붙임성 좋은 총총이 성공
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	1024 MB	15645	9869	8735	63.509%

문제
---
무지개 댄스를 추는 총총과 그걸 보는 총총

총총이는 친구 곰곰이의 소개로 제2회 곰곰컵에 출연할 기회를 얻었다!

총총이는 자신의 묘기인 무지개 댄스를 선보여, 여러분의 환심을 사려 한다. 이 댄스는 중독성이 강하기 때문에, 한번 보게 된 사람은 모두 따라 하게 돼버린다.

무지개 댄스를 추는 총총 2마리

사람들이 만난 기록이 시간 순서대로 N 개 주어진다.

(총총이는 토끼이지만 이 문제에서는 편의상 사람이라고 가정한다.)

무지개 댄스를 추지 않고 있던 사람이 무지개 댄스를 추고 있던 사람을 만나게 된다면, 만난 시점 이후로 무지개 댄스를 추게 된다.

기록이 시작되기 이전 무지개 댄스를 추고 있는 사람은 총총이 뿐이라고 할 때, 마지막 기록 이후 무지개 댄스를 추는 사람이 몇 명인지 구해보자!


입력
---
첫 번째 줄에는 사람들이 만난 기록의 수 N (1 <= N <= 1_000) 이 주어진다.

두 번째 줄 부터 N 개의 줄에 걸쳐 사람들이 만난 기록이 주어진다.

i + 1 번째 줄에는 i 번째로 만난 사람들의 이름 A_i 와 B_i 가 공백을 사이에 두고 주어진다.

A_i 와 B_i 는 숫자와 영문 대소문자로 이루어진 최대 길이 20 의 문자열이며, 서로 같지 않다.

총총이의 이름은 ChongChong 으로 주어지며, 기록에서 1 회 이상 주어진다.

동명이인은 없으며, 사람의 이름은 대소문자를 구분한다. (ChongChong 과 chongchong 은 다른 이름이다.)


출력
---
마지막 기록 이후 무지개 댄스를 추는 사람의 수를 출력하라.

예제 입력 1
12
bnb2011 chansol
chansol chogahui05
chogahui05 jthis
jthis ChongChong
jthis jyheo98
jyheo98 lms0806
lms0806 pichulia
pichulia pjshwa
pjshwa r4pidstart
r4pidstart swoon
swoon tony9402
tony9402 bnb2011
예제 출력 1
10
*/

/**
이번에는 HashSet 을 이용하여 문제를 풀어보자.
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

unsigned int hash(const char* str) {
    unsigned int seed = 177237;
    unsigned int width = 5;
    unsigned int byte = 32;

    unsigned int result = seed;
    char* strPtr = (char*)str;
    while(*strPtr) {
        unsigned int ch = *strPtr++;

        // 5 비트 회전 로테이션하기
        result = (result << width) | (result >> (byte - width));
        // xor 계산을 통해 확산
        result ^= ch;
    }

    return result;
}

typedef struct HashMap HashMap;
typedef struct Tree Tree;
typedef struct LinkedNode LinkedNode;
typedef struct Element Element;
typedef struct Node Node;

HashMap* NewHashMap(void);
void add_hashmap(HashMap* this, const char* str);
Element* get_hashmap(HashMap* this, const char* str);

Tree* NewTree(void);
Element* add_tree(Tree* this, Element* currElem, const char* str, unsigned int hash);
Element* get_tree(Element* currElem, const char* str, unsigned int hash);
int get_height(Element* elem);
Element* left_rotate(Tree* this, Element* currElem);
Element* right_rotate(Tree* this, Element* currElem);

LinkedNode* NewLinkedNode(void);
void addNode(LinkedNode* linkedNode, Element* elem);
void freeAllNode(LinkedNode* linkedNode);

Element* NewElement(char* str, unsigned int hash);
int compare_elem(Element* e1, Element* e2);
int compare_target(Element* elem, unsigned int hash);
void freeElement(Element* elem);

Node* NewNode(Element* chainedElem);
void freeNode(LinkedNode* linkedNode, Node* node);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

struct HashMap {
    int size;
    int hashSize;
    Tree** trees;

    void (*add)(HashMap* this, const char* str);
    Element* (*get)(HashMap* this, const char* str);
};
struct Tree {
    int size;
    Element* topElement;

    Element* (*add)(Tree* this, Element* currElem, const char* str, unsigned int hash);
    Element* (*get)(Element* currElem, const char* str, unsigned int hash);
    int (*get_height)(Element* elem);
    Element* (*left_rotate)(Tree* this, Element* currElem);
    Element* (*right_rotate)(Tree* this, Element* currElem);
};
struct LinkedNode {
    Node* startNode;
    Node* endNode;
};
struct Element {
    unsigned int hash;
    char* str;

    Element* left;
    Element* right;

    int height;
};
struct Node {
    Node* nextNode;
    Node* prevNode;
    Element* chained_elem;
};

HashMap* NewHashMap(void) {
    HashMap* newHashMap = (HashMap*)malloc(sizeof(HashMap));

    newHashMap->size = 0;
    newHashMap->hashSize = 40;

    newHashMap->trees = (Tree**)malloc(sizeof(Tree*) * (newHashMap->hashSize + 1));
    *(newHashMap->trees + newHashMap->hashSize) = NULL;

    int idx = 0;
    while(idx < newHashMap->hashSize) {
        *(newHashMap->trees + idx) = NewTree();
        idx++;
    }

    newHashMap->add = add_hashmap;
    newHashMap->get = get_hashmap;

    return newHashMap;
}
void add_hashmap(HashMap* this, const char* str) {
    unsigned int hashNum = hash(str);
    int select = hashNum % this->hashSize;
    Tree* selectedTree = *(this->trees + select);

    int saveSize = selectedTree->size;

    selectedTree->topElement
        = selectedTree->add(selectedTree, selectedTree->topElement, str, hashNum);

    if(saveSize != selectedTree->size) {
        this->size++;
    }

    return;
}

Element* get_hashmap(HashMap* this, const char* str) {
    unsigned int hashNum = hash(str);
    int select = hashNum % this->hashSize;
    Tree* selectedTree = *(this->trees + select);


    return selectedTree->get(selectedTree->topElement, str, hashNum);
}

Tree* NewTree(void) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));

    newTree->size = 0;

    newTree->topElement = NULL;

    newTree->add = add_tree;
    newTree->get = get_tree;
    newTree->get_height = get_height;
    newTree->left_rotate = left_rotate;
    newTree->right_rotate = right_rotate;

    return newTree;
}
Element* add_tree(Tree* this, Element* currElem, const char* str, unsigned int hash) {
    if(currElem == NULL) {
        Element* newElem = NewElement((char*)str, hash);
        this->size++;
        return newElem;
    }

    int compareResult = compare_target(currElem, hash);

    if(compareResult == 0) {
        return currElem;
    } else if(compareResult < 0) {
        currElem->right = add_tree(this, currElem->right, str, hash);
    } else {
        currElem->left = add_tree(this, currElem->left, str, hash);
    }

    int leftHeight = this->get_height(currElem->left);
    int rightHeight = this->get_height(currElem->right);

    currElem->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    int diff = leftHeight - rightHeight;

    // LL
    if(
        diff > 1 &&
        this->get_height(currElem->left->left) > this->get_height(currElem->left->right)
    ) {
        currElem = this->right_rotate(this, currElem);
    }
    // RR
    if(
        diff < -1 &&
        this->get_height(currElem->right->right) > this->get_height(currElem->right->left)
    ) {
        currElem = this->left_rotate(this, currElem);
    }
    // LR
    if(
        diff > 1 &&
        this->get_height(currElem->left->right) > this->get_height(currElem->left->left)
    ) {
        currElem->left = this->left_rotate(this, currElem->left);
        currElem = this->right_rotate(this, currElem);
    }

    // RL
    if(
        diff < -1 &&
        this->get_height(currElem->right->left) > this->get_height(currElem->right->right)
    ) {
        currElem->right = this->right_rotate(this, currElem->right);
        currElem = this->left_rotate(this, currElem);
    }

    leftHeight = this->get_height(currElem->left);
    rightHeight = this->get_height(currElem->right);

    currElem->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    return currElem;
}
Element* get_tree(Element* currElem, const char* str, unsigned int hash) {
    if(currElem == NULL) {
        return NULL;
    }

    int diffResult = compare_target(currElem, hash);

    if(diffResult == 0) {
        return currElem;
    } else if(diffResult < 0) {
        return get_tree(currElem->right, str, hash);
    } else {
        return get_tree(currElem->left, str, hash);
    }
}
int get_height(Element* elem) {
    return elem == NULL ? 0 : elem->height;
}
Element* left_rotate(Tree* this, Element* currElem) {
    Element* topElem = currElem->right;
    currElem->right = topElem->left;
    topElem->left = currElem;

    topElem->height++;
    currElem->height--;

    return topElem;
}
Element* right_rotate(Tree* this, Element* currElem) {
    Element* topElem = currElem->left;
    currElem->left = topElem->right;
    topElem->right = currElem;

    topElem->height++;
    currElem->height--;

    return topElem;
}

LinkedNode* NewLinkedNode(void) {
    LinkedNode* newLinkedNode = (LinkedNode*)malloc(sizeof(LinkedNode));

    newLinkedNode->startNode = NULL;
    newLinkedNode->endNode = NULL;

    return newLinkedNode;
}
void addNode(LinkedNode* linkedNode, Element* elem) {
    Node* newNode = NewNode(elem);

    if(linkedNode->startNode == NULL) {
        linkedNode->startNode = newNode;
        linkedNode->endNode = newNode;
    } else {
        linkedNode->endNode->nextNode = newNode;
        newNode->prevNode = linkedNode->endNode;
        linkedNode->endNode = newNode;
    }

    return;
}
void freeAllNode(LinkedNode* linkedNode) {
    Node* node = linkedNode->startNode;
    while(node != NULL) {
        Node* tmpNode = node->nextNode;
        freeElement(tmpNode->chained_elem);
        freeNode(linkedNode, node);
        node = tmpNode;
    }

    free(linkedNode);

    return;
}

Element* NewElement(char* str, unsigned int hash) {
    Element* newElem = (Element*)malloc(sizeof(Element));
    newElem->str = (char*)str;
    newElem->hash = hash;
    newElem->height = 1;
    newElem->left = NULL;
    newElem->right = NULL;

    return newElem;
}
int compare_elem(Element* e1, Element* e2) {
    unsigned int hash1 = e1->hash;
    unsigned int hash2 = e2->hash;

    return hash1 > hash2 ? 1 : hash1 < hash2 ? -1 : 0;
}
int compare_target(Element* elem, unsigned int hash) {
    unsigned int hash1 = elem->hash;
    unsigned int hash2 = hash;

    return hash1 > hash2 ? 1 : hash1 < hash2 ? -1 : 0;
}
void freeElement(Element* elem) {
    free(elem->str);
    free(elem);

    return;
}

Node* NewNode(Element* chainedElem) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;
    newNode->chained_elem = NULL;

    return newNode;
}
void freeNode(LinkedNode* linkedNode, Node* node) {
    if(node->prevNode) {
        node->prevNode->nextNode = node->nextNode;
    }
    if(node->nextNode) {
        node->nextNode->prevNode = node->prevNode;
    }

    node->prevNode = NULL;
    node->nextNode = NULL;
    node->chained_elem = NULL;

    free(node);

    return;
}


char** tokenizer(const char* input) {
    int size = 5;
    int currSize = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    char* inputPtr = (char*)input;
    int start = 0;
    int end = 0;

    while(*inputPtr) {
        char ch = *inputPtr++;

        if(isBlank(ch)) {
            if(start == end) {
                start = ++end;
                continue;
            }

            int tknSize = end - start;
            char* newTkn = (char*)malloc(sizeof(char) * (tknSize + 1));
            *(newTkn + tknSize) = 0;
            char* newTknPtr = newTkn;

            while(start != end) {
                *newTknPtr++ = input[start++];
            }
            *tokensPtr++ = newTkn; currSize++;

            start = ++end;

            if(size == currSize) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char) * (size + 1));
                tokensPtr = (char**)(tokens + currSize);
            }
        } else {
            end++;
        }
    }
    *tokensPtr = NULL;

    return tokens;
}
void freeTokens(char** tokens) {
    char** tokensPtr = tokens;

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

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    HashMap* hashMap = NewHashMap();
    hashMap->add(hashMap, "ChongChong");

    while(--N >= 0) {
        fgets(input, sizeof(input), stdin);

        char** tokens = tokenizer(input);
        char** tokensPtr = tokens;

        _Bool isDance = 0;
        while(*tokensPtr) {
            Element* isElem = hashMap->get(hashMap, *tokensPtr++);
            if(isElem != NULL) {
                isDance = 1;
                break;
            }
        }

        if(isDance == 0) {
            continue;
        }

        tokensPtr = tokens;
        while(*tokensPtr) {
            hashMap->add(hashMap, *tokensPtr++);
        }

    }

    int result = hashMap->size;
    char* resultStr = intToStr(result);
    fputs(resultStr, stdout); fputc('\n', stdout);
    free(resultStr);

    return 0;
}
