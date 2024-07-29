import java.util.*;
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        long N = Long.parseLong(br.readLine());
        long k = Long.parseLong(br.readLine());

        long result = findKthNumber(N, k);

        System.out.println(result);
    }

    public static long findKthNumber(long N, long k) {
        long left = 1;
        long right = N * N;
        long result = 0;

        while (left <= right) {
            long mid = (left + right) / 2;
            long count = countLessOrEqual(mid, N);

            if (count < k) {
                left = mid + 1;
            } else {
                result = mid; // mid 값이 조건을 만족하면 저장
                right = mid - 1;
            }
        }

        return result;
    }

    public static long countLessOrEqual(long x, long N) {
        long count = 0;
        for (long i = 1; i <= N; i++) {
            count += Math.min(x / i, N);
        }
        return count;
    }
}
