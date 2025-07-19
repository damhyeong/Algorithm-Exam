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
2 초	128 MB	152152	77254	61406	50.669%

문제
---
지민이는 자신의 저택에서 MN개의 단위 정사각형으로 나누어져 있는 M×N 크기의 보드를 찾았다.

어떤 정사각형은 검은색으로 칠해져 있고, 나머지는 흰색으로 칠해져 있다.

지민이는 이 보드를 잘라서 8×8 크기의 체스판으로 만들려고 한다.

체스판은 검은색과 흰색이 번갈아서 칠해져 있어야 한다.

구체적으로, 각 칸이 검은색과 흰색 중 하나로 색칠되어 있고, 변을 공유하는 두 개의 사각형은 다른 색으로 칠해져 있어야 한다.

따라서 이 정의를 따르면 체스판을 색칠하는 경우는 두 가지뿐이다.

하나는 맨 왼쪽 위 칸이 흰색인 경우, 하나는 검은색인 경우이다.


보드가 체스판처럼 칠해져 있다는 보장이 없어서, 지민이는 8×8 크기의 체스판으로 잘라낸 후에 몇 개의 정사각형을 다시 칠해야겠다고 생각했다.

당연히 8*8 크기는 아무데서나 골라도 된다.

지민이가 다시 칠해야 하는 정사각형의 최소 개수를 구하는 프로그램을 작성하시오.


입력
---
첫째 줄에 N과 M이 주어진다.

N과 M은 8보다 크거나 같고, 50보다 작거나 같은 자연수이다.

둘째 줄부터 N개의 줄에는 보드의 각 행의 상태가 주어진다.

B는 검은색이며, W는 흰색이다.


출력
---
첫째 줄에 지민이가 다시 칠해야 하는 정사각형 개수의 최솟값을 출력한다.


예제 입력 1
8 8
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBBBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
예제 출력 1
1
예제 입력 2
10 13
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
WWWWWWWWWWBWB
WWWWWWWWWWBWB
예제 출력 2
12
예제 입력 3
8 8
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
예제 출력 3
0
예제 입력 4
9 23
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBW
예제 출력 4
31
예제 입력 5
10 10
BBBBBBBBBB
BBWBWBWBWB
BWBWBWBWBB
BBWBWBWBWB
BWBWBWBWBB
BBWBWBWBWB
BWBWBWBWBB
BBWBWBWBWB
BWBWBWBWBB
BBBBBBBBBB
예제 출력 5
0
예제 입력 6
8 8
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBBBWBW
WBWBWBWB
BWBWBWBW
WBWBWWWB
BWBWBWBW
예제 출력 6
2
예제 입력 7
11 12
BWWBWWBWWBWW
BWWBWBBWWBWW
WBWWBWBBWWBW
BWWBWBBWWBWW
WBWWBWBBWWBW
BWWBWBBWWBWW
WBWWBWBBWWBW
BWWBWBWWWBWW
WBWWBWBBWWBW
BWWBWBBWWBWW
WBWWBWBBWWBW
예제 출력 7
15
*/

/**
데이터를 입력받는 도중에 계산할 것인가, 데이터를 저장 한 후 계산할 것인가에 대한 생각이 든다.

여기에 적용할 수 있는 방법론 목록

**비교 방법**

1. 줄(row) + 열(column) 결과 % 2 에 따라 하얀색인지, 검은색인지 구별할 수 있다. - 그런데, 하얀색 시작인지, 검은색 시작인지 분간해야 한다.

2. 혹은, 입력된 줄, 열 데이터에 따라, 미리 해당 크기의 체스판을 만들어 둔다.

**최소값 구하는 방법**

1. 브루트 포스 방식으로, 하나의 인덱스에서 시작하여 8 * 8 을 비교한다. - 비교방식은 위의 방식 중 하나를 선택.

2. DP 방식으로, 처음부터 기존 체스판과의 비교 수를 더해가며 하나의 루프로 모든 계산을 끝낸다. - 비교방식의 위의 방식 중 하나를 선택.

DP 방식으로 풀기 위해서는, 루프 내부에 8 * 8 비교를 시작 할 수 있는 특정 요소를 넣어야 한다.

**필수 조건**

1. 하얀색 시작, 검은색 시작 보드의 기준이 필요함.

2. 검은색 시작 최소값, 하얀색 시작 최소값을 저장해야 하며, 이를 계산할 하나의 알고리즘 선택.

**선택 조건**

최대 길이가 50 이기 때문에, 브루트포스를 사용하더라도,

(50 * 50) = 250 --> 최대 보드 루프

(8 * 8 * 2) = 128 --> 하나의 타일 당 검사하게 될 시간복잡도 (정해짐)

250 * 128 정도로, O(n^3) 에서도 충분히 가능한 로직. (열 * 행 * 색상)


DP 를 선택한다면, 로직이 복잡해지겠지만, "O(n^2)" 정도로 끝낼 수 있다.

이미 풀어본 문제이니, 이번엔 어렵게 가보자.

*/

#include<stdio.h>

extern void* malloc(size_t byte);
extern void free(void* memory);
extern void* realloc(void* memory, size_t byte);
extern void* calloc(size_t size, size_t byte);

int calDiff(int** lists, int i, int j, int mode);

char wListMustBe(int i, int j);
char bListMustBe(int i, int j);

