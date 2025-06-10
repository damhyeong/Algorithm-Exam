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
1 초	128 MB	473699	220097	182554	46.372%
문제
(세 자리 수) × (세 자리 수)는 다음과 같은 과정을 통하여 이루어진다.

---

                    4   7   2 --- (1)
                x   3   8   2 --- (2)
-------------------------------------
                2   3   6   0 --- (3)
            3   7   7   6     --- (4)
        1   4   1   6         --- (5)
-------------------------------------
        1   8   1   7   2   0 --- (6)


---

(1)과 (2)위치에 들어갈 세 자리 자연수가 주어질 때 (3), (4), (5), (6)위치에 들어갈 값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 (1)의 위치에 들어갈 세 자리 자연수가, 둘째 줄에 (2)의 위치에 들어갈 세자리 자연수가 주어진다.

출력
첫째 줄부터 넷째 줄까지 차례대로 (3), (4), (5), (6)에 들어갈 값을 출력한다.

예제 입력 1
472
385
예제 출력 1
2360
3776
1416
181720
*/

#include<stdio.h>

extern void* malloc(size_t);
extern void free(void*);
extern void* realloc(void*, size_t);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main () {
    char str[255];

    char* input;
    input = fgets(str, sizeof(str), stdin);
    char* inputPtr = (char*)input;

    char numStr1[100];
    int idx = 0;
    while(isBlank(*inputPtr) != 1) {
        numStr1[idx++] = *inputPtr;
        inputPtr++;
    }
    numStr1[idx] = '\0';

    input = fgets(str, sizeof(str), stdin);
    inputPtr = (char*)input;

    char numStr2[100];
    idx = 0;
    while(isBlank(*inputPtr) != 1) {
        numStr2[idx++] = *inputPtr;
        inputPtr++;
    }
    numStr2[idx] = '\0';

    int num1 = parseInt(numStr1);

    int num2 = parseInt(numStr2);
    int num2Save = num2;

    int* list = (int*)malloc(sizeof(int) * (4 + 1));
    list[4] = -1;
    int* listPtr = (int*)list;



    while(num2 != 0) {
        int extract = num2 % 10; num2 /= 10;

        int tempResult = num1 * extract;

        *listPtr = tempResult;
        listPtr++;
    }

    *listPtr = num1 * num2Save;


    listPtr = (int*)list;

    while(*listPtr != -1) {
        fputs(intToStr(*listPtr), stdout);
        fputc('\n', stdout);
        listPtr++;
    }
}

char* intToStr(int target) {
    int sign = 1;

    if(target < 0) {
        sign = -1;
        target *= -1;
    }

    int len = 0;
    int temp = target;

    do {
        temp /= 10;
        len++;
    } while(temp != 0);

    int size = (sign == 1) ? len : len + 1;
    int startIdx = (sign == 1) ? 0 : 1;
    int endIdx = size - 1;

    char* result = (char*)malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    for(int i = endIdx; i >= startIdx; i--) {
        int extract = target % 10;
        target /= 10;
        result[i] = extract + '0';
    }

    if(sign == -1) {
        result[0] = '-';
    }
    return result;
}

int parseInt(const char* str) {
    int result = 0;
    int sign = 1;

    char* strPtr = (char*) str;

    while(isBlank(*strPtr) == 1) {
        strPtr++;
    }

    if(*strPtr == '-') {
        sign = -1;
        strPtr++;
    }

    while(*strPtr) {
        result *= 10;
        result += *strPtr - '0';

        strPtr++;
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
