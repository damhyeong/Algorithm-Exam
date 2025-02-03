import java.io.*;
import java.util.*;

public class Main {
    // 인접 리스트로 트리 구성
    static ArrayList<Integer>[] tree;
    // dp[node][0] : node를 비조기채택자로 두었을 때 최소값
    // dp[node][1] : node를 조기채택자로 두었을 때 최소값
    static int[][] dp;
    // 방문 여부 체크 (트리이므로 사이클은 없지만 부모-자식 관계 판별에 사용)
    static boolean[] visited;
    
    public static void main(String[] args) throws Exception {
        new Main().solve();
    }
    
    public void solve() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        
        // 트리 초기화 (1번부터 n번까지)
        tree = new ArrayList[n+1];
        for (int i = 1; i <= n; i++) {
            tree[i] = new ArrayList<>();
        }
        
        // 간선 입력 (트리이므로 간선의 개수는 n-1)
        for (int i = 1; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            tree[u].add(v);
            tree[v].add(u);
        }
        
        dp = new int[n+1][2];
        visited = new boolean[n+1];
        
        // 루트를 1번으로 하여 DFS 수행
        dfs(1);
        
        // 결과는 1번 노드를 조기채택자로 하거나 아닌 경우 중 최솟값
        System.out.println(Math.min(dp[1][0], dp[1][1]));
    }
    
    // 재귀 DFS: 후위 순회(postorder)로 dp값 계산
    private void dfs(int node) {
        visited[node] = true;
        // node를 조기 채택하지 않을 경우, 초기값 0
        dp[node][0] = 0;
        // node를 조기 채택할 경우, 자기 자신을 포함하므로 1부터 시작
        dp[node][1] = 1;
        
        for (int child : tree[node]) {
            if (!visited[child]) {
                dfs(child);
                // node가 조기채택자가 아니면, 자식은 반드시 조기 채택자여야 함.
                dp[node][0] += dp[child][1];
                // node가 조기채택자라면, 자식은 채택 여부에 상관없이 최소값 선택 가능
                dp[node][1] += Math.min(dp[child][0], dp[child][1]);
            }
        }
    }
}
