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
2 초	128 MB	338157	137585	107793	40.257%
문제
알파벳 대소문자로 된 단어가 주어지면, 이 단어에서 가장 많이 사용된 알파벳이 무엇인지 알아내는 프로그램을 작성하시오. 단, 대문자와 소문자를 구분하지 않는다.

입력
첫째 줄에 알파벳 대소문자로 이루어진 단어가 주어진다. 주어지는 단어의 길이는 1,000,000을 넘지 않는다.

출력
첫째 줄에 이 단어에서 가장 많이 사용된 알파벳을 대문자로 출력한다. 단, 가장 많이 사용된 알파벳이 여러 개 존재하는 경우에는 ?를 출력한다.

예제 입력 1
Mississipi
예제 출력 1
?
예제 입력 2
zZa
예제 출력 2
Z
예제 입력 3
z
예제 출력 3
Z
예제 입력 4
baaa
예제 출력 4
A
*/

#include<stdio.h>

extern void* calloc(size_t size, size_t byte);
extern void free(void* memory);

_Bool isBlank(char ch);

int main(void) {
    char inputCh;
    int size = 'z' - 'a' + 1;
    int* alphabet = (int*)calloc(size, sizeof(int));

    while((inputCh = fgetc(stdin)) != -1 && isBlank(inputCh) != 1) {
        if(inputCh >= 'A' && inputCh <= 'Z') {
            int temp = inputCh - 'A';
            *(alphabet + temp) += 1;
        } else {
            int temp = inputCh - 'a';
            *(alphabet + temp) += 1;
        }
    }

    char mostShown;
    int biggest = -1;
    _Bool isDuplicate = 0;

    int idx = 0;

    mostShown = idx++ + 'A';
    biggest = *alphabet;

    while(idx < size) {
        int temp = *(alphabet + idx);

        if(biggest < temp) {
            isDuplicate = 0;
            mostShown = idx + 'A';
            biggest = temp;
        } else if(biggest == temp) {
            isDuplicate = 1;
        }

        idx++;
    }

    if(isDuplicate == 1) {
        fputs("?\n", stdout);
    } else {
        fputc(mostShown, stdout); fputc('\n', stdout);
    }

    free(alphabet);

    return 0;
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
