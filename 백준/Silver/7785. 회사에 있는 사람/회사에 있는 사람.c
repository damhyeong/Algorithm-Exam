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
1 초	256 MB	78980	33342	25532	41.252%

문제
---
상근이는 세계적인 소프트웨어 회사 기글에서 일한다.

이 회사의 가장 큰 특징은 자유로운 출퇴근 시간이다.

따라서, 직원들은 반드시 9시부터 6시까지 회사에 있지 않아도 된다.

각 직원은 자기가 원할 때 출근할 수 있고, 아무때나 퇴근할 수 있다.

상근이는 모든 사람의 출입카드 시스템의 로그를 가지고 있다.

이 로그는 어떤 사람이 회사에 들어왔는지, 나갔는지가 기록되어져 있다.

로그가 주어졌을 때, 현재 회사에 있는 모든 사람을 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 로그에 기록된 출입 기록의 수 n이 주어진다. (2 ≤ n ≤ 10^6)

다음 n개의 줄에는 출입 기록이 순서대로 주어지며, 각 사람의 이름이 주어지고 "enter"나 "leave"가 주어진다.

"enter"인 경우는 출근, "leave"인 경우는 퇴근이다.

회사에는 동명이인이 없으며, 대소문자가 다른 경우에는 다른 이름이다.

사람들의 이름은 알파벳 대소문자로 구성된 5글자 이하의 문자열이다.


출력
---
현재 회사에 있는 사람의 이름을 사전 순의 역순으로 한 줄에 한 명씩 출력한다.

예제 입력 1
4
Baha enter
Askar enter
Baha leave
Artem enter
예제 출력 1
Askar
Artem
*/

/**
저번 문제에서 HashSet 직접 구현으로 이번에는 Heap_Sort 를 구현하려고 했는데,

엘리먼트의 요소를 단순히 "추가" 하는 것이 아니라, "제거" 를 해야 하는 상황이라 HashSet 을 다시 직접 구현해야 할 것 같다.

그런데, 문제를 유심히 보다 보니까, 굳이 HashSet 까지 구현하지 않고, Tree 로만 구현해도 되겠다는 생각이 든다.

이전에 추가하지 않았던 요소에 집중하기 위함이다.

---추가하지 않은 요소---

1. remove 기능 메서드

2. 남아있는 엘리먼트 전부 추출

여기서 남아있는 엘리먼트를 "어떻게?" 추출할 것인지가 조금 문제이다.

직관적으로 BFS 를 이용하고 난 뒤 다시 정렬하여 출력하는 것도 방법이지만,

애초에 새로운 엘리먼트가 생길 때, 이들의 주소를 저장할 배열을 만드는 것도 방법이라고 생각한다.

이는 LinkedList 로 만드는 것이 좋다고도 생각하긴 하는데, 그렇다면 LinkedList 또한 제작해야 한다..
*/


#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct Node {
    struct Node* nextNode;
    struct Node* prevNode;

    struct Element* chained_elem;

    void (*free_node)(struct Node* thisNode);
} Node;

Node* NewNode(void);
void free_node_node(Node* thisNode);

typedef struct Element {
    char* str;
    int height;
    Node* chained_node;

    struct Element* leftElem;
    struct Element* rightElem;

    int (*compare)(struct Element* element, const char* str);
} Element;

void swap_element(Element* e1, Element* e2) {
    char* tempStr = e1->str;
    e1->str = e2->str;
    e2->str = tempStr;

    return;
}

Element* NewElement(const char* newStr);
int compare_element(Element* element, const char* str);


typedef struct Tree {
    int size;
    Node* firstNode;
    Node* tailNode;

    Element* topElem;

    Element* (*get)(struct Tree* this, Element* currElem, const char* str);
    Element* (*add)(struct Tree* this, Element* currElem, const char* str);
    Element* (*remove)(struct Tree* this, Element* currElem, const char* str);

    int (*get_height)(struct Element* target);

    Element* (*left_rotate)(struct Tree* this, Element* currElem);
    Element* (*right_rotate)(struct Tree* this, Element* currElem);
} Tree;

void freeElement(Tree* tree, Element* this);

Tree* NewTree(void);

Element* get_tree(Tree* this, Element* currElem, const char* str);
Element* add_tree(Tree* this, Element* currElem, const char* str);
Element* remove_tree(Tree* this, Element* currElem, const char* str);

