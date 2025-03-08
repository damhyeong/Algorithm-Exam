import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());

        // 입력 될 row 의 수
        int N = Integer.parseInt(st.nextToken());
        // 입력 될 column 의 수
        int M = Integer.parseInt(st.nextToken());

        // 하얀색 시작 보드와의 차이를 기억할 배열
        int[][] whiteDiff = new int[N][M];
        // 검은색 시작 보드와의 차이를 기억할 배열
        int[][] blackDiff = new int[N][M];

        // 0번째 줄, 0번째 열 보드 색상.
        char whiteBoardColor = 'W';
        char blackBoardColor = 'B';

        // 첫 줄 입력
        String currLine = br.readLine();

        int whiteMin = Integer.MAX_VALUE;
        int blackMin = Integer.MAX_VALUE;


        // 첫 번째 줄 초기화.
        for(int col = 0; col < M; col++) {
            if(col > 0) {
                whiteDiff[0][col] = whiteDiff[0][col - 1];
                blackDiff[0][col] = blackDiff[0][col - 1];
            }

            if(col % 2 == 0) {
                whiteBoardColor = 'W';
                blackBoardColor = 'B';
            } else {
                whiteBoardColor = 'B';
                blackBoardColor = 'W';
            }

            char currColor = currLine.charAt(col);

            if(whiteBoardColor != currColor)
                whiteDiff[0][col]++;
            if(blackBoardColor != currColor)
                blackDiff[0][col]++;
        }

        // i = row,  j = column
        for(int i = 1; i < N; i++) {
            currLine = br.readLine();

            for(int j = 0; j < M; j++) {
                char currColor = currLine.charAt(j);

                whiteBoardColor = 'I';
                blackBoardColor = 'I';

                if((i + j) % 2 == 0) {
                    whiteBoardColor = 'W';
                    blackBoardColor = 'B';
                } else {
                    whiteBoardColor = 'B';
                    blackBoardColor = 'W';
                }

                // 1 번째 열 이라면.
                if(j == 0) {
                    whiteDiff[i][j] = whiteDiff[i - 1][j];
                    blackDiff[i][j] = blackDiff[i - 1][j];
                } else {
                    // 도형으로 생각해보자. - 이전 열 까지의 직사각형을 더한다.
                    whiteDiff[i][j] += whiteDiff[i][j - 1];
                    blackDiff[i][j] += blackDiff[i][j - 1];

                    // 바로 위에 해당하는 "한 줄의" 차이들을 더한다.
                    whiteDiff[i][j] += (whiteDiff[i - 1][j] - whiteDiff[i - 1][j - 1]);
                    blackDiff[i][j] += (blackDiff[i - 1][j] - blackDiff[i - 1][j - 1]);
                }

                // 만약 현재 색상과, 하얀색 시작 보드와의 색상이 다르다면,
                // 현재 줄의 하얀색 시작 보드 차이를 적층한다.
                if(currColor != whiteBoardColor) {
                    whiteDiff[i][j]++;
                }

                // 검은색 보드와의 색상이 다르다면, 현재 줄의 검은색 보드 차이를 적층한다.
                if(currColor != blackBoardColor) {
                    blackDiff[i][j]++;
                }


                // 마지막으로, 8 x 8 체스판을 수용할 수 있을 때, 최소값을 계산한다.
                if(i >= 7 && j >= 7) {
                    int eraseRow = i - 8;
                    int eraseCol = j - 8;

                    // 윗 부분 차이점 가져오기
                    int upperWhiteDiff = 0;
                    int upperBlackDiff = 0;

                    // 만약 자를 윗 부분이 있다면, 그 때 계산.
                    if(eraseRow >= 0) {
                        upperWhiteDiff = whiteDiff[eraseRow][j];
                        upperBlackDiff = blackDiff[eraseRow][j];
                    }

                    // 정확히 왼쪽의 차이점을 추출
                    int rightWhiteDiff = 0;
                    int rightBlackDiff = 0;

                    // 자를 윗 부분과 왼쪽 부분이 없을 때. (정확히 8 x 8)
                    if(eraseRow < 0 && eraseCol < 0) {
                        rightWhiteDiff = 0;
                        rightBlackDiff = 0;
                    } else if(eraseRow < 0) { // 자를 윗 부분만 없을 때.
                        rightWhiteDiff = whiteDiff[i][eraseCol];
                        rightBlackDiff = blackDiff[i][eraseCol];
                    } else if(eraseCol < 0) { // 자를 왼쪽 부분이 없을 때.
                        rightWhiteDiff = 0;
                        rightBlackDiff = 0;
                    } else { // 윗 부분, 왼쪽 부분 둘 다 잘라야 할 때.
                        rightWhiteDiff = whiteDiff[i][eraseCol] - whiteDiff[eraseRow][eraseCol];
                        rightBlackDiff = blackDiff[i][eraseCol] - blackDiff[eraseRow][eraseCol];
                    }

                    // 현재 위치에서 8 x 8 크기로 잘랐을 때, 하얀색, 검은색 보드와의 차이를 구했다.
                    int totalWhiteDiff = whiteDiff[i][j] - upperWhiteDiff - rightWhiteDiff;
                    int totalBlackDiff = blackDiff[i][j] - upperBlackDiff - rightBlackDiff;

                    // 보드 별 최소값 갱신.
                    whiteMin = whiteMin > totalWhiteDiff ? totalWhiteDiff : whiteMin;
                    blackMin = blackMin > totalBlackDiff ? totalBlackDiff : blackMin;

                }
            }
        }

        int totalMin = whiteMin < blackMin ? whiteMin : blackMin;

        System.out.println(totalMin);
    }
}