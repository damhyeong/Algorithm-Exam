/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// double b;
// char g;
// String var;
// long AB;
// a = sc.nextInt();                           // int 변수 1개 입력받는 예제
// b = sc.nextDouble();                        // double 변수 1개 입력받는 예제
// g = sc.nextByte();                          // char 변수 1개 입력받는 예제
// var = sc.next();                            // 문자열 1개 입력받는 예제
// AB = sc.nextLong();                         // long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// double b = 1.0;               
// char g = 'b';
// String var = "ABCDEFG";
// long AB = 12345678901234567L;
//System.out.println(a);                       // int 변수 1개 출력하는 예제
//System.out.println(b); 		       						 // double 변수 1개 출력하는 예제
//System.out.println(g);		       						 // char 변수 1개 출력하는 예제
//System.out.println(var);		       				   // 문자열 1개 출력하는 예제
//System.out.println(AB);		       				     // long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
import java.util.*;
import java.io.*;

/*
   사용하는 클래스명이 Solution 이어야 하므로, 가급적 Solution.java 를 사용할 것을 권장합니다.
   이러한 상황에서도 동일하게 java Solution 명령으로 프로그램을 수행해볼 수 있습니다.
 */
class Solution
{
	public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());

        // 오른쪽, 아래쪽, 왼쪽, 위쪽
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        for(int t = 1; t <= T; t++) {
            int N = Integer.parseInt(br.readLine());
            boolean[][] isVisit = new boolean[N][N];
            int[][] arr = new int[N][N];

            int num = 1, x = 0, y = 0;
            int dir = 0; // 오른쪽부터 시작한다.
            // 달팽이 수가 채워질 때 까지 반복한다.
            while(num <= N * N) {
                // 이 루프문이 끝날 때, 한 번의 방향을 휩쓴 상황을 의미.
                do {
                    arr[y][x] = num++;
                    isVisit[y][x] = true;
                    y += directions[dir][0];
                    x += directions[dir][1];
                } while(isDirOkay(y, x, isVisit, N));
                y -= directions[dir][0];
                x -= directions[dir][1];
                //방향 전환. 및 "num < N"(다 작성했는지) 조건 조사.
                dir = (dir + 1) % 4;
                // 꺾이면서 겹쳐작성되는 것을 회피.
                y += directions[dir][0];
                x += directions[dir][1];
            }

            StringBuilder sb = new StringBuilder();

            sb.append("#").append(t).append('\n');
            for(int i = 0; i < N; i++) {
                for(int j = 0; j < N; j++) {
                    sb.append(arr[i][j]).append(' ');
                }
                sb.append('\n');
            }
            System.out.print(sb.toString());
        }
    }

    // 해당 방향으로 나아가도 될지 책임지는 관심사 분리
    public static boolean isDirOkay(int cY, int cX, boolean[][] isVisit, int N) {
        // 인덱스 확인
        if(cY < 0 || cY >= N || cX < 0 || cX >= N) {
            return false;
        }

        // 방문 확인 - 만약에 문제가 음수부터 시작일 경우를 상정. 아니면 그냥 arr[.][.] != 0 하면 될듯.
        if(isVisit[cY][cX])
            return false;

        return true;
    }
}