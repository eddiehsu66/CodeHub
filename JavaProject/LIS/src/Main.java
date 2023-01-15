import java.util.*;
public class Main {

    public static void main(String[] args){
        start();
    }
    public static void start(){
        Scanner scanner = new Scanner(System.in);
        int num = scanner.nextInt();
        int[] nlist =new int[num];
        for(int i =0;i <num;i++) {
            nlist[i] = scanner.nextInt();
        }
        //使用动态规划算法
        int [] nlist1 = new int[nlist.length];
        int [] nlist2 = new int[nlist.length];
        int [] nlist3 = new int[nlist.length];
        System.arraycopy(nlist, 0, nlist1, 0, nlist.length);
        System.arraycopy(nlist, 0, nlist2, 0, nlist.length);
        System.arraycopy(nlist, 0, nlist3, 0, nlist.length);
        long startTime1 = System.nanoTime();
        int i1 =dy_LIS(nlist1);
        System.out.print("动态规划解法:"+i1+" ");
        long endTime1 = System.nanoTime();
        System.out.println("动态规划程序运行时间："+(endTime1-startTime1)+"ns");
        //使用二分法算法
        long startTime2 = System.nanoTime();
        int i2 =double_LIS(nlist2);
        System.out.print("贪心算法解法:"+i2+" ");
        long endTime2 = System.nanoTime();
        System.out.println("贪心算法运行时间："+(endTime2-startTime2)+"ns");

        //使用记忆化搜所
        long startTime3 = System.nanoTime();
        int i3 =mem_LIS(nlist3);
        System.out.print("记忆化搜所解法:"+i3+" ");
        long endTime3 = System.nanoTime();
        System.out.println("记忆化搜所运行时间："+(endTime3-startTime3)+"ns");
    }
    public static int dy_LIS(int[] nums) {//动态规划解法
        int[] dp = new int[nums.length];
        Arrays.fill(dp, 1);
        for (int i = 0; i < nums.length; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j])
                    dp[i] = Math.max(dp[i], dp[j] + 1);
            }
        }

        int res = 0;
        for (int i = 0; i < dp.length; i++) {
            res = Math.max(res, dp[i]);
        }
        return res;
    }
    public static int double_LIS(int[] nums) {//贪心算法+二分查找
        int[] top = new int[nums.length];
        // 牌堆数初始化为 0
        int piles = 0;
        for (int i = 0; i < nums.length; i++) {
            // 要处理的扑克牌
            int poker = nums[i];
            int left = 0, right = piles;
            while (left < right) {
                int mid = (left + right) / 2;
                if (top[mid] > poker) {
                    right = mid;
                } else if (top[mid] < poker) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            // 没找到合适的牌堆，新建一堆
            if (left == piles) piles++;
            // 把这张牌放到牌堆顶
            top[left] = poker;
        }
        // 牌堆数就是 LIS 长度
        return piles;
    }
    public static int mem_LIS(int[] nums) {
        int len = nums.length;
        if (len <= 1) {
            return len;
        }

        int ans = 0;
        int[] memo = new int[len];

        //以每个元素为起点的最长递增子序列
        for (int i = 0; i < len; i++) {
            // 已经搜索过的直接跳过
            if (memo[i] == 0) {
                ans = Math.max(ans, dfs(nums, i, memo));
            }
        }
        return ans;
    }

    private static int dfs(int[] nums, int index, int[] memo) {
        if (memo[index] != 0) {
            return memo[index];
        }

        int ans = 0;

        // 需要下探后面所有比当前元素大的元素
        for (int i = index + 1; i < nums.length; i++) {
            if (nums[i] > nums[index]) {
                ans = Math.max(ans, dfs(nums, i, memo));
            }
        }

        memo[index] = ++ans;
        return ans;
    }
}