int get_height_tree(Element* target);

Element* left_rotate_tree(Tree* this, Element* currElem);
Element* right_rotate_tree(Tree* this, Element* currElem);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int compareStr(const char* s1, const char* s2) {
    char* s1Ptr = (char*)s1;
    char* s2Ptr = (char*)s2;

    while(*s1Ptr && *s2Ptr) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }
    }

    return (*s2Ptr == 0) ? (*s1Ptr == 0) ? 0 : 1 : -1;
}

void quickSort(char** strList, int start, int end) {
    if(start >= end) {
        return;
    }

    int pivot = start;
    int i = start;
    int j = end;

    while(i < j) {
        while(compareStr(*(strList + pivot), *(strList + j)) < 0) {
            j--;
        }
        while(i < j && compareStr(*(strList + pivot), *(strList + i)) >= 0) {
            i++;
        }

        char* tempStr = *(strList + j);
        *(strList + j) = *(strList + i);
        *(strList + i) = tempStr;
    }

    char* tempStr = *(strList + pivot);
    *(strList + pivot) = *(strList + i);
    *(strList + i) = tempStr;

    quickSort(strList, start, i - 1);
    quickSort(strList, i + 1, end);
}

int main(void) {
    char input[255];

    int tree_size = 30;

    Tree** trees = (Tree**)malloc(sizeof(Tree*) * (tree_size + 1));
    *(trees + tree_size) = 0;

    int idx = 0;
    while(idx < tree_size) {
        *(trees + idx) = NewTree();
        idx++;
    }

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    idx = 0;
    while(idx++ < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);

        char* name = *tokens;
        char* active = *(tokens + 1);

        int hash = (int)(*name) % tree_size;

        Tree* tree = *(trees + hash);

        if(compareStr(active, "enter") == 0) {
            tree->topElem = tree->add(tree, tree->topElem, name);
        } else if(compareStr(active, "leave") == 0) {
            tree->topElem = tree->remove(tree, tree->topElem, name);
        }
        freeTokens(tokens);
    }

    int size = 0;

    idx = 0;
    while(idx < tree_size) {
        Tree* tempTree = *(trees + idx);

        size += tempTree->size;

        idx++;
    }

    char** result = (char**)malloc(sizeof(char*) * (size + 1));
    *(result + size) = NULL;

    idx = 0;
    int i = 0;
    while(idx < tree_size) {
        Tree* tempTree = *(trees + idx);

        Node* tempNode = tempTree->firstNode;

        while(tempNode != NULL) {
            Element* tempElem = tempNode->chained_elem;
            tempNode = tempNode->nextNode;
            *(result + i) = tempElem->str;
            i++;
        }

        idx++;
    }

    // 정렬 시작
    quickSort(result, 0, size - 1);

    idx = size - 1;
    while(idx >= 0) {
        fputs(*(result + idx), stdout); fputc('\n', stdout);

        idx--;
    }

    return 0;
}

Node* NewNode(void) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    newNode->chained_elem = NULL;

    newNode->free_node = free_node_node;

    return newNode;
}
void free_node_node(Node* thisNode) {
    Node* nextNode = thisNode->nextNode;
    Node* prevNode = thisNode->prevNode;

    if(prevNode) {
        prevNode->nextNode = nextNode;
    }
    if(nextNode) {
        nextNode->prevNode = prevNode;
    }

    free(thisNode);

    return;
}

Element* NewElement(const char* newStr) {
    Element* newElem = (Element*)malloc(sizeof(Element));

    int len = 0;
    char* newStrPtr = (char*)newStr;
    while(*newStrPtr++) {
        len++;
    }

    char* elemStr = (char*)malloc(sizeof(char) * (len + 1));
    *(elemStr + len) = 0;

    int idx = 0;
    while(idx < len) {
        *(elemStr + idx) = *(newStr + idx);
        idx++;
    }

    newElem->str = elemStr;
    newElem->height = 1;

    newElem->chained_node = NULL;

    newElem->leftElem = NULL;
    newElem->rightElem = NULL;

    newElem->compare = compare_element;

    return newElem;
}
int compare_element(Element* element, const char* str) {
    char* elemStrPtr = element->str;
    char* strPtr = (char*)str;

    while(*elemStrPtr && *strPtr) {
        char ch1 = *elemStrPtr++;
        char ch2 = *strPtr++;

        if(ch1 < ch2) {
            return -1;
        } else if(ch1 > ch2) {
            return 1;
        }
    }

    return (*strPtr == 0) ? (*elemStrPtr == 0) ? 0 : 1 : -1;
}

