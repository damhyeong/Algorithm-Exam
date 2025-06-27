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
1 초	256 MB	287100	95868	80080	35.687%

문제
---
입력 받은 대로 출력하는 프로그램을 작성하시오.


입력
---
입력이 주어진다.

입력은 최대 100줄로 이루어져 있고, 알파벳 소문자, 대문자, 공백, 숫자로만 이루어져 있다.

각 줄은 100글자를 넘지 않으며, 빈 줄은 주어지지 않는다.

또, 각 줄은 공백으로 시작하지 않고, 공백으로 끝나지 않는다.


출력
---
입력받은 그대로 출력한다.

예제 입력 1
Hello
Baekjoon
Online Judge
예제 출력 1
Hello
Baekjoon
Online Judge
*/

#include<stdio.h>

typedef struct StringBuilder {
    int size;
    int currIdx;

    char* str;
    char* strPtr;

    struct StringBuilder* (*append_ch)(struct StringBuilder* this, char newCh);
    char* (*to_string)(struct StringBuilder* this);
} StringBuilder;

StringBuilder* NewStringBuilder(void);
void DeleteStringBuilder(StringBuilder* this);

StringBuilder* append_ch_sb(StringBuilder* this, char newCh);
char* to_string_sb(StringBuilder* this);

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

int main(void) {
    char ch;

    StringBuilder* sb = NewStringBuilder();

    while((ch = fgetc(stdin)) != -1) {
        sb->append_ch(sb, ch);
    }

    fputs(sb->to_string(sb), stdout);

    DeleteStringBuilder(sb);

    return 0;
}


StringBuilder* NewStringBuilder(void) {
    StringBuilder* sb = (StringBuilder*) malloc(sizeof(StringBuilder));

    sb->size = 2;
    sb->currIdx = 0;

    sb->str = (char*)malloc(sizeof(char) * (sb->size + 1));
    *(sb->str + sb->size) = 0;
    sb->strPtr = sb->str;

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
char* to_string_sb(StringBuilder* this) {
    *this->strPtr = 0;
    return this->str;
}
