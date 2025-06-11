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
1 초	512 MB	328183	197588	169730	60.820%
문제
흔한 수학 문제 중 하나는 주어진 점이 어느 사분면에 속하는지 알아내는 것이다. 사분면은 아래 그림처럼 1부터 4까지 번호를 갖는다. "Quadrant n"은 "제n사분면"이라는 뜻이다.


                    |
                    |
         2          |          1
                    |
                    |
----------------------------------------
                    |
                    |
         3          |          4
                    |
                    |
                    |


예를 들어, 좌표가 (12, 5)인 점 A는 x좌표와 y좌표가 모두 양수이므로 제1사분면에 속한다. 점 B는 x좌표가 음수이고 y좌표가 양수이므로 제2사분면에 속한다.

점의 좌표를 입력받아 그 점이 어느 사분면에 속하는지 알아내는 프로그램을 작성하시오. 단, x좌표와 y좌표는 모두 양수나 음수라고 가정한다.

입력
첫 줄에는 정수 x가 주어진다. (−1000 ≤ x ≤ 1000; x ≠ 0) 다음 줄에는 정수 y가 주어진다. (−1000 ≤ y ≤ 1000; y ≠ 0)

출력
점 (x, y)의 사분면 번호(1, 2, 3, 4 중 하나)를 출력한다.

예제 입력 1
12
5
예제 출력 1
1
예제 입력 2
9
-13
예제 출력 2
4
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main () {
    char input[255];

    fgets(input, sizeof(input), stdin);

    int x = parseInt(input);

    fgets(input, sizeof(input), stdin);

    int y = parseInt(input);

    char* result;
    if(x > 0) {
        if(y > 0) {
            result = intToStr(1);
        } else {
            result = intToStr(4);
        }
    } else {
        if(y > 0) {
            result = intToStr(2);
        } else {
            result = intToStr(3);
        }
    }

    fputs(result, stdout);
    fputc('\n', stdout);

    free(result);

    return 0;
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
        len++;
        temp /= 10;
    } while (temp != 0);

    int size = sign == 1 ? len : len + 1;
    int endIdx = size - 1;
    int startIdx = sign == 1 ? 0 : 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        result[i] = target % 10 + '0';
        target /= 10;
    }
    if(sign == -1) {
        result[0] = '-';
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
    if(ch == 32) {
        return 1;
    } else if(ch >= 9 && ch <= 13) {
        return 1;
    } else {
        return 0;
    }
}
