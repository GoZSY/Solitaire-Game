/********************************************************************************
a和b都是绝顶聪明，他们每次拿元素时，肯定是按对自己最有力的方式拿。该题目先由最普通的递归解法，然后进行优化，到动态规划。
递归方式，对数组arr，元素数为n。
F(arr, l , r)表示对于数组arr，元素从l到r，先拿可以达到的最大分数；
S(arr, l, r)表示对于数组arr, 元素从l到r，后拿可以达到的最大分数。
对于F(arr, l, r)，先拿时，有两种拿法，拿第一个arr[l]，或最后一个arr[r]；
如果拿arr[l]，那么剩余的arr[l+1,....r]能拿到的最大分数为S(arr, l+1, r)，分数为arr[l] +S(arr, l+1, r)；
如果拿arr[r]，剩余的arr[l, ...r-1]能拿到的最大分数为S(arr, l, r-1)，分数为arr[r] + S(arr, l, r-1)，
因为对于先拿后剩余的数组，当前人再拿的话是后拿的，然后取这两种拿法较大的分数。

对于S(arr, l, r)，如果前一个人先拿了arr[l]，则后拿的分数为F(arr, l+1, r)，如果前一个人先拿了arr[r]，
则后拿的分数为F(arr, l, r-1)，因为对于剩余的元素来说，你是先拿的，取两种方式的较小值才是S的值。
（为什么取较小值，而不是较大值？因为a和b都是绝顶聪明人，你是在另一个绝顶聪明人之后才拿的，他给你剩下的肯定是较坏的情况）
*********************************************************************************/
//递归
class Cards {
public:
    int cardGame(vector<int> A, int n) {
        if(n == 0 || A.size() == 0)
            return 0;
        //返回先拿和后拿之间的最大者
        return max(f(A, 0, n-1), s(A, 0, n-1));
    }
    //先拿
    int f(vector<int> A, int i, int j){
        if(i == j)
            return A[i];
        //那最大的值
        return max(A[i] + s(A, i+1, j), A[j] + s(A, i, j-1));
    }
    //后拿
    int s(vector<int> A, int i, int j){
        if(i == j)
            return 0;
        //对手留给剩下的最少钱数
        return min(f(A, i+1, j), f(A, i, j-1));
    }
};
//非递归
class Cards {
public:
    int cardGame(vector<int> A, int n) {
        // write code here
        vector<vector<int> > first(n+1,vector<int>(n,0));
        vector<vector<int> > second(n+1,vector<int>(n,0));
        first[0][0]=A[0];
        first[n-1][n-1]=A[n-1];
          
        for(int j=1;j<n;++j)
            for(int i=j;i>=0;--i){
                first[i][j]=max(A[i]+second[i+1][j],A[j]+second[i][j-1]);
                second[i][j]=min(first[i+1][j],first[i][j-1]);
        }
        return max(first[0][n-1],second[0][n-1]);
    }
};
/**********************************************************************************************
 考虑记忆化搜索，dp[l][r]表示l..r区间内取纸牌，先手的最大收益。
每个人要让自己收益最大，也就是让对手收益最小。
收益是l..r区间内所有纸牌的和 - 我取了之后剩下区间对手的收益。
 ***********************************************************************************************/
 class Cards {
public:
    const static int size = 300;
    int sums[size] = {0};
    int dp[size][size];
 
    int dfs_cache(const int &l, const int &r, const vector<int> &cards){
        if(l==r){
            dp[l][r] = cards[l];
        }
        if(dp[l][r]!=-1){
            return dp[l][r];
        }
        int all_sum = sums[r] - (l == 0 ? 0:sums[l-1]);
        dp[l][r] = all_sum - min(dfs_cache(l+1, r, cards), dfs_cache(l, r-1, cards));
        return dp[l][r];
    }
 
    int cardGame(vector<int> A, int n) {
        // write code here
        sums[0] = A[0];
        for(int i=1; i<n;i++){
            sums[i] = sums[i-1] + A[i];
        }
        memset(dp, -1, sizeof(dp));
        int first_profit = dfs_cache(0, n-1, A);
        return max(first_profit, sums[n-1]-first_profit);
    }
};
