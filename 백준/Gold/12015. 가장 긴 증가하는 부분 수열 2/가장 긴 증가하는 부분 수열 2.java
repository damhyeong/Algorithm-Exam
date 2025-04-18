import java.util.*;
import java.io.*;
/*
 {0  10  20  10  30  15  50  35  40  50}
 0 10 20 30
      st==ed
1. 마지막보다 큰 거 나오면 추가
2. 마지막보다 작은거 나오면 내부 배열을 무조건 변환

1. 같은거
2.

 */
/*
현재의 값을 기준으로, 앞의 수 중에서, 최대한 작으며 가장 긴 수열을 찾을 수 있는 방법은 무엇인가?

 */
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());

        StringTokenizer st = new StringTokenizer(br.readLine());

        int[] arr = new int[N + 1];
        int[] dp = new int[N + 1];


        int endIdx = 0;

        for(int i = 1; i <= N; i++) {
            int num = Integer.parseInt(st.nextToken());

            // 현재 최대치보다 추출한 수가 더 높을 경우, dp 에 추가한다.
            if(dp[endIdx] < num) {
                endIdx++;
                dp[endIdx] = num;
            } else {
                // dp, 0, endIdx, num ==> 들어가야 할 인덱스
                binarySearch(dp, 0, endIdx, num);
                // dp[추출된 인덱스] = num;

            }
        }

        System.out.println(endIdx);

    }

    public static void binarySearch(int[] dp, int start, int end, int num) {
        if(start > end) {
            dp[start] = num;
            return;
        }

        int mid = (start + end) / 2;

        // 중앙값이 찾는 거 보다 작을때 - +
        if(dp[mid] < num) {
            binarySearch(dp, mid + 1, end, num);
        } else if (dp[mid] > num) { // 중앙값이 찾는 거 보다 클 때 -
            binarySearch(dp, start, mid - 1, num);
        } else {
            dp[mid] = num;
            return;
        }


    }

}
