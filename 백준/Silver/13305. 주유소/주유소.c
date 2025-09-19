/**
    @Author : 공담형
    @Email : rhdwhdals8765@gmail.com
    @Github : https://github.com/damhyeong
    @Blog : https://codecreature.tistory.com

    "코드를 보다가 궁금하시면 EMAIL 로 연락 주셔도 괜찮습니다!"

    "최소한의" 기능과 라이브러리를 사용하고, 나머지 기능을 직접 구현하기 때문에,

    다른 C 코드를 참조하시는 것이 좋습니다.


    블로그에서 다양한 컴퓨터 관점과 Computer Science 를 다루고 있으니 궁금하면 들러보셔요!

    참고로, AI 작성 글이 아니라, 진짜 공식문서 뒤져가면서 힘들게 얻은 지식을 나눠보려고 합니다.
*/

/**
주유소 서브태스크

시간 제한	메모리 제한	제출	정답	맞힌 사람	정답 비율
2 초	512 MB	83638	33537	26134	39.566%

문제
---
어떤 나라에 N개의 도시가 있다.

이 도시들은 일직선 도로 위에 있다.

편의상 일직선을 수평 방향으로 두자.

제일 왼쪽의 도시에서 제일 오른쪽의 도시로 자동차를 이용하여 이동하려고 한다.

인접한 두 도시 사이의 도로들은 서로 길이가 다를 수 있다.

도로 길이의 단위는 km 를 사용한다.

처음 출발할 때 자동차에는 기름이 없어서 주유소에서 기름을 넣고 출발하여야 한다.

기름통의 크기는 무제한이어서 얼마든지 많은 기름을 넣을 수 있다.

도로를 이용하여 이동할 때 1km마다 1리터의 기름을 사용한다.

각 도시에는 단 하나의 주유소가 있으며, 도시 마다 주유소의 리터당 가격은 다를 수 있다.

가격의 단위는 원을 사용한다.

예를 들어, 이 나라에 다음 그림처럼 4개의 도시가 있다고 하자.

원 안에 있는 숫자는 그 도시에 있는 주유소의 리터당 가격이다.

도로 위에 있는 숫자는 도로의 길이를 표시한 것이다.


         2             3             1
( 5 ) ------> ( 2 ) ------> ( 4 ) ------> ( 1 )


제일 왼쪽 도시에서 6리터의 기름을 넣고, 더 이상의 주유 없이 제일 오른쪽 도시까지 이동하면 총 비용은 30원이다.

만약 제일 왼쪽 도시에서 2리터의 기름을 넣고(2×5 = 10원)

다음 번 도시까지 이동한 후 3리터의 기름을 넣고(3×2 = 6원)

다음 도시에서 1리터의 기름을 넣어(1×4 = 4원) 제일 오른쪽 도시로 이동하면,

총 비용은 20원이다.

또 다른 방법으로

제일 왼쪽 도시에서 2리터의 기름을 넣고(2×5 = 10원)

다음 번 도시까지 이동한 후 4리터의 기름을 넣고(4×2 = 8원)

제일 오른쪽 도시까지 이동하면,

총 비용은 18원이다.

각 도시에 있는 주유소의 기름 가격과,

각 도시를 연결하는 도로의 길이를 입력으로 받아

제일 왼쪽 도시에서 제일 오른쪽 도시로 이동하는 최소의 비용을 계산하는 프로그램을 작성하시오.

입력
---
표준 입력으로 다음 정보가 주어진다.

첫 번째 줄에는 도시의 개수를 나타내는 정수 N(2 ≤ N ≤ 100,000)이 주어진다.

다음 줄에는 인접한 두 도시를 연결하는 도로의 길이가 제일 왼쪽 도로부터 N-1개의 자연수로 주어진다.

다음 줄에는 주유소의 리터당 가격이 제일 왼쪽 도시부터 순서대로 N개의 자연수로 주어진다.

제일 왼쪽 도시부터 제일 오른쪽 도시까지의 거리는 1이상 1,000,000,000 이하의 자연수이다.

리터당 가격은 1 이상 1,000,000,000 이하의 자연수이다.

출력
---
표준 출력으로 제일 왼쪽 도시에서 제일 오른쪽 도시로 가는 최소 비용을 출력한다.

서브태스크
-------
번호	배점	제한
1	 17
모든 주유소의 리터당 가격은 1원이다.

2	 41
2 ≤ N ≤ 1,000, 제일 왼쪽 도시부터 제일 오른쪽 도시까지의 거리는 최대 10,000, 리터 당 가격은 최대 10,000이다.

3	 42
원래의 제약조건 이외에 아무 제약조건이 없다.


예제 입력 1
4
2 3 1
5 2 4 1
예제 출력 1
18
예제 입력 2
4
3 3 4
1 1 1 1
예제 출력 2
10
*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);

char** tokenizer(FILE* stream);
void freeArrs(void** arrs);

char* intToStr(long target, int bufSize, char* buf);
int parseInt(const char* str, FILE* stream);
_Bool isBlank(char ch);

int main(void) {
    int N = parseInt(NULL, stdin);

    int* distances = (int*)malloc(sizeof(int) * (N));
    int* prices = (int*)malloc(sizeof(int) * (N + 1));

    char** tokens = tokenizer(stdin);
    int idx = 0;
    while(idx < N - 1) {
        *(distances + idx) = parseInt(*(tokens + idx), NULL);
        idx++;
    }
    freeArrs((void**)tokens);

    tokens = tokenizer(stdin);
    idx = 0;
    while(idx < N) {
        *(prices + idx) = parseInt(*(tokens + idx), NULL);
        idx++;
    }
    freeArrs((void**)tokens);

    long totalPrice = 0;
    long tempDistance = 0;
    int currIdx = 0;
    int searchIdx = 0;
    while(searchIdx < N - 1) {
        // 고정된 인덱스가 여전히 탐색중인 인덱스보다 높은 가격을 가지고 있을 경우
        if(*(prices + currIdx) <= *(prices + searchIdx)) {
            tempDistance += *(distances + searchIdx);
            searchIdx++;
        } else { // 고정된 인덱스보다 탐색된 새로운 인덱스가 낮은 가격을 가지고 있을 경우
            totalPrice += (long)*(prices + currIdx) * (long)tempDistance;

            currIdx = searchIdx;
            tempDistance = 0;
        }
    }
    totalPrice += (long)(tempDistance) * (long)*(prices + currIdx);

    char buf[32];
    char* resultStr = intToStr(totalPrice, sizeof(buf), buf);
    fputs(resultStr, stdout); fputc('\n', stdout);

    return 0;
}

char** tokenizer(FILE* stream) {
    int size = 5;
    int curr = 0;

    char** tokens = (char**)malloc(sizeof(char*) * (size + 1));
    char** tokensPtr = tokens;

    int tknSize = 0;
    int bufSize = 100;
    char* buf = (char*)malloc(sizeof(char) * (bufSize + 1));
    char* bufPtr = buf;

    char ch;
    while((ch = fgetc(stream)) != -1) {
        if(isBlank(ch)) {
            if(tknSize == 0)
                continue;

            *bufPtr = 0;
            *tokensPtr++ = (char*)realloc(buf, sizeof(char) * (tknSize + 1));
            curr++;

            buf = (char*)malloc(sizeof(char) * (bufSize + 1));
            bufPtr = buf; tknSize = 0;

            if(size == curr) {
                size *= 2;
                tokens = (char**)realloc(tokens, sizeof(char*) * (size + 1));
                tokensPtr = (char**)(tokens + curr);
            }
        } else {
            *bufPtr++ = ch; tknSize++;
        }

        if(ch == '\n')
            break;
    }
    free(buf);

    *tokensPtr = NULL;

    return tokens;
}
void freeArrs(void** arrs) {
    void** arrsPtr = arrs;
    while(*arrsPtr) {
        free(*arrsPtr++);
    }
    free(arrs);

    return;
}

char* intToStr(long target, int bufSize, char* buf) {
    char* bufPtr = buf + bufSize;
    *--bufPtr = 0;

    long long temp = target;
    if(target < 0)
        temp *= -1;

    do {
        *--bufPtr = (temp % 10) + '0';
        temp /= 10;
    } while(temp != 0);

    if(target < 0) {
        *--bufPtr = '-';
    }

    return bufPtr;
}
int parseInt(const char* str, FILE* stream) {
    int sign = 1;
    int result = 0;

    if(stream == NULL) {
        char* strPtr = (char*)str;
        if(*strPtr == '-') {
            sign = -1;
            strPtr++;
        }

        while(!isBlank(*strPtr)) {
            result *= 10;
            result += *strPtr++ - '0';
        }
    } else {
        char ch = fgetc(stream);
        if(ch == '-') {
            sign = -1;
            ch = fgetc(stream);
        }

        while(!isBlank(ch)) {
            result *= 10;
            result += ch - '0';
            ch = fgetc(stream);
        }
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
