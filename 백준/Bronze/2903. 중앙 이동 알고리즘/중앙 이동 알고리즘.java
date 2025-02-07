import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        // N 번 거친 후의 점 개수를 구하라 했으므로.
        int N = Integer.parseInt(br.readLine());
        
        // 한 번도 중앙 이동 알고리즘을 수행하지 않은 상태는, 한 변의 길이가 2 이다.
        // 그냥 순수 정사각형.
        int currPoint = 2;
        
        // 결과값 루프 시작
        for(int i = 0; i < N; i++) {
            // 현재 한 변의 점 개수는, 이전의 변 개수 + (이전 변 개수 - 1) 이다. - 중앙에 점 추가하므로
            currPoint = currPoint + (currPoint - 1);
        }
        
        System.out.println(currPoint * currPoint);
    }
}