void** createArr(int row, int col, int byte);
void DeleteArr(void** arr);

char** tokenizer(const char* input);
void freeTokens(char** tokens);

char* intToStr(int target);
int parseInt(const char* str);
_Bool isBlank(char ch);

int main(void) {
    char input[100];

    fgets(input, sizeof(input), stdin);

    char** tokens = (char**)tokenizer(input);

    int row = parseInt(*tokens);
    int col = parseInt(*(tokens + 1));

    freeTokens(tokens);

    /**
     * DP 방식을 풂에 있어, 하나의 공간을 더 창출하여 첫 인덱스를 0으로 만드는 것은 매우 중요하다.
     */

    // 하얀색 시작 보드의 차이 기록
    int** wLists = (int**)createArr(row + 1, col + 1, sizeof(int));

    // 검은색 시작 보드의 차이 기록
    int** bLists = (int**)createArr(row + 1, col + 1, sizeof(int));


    // DP 방식으로 채택하여 구성한다.
    int idx = 1;
    while(idx <= row) {
        int jdx = 1;

        fgets(input, sizeof(input), stdin);

        while(jdx <= col) {
            // 시작 전, 각 색상 시작 보드들의 차이를 DP 식으로 추가한다.

            *(*(wLists + idx) + jdx) = calDiff(wLists, idx, jdx, 1);
            *(*(bLists + idx) + jdx) = calDiff(bLists, idx, jdx, 1);

            // 현재 보드 색상을 가져온다.
            char currCh = *(input + (jdx - 1));

            // 각 상황, 하얀색 시작 블록, 검은색 시작 블록 분기에 따라 각 저장 리스트의 추가 조건을 달리 한다.

            // 현재 문자와 비교하여, 하얀색 블록 시작 보드에 알맞는 색상이 오지 않았다면, 차이점을 누적한다.
            if(currCh != wListMustBe(idx, jdx)) {
                *(*(wLists + idx) + jdx) = *(*(wLists + idx) + jdx) + 1;
            }

            // 현재 문자와 비교하여, 검은색 블록 시작 보드에 알맞는 색상이 오지 않았다면, 차이점을 누적한다.
            if(currCh != bListMustBe(idx, jdx)) {
                *(*(bLists + idx) + jdx) = *(*(bLists + idx) + jdx) + 1;
            }


            jdx++;
        }

        idx++;
    }

    int whiteDiffMin = 10000000;
    int blackDiffMin = 10000000;

    idx = 8;
    while(idx <= row) {
        int jdx = 8;
        while(jdx <= col) {
            int currWhiteDiff = calDiff(wLists, idx, jdx, 0);
            int currBlackDiff = calDiff(bLists, idx, jdx, 0);

            whiteDiffMin = whiteDiffMin > currWhiteDiff ? currWhiteDiff : whiteDiffMin;
            blackDiffMin = blackDiffMin > currBlackDiff ? currBlackDiff : blackDiffMin;

            jdx++;
        }
        idx++;
    }

    char* result = (char*)intToStr(whiteDiffMin < blackDiffMin ? whiteDiffMin : blackDiffMin);

    fputs(result, stdout); fputc('\n', stdout);

    free(result);

    return 0;
}

/**
 * 이 메서드를 이해하시려면, 2차원 형태의 엘리먼트 형식으로 생각하셔야 합니다. (도형을 생각)
 */
int calDiff(int** lists, int i, int j, int mode) {
    // 따로 모드를 나누어서, 정확히 현재 블록에 대한 차이를 누적하기 위한 용도라면, mode == 1 이 되어야 한다.
    if(mode == 1) {
        // 현재 j 인덱스로부터 모든 i - 1 까지의 차이점을 가져온다.
        int upperDiff = *(*(lists + i - 1) + j);

        // 현재 줄의 차이만 빼서 j - 1 까지의 차이점을 따로 구한다.
        int currLineDiff = *(*(lists + i) + j - 1) - *(*(lists + i - 1) + j - 1);

        return upperDiff + currLineDiff;
    } else { // 나머지
        int upperDiff = *(*(lists + i - 8) + j);

        int currBlockDiff = *(*(lists + i) + j - 8) - *(*(lists + i - 8) + j - 8);

        return *(*(lists + i) + j) - upperDiff - currBlockDiff;
    }
}

// 주어진 인덱스에 대해 해당 블록은 어떤 색상을 가져야 하는가를 반환한다. (문자)
char wListMustBe(int i, int j) {
    if((i + j) % 2 == 0) {
        return 'W';
    } else {
        return 'B';
    }
}
// 주어진 인덱스에 대해 해당 블록은 어떤 색상을 가져야 하는가를 반환한다. (문자)
char bListMustBe(int i, int j) {
    if((i + j) % 2 == 0) {
        return 'B';
    } else {
        return 'W';
    }
}


void** createArr(int row, int col, int byte) {
    void** arr = malloc(sizeof(void*) * (row + 1));
    *(arr + row) = NULL;
    void** arrPtr = arr;

    int idx = 0;
    while(idx++ < row) {
        void* line = (void*)calloc(col + 1, sizeof(byte));

        *arrPtr++ = line;
    }

    return arr;
}
void DeleteArr(void** arr) {
    void** arrPtr = arr;

    while(*arrPtr) {
        free(*arrPtr++);
    }
    free(arr);
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
