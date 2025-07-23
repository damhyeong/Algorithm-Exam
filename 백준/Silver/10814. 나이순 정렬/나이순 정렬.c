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
3 초	256 MB	179874	82795	63842	44.512%

문제
---
온라인 저지에 가입한 사람들의 나이와 이름이 가입한 순서대로 주어진다.

이때,

1. 회원들을 나이가 증가하는 순으로,

2. 나이가 같으면 먼저 가입한 사람이 앞에 오는 순서로

정렬하는 프로그램을 작성하시오.

입력
---
첫째 줄에 온라인 저지 회원의 수 N이 주어진다.

(1 ≤ N ≤ 100,000)


둘째 줄부터 N개의 줄에는 각 회원의 나이와 이름이 공백으로 구분되어 주어진다.

나이는 1보다 크거나 같으며,
200보다 작거나 같은 정수이고,
이름은 알파벳 대소문자로 이루어져 있고,
길이가 100보다 작거나 같은 문자열이다.

입력은 가입한 순서로 주어진다.


출력
---
첫째 줄부터 총 N개의 줄에 걸쳐 온라인 저지

회원을 나이 순,

나이가 같으면 가입한 순으로

한 줄에 한 명씩 나이와 이름을 공백으로 구분해 출력한다.


예제 입력 1
3
21 Junkyu
21 Dohyun
20 Sunyoung
예제 출력 1
20 Sunyoung
21 Junkyu
21 Dohyun
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct User {
    int age;
    int idx;
    char* name;

    void (*print)(struct User* this);
} User;

User* NewUser(int age, int idx, const char* nameStr);
void DelUser(User* this);
void freeUsers(User** userList);
void print_user(User* this);
int compare_user(User* u1, User* u2);

User** sort_merge(User** usrList, int length);
User* copy_user(User* target);

char** tokenzier(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int N = parseInt(input);

    User** usrList = (User**)malloc(sizeof(char*) * (N + 1));
    *(usrList + N) = NULL;

    int idx = 0;
    while(idx < N) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenzier(input);
        char** tokensPtr = (char**)tokens;

        int age = parseInt(*tokensPtr++);

        // 바로 free 하면 안됨.
        char* name = *tokensPtr++;

        User* newUser = NewUser(age, idx, name);

        *(usrList + idx) = newUser;

        free(tokens);

        idx++;
    }

    usrList = sort_merge(usrList, N);

    idx = 0;
    while(idx < N) {
        User* tempUsr = *(usrList + idx++);
        tempUsr->print(tempUsr);
    }

    freeUsers(usrList);

    return 0;
}

User* NewUser(int age, int idx, const char* nameStr) {
    User* newUser = (User*)malloc(sizeof(User));

    newUser->age = age;
    newUser->idx = idx;

    int len = 0;
    char* nameStrPtr = (char*)nameStr;
    while(*nameStrPtr++) {
        len++;
    }

    char* newName = (char*)malloc(sizeof(char) * (len + 1));
    *(newName + len) = 0;

    int i = 0;
    while(i < len) {
        *(newName + i) = *(nameStr + i);
        i++;
    }

    newUser->name = newName;

    newUser->print = print_user;

    return newUser;
}
void DelUser(User* this) {
    free(this->name);
    free(this);
}
void freeUsers(User** userList) {
    User** usrListPtr = (User**)userList;

    while(*usrListPtr) {
        DelUser(*usrListPtr++);
    }
    free(userList);

    return;
}
void print_user(User* this) {
    char* ageStr = intToStr(this->age);
    char* nameStr = this->name;

    fputs(ageStr, stdout); fputc(' ', stdout); fputs(nameStr, stdout); fputc('\n', stdout);

    free(ageStr);

    return;
}
int compare_user(User* u1, User* u2) {
    int u1Age = u1->age;
    int u2Age = u2->age;

    int u1Idx = u1->idx;
    int u2Idx = u2->idx;

    if(u1Age == u2Age) {
        return u1Idx < u2Idx ? -1 : 1;
    } else {
        return u1Age < u2Age ? -1 : 1;
    }
}

User** sort_merge(User** usrList, int length) {
    if(length <= 1) {
        return usrList;
    }

    int leftLen = length / 2;
    int rightLen = length - leftLen;

    User** leftUsers = (User**)malloc(sizeof(User*) * (leftLen + 1));
    *(leftUsers + leftLen) = NULL;
    User** rightUsers = (User**)malloc(sizeof(User*) * (rightLen + 1));
    *(rightUsers + rightLen) = NULL;

    int i = 0, idx = 0;
    while(i < leftLen) {
        *(leftUsers + i++) = copy_user(*(usrList + idx++));
    }
    i = 0;
    while(i < rightLen) {
        *(rightUsers + i++) = copy_user(*(usrList + idx++));
    }

    leftUsers = sort_merge(leftUsers, leftLen);
    rightUsers = sort_merge(rightUsers, rightLen);

    freeUsers(usrList);
    usrList = (User**)malloc(sizeof(User*) * (length + 1));
    *(usrList + length) = NULL;

    i = 0, idx = 0;
    int j = 0;

    while(i < leftLen && j < rightLen) {
        if(compare_user(*(leftUsers + i), *(rightUsers + j)) < 0) {
            *(usrList + idx++) = copy_user(*(leftUsers + i++));
        } else {
            *(usrList + idx++) = copy_user(*(rightUsers + j++));
        }
    }

    while(i < leftLen) {
        *(usrList + idx++) = copy_user(*(leftUsers + i++));
    }
    while(j < rightLen) {
        *(usrList + idx++) = copy_user(*(rightUsers + j++));
    }

    freeUsers(leftUsers); freeUsers(rightUsers);

    return usrList;
}
User* copy_user(User* target) {
    User* copyUser = (User*)malloc(sizeof(User));

    copyUser->age = target->age;
    copyUser->idx = target->idx;
    copyUser->print = print_user;

    int len = 0;
    char* targetNamePtr = target->name;
    while(*targetNamePtr++) {
        len++;
    }
    targetNamePtr = target->name;

    copyUser->name = (char*)malloc(sizeof(char) * (len + 1));
    *(copyUser->name + len) = 0;

    int idx = 0;
    while(idx < len) {
        *(copyUser->name + idx) = *(target->name + idx);
        idx++;
    }

    return copyUser;
}


char** tokenzier(const char* input) {
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
                tokens = (char**)malloc(sizeof(char*) * (size + 1));
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
        target *= -1;
        sign = -1;
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
