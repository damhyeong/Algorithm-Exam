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
1 초	1024 MB	170044	88504	81841	53.222%
문제
아래 예제와 같이 새싹을 출력하시오.

입력
입력은 없다.

출력
새싹을 출력한다.

예제 입력 1
예제 출력 1
         ,r'"7
r`-_   ,'  ,/
 \. ". L_r'
   `~\/
      |
      |
*/

#include<stdio.h>

int main(void) {
    fputs("         ,r'\"7", stdout); fputc('\n', stdout);
    fputs("r`-_   ,'  ,/", stdout); fputc('\n', stdout);
    fputs(" \\. \". L_r'", stdout); fputc('\n', stdout);
    fputs("   `~\\/", stdout); fputc('\n', stdout);
    fputs("      |", stdout); fputc('\n', stdout);
    fputs("      |", stdout); fputc('\n', stdout);
    return 0;
}
