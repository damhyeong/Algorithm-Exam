import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int X = Integer.parseInt(br.readLine());
        
        // 시작 라인
        int currLine = 0;
       // 현재 분수 번호 초기화
        int currNumber = 0;
        
        // 현재까지 파악된 분수 번호가 X 보다 작을 때. - 넘으면 해당 라인에 포함된 것으로 간주.
        while(currNumber < X) {
            currNumber += (currLine + 1);
            currLine++;
        }
        
        // while 탈출 시, currLine 내에 `X` 번째 분수가 있다는 결과를 얻은 상태
       
        int frontNum = 0;
        int backNum = 0;
        
        // X 라인이 홀수 일 경우 - 시작 부분부터 중간의 분수를 구하는 경우
        if(currLine % 2 == 1) {
            // currLine 의 시작 분수 번째를 구해놓는다.
            int start = currNumber - currLine + 1;
            
            // 이동 총량은 중간의 X 번째 - 시작 번째.
            int move = X - start;
            
            frontNum = (currLine - move);
            backNum = (move + 1);
            
        } else { //  X 라인이 짝수 일 경우 - 마지막 부분부터 중간의 분수를 구하는 경우
            // currLine 의 마지막 분수 번째는 현재 currNumber 이다.
            int end = currNumber;
            
            // 마지막부터 시작하는 경우, 이동 총량은 마지막 - X 번째이다.
            int move = end - X;
            
            frontNum = (currLine - move);
            backNum = (move + 1);
        }
        
        System.out.println(frontNum + "/" + backNum);
    }
}