void freeElement(Tree* tree, Element* this) {
    Node* currNode = this->chained_node;

    if (tree->firstNode == currNode) tree->firstNode = currNode->nextNode;
    if (tree->tailNode  == currNode) tree->tailNode  = currNode->prevNode;

    // 선택: 새 head/tail의 양방향 링크도 정리
    if (tree->firstNode) tree->firstNode->prevNode = NULL;
    if (tree->tailNode)  tree->tailNode->nextNode  = NULL;

    free(this->str);

    currNode->free_node(currNode);

    free(this);


    return;
}

Tree* NewTree(void) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));

    newTree->size = 0;
    newTree->firstNode = NULL;
    newTree->tailNode = NULL;

    newTree->topElem = NULL;

    newTree->get = get_tree;
    newTree->add = add_tree;
    newTree->remove = remove_tree;

    newTree->get_height = get_height_tree;

    newTree->left_rotate = left_rotate_tree;
    newTree->right_rotate = right_rotate_tree;

    return newTree;
}

Element* get_tree(Tree* this, Element* currElem, const char* str) {
    if(currElem == NULL) {
        return NULL;
    }

    int diffResult = currElem->compare(currElem, str);

    if(diffResult == 0) {
        return currElem;
    } else if(diffResult < 0) {
        return get_tree(this, currElem->rightElem, str);
    } else {
        return get_tree(this, currElem->leftElem, str);
    }
}
Element* add_tree(Tree* this, Element* currElem, const char* str) {
    if(currElem == NULL) {
        Element* newElem = NewElement(str);
        Node* newNode = NewNode();
        newElem->chained_node = newNode;
        newNode->chained_elem = newElem;

        if(this->size == 0) {
            this->firstNode = newNode;
            this->tailNode = newNode;
        } else {
            newNode->prevNode = this->tailNode;
            this->tailNode->nextNode = newNode;
            this->tailNode = newNode;
        }

        this->size++;

        return newElem;
    }

    int diffResult = currElem->compare(currElem, str);

    if(diffResult == 0) {
        return currElem;
    } else if(diffResult < 0) {
        currElem->rightElem = add_tree(this, currElem->rightElem, str);
    } else {
        currElem->leftElem = add_tree(this, currElem->leftElem, str);
    }

    int leftHeight = this->get_height(currElem->leftElem);
    int rightHeight = this->get_height(currElem->rightElem);

    int diff = leftHeight - rightHeight;

    // LL
    if(
        diff > 1 &&
        this->get_height(currElem->leftElem->leftElem) > this->get_height(currElem->leftElem->rightElem)
    ) {
        currElem = this->right_rotate(this, currElem);
    }
    // RR
    if(
        diff < -1 &&
        this->get_height(currElem->rightElem->rightElem) > this->get_height(currElem->rightElem->leftElem)
    ) {
        currElem = this->left_rotate(this, currElem);
    }
    // LR
    if(
        diff > 1 &&
        this->get_height(currElem->leftElem->rightElem) > this->get_height(currElem->leftElem->leftElem)
    ) {
        currElem->leftElem = this->left_rotate(this, currElem->leftElem);
        currElem = this->right_rotate(this, currElem);
    }
    // RL
    if(
        diff < -1 &&
        this->get_height(currElem->rightElem->leftElem) > this->get_height(currElem->rightElem->rightElem)
    ) {
        currElem->rightElem = this->right_rotate(this, currElem->rightElem);
        currElem = this->left_rotate(this, currElem);
    }

    leftHeight = this->get_height(currElem->leftElem);
    rightHeight = this->get_height(currElem->rightElem);

    currElem->height
        = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

    return currElem;
}
Element* remove_tree(Tree* this, Element* currElem, const char* str) {
    if(currElem == NULL) {
        return NULL;
    }

    int compareResult = currElem->compare(currElem, str);

    if(compareResult == 0) {
        // freeElement 메소드에서 해제 절차를 밣자.
        // Node* currNode = currElem->chained_node;

        Element* leftElem = currElem->leftElem;
        Element* rightElem = currElem->rightElem;

        if(leftElem == NULL && rightElem == NULL) {
            this->size--;
            freeElement(this, currElem);
            return NULL;
        } else if(leftElem == NULL) {
            this->size--;
            freeElement(this, currElem);
            return rightElem;
        } else if(rightElem == NULL) {
            this->size--;
            freeElement(this, currElem);
            return leftElem;
        } else { // 왼쪽 오른쪽 둘 다 있다는 소리.
            // 나의 경우, 오른쪽 트리의 "최소값" 을 찾는 재귀를 통해 해결한다.
            // 이미 균형잡힌 트리가 형성되었으므로, 이를 사용할 수 있다.
            // 이번에는 따로 메서드로 빼지 않고, 여기서 직접 수행한다.
            Element* parent = currElem;
            Element* tempRoot = currElem->rightElem;
            while(tempRoot->leftElem != NULL) {
                parent = tempRoot;
                tempRoot = tempRoot->leftElem;
            }

            Element* lowerRightElem = NULL;
            if(tempRoot->rightElem != NULL) {
                lowerRightElem = tempRoot->rightElem;
            }

            // 내부 값인 str 값만 서로 바꾼다.
            swap_element(currElem, tempRoot);

            if (parent == currElem) {
                // succ가 currElem의 즉시 오른쪽 자식이었던 경우
                parent->rightElem = lowerRightElem;
            } else {
                // 일반적으로 parent의 left가 succ였음
                parent->leftElem = lowerRightElem;
            }

            this->size--;
            freeElement(this, tempRoot);
        }

    } else if(compareResult < 0){
        currElem->rightElem = remove_tree(this, currElem->rightElem, str);
    } else {
        currElem->leftElem = remove_tree(this, currElem->leftElem, str);
    }

    int leftHeight = this->get_height(currElem->leftElem);
    int rightHeight = this->get_height(currElem->rightElem);

    int diff = leftHeight - rightHeight;

    // LL
    if(
        diff > 1 &&
        this->get_height(currElem->leftElem->leftElem) > this->get_height(currElem->leftElem->rightElem)
    ) {
        currElem = this->right_rotate(this, currElem);
    }
    // RR
    if(
        diff < -1 &&
        this->get_height(currElem->rightElem->rightElem) > this->get_height(currElem->rightElem->leftElem)
    ) {
        currElem = this->left_rotate(this, currElem);
    }
    // LR
    if(
        diff > 1 &&
        this->get_height(currElem->leftElem->rightElem) > this->get_height(currElem->leftElem->leftElem)
    ) {
        currElem->leftElem = this->left_rotate(this, currElem->leftElem);
        currElem = this->right_rotate(this, currElem);
    }
    // RL
    if(
        diff < -1 &&
        this->get_height(currElem->rightElem->leftElem) > this->get_height(currElem->rightElem->rightElem)
    ) {
        currElem->rightElem = this->right_rotate(this, currElem->rightElem);
        currElem = this->left_rotate(this, currElem);
    }


    leftHeight = this->get_height(currElem->leftElem);
    rightHeight = this->get_height(currElem->rightElem);

    currElem->height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

    return currElem;
}

int get_height_tree(Element* target) {
    return target == NULL ? 0 : target->height;
}

Element* left_rotate_tree(Tree* this, Element* currElem) {
    Element* rootElement = currElem->rightElem;
    currElem->rightElem = rootElement->leftElem;
    rootElement->leftElem = currElem;

    int newLeftHeight = this->get_height(rootElement->leftElem);
    int newRightHeight = this->get_height(rootElement->rightElem);

    rootElement->height =
        newLeftHeight > newRightHeight ? newLeftHeight + 1 : newRightHeight + 1;

    return rootElement;
}
Element* right_rotate_tree(Tree* this, Element* currElem) {
    Element* rootElement = currElem->leftElem;
    currElem->leftElem = rootElement->rightElem;
    rootElement->rightElem = currElem;

    int newLeftHeight = this->get_height(rootElement->leftElem);
    int newRightHeight = this->get_height(rootElement->rightElem);

    rootElement->height =
        newLeftHeight > newRightHeight ? newLeftHeight + 1 : newRightHeight + 1;

    return rootElement;
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
