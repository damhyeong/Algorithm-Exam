import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        
        // 입력될 보드의 상태를 저장할 2차원 배열 생성.
        char[][] inputBoard = new char[N][M];

        // 하얀색 시작 보드
        char[][] white = new char[8][8];
        // 검은색 시작 보드
        char[][] black = new char[8][8];

        // 열과 행의 인덱스 합이 짝수인지, 홀수인지에 따라서, 간단히 흑백을 나눌수가 있단 것을 관찰 후 알게 되었다!
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if((i + j) % 2 == 0) {
                    white[i][j] = 'W';
                    black[i][j] = 'B';
                } else {
                    white[i][j] = 'B';
                    black[i][j] = 'W';
                }
            }
        }

        // 초기화 시작 
        for(int i = 0; i < N; i++) {
            String row = br.readLine();
            for(int j = 0; j < M; j++) {
                inputBoard[i][j] = row.charAt(j);
            }
        }
        
        // 최소값 초기화.
        int minDiff = Integer.MAX_VALUE;
        
        // 8 x 8 칸을 잘랐을 때, 차이 최소값을 구한다.
        for(int i = 0; i < inputBoard.length - 7; i++) {
            for(int j = 0; j < inputBoard[0].length - 7; j++) {
                // 현재 점으로부터 하얀색, 검은색 보드와의 최소 차이 값을 가져온다.
                int min = getMinDiff(inputBoard, white, black, i, j);
                
                // 최소값 갱신.
                minDiff = min < minDiff ? min : minDiff;
            }
        }
        
        System.out.println(minDiff);
    }
    
    // 하얀색과 검은색 시작 보드 중 차이가 가장 작은 수를 반환한다.
    static int getMinDiff(char[][] inputBoard, char[][] whiteBoard, char[][] blackBoard, int y, int x) {
        int whiteDiff = 0;
        int blackDiff = 0;
        
        // 시작점으로부터 8 줄 비교
        for(int i = y; i < y + 8; i++) {
            // 시작점으로부터 8 열 비교
            for(int j = x; j < x + 8; j++) {
                // 주어진 보드의 색상을 가져온다.
                char currColor = inputBoard[i][j];
                
                // 하얀색 시작 보드의 색상 (0, 0 부터 시작해야 한다.)
                char whiteColor = whiteBoard[i - y][j - x];
                // 검은색 시작 보드의 색상 (이것도 0, 0 부터 시작해야 한다.)
                char blackColor = blackBoard[i - y][j - x];
                
                // 하얀색 보드와의 차이를 적층하자.
                if(currColor != whiteColor) {
                    whiteDiff++;
                }
                
                // 검은색 보드와의 차이를 적층.
                if(currColor != blackColor) {
                    blackDiff++;
                }
            }
        }
        
        // 하얀색, 검은색 보드 차이 중 작은 수를 반환한다.
        return whiteDiff < blackDiff ? whiteDiff : blackDiff;
    }
}