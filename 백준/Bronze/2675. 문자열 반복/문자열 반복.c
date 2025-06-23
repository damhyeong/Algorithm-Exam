/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.

    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!
*/
/**
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	128 MB	279172	140927	119019	50.168%

문제
---
문자열 S를 입력받은 후에, 각 문자를 R번 반복해 새 문자열 P를 만든 후 출력하는 프로그램을 작성하시오.

즉, 첫 번째 문자를 R번 반복하고, 두 번째 문자를 R번 반복하는 식으로 P를 만들면 된다.

S에는 QR Code "alphanumeric" 문자만 들어있다.

QR Code "alphanumeric" 문자는

0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\$%*+-./: 이다.

입력
---
첫째 줄에 테스트 케이스의 개수 T(1 ≤ T ≤ 1,000)가 주어진다.

각 테스트 케이스는 반복 횟수 R(1 ≤ R ≤ 8), 문자열 S가 공백으로 구분되어 주어진다.

S의 길이는 적어도 1이며, 20글자를 넘지 않는다.

출력
---
각 테스트 케이스에 대해 P를 출력한다.

예제 입력 1
2
3 ABC
5 /HTP
예제 출력 1
AAABBBCCC
/////HHHHHTTTTTPPPPP
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct StringBuilder {
    struct StringBuilder* this;

    int size;
    int currIdx;

    char* str;
    char* strPtr;

    struct StringBuilder* (*append_str)(struct StringBuilder* this, const char* newStr);
    struct StringBuilder* (*append_ch)(struct StringBuilder* this, char newCh);
    const char* (*to_string)(struct StringBuilder* this);

} StringBuilder;

StringBuilder* NewStringBuilder(void);
void DeleteStringBuilder(StringBuilder* this);

StringBuilder* append_str_sb(StringBuilder* this, const char* newStr);
StringBuilder* append_ch_sb(StringBuilder* this, char newCh);

const char* to_string_sb(StringBuilder* this);

void resize(StringBuilder* this);

char** tokenizer(const char* input);
void freeTokens(char** tokens);
char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);


int main(void) {
    char input[1000];

    fgets(input, sizeof(input), stdin);

    int loop = parseInt(input);

    StringBuilder* sb = NewStringBuilder();

    while(--loop >= 0) {
        fgets(input, sizeof(input), stdin);

        char** tokens = (char**)tokenizer(input);
        char** tokensPtr = (char**)tokens;

        int R = parseInt(*tokensPtr++);
        char* S = *tokensPtr++;

        char* SPtr = (char*)S;

        while(*SPtr) {
            char ch = *SPtr++;
            int idx = 0;

            while(idx++ < R) {
                sb->append_ch(sb, ch);
            }
        }
        sb->append_ch(sb, '\n');

        freeTokens(tokens);
    }

    fputs(sb->to_string(sb), stdout);

    DeleteStringBuilder(sb);

    return 0;
}

StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*) malloc(sizeof(StringBuilder));

    sb->this = sb;

    sb->size = 5;
    sb->currIdx = 0;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    *(sb->str + sb->size) = '\0';
    sb->strPtr = (char*)sb->str;

    sb->append_str = append_str_sb;
    sb->append_ch = append_ch_sb;
    sb->to_string = to_string_sb;

    return sb;
}
void DeleteStringBuilder(StringBuilder* this) {
    free(this->str);
    free(this);
}

StringBuilder* append_str_sb(StringBuilder* this, const char* newStr) {
    char* newStrPtr = (char*)newStr;

    while(*newStrPtr) {
        *(this->strPtr++) = *newStrPtr++; this->currIdx++;

        if(this->size == this->currIdx) {
            resize(this);
        }
    }
    *this->strPtr = '\0';

    return this;
}
StringBuilder* append_ch_sb(StringBuilder* this, char newCh) {
    *this->strPtr++ = newCh; this->currIdx++;

    if(this->size == this->currIdx) {
        resize(this);
    }

    return this;
}
const char* to_string_sb(StringBuilder* this) {
    *this->strPtr = '\0';
    return this->str;
}

void resize(StringBuilder* this) {
    this->size *= 2;

    this->str = (char*)realloc(this->str, sizeof(char) * (this->size + 1));
    *(this->str + this->size) = '\0';

    if(this->str == NULL) {
        fputs("ERR : resize 과정에서 에러 발생\n", stderr);
    }

    this->strPtr = (char*)(this->str + this->currIdx);

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
            *(newTkn + tknSize) = '\0';
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
    } while (temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    *(result + size) = '\0';

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
    if(ch == 32 || ch == '\0') {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
