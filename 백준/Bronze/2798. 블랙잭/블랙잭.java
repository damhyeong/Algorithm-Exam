import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());

        // 주어지는 모든 카드의 개수 - 배열 크기 생성하면 됨.
        int N = Integer.parseInt(st.nextToken());
        // 딜러가 크게 외칠 숫자 - 3 개의 요소를 더했을 때, 가장 가까운 숫자를 구할 때 비교하게 됨.
        int M = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());
        
        int[] cards = new int[N];
        
        for(int i = 0; i < N; i++)
            cards[i] = Integer.parseInt(st.nextToken());

        // 3 개를 뽑으므로. - 초기화
        int[] select = new int[3];
        
        // 가장 큰 수 - 초기화
        int max = -1;

        for (int i = 0; i < N; i++) { // 1 번째 카드 선택
            select[0] = cards[i];
            for (int j = i + 1; j < N; j++) { // 2 번째 카드 선택
                select[1] = cards[j];
                for (int k = j + 1; k < N; k++) { // 3 번째 카드 선택
                    select[2] = cards[k];
                    
                    // 현재 선택한 3 개의 카드에 대해서 총합을 계산한다.
                    int sum = select[0] + select[1] + select[2];

                    // 만약 딜러가 말한 숫자보다, 현재 3 개 카드의 합이 더 크면 안된다는 규칙이 있었다.
                    if (sum > M) {
                        // 무시하고, 다른 카드의 조합을 찾는다.
                        continue;
                    } else {
                        // 현재까지 저장하고 있는 최대 값 보다, 
                        // 조합된 3 개의 카드 합이 더 크다면, 최대값을 최신화한다.
                        max = max < sum ? sum : max;
                    }
                }
            }
        }
        System.out.println(max);
    }
}