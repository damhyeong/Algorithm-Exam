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
2 초	128 MB	67772	33955	30003	50.705%
문제
어떤 숫자 n이 자신을 제외한 모든 약수들의 합과 같으면, 그 수를 완전수라고 한다.

예를 들어 6은 6 = 1 + 2 + 3 으로 완전수이다.

n이 완전수인지 아닌지 판단해주는 프로그램을 작성하라.

입력
입력은 테스트 케이스마다 한 줄 간격으로 n이 주어진다. (2 < n < 100,000)

입력의 마지막엔 -1이 주어진다.

출력
테스트케이스 마다 한줄에 하나씩 출력해야 한다.

n이 완전수라면, n을 n이 아닌 약수들의 합으로 나타내어 출력한다(예제 출력 참고).

이때, 약수들은 오름차순으로 나열해야 한다.

n이 완전수가 아니라면 n is NOT perfect. 를 출력한다.

예제 입력 1
6
12
28
-1
예제 출력 1
6 = 1 + 2 + 3
12 is NOT perfect.
28 = 1 + 2 + 4 + 7 + 14
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

typedef struct StringBuilder {
    int size;
    int currIdx;

    char* str;
    char* strPtr;

    struct StringBuilder* (*append_str)(struct StringBuilder* this, const char* newStr);
    char* (*to_string)(struct StringBuilder* this);
} StringBuilder;

StringBuilder* NewStringBuilder(void);
void DelStringBuilder(StringBuilder* this);

StringBuilder* append_str_sb(StringBuilder* this, const char* newStr);
char* to_string_sb(StringBuilder* this);

char* insertStr(char* targetPtr, char* str);
_Bool isEqual(const char* s1, const char* s2);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    StringBuilder* sb = NewStringBuilder();

    while(1) {
        fgets(input, sizeof(input), stdin);

        if(isEqual(input, "-1") == 1) {
            break;
        }

        char* tempStr = (char*)malloc(sizeof(char) * (10001));
        *(tempStr + 10000) = 0;
        char* tempStrPtr = (char*)tempStr;

        int number = parseInt(input);
        int check = 1;

        int total = 0;

        tempStrPtr = insertStr(tempStrPtr, intToStr(number));
        tempStrPtr = insertStr(tempStrPtr, " = ");

        while(check <= (number / 2)) {
            if(number % check == 0) {
                total += check;

                char* checkNumStr = intToStr(check);

                tempStrPtr = insertStr(tempStrPtr, checkNumStr);
                tempStrPtr = insertStr(tempStrPtr, " + ");
                free(checkNumStr);
            }
            check++;
        }
        *tempStrPtr = 0;

        // remove last of " + "
        tempStrPtr = (char*)(tempStrPtr - 2);
        *tempStrPtr = 0;

        if(total == number) {
            sb->append_str(sb, tempStr)->append_str(sb, "\n");
        } else {
            char* numStr = intToStr(number);
            sb->append_str(sb, numStr)->append_str(sb, " is NOT perfect.\n");
            free(numStr);
        }

        free(tempStr);
    }

    char* result = sb->to_string(sb);
    fputs(result, stdout);

    DelStringBuilder(sb);

    return 0;
}

StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*)malloc(sizeof(StringBuilder));

    sb->size = 50;
    sb->currIdx = 0;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    sb->strPtr = (char*)sb->str;

    sb->append_str = append_str_sb;
    sb->to_string = to_string_sb;

    return sb;
}

void DelStringBuilder(StringBuilder* this) {
    free(this->str);
    free(this);

    return;
}

StringBuilder* append_str_sb(StringBuilder* this, const char* newStr) {
    char* newStrPtr = (char*)newStr;

    while(*newStrPtr != 0) {
        *this->strPtr++ = *newStrPtr++; this->currIdx++;

        if(this->size == this->currIdx) {
            this->size *= (this->size * 3) / 2;
            this->str = (char*)realloc(this->str, sizeof(char) * (this->size + 1));
            this->strPtr = (char*)(this->str + this->currIdx);
        }
    }

    return this;
}
char* to_string_sb(StringBuilder* this) {
    *this->strPtr = 0;
    return this->str;
}

char* insertStr(char* targetPtr, char* str) {
    while(*str) {
        *targetPtr++ = *str++;
    }
    return targetPtr;
}
_Bool isEqual(const char* s1, const char* s2) {
    char* s1Ptr = (char*)s1;
    char* s2Ptr = (char*)s2;

    _Bool isSame = 1;

    while(isBlank(*s1Ptr) != 1 && isBlank(*s2Ptr) != 1) {
        char ch1 = *s1Ptr++;
        char ch2 = *s2Ptr++;

        if(ch1 != ch2) {
            isSame = 0;
            break;
        }
    }

    return isSame;
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
