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
팰린드롬인지 확인하기 성공
시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
1 초	256 MB	112626	68500	57533	60.781%
문제
알파벳 소문자로만 이루어진 단어가 주어진다. 이때, 이 단어가 팰린드롬인지 아닌지 확인하는 프로그램을 작성하시오.

팰린드롬이란 앞으로 읽을 때와 거꾸로 읽을 때 똑같은 단어를 말한다.

level, noon은 팰린드롬이고, baekjoon, online, judge는 팰린드롬이 아니다.

입력
첫째 줄에 단어가 주어진다. 단어의 길이는 1보다 크거나 같고, 100보다 작거나 같으며, 알파벳 소문자로만 이루어져 있다.

출력
첫째 줄에 팰린드롬이면 1, 아니면 0을 출력한다.

예제 입력 1
level
예제 출력 1
1
예제 입력 2
baekjoon
예제 출력 2
0
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

    struct StringBuilder* (*append_ch)(struct StringBuilder* this, char newCh);
    const char* (*to_string)(struct StringBuilder* this);
} StringBuilder;

StringBuilder* NewStringBuilder(void);
void DeleteStringBuilder(StringBuilder* this);

StringBuilder* append_ch_sb(StringBuilder* this, char newCh);
const char* to_string_sb(StringBuilder* this);

_Bool isBlank(char ch);

int main(void) {
    char inputCh;

    StringBuilder* sb = NewStringBuilder();

    while((inputCh = fgetc(stdin)) != -1 && isBlank(inputCh) != 1) {
        sb->append_ch(sb, inputCh);
    }

    int i = 0;
    int j = sb->currIdx - 1;

    const char* str = sb->to_string(sb);

    _Bool isPalindrome = 1;

    while(i < j) {
        char first = *(str + i++);
        char end = *(str + j--);

        if(first != end) {
            isPalindrome = 0;
            break;
        }
    }

    DeleteStringBuilder(sb);

    if(isPalindrome == 1) {
        fputs("1\n", stdout);
    } else {
        fputs("0\n", stdout);
    }

    return 0;
}

StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*) malloc(sizeof(StringBuilder));

    sb->size = 2;
    sb->currIdx = 0;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    *(sb->str + sb->size) = 0;
    sb->strPtr = (char*)sb->str;

    sb->append_ch = append_ch_sb;
    sb->to_string = to_string_sb;

    return sb;
}
void DeleteStringBuilder(StringBuilder* this) {
    free(this->str);
    free(this);
}

StringBuilder* append_ch_sb(StringBuilder* this, char newCh) {
    *this->strPtr++ = newCh; this->currIdx++;

    if(this->size == this->currIdx) {
        this->size *= 2;
        this->str = (char*)realloc(this->str, sizeof(char) * (this->size + 1));
        *(this->str + this->size) = 0;
        this->strPtr = (char*)(this->str + this->currIdx);
    }

    return this;
}
const char* to_string_sb(StringBuilder* this) {
    *this->strPtr = 0;
    return this->str;
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
