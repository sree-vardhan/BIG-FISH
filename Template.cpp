#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

//~ GENERIC CLASSES

class __TRIPLET
{
private:
    //~ DECLARE PRIVATE CLASSES  AND FUNCTIONS IF NEEDED.
public:
    int first, second, third;
    __TRIPLET(int, int, int);
    __TRIPLET(void);
};
__TRIPLET ::__TRIPLET(int first, int second, int third)
{
    this->first = first;
    this->second = second;
    this->third = third;
}
__TRIPLET::__TRIPLET(void)
{
    //~ ACTS AS A DEFAULT CONSTRUCTOR.
}

//~ OUTER CLASSES DECLARATION.

class __DYNAMICPROG;
class __GRAPHS;

//~ OUTER FUNCTIONS DECLARATION.

void solve(void);
signed main(signed, char const *[]);

// NOTE - DYNAMIC PROGRAMMING.

class __DYNAMICPROG
{
private:
    //~ DECLARE PRIVATE CLASSES  AND FUNCTIONS IF NEEDED.

    int __KnapSackRec(vector<int> &, vector<int> &, int, int, vector<vector<int>> &);
    int __KnapSackItr(vector<int> &, vector<int> &, int, int);
    int __KnapSackOpt(vector<int> &, vector<int> &, int, int);
    int __SubSetSumRec(vector<int> &, int, int, vector<vector<int>> &);
    int __SubSetSumItr(vector<int> &, int, int);
    int __SubSetSumOpt(vector<int> &, int, int);
    int __RodCutRec(vector<int> &, vector<int> &, int, int, vector<vector<int>> &);
    int __RodCutItr(vector<int> &, vector<int> &, int);
    int __RodCutOpt(vector<int> &, vector<int> &, int);
    int __LngCmnSubSeqRec(string &, string &, int, int, vector<vector<int>> &);
    int __LngCmnSubSeqItr(string &, string &, int, int);
    int __LngCmnSubSeqOpt(string &, string &, int, int);
    int __LngCmnSubStrOpt(string &, string &, int, int);
    string __PrintLngCmnSubSeqItr(string &, string &, int, int);
    string __PrintLngCmnSubStrItr(string &, string &, int, int);
    string __PrintSrtCmnSupSeqItr(string &, string &, int, int);

public:
    //~ INNER CLASSES DECLARATION.

    class __KNAPSACK;
    class __UBKNAPSACK;
    class __LCS;
    class __MCM;
    class __GRIDS;

    //~ INNER FUNCTIONS DECLARATION.

    class __KNAPSACK
    {
    private:
        int __KnapSackRec(vector<int> &Weight, vector<int> &Price, int W, int N, vector<vector<int>> &DP)
        {

            // ^ RECUSIVE WITH MEMOIZATION.
            // ^ Choose weight vs price such that max weight is W and you get the max price possible.

            if (W <= 0 || N <= 0)
                return 0;

            // ^ Imagine a DP array as DP[N+1][W+1].

            else if (DP[N][W] != -1)
                return DP[N][W];

            else if (W >= Weight[N - 1])
                return DP[N][W] = max(Price[N - 1] + __KnapSackRec(Weight, Price, W - Weight[N - 1], N - 1, DP), __KnapSackRec(Weight, Price, W, N - 1, DP));
            else
                return DP[N][W] = __KnapSackRec(Weight, Price, W, N - 1, DP);
        }
        int __KnapSackItr(vector<int> &Weight, vector<int> &Price, int W, int N)
        {

            // ^ We convert recusive to itrative via top Down DP application

            int DP[N + 1][W + 1];
            for (int i = 0; i < N + 1; i++)
                for (int j = 0; j < W + 1; j++)
                    if (i == 0 || j == 0)
                        DP[i][j] = 0;
                    else if (j >= Weight[i - 1])
                        DP[i][j] = max(Price[i - 1] + DP[i - 1][j - Weight[i - 1]], DP[i - 1][j]);
                    else
                        DP[i][j] = DP[i - 1][j];
            return DP[N][W];
        }
        int __KnapSackOpt(vector<int> &Weight, vector<int> &Price, int W, int N)
        {

            // ^ In Space optimisation we must replace DP[i-1] By Prev and DP[i] By Curr and continue the rest and we must modify Prev = Curr in each inner loop.

            vector<int> Prev(W + 1, 0), Curr(W + 1, 0);

            // ^ Here basically we directly start from i = 1 as we know that when i = 0 DP[0][j] is nothing but Prev

            for (int i = 0; i < N + 1; i++)
            {
                for (int j = 0; j < W + 1; j++)
                    if (i == 0 || j == 0)
                        Curr[j] = 0;
                    else if (j >= Weight[i - 1])
                        Curr[j] = max(Price[i - 1] + Prev[j - Weight[i - 1]], Prev[j]);
                    else
                        Curr[j] = Prev[j];
                Prev = Curr;
            }
            return Curr[W];
        }
        int __SubSetSumRec(vector<int> &value, int target, int n, vector<vector<int>> &DP)
        {

            // ^ Here we would basically add all kinds of possibilities present , i.e the pick case and the not pick case add them to find total number of possibilities.

            if (target == 0 && n == 0)
                return 1;
            else if (n == 0)
                return 0;
            else if (DP[n][target] != -1)
                return DP[n][target];
            else if (value[n - 1] <= target)
                return DP[n][target] = __SubSetSumRec(value, target - value[n - 1], n - 1, DP) + __SubSetSumRec(value, target, n - 1, DP);
            else
                return DP[n][target] = __SubSetSumRec(value, target, n - 1, DP);
        }
        int __SubSetSumItr(vector<int> &value, int target, int n)
        {

            // ^ We now convert recursive to top down by two loops with the same base cases replacing n with i and target with j.

            int DP[n + 1][target + 1];
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < target + 1; j++)
                    if (i == 0 && j == 0)
                        DP[i][j] = 1;
                    else if (i == 0)
                        DP[i][j] = 0;
                    else if (value[i - 1] <= j)
                        DP[i][j] = DP[i - 1][j - value[i - 1]] + DP[i - 1][j];
                    else
                        DP[i][j] = DP[i - 1][j];
            return DP[n][target];
        }
        int __SubSetSumOpt(vector<int> &value, int target, int n)
        {

            // ^ Most of the Questions can be space optimised as Creating Prev and Curr arrays and then we would apply same top down DP by replacing DP[i] with Curr and DP[i-1] with Prev , intially declare both of the arrays with 0's and later apply the above rule for space optimization.

            vector<int> Prev(target + 1, 0);
            vector<int> Curr(target + 1, 0);
            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < target + 1; j++)
                    if (i == 0 && j == 0)
                        Curr[j] = 1;
                    else if (i == 0)
                        Curr[j] = 0;
                    else if (value[i - 1] <= j)
                        Curr[j] = Prev[j - value[i - 1]] + Prev[j];
                    else
                        Curr[j] = Prev[j];
                Prev = Curr;
            }
            return Curr[target];
        }

    public:
        //~ DECLARE YOUR OWN FUNCTIONS TO CALL THE PRIVATE MEMBERS.
    };
    class __UBKNAPSACK
    {
    private:
        int __RodCutRec(vector<int> &length, vector<int> &price, int len, int n, vector<vector<int>> &DP)
        {

            //^ Here in unbounded knapsack we don't have te requirement of having a limited number of usage , we can use as many times as possible.

            if (n == 0)
                return 0;
            else if (len <= 0)
                return 0;
            else if (DP[n][len] != -1)
                return DP[n][len];
            else if (length[n - 1] <= len)
                return DP[n][len] = max(price[n - 1] + __RodCutRec(length, price, len - length[n - 1], n, DP), __RodCutRec(length, price, len, n - 1, DP));
            else
                return DP[n][len] = __RodCutRec(length, price, len, n - 1, DP);
        }
        int __RodCutItr(vector<int> &length, vector<int> &price, int n)
        {
            // ^ Same thing converted to the iteration method by following the above rules.
            int DP[n + 1][n + 1];
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < n + 1; j++)
                    if (i == 0)
                        DP[i][j] = 0;
                    else if (j == 0)
                        DP[i][j] = 0;
                    else if (length[i - 1] <= j)
                        DP[i][j] = max(price[i - 1] + DP[i][j - length[i - 1]], DP[i - 1][j]);
                    else
                        DP[i][j] = DP[i - 1][j];
            return DP[n][n];
        }
        int __RodCutOpt(vector<int> &length, vector<int> &price, int n)
        {
            // ^ Here the logic is same Prev is nothing but DP[i-1][] and Curr is same as DP[i][].
            vector<int> Curr(n + 1, 0), Prev(n + 1, 0);
            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < n + 1; j++)
                    if (i == 0)
                        Curr[j] = 0;
                    else if (j == 0)
                        Curr[j];
                    else if (length[i - 1] <= j)
                        Curr[j] = max(price[i - 1] + Curr[j - length[i - 1]], Prev[j]);
                    else
                        Curr[j] = Prev[j];
                Prev = Curr;
            }
            return Curr[n];
        }
        /*TODO  __MinNoCoinsRec(vector<int> &coins, int amount, int n, vector<vector<int>> &DP)
        {
            if (amount == 0)
                return 0;
            else if (n == 0)
                return INT_MAX;
            else if (coins[n - 1] >= amount)
                return (min(1 + __MinNoCoinsRec(coins, amount - coins[n - 1], n, DP), __MinNoCoinsRec(coins, amount, n - 1, DP)));
            else
                return __MinNoCoinsRec(coins, amount, n - 1, DP);
        }
        */

    public:
        //~ DECLARE YOUR OWN FUNCTIONS TO CALL THE PRIVATE MEMBERS.
    };
    class __LCS
    {
    private:
        int __LngCmnSubSeqRec(string &X, string &Y, int n, int m, vector<vector<int>> &DP)
        {
            //^ Here this is broken to the three options as -> X[n-1] == Y[m-1] , -> shorten X , -> shorten Y.
            if (n == 0 || m == 0)
                return 0;
            else if (DP[n][m] != -1)
                return DP[n][m];
            else if (X[n - 1] == Y[m - 1])
                return DP[n][m] = 1 + __LngCmnSubSeqRec(X, Y, n - 1, m - 1, DP);
            else
                return DP[n][m] = max(__LngCmnSubSeqRec(X, Y, n - 1, m, DP), __LngCmnSubSeqRec(X, Y, n, m - 1, DP));
        }
        int __LngCmnSubSeqItr(string &X, string &Y, int n, int m)
        {
            //^ Now the Lenght of LCS is stored into the DP array and we continue.
            int DP[n + 1][m + 1];
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < m + 1; j++)
                    if (i == 0 || j == 0)
                        DP[i][j] = 0;
                    else if (X[i - 1] == Y[j - 1])
                        DP[i][j] = 1 + DP[i - 1][j - 1];
                    else
                        DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            return DP[n][m];
        }
        int __LngCmnSubSeqOpt(string &X, string &Y, int n, int m)
        {
            //^ Now we space optimise it via DP[i][] -- Curr , DP[i-1][] -- Prev.
            vector<int> Curr(m + 1, 0), Prev(m + 1, 0);
            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < m + 1; j++)
                    if (i == 0 || j == 0)
                        Curr[j] = 0;
                    else if (X[i - 1] == Y[j - 1])
                        Curr[j] = 1 + Prev[j - 1];
                    else
                        Curr[j] = max(Prev[j], Curr[j - 1]);
                Prev = Curr;
            }
            return Curr[m];
        }
        int __LngCmnSubStrOpt(string &X, string &Y, int n, int m)
        {
            //^ Now for substring we make DP[i][j] = 0 , when X[i-1] == Y[j-1].
            vector<int> Curr(m + 1, 0), Prev(m + 1, 0);
            int mx = 0;
            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < m + 1; j++)
                    if (i == 0 || j == 0)
                        Curr[j] = 0;
                    else if (X[i - 1] == Y[j - 1])
                        Curr[j] = 1 + Prev[j - 1], mx = max(Curr[j], mx);
                    else
                        Curr[j] = 0;
                Prev = Curr;
            }
            return mx;
        }
        string __PrintLngCmnSubSeqItr(string &X, string &Y, int n, int m)
        {
            //^ For printing we would backtack the formulated DP array.
            int DP[n + 1][m + 1];
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < m + 1; j++)
                    if (i == 0 || j == 0)
                        DP[i][j] = 0;
                    else if (X[i - 1] == Y[j - 1])
                        DP[i][j] = 1 + DP[i - 1][j - 1];
                    else
                        DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            //^ Now from the back we would move to DP[i-1][j-1] and pushback when both are same and when they are not same then we go according to the max of DP[i-1][j] , DP[i][j-1].
            int i = n, j = m;
            string LCS;
            while (i != 0 && j != 0)
                if (X[i - 1] == Y[j - 1])
                    LCS.push_back(X[i - 1]), i--, j--;
                else if (DP[i - 1][j] > DP[i][j - 1])
                    i--;
                else
                    j--;
            reverse(LCS.begin(), LCS.end());
            return LCS;
        }
        string __PrintLngCmnSubStrItr(string &X, string &Y, int n, int m)
        {
            // ^ To Print the longest common substring we find the max value and index where it is found and we keep on printing by going to DP[i-1][j-1] till we find the end of it.
            pair<int, int> pr;
            int mx = 0;
            vector<vector<int>> DP(n + 1, vector<int>(m + 1, 0));
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < m + 1; j++)
                    if (i == 0 || j == 0)
                        DP[i][j] = 0;
                    else if (X[i - 1] == Y[j - 1])
                    {
                        DP[i][j] = 1 + DP[i - 1][j - 1];
                        if (mx < DP[i][j])
                        {
                            mx = DP[i][j];
                            pr.first = mx;
                            pr.second = i;
                        }
                    }
                    else
                        DP[i][j] = 0;
            int length = pr.first;
            int end = pr.second;
            string str;
            while (length--)
                str.push_back(X[end - 1]), end--;
            reverse(str.begin(), str.end());
            return str;
        }
        string __PrintSrtCmnSupSeqItr(string &X, string &Y, int n, int m)
        {
            //^ For Printing the SCS we use the same logic for printing the LCS.
            int DP[n + 1][m + 1];
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < m + 1; j++)
                    if (i == 0 || j == 0)
                        DP[i][j] = 0;
                    else if (X[i - 1] == Y[j - 1])
                        DP[i][j] = 1 + DP[i - 1][j - 1];
                    else
                        DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            //^ In this SCS printing when end of X , Y aren't matching then we would still print the maximum path element till we Reach (0 , 0) if they match we goto DP[i-1][j-1] and we continue.
            int i = n, j = m;
            string SCS;
            while (i != 0 && j != 0)
                if (X[i - 1] == Y[j - 1])
                    SCS.push_back(X[i - 1]), i--, j--;
                else if (DP[i - 1][j] > DP[i][j - 1])
                {
                    SCS.push_back(X[i - 1]);
                    i--;
                }
                else
                {
                    SCS.push_back(Y[j - 1]);
                    j--;
                }
            while (i != 0)
            {
                SCS.push_back(X[i - 1]);
                i--;
            }
            while (j != 0)
            {
                SCS.push_back(Y[j - 1]);
                j--;
            }
            reverse(SCS.begin(), SCS.end());
            return SCS;

            //^ Similarly if someone asks to find the shortest palindrome in a string which can be made would be nothing but the LCS (str , str.reverse ).
        }
        int __LngIncSubSeqRec(vector<int> &v, int ind, int Prev, vector<vector<int>> &DP)
        {
            if (ind >= signed(v.size()))
                return 0;
            if (DP[ind][Prev + 1] != -1)
                return DP[ind][Prev + 1];
            int take = 0, dontTake = __LngIncSubSeqRec(v, ind + 1, Prev, DP);
            if (Prev == -1 || v[ind] > v[Prev])
                take = 1 + __LngIncSubSeqRec(v, ind + 1, ind, DP);
            return DP[ind][Prev + 1] = max(take, dontTake);
        }
        int __LngIncSubSeqOpt(vector<int> &v, int ind, int Prev, vector<int> &DP)
        {
            if (ind >= signed(v.size()))
                return 0;
            if (DP[Prev + 1] != -1)
                return DP[Prev + 1];
            int take = 0, dontTake = __LngIncSubSeqOpt(v, ind + 1, Prev, DP);
            if (Prev == -1 || v[ind] > v[Prev])
                take = 1 + __LngIncSubSeqOpt(v, ind + 1, ind, DP);
            return DP[Prev + 1] = max(take, dontTake);
        }

    public:
        //~ DECLARE YOUR OWN FUNCTIONS TO CALL THE PRIVATE MEMBERS.
    };
    class __GRIDS
    {
    private:
        int __UniquePathsCntRec(int m, int n, vector<vector<int>> &DP)
        {
            if (m == 0 || n == 0)
                return 0;
            else if (m == 1 && n == 1)
                return 1;
            else if (DP[m][n] != -1)
                return DP[m][n];
            else
                return DP[m][n] = (__UniquePathsCntRec(m - 1, n, DP) + __UniquePathsCntRec(m, n - 1, DP));
        }
        int __UniquePathsCntItr(int m, int n, vector<vector<int>> &DP)
        {
            for (int i = 0; i < m + 1; i++)
                for (int j = 0; j < n + 1; j++)
                    if (i == 0 || j == 0)
                        DP[i][j] = 0;
                    else if (i == 1 && j == 1)
                        DP[i][j] = 1;
                    else
                        DP[i][j] = DP[i - 1][j] + DP[i][j - 1];
            return DP[m][n];
        }
        int __UniquePathsCntOpt(int m, int n)
        {
            vector<int> Prev(n + 1);
            vector<int> Curr(n + 1);
            for (int i = 0; i < m + 1; i++)
            {
                for (int j = 0; j < n + 1; j++)
                {
                    if (i == 0 || j == 0)
                        Prev[j] = 0, Curr[j] = 0;
                    else if (i == 1 && j == 1)
                        Curr[j] = 1;
                    else
                        Curr[j] = Prev[j] + Curr[j - 1];
                }
                Prev = Curr;
            }
            return Curr[n];
        }
        int __UniquePathsCntTwoOpt(int m, int n, vector<vector<int>> &Obs)
        {
            vector<int> Prev(n + 1);
            vector<int> Curr(n + 1);
            if (Obs[0][0] == 1)
                return 0;
            for (int i = 0; i < m + 1; i++)
            {
                for (int j = 0; j < n + 1; j++)
                {
                    if (i == 0 || j == 0)
                        Prev[j] = 0, Curr[j] = 0;
                    else if (i == 1 && j == 1)
                        Curr[j] = 1;
                    else if (Obs[i - 1][j - 1] == 1)
                        Curr[j] = 0;
                    else
                        Curr[j] = Prev[j] + Curr[j - 1];
                }
                Prev = Curr;
            }
            return Curr[n];
        }
    };
    class __DPONTREES
    {
    private:
        class TreeNode
        {
        public:
            int val;
            TreeNode *left;
            TreeNode *right;
        };

        int __BinTreeMaxPathSumM1(TreeNode *Root, int &Res)
        {
            //^ Res is the final answer in  DP on trees.
            if (Root == NULL)
                return INT16_MIN;
            else
            {
                int x = __BinTreeMaxPathSumM1(Root->left, Res);
                int y = __BinTreeMaxPathSumM1(Root->right, Res);
                int temp = max(Root->val + max(x, y), Root->val);
                int ans = Root->val + x + y;
                Res = max({Res, temp, ans});
                return temp;
            }
        }
        int __BinTreeMaxPathSumM2(TreeNode *root, int &Res)
        {
            if (root == NULL)
                return 0;
            int leftSum = __BinTreeMaxPathSumM2(root->left, Res);
            int rightSum = __BinTreeMaxPathSumM2(root->right, Res);
            Res = max({Res, root->val, root->val + leftSum, root->val + rightSum, root->val + leftSum + rightSum});
            return max({root->val, root->val + leftSum, root->val + rightSum});
        }

    public:
    };
    class __LEETCODE
    {
        bool __RegexMatching(string &s, string &p, int n, int m)
        {
            return false;
        }
        int __LngValidParenthesesM1(string &str)
        {
            stack<int> stk;
            stk.push(-1);
            int maxi = 0;
            for (int i = 0; i < signed(str.length()); i++)
            {
                if (str[i] == '(')
                    stk.push(i);
                else if (stk.size() > 1)
                    stk.pop(), maxi = max(maxi, i - stk.top());
                else
                    stk.pop(), stk.push(i);
            }
            return maxi;
        }
        int __LngValidParenthesesM2(string &str)
        {
            int left = 0, right = 0, ans = 0, n = str.size();
            for (int i = 0; i < n; i++)
            {
                if (str[i] == '(')
                    ++left;
                else
                    ++right;
                if (right == left)
                    ans = max(ans, 2 * right);
                else if (right > left)
                    left = right = 0;
            }
            left = right = 0;
            for (int i = n - 1; i >= 0; --i)
            {
                if (str[i] == '(')
                    ++left;
                else
                    ++right;
                if (right == left)
                    ans = max(ans, 2 * right);
                else if (left > right)
                    left = right = 0;
            }
            return ans;
        }
        int __LngValidParenthesesM3(int i, string &s, vector<int> &DP)
        {
            if (i <= 0)
                return 0;
            if (DP[i] != -1)
                return DP[i];
            if (s[i] == '(')
                DP[i] = 0;
            else if (s[i] == ')' && s[i - 1] == '(')
                DP[i] = __LngValidParenthesesM3(i - 2, s, DP) + 2;
            else if (s[i] == ')' && s[i - 1] == ')')
            {
                int len = __LngValidParenthesesM3(i - 1, s, DP);
                if (i - 1 - len >= 0 && s[i - 1 - len] == '(')
                    DP[i] = len + 2 + __LngValidParenthesesM3(i - len - 2, s, DP);
                else
                    DP[i] = 0;
            }
            return DP[i];
        }
        int __MaxSubArray(vector<int> &v)
        {
            vector<int> dp(v.size());
            int n = v.size();
            dp[0] = v[0];
            int maxx = dp[0];
            for (int i = 1; i < n; i++)
            {
                dp[i] = v[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0);
                maxx = max(maxx, dp[i]);
            }
            return maxx;
        }
        int __EditDistance(string &str, string &str1)
        {
            int n = str.length();
            int m = str1.length();
            int DP[n + 1][m + 1];
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < m + 1; j++)
                    DP[i][j] = 0;
            for (int i = 0; i < n + 1; i++)
                for (int j = 0; j < m + 1; j++)
                    if (i == 0)
                        DP[i][j] = j;
                    else if (j == 0)
                        DP[i][j] = i;
                    else if (str[i - 1] == str1[j - 1])
                        DP[i][j] = DP[i - 1][j - 1];
                    else
                        DP[i][j] = 1 + min({DP[i - 1][j], DP[i][j - 1], DP[i - 1][j - 1]});
            return DP[n][m];
        }
        int __NumDecodings(string &str, int Ind, int N, vector<int> &DP)
        {
            if (Ind >= N)
                return 1;
            else if (str[Ind] == '0')
                return 0;
            else if (DP[Ind] != -1)
                return DP[Ind];
            int take = 0;
            int nottake = 0;
            if (Ind + 1 < N)
            {
                if ((str[Ind] - '0') * 10 + (str[Ind + 1] - '0') <= 26)
                    take = __NumDecodings(str, Ind + 2, N, DP);
            }
            nottake = __NumDecodings(str, Ind + 1, N, DP);
            return DP[Ind] = take + nottake;
        }
        int __NumDecodingsItrM1(string &str, int N, vector<int> &DP)
        {
            DP[N] = 1;
            DP[N + 1] = 1;
            for (int i = N - 1; i > 0; i--)
            {
                if (str[i] == '0')
                {
                    DP[i] = 0;
                    continue;
                }
                int take = 0;
                int nottake = 0;
                if (i + 1 < N)
                {
                    if ((str[i] - '0') * 10 + (str[i + 1] - '0') <= 26)
                        take = DP[i + 2];
                }
                nottake = DP[i + 1];
                DP[i] = take + nottake;
            }
            return DP[0];
        }
        int __NumDecodingsItrM2(string &str)
        {
            vector<int> DP(str.size() + 1, 0);
            DP[str.size()] = 1;
            for (int i = str.size() - 1; i >= 0; i--)
            {

                if (str[i] != '0')
                {
                    DP[i] += DP[i + 1];
                }
                if (i + 1 < signed(str.size()) && ((str[i] == '1') || (str[i] == '2' && str[i + 1] <= '6')))
                    DP[i] += DP[i + 2];
            }
            return DP[0];
        }
        bool __IsInterLeave(string &s1, string &s2, string &s3, int x, int y, int z, vector<vector<bool>> &DP)
        {
            if (x < 0 && y < 0 && z < 0)
                return true;
            if (x >= 0 && y >= 0 && DP[x][y] != -1)
                return DP[x][y];
            if (x >= 0 && s1[x] == s3[z] && y >= 0 && s2[y] == s3[z])
                return DP[x][y] = __IsInterLeave(s1, s2, s3, x - 1, y, z - 1, DP) || __IsInterLeave(s1, s2, s3, x, y - 1, z - 1, DP);
            else if (x >= 0 && s1[x] == s3[z])
                return __IsInterLeave(s1, s2, s3, x - 1, y, z - 1, DP);
            else if (y >= 0 && s2[y] == s3[z])
                return __IsInterLeave(s1, s2, s3, x, y - 1, z - 1, DP);
            else
                return false;
        }
        int __Triangle(int row, int col, int n, vector<vector<int>> &v, vector<vector<int>> &DP)
        {
            if (row == n)
                return 0;
            else if (DP[row][col] != -1)
                return DP[row][col];
            else
                return DP[row][col] = v[row][col] + (min(__Triangle(row + 1, col, n, v, DP), __Triangle(row + 1, col + 1, n, v, DP)));
        }
        int __TriangleItr(int n, vector<vector<int>> &v, vector<vector<int>> &DP)
        {
            for (auto &&it : DP[n])
                it = 0;
            for (int i = n - 1; i >= 0; i--)
                for (int j = i; j >= 0; j--)
                    DP[i][j] = v[i][j] + min(DP[i + 1][j], DP[i + 1][j + 1]);
            return DP[0][0];
        }
        int __MaxProdSubArr(vector<int> &v)
        {
            int maxx = v[0];
            int minn = v[0];
            int val = v[0];
            for (int i = 1; i < signed(v.size()); i++)
            {
                if (v[i] < 0)
                    swap(maxx, minn);
                maxx = max(maxx, maxx * v[i]);
                minn = min(minn, minn * v[i]);
                val = max({val, maxx, minn});
            }
            return val;
        }
        bool __DungeonGame(int row, int col, int n, int m, int target, vector<vector<int>> &v)
        {
            if (target <= 0)
                return false;
            else if ((row == n + 1 && col == m) || (row == n && col == m + 1))
                return true;
            else if (row == n + 1)
                return false;
            else if (col == m + 1)
                return false;
            else
            {
                bool Rowval = __DungeonGame(row + 1, col, n, m, target + v[row][col], v);
                bool Colval = false;
                if (Rowval != true)
                    Colval = __DungeonGame(row, col + 1, n, m, target + v[row][col], v);
                return (Rowval || Colval);
            }
        }
        bool __DungeonGameItrM1(vector<vector<int>> v, int value, int m, int n)
        {
            //^ Basically we are checking that whether we can reach the end [m-1][n-1] with a value and during this path it should not become less than or equal to zero.
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                {
                    int prev = -1;
                    if (i == 0 && j == 0)
                    {
                        v[i][j] += value;
                        continue;
                    }
                    else if (i == 0)
                        prev = v[i][j - 1];
                    else if (j == 0)
                        prev = v[i - 1][j];
                    else
                        //^ This part basically find the best path to reach v[i][j]
                        prev = max(v[i - 1][j], v[i][j - 1]);
                    if (prev <= 0)
                        //^ When no path is good we write -1 in that Loc.
                        v[i][j] = -1;
                    else
                        v[i][j] += prev;
                }
            return v[m - 1][n - 1] > 0;
        }
        int __DungeonGameItrM2(vector<vector<int>> &v, int n, int m)
        {
            //^ State: DP[i][j]-> min health needed to go from (i,j) to (n-1,m-1)
            //^ Transition: DP[i][j]= max(min(DP[i+1][j], DP[i][j+1]) - v[i][j],1)
            //^ Base Case: DP[n-1][m-1]=max(1, 1 - v[n-1][m-1])
            //^ Final Answer: DP[0][0]
            vector<vector<int>> DP(n, vector<int>(m, 1e9));

            DP[n - 1][m - 1] = (v[n - 1][m - 1] <= 0 ? abs(v[n - 1][m - 1]) + 1 : 1);
            for (int i = n - 1; i >= 0; i--)
                for (int j = m - 1; j >= 0; j--)
                {
                    if (i + 1 < n)
                        DP[i][j] = min(DP[i][j], max(DP[i + 1][j] - v[i][j], 1LL));
                    if (j + 1 < m)
                        DP[i][j] = min(DP[i][j], max(DP[i][j + 1] - v[i][j], 1LL));
                }
            return DP[0][0];
        }
        int __RainWaterTrappingM1(vector<int> &Height)
        {
            int start = 0, end = Height.size() - 1, water = 0, start1 = start + 1, end1 = end - 1;
            while (start < end && start1 <= end1)
            {
                if (Height[start] >= Height[end])
                    if (Height[end] > Height[end1])
                        water += Height[end] - Height[end1], end1--;
                    else
                        end = end1, end1--;
                else if (Height[start] > Height[start1])
                    water += Height[start] - Height[start1], start1++;
                else
                    start = start1, start1++;
            }
            return water;
        }
        int __RainWaterTrappingM2(vector<int> &Height)
        {
            int water = 0;
            for (int Left = 0, Right = Height.size() - 1, Lmaxx = Height[Left], Rmaxx = Height[Right]; Left < Right; Lmaxx = max(Lmaxx, Height[Left]), Rmaxx = max(Rmaxx, Height[Right]))
                if (Lmaxx <= Rmaxx)
                    water += Lmaxx - Height[Left], Left++;
                else
                    water += Rmaxx - Height[Right], Right--;
            return water;
        }
        bool __JumpGame_i(vector<int> &v, int Start, int Dest, vector<bool> &DP)
        {
            if (Start == Dest)
                return true;
            else if (v[Start] == 0)
                return false;
            //^ Here we assumed DP array to be filled with true and as the fail cases need to be found and overlapped than the passed casses so we find the failed cases and mark it as false and when it doesn't fail programme automatically returns true.
            else if (DP[Start] != true)
                return false;
            else
            {
                bool val = false;
                if (Start + v[Start] >= Dest)
                    return true;
                else
                    for (int i = Start + 1; i <= min((Start + v[Start]), Dest); i++)
                        if (!val)
                            val |= __JumpGame_i(v, i, Dest, DP);
                        else
                            return true;
                return DP[Start] = val;
            }
        }
        bool __JumpGameItr_i(vector<int> &v)
        {
            int n = v.size();
            int maxPos = 0, i = 0;
            while (i <= maxPos)
            {
                maxPos = max(maxPos, i + v[i]);
                if (maxPos >= n - 1)
                    return 1;
                i++;
            }
            return 0;
        }
        int __JumpGame_ii(vector<int> &v, int Start, int Dest, vector<int> &DP)
        {
            if (Start == Dest)
                return 0;
            else if (v[Start] == 0)
                return 1e9;
            else if (Start + v[Start] >= Dest)
                return 1;
            else if (DP[Start] != -1)
                return DP[Start];
            else
            {
                int val = INT_MAX;
                for (int i = Start + 1; i <= min(Start + v[Start], Dest); i++)
                    val = min(val, 1 + __JumpGame_ii(v, i, Dest, DP));
                return DP[Start] = val;
            }
        }
        int __JumpGameItr_ii(vector<int> &v)
        {
            int n = v.size();
            int end = 0, range = 0, res = 0;
            for (int i = 0; i < n - 1; i++)
            {
                range = max(range, i + v[i]);
                if (i == end)
                    res++, end = range;
                if (range >= n - 1)
                    return res;
            }
            return res;
        }
        int __MinPathSum(vector<vector<int>> &Grid)
        {
            int n = Grid.size();
            int m = Grid[0].size();
            vector<vector<int>> DP(n, vector<int>(m));
            DP[0][0] = Grid[0][0];
            for (int i = 1; i < n; i++)
                DP[i][0] += DP[i - 1][0] + Grid[i][0];
            for (int j = 1; j < m; j++)
                DP[0][j] += DP[0][j - 1] + Grid[0][j];
            for (int i = 1; i < n; i++)
                for (int j = 1; j < m; j++)
                    DP[i][j] += Grid[i][j] + min(DP[i - 1][j], DP[i][j - 1]);
            return DP[n - 1][m - 1];
        }
        int __MaximalSquare(vector<vector<char>> &Matrix)
        {
            int n = Matrix.size();
            int m = Matrix[0].size();
            vector<vector<int>> Grid(n, vector<int>(m, 0));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (Matrix[i][j] == '1')
                        Grid[i][j]++;
            int Maxsize = 0;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (i == 0 || j == 0)
                        Maxsize = max(Maxsize, Grid[i][j]);
                    else if (Grid[i][j])
                        Grid[i][j] = 1 + min({Grid[i - 1][j - 1], Grid[i][j - 1], Grid[i - 1][j]}), Maxsize = max(Maxsize, Grid[i][j]);
            return Maxsize * Maxsize;
        }
        int __BuyAndSellStocksM1_ii(int Ind, vector<int> &Prices, bool Buy, vector<vector<int>> &DP)
        {
            if (Ind == signed(Prices.size()))
                return 0;
            if (DP[Ind][Buy] != -1)
                return DP[Ind][Buy];
            if (Buy)
                DP[Ind][Buy] = max(-Prices[Ind] + __BuyAndSellStocksM1_ii(Ind + 1, Prices, !Buy, DP), __BuyAndSellStocksM1_ii(Ind + 1, Prices, Buy, DP));
            else
                DP[Ind][Buy] = max(Prices[Ind] + __BuyAndSellStocksM1_ii(Ind + 1, Prices, !Buy, DP), __BuyAndSellStocksM1_ii(Ind + 1, Prices, Buy, DP));
            return DP[Ind][Buy];
        }
        int __BuyAndSellStocksM2_ii(int Ind, vector<int> &Prices, bool Buy, bool Sell, vector<vector<vector<int>>> &DP)
        {
            int take = INT_MIN;
            int nottake = INT_MIN;
            if (Ind == signed(Prices.size()))
                return 0;
            if (DP[Ind][Buy][Sell] != -1)
                return DP[Ind][Buy][Sell];
            if (Buy)
            {
                take = __BuyAndSellStocksM2_ii(Ind + 1, Prices, !Buy, !Sell, DP) - Prices[Ind];
                nottake = __BuyAndSellStocksM2_ii(Ind + 1, Prices, Buy, Sell, DP);
            }
            else
            {
                take = __BuyAndSellStocksM2_ii(Ind + 1, Prices, !Buy, !Sell, DP) + Prices[Ind];
                nottake = __BuyAndSellStocksM2_ii(Ind + 1, Prices, Buy, Sell, DP);
            }
            return DP[Ind][Buy][Sell] = max(take, nottake);
        }
        int __BuyAndSellStocksItr_ii(vector<int> &Prices)
        {
            int val = 0;
            for (int i = 0; i < signed(Prices.size()) - 1; i++)
                if (Prices[i + 1] > Prices[i])
                    val += Prices[i + 1] - Prices[i];
            return val;
        }
        int __BuyAndSellStocks_iii(int Ind, bool Buy, vector<int> &Prices, int Transactions, vector<vector<vector<int>>> &DP)
        {
            if (Ind == signed(Prices.size()))
                return 0;
            else if (Transactions > 2)
                return 0;
            else if (DP[Ind][Buy][Transactions] != -1)
                return DP[Ind][Buy][Transactions];
            else if (Buy)
                DP[Ind][Buy][Transactions] = max(-Prices[Ind] + __BuyAndSellStocks_iii(Ind + 1, !Buy, Prices, Transactions + 1, DP), __BuyAndSellStocks_iii(Ind + 1, Buy, Prices, Transactions, DP));
            else
                DP[Ind][Buy][Transactions] = max(Prices[Ind] + __BuyAndSellStocks_iii(Ind + 1, !Buy, Prices, Transactions, DP), __BuyAndSellStocks_iii(Ind + 1, Buy, Prices, Transactions, DP));
            return DP[Ind][Buy][Transactions];
        }
        int __BuyAndSellStocksItrM1_iii(vector<int> &Prices)
        {
            int n = Prices.size();
            vector<vector<vector<int>>> DP(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
            for (auto &&it : DP[n])
                for (auto &&itt : it)
                    itt = 0;
            for (int ind = n - 1; ind >= 0; ind--)
                for (int buy = 0; buy < 2; buy++)
                    for (int trans = 1; trans < 3; trans++)
                        if (buy == 1)
                            DP[ind][buy][trans] = max(-Prices[ind] + DP[ind + 1][1 - buy][trans], DP[ind + 1][buy][trans]);
                        else
                            DP[ind][buy][trans] = max(Prices[ind] + DP[ind + 1][1 - buy][trans - 1], DP[ind + 1][buy][trans]);
            return DP[0][1][2];
        }
        int __BuyAndSellStocksItrM2_iii(vector<int> &Prices)
        {
            //^ Aim is to find two pairs one after the other such that their profit would be the maximum
            int Cost1 = INT_MAX;
            int Profit1 = 0;
            int Cost2 = INT_MAX;
            int Profit2 = 0;
            for (auto &&Curr : Prices)
            {
                Cost1 = min(Cost1, Curr);
                Profit1 = max(Profit1, Curr - Cost1);
                //^ This step is especially used to reduce the Cost2 so that the new Profit2 will have Profit1 included in it.
                Cost2 = min(Cost2, Curr - Profit1);
                Profit2 = max(Profit2, Curr - Cost2);
            }
            return Profit2;
        }

    public:
    };

public:
};

// NOTE - GRAPHS.

class __GRAPHS
{
private:
    void __NumOfProvinceDfs(vector<int>[], vector<bool> &, int);
    void __NumOfProvinceBfs(vector<int>[], vector<bool> &, int);
    void __NumberOfIslandsBfs(vector<vector<char>> &, vector<vector<bool>> &, int, int, int, int);
    void __NumberOfIslandsDfs(vector<vector<char>> &, vector<vector<bool>> &, int, int, int, int);
    void __FloodFillBfs(vector<vector<int>> &, int, int, int);
    void __FloodFillDfs(vector<vector<int>> &, vector<vector<bool>> &, int, int, int, int);
    int __RottenOrangesBfs(vector<vector<int>> &);
    bool __IsCycleBfs(vector<int>[], vector<bool> &, int);
    bool __IsCycleDfs(vector<int>[], vector<bool> &, int, int);
    bool __IsBipartiteBfs(vector<int>[], vector<int> &, int);
    bool __IsBipartiteDfs(vector<int>[], vector<int> &, int, int);

public:
    class __TRAVERSAL_APPLICATIONS
    {
    private:
        void __NumOfProvinceDfs(vector<int> Graph[], vector<bool> &Vis, int Par)
        {
            //^ Here The Graph is already given.

            // ^ Here we are doing Dfs and marking the entire province as visited and the main function be like

            Vis[Par] = true;
            for (auto &Child : Graph[Par])
                if (!Vis[Par])
                    __NumOfProvinceDfs(Graph, Vis, Child);
            /*
                Main Function of this DFS be like..
                for (int i = 0; i < N; i++)
                   if (!Vis[i])
                        cnt++, __NumOfProvinceBfs(Graph, Vis, i);
                return cnt;
            */
        }
        void __NumOfProvinceBfs(vector<int> Graph[], vector<bool> &Vis, int Par)
        {
            //^ Here the Graph is already given.

            queue<int> que;
            que.push(Par);
            Vis[Par] = true;
            while (!que.empty())
            {
                int Node = que.front();
                que.pop();
                for (auto &Child : Graph[Node])
                    if (!Vis[Child])
                    {
                        que.push(Child);
                        Vis[Child] = 1;
                    }
            }

            /*
                Main Function of this BFS be like..
                for (int i = 0; i < N; i++)
                   if (!Vis[i])
                        cnt++, __NumOfProvinceBfs(Graph, Vis, i);
                return cnt;
                This is also same as DFS.
            */
        }
        void __NumberOfIslandsBfs(vector<vector<char>> &Grid, vector<vector<bool>> &Vis, int Currow, int CurCol, int rows, int cols)
        {
            //^ We need to Return the number of connected comp. int this island Grid given by 2D vector of char's with 0's and 1's representing water and land the comp. can be connected either horizontally or vertically or diagonally , now we need to tell the max number of connected comp via Bfs.

            //^ drow , dcol is of the form UDLR
            int drow[] = {-1, -1, -1, 0, 0, +1, +1, +1};
            int dcol[] = {-1, 0, +1, -1, +1, -1, 0, +1};

            queue<pair<int, int>> que;
            que.push({Currow, CurCol});
            Vis[Currow][CurCol] = true;

            while (!que.empty())
            {
                int x, y;
                x = que.front().first;
                y = que.front().second;
                que.pop();
                for (int i = 0; i < 8; i++)
                {
                    int Newx = x + drow[i];
                    int Newy = y + dcol[i];
                    if (Newx >= 0 && Newx < rows && Newy >= 0 && Newy < cols && Vis[Newx][Newy] == false && Grid[Newx][Newy] == '1')
                    {
                        que.push({Newx, Newy});
                        Vis[Newx][Newy] = true;
                    }
                }
            }

            /*
                Main Function Be like..
                int rows = Grid.size();
                int cols = Grid[0].size();
                int cnt = 0;
                vector<vector<bool>>Vis(rows,vector<bool>(cols, false));
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        if (Grid[i][j] == '1' && Vis[i][j] == false)
                        {
                            __NumberOfIslandsBfs(Grid, Vis, i, j, rows, cols);
                            cnt++;
                        }
                return cnt;
            */
        }
        void __NumberOfIslandsDfs(vector<vector<char>> &Grid, vector<vector<bool>> &Vis, int Currow, int CurCol, int rows, int cols)
        {
            //^ Here we would call Dfs for all the sides.

            int drow[] = {-1, -1, -1, 0, 0, +1, +1, +1};
            int dcol[] = {-1, 0, +1, -1, +1, -1, 0, +1};

            Vis[Currow][CurCol] = 1;

            int x, y;
            x = Currow;
            y = CurCol;

            for (int i = 0; i < 8; i++)
            {
                int Newx = x + drow[i];
                int Newy = y + dcol[i];
                if (Newx >= 0 && Newx < rows && Newy >= 0 && Newy < cols && Vis[Newx][Newy] == false && Grid[Newx][Newy] == '1')
                {
                    __NumberOfIslandsDfs(Grid, Vis, Newx, Newy, rows, cols);
                }
            }

            /*
                Main Function Be like..
                int rows = Grid.size();
                int cols = Grid[0].size();
                int cnt = 0;
                vector<vector<bool>>Vis(rows,vector<bool>(cols, false));
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        if (Grid[i][j] == '1' && Vis[i][j] == false)
                        {
                            __NumberOfIslandsBfs(Grid, Vis, i, j, rows, cols);
                            cnt++;
                        }
                return cnt;
                Same as it is in BFS.
            */
        };
        void __FloodFillBfs(vector<vector<int>> &Image, int sr, int sc, int color)
        {
            int rows = Image.size();
            int cols = Image[0].size();
            int currcol = Image[sr][sc];
            int drow[] = {-1, 0, 0, +1};
            int dcol[] = {0, -1, +1, 0};
            vector<vector<bool>> Vis(rows, vector<bool>(cols, 0));
            queue<pair<int, int>> que;
            que.push({sr, sc});
            Image[sr][sc] = color;
            while (!que.empty())
            {
                int x = que.front().first;
                int y = que.front().second;
                que.pop();
                for (int i = 0; i < 4; i++)
                {
                    int Newx = x + drow[i];
                    int Newy = y + dcol[i];
                    if (Newx >= 0 && Newx < rows && Newy >= 0 && Newy < cols && Vis[Newx][Newy] == false && Image[Newx][Newy] == currcol)
                    {
                        que.push({Newx, Newy});
                        Image[Newx][Newy] = color;
                        Vis[Newx][Newy] = true;
                    }
                }
            }
        }
        void __FloodFillDfs(vector<vector<int>> &Image, vector<vector<bool>> &Vis, int sr, int sc, int currcol, int color)
        {
            int rows = Image.size();
            int cols = Image[0].size();
            int drow[] = {-1, 0, 0, +1};
            int dcol[] = {0, -1, +1, 0};
            int x = sr;
            int y = sc;
            for (int i = 0; i < 4; i++)
            {
                int Newx = x + drow[i];
                int Newy = y + dcol[i];
                if (Newx >= 0 && Newx < rows && Newy >= 0 && Newy < cols && Vis[Newx][Newy] == false && Image[Newx][Newy] == currcol)
                {
                    Vis[sr][sc] = true;
                    Image[Newx][Newy] = color;
                    __FloodFillDfs(Image, Vis, Newx, Newy, currcol, color);
                }
            }

            /*
                Main function be like..
                vector<vector<bool>> Vis(Image.size(), vector<bool>(Image[0].size(), false));
                Vis[sr][sc] = true;
                int currcol = Image[sr][sc];
                Image[sr][sc] = color;
                __FloodFillDfs(Image, Vis, sr, sc, currcol, color);
                return Image;
            */
        }
        int __RottenOrangesBfs(vector<vector<int>> &Grid)
        {
            int rows = Grid.size();
            int cols = Grid[0].size();
            int cnt = 0;

            queue<__TRIPLET> que;
            vector<vector<bool>> Vis(rows, vector<bool>(cols, false));

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    if (Grid[i][j] == 2)
                    {
                        que.push(__TRIPLET(i, j, 0));
                        Vis[i][j] = true;
                    }
                    else if (Grid[i][j] == 1)
                        cnt++;

            int drow[] = {-1, 0, 0, +1};
            int dcol[] = {0, -1, +1, 0};

            int mx = 0;

            while (!que.empty())
            {
                __TRIPLET obj = que.front();
                que.pop();
                int x = obj.first;
                int y = obj.second;
                mx = max(mx, obj.third);
                for (int i = 0; i < 4; i++)
                {
                    int Newx = x + drow[i];
                    int Newy = y + dcol[i];
                    if (Newx >= 0 && Newx < rows && Newy >= 0 && Newy < cols && Vis[Newx][Newy] == false && Grid[Newx][Newy] == 1)
                    {
                        que.push({Newx, Newy, obj.third + 1});
                        Vis[Newx][Newy] = true;
                        cnt--;
                    }
                }
            }
            //^ This is very difficult to be done via DFS as you need to traverse through all of those nodes level wise so we can't use DFS.
            return (cnt ? -1 : mx);
        }
        bool __IsCycleBfs(vector<int> Graph[], vector<bool> &Vis, int Node)
        {
            queue<pair<int, int>> que;
            que.push({Node, -1});

            Vis[Node] = true;

            while (!que.empty())
            {
                int x = que.front().first;
                int y = que.front().second;
                que.pop();
                for (auto &&Child : Graph[x])
                    if (!Vis[Child])
                    {
                        Vis[Child] = true;
                        que.push({Child, x});
                    }
                    else if (Vis[Child] && Child != y)
                        return true;
            }
            return false;

            /*
                MAIN FUNCTION be like :-
                bool isCycle(int V, vector<int> adj[])
                {
                    vector<bool> vis(V, 0);
                    for (int i = 0; i < V; i++)
                    {
                        if (!vis[i])
                        {
                            if (__IsCycleBfs(adj, vis, i))
                                return true;
                        }
                    }
                    return false;
                }
            */
        }
        bool __IsCycleDfs(vector<int> Graph[], vector<bool> &Vis, int Node, int Par)
        {
            bool k = false;
            Vis[Node] = true;
            for (auto &Child : Graph[Node])
            {
                if (Child == Par)
                    continue;
                else if (Vis[Child])
                    return true;
                else
                {
                    k = (k | __IsCycleDfs(Graph, Vis, Child, Node));
                }
            }
            return k;
            /*
                MAIN FUNCTION be like :-
                bool isCycle(int V, vector<int> adj[])
                {
                    vector<bool> vis(V, 0);
                    for (int i = 0; i < V; i++)
                    {
                        if (!vis[i])
                        {
                            if (__IsCycleDfs(adj, vis, i, -1))
                                return true;
                        }
                    }
                    return false;
                }
            */
        }
        bool __IsBipartiteBfs(vector<int> Graph[], vector<int> &Vis, int Node)
        {
            queue<pair<int, int>> que;
            que.push({Node, -1});
            Vis[Node] = 0;
            while (!que.empty())
            {
                int x = que.front().first;
                int y = que.front().second;
                que.pop();
                for (auto &Child : Graph[x])
                    if (Child == y)
                        continue;
                    else if (Vis[Child] == -1)
                    {
                        Vis[Child] = !Vis[x];
                        que.push({Child, x});
                    }
                    else if (Vis[Child] == Vis[x])
                        return false;
                    else
                        continue;
            }
            return true;
            /*
                MAIN FUNCTION be like :-
                bool isBipartite(int V, vector<int> adj[])
                {
                    vector<int> vis(V, -1);
                    for (int i = 0; i < V; i++)
                    {
                        if (vis[i] == -1)
                        {
                            if (!__IsBipartiteBfs(adj, vis, i))
                                return false;
                        }
                    }
                    return true;
                }
            */
        }
        bool __IsBipartiteDfs(vector<int> Graph[], vector<int> &Vis, int Node, int Par)
        {
            bool k = true;
            for (auto &Child : Graph[Node])
            {
                if (Child == Par)
                    continue;
                else if (Vis[Child] == -1)
                {
                    Vis[Child] = !Vis[Node];
                    k = (k & __IsBipartiteDfs(Graph, Vis, Child, Node));
                }
                else if (Vis[Child] == Vis[Node])
                    return false;
            }
            return k;
            /*
                MAIN FUNCTION be like :-
                bool isBipartite(int V, vector<int> adj[])
                {
                    vector<int> vis(V, -1);
                    for (int i = 0; i < V; i++)
                    {
                        if (vis[i] == -1)
                        {
                            vis[i] = 0;
                            if (!__IsBipartiteDfs(adj, vis, i, -1))
                                return false;
                        }
                    }
                    return true;
                }
            */
        }
        bool __Eventual_Safe_StatesDfs(vector<int> Graph[], vector<bool> &Vis, vector<bool> &PathVis, vector<bool> &Check, int Node)
        {
            Vis[Node] = 1;
            PathVis[Node] = 1;
            Check[Node] = 0;
            for (auto &Child : Graph[Node])
            {
                if (!Vis[Child])
                {
                    if (__Eventual_Safe_StatesDfs(Graph, Vis, PathVis, Check, Child))
                    {
                        Check[Node] = 0;
                        return true;
                    }
                }
                else if (PathVis[Child])
                {
                    Check[Node] = 0;
                    return true;
                }
            }
            Check[Node] = 1;
            PathVis[Node] = 0;
            return false;
            /*
                Main function be like :-
                vector<int> eventualSafeNodes(int V, vector<int> adj[])
                {
                    vector<bool>Vis(V,false);
                    vector<bool>PathVis(V,false);
                    vector<bool>Check(V,false);
                    vector<int>Ans;
                    for(int i = 0 ; i < V ; i++)
                    {
                        if(!Vis[i])
                            __Eventual_Safe_StatesDfs(adj, Vis, PathVis, Check, i);
                        if(Check[i])
                            Ans.push_back(i);
                    }
                    return Ans;
                }
            */
        }
        void __TopoSortDfs(vector<int> Graph[], vector<bool> &Vis, stack<int> &Stk, int Node)
        {
            Vis[Node] = true;
            for (auto &Child : Graph[Node])
                if (!Vis[Child])
                    __TopoSortDfs(Graph, Vis, Stk, Child);
            Stk.push(Node);
            /*
                Main function be like :-
                vector<int> topoSort(int V, vector<int> adj[])
                {
                    stack<int> Stk;
                    vector<bool> Vis(V, false);
                    vector<int>Ans;
                    for(int i = 0 ; i < V ; i++)
                    {
                        if(!Vis[i])
                            __TopoSortDfs(adj, Vis, Stk, i);
                    }
                    while(!Stk.empty())
                    {
                        Ans.push_back(Stk.top());
                        Stk.pop();
                    }
                    return Ans;
                }
            */
        }
        vector<int> __TopoSortBfs(vector<int> Graph[], vector<bool> &Vis, int N)
        {
            vector<int> Degree(N);
            queue<int> que;
            for (int i = 0; i < N; i++)
            {
                for (auto &&it : Graph[i])
                {
                    Degree[it]++;
                }
            }
            for (int i = 0; i < N; i++)
            {
                if (Degree[i] == 0)
                    que.push(i);
            }
            vector<int> ans;
            while (!que.empty())
            {
                int node = que.front();
                ans.push_back(node);
                Vis[node] = true;
                que.pop();
                for (auto &Child : Graph[node])
                    if (!Vis[Child])
                    {
                        Degree[Child]--;
                        if (Degree[Child] == 0)
                            que.push(Child);
                    }
            }
            return ans;
            /*
                Main function be like :-
                vector<int> toposort(int V , vector<int> adj[])
                {
                    vector<bool> Vis(V,false);
                    return (__TopoSortBfs(adj, Vis, N));
                }
            */
        }
        bool __IsCycle_DirectedDfs(vector<int> Graph[], vector<bool> &Vis, vector<bool> &PathVis, int Node)
        {
            Vis[Node] = true;
            PathVis[Node] = true;
            for (auto &Child : Graph[Node])
                if (!Vis[Child])
                {
                    if (__IsCycle_DirectedDfs(Graph, Vis, PathVis, Node))
                        return true;
                }
                else if (PathVis[Child])
                    return true;
            PathVis[Node] = false;
            return false;
            /*
                Main function be like :-
                bool isCyclic(int V, vector<int> adj[])
                {
                    vector<bool> Vis(V, false);
                    vector<bool> PathVis(V, false);
                    for (int i = 0; i < V; i++)
                        if (!Vis[i])
                            if (__IsCycle_DirectedDfs(adj, Vis, PathVis, i))
                                return true;
                    return false;
                }
            */
        }
        bool __IsCycle_DirectedBfs(vector<int> Graph[], vector<bool> &Vis, int N)
        {
            vector<int> Degree(N);
            queue<int> que;
            for (int i = 0; i < N; i++)
                for (auto &&it : Graph[i])
                    Degree[it]++;
            for (int i = 0; i < N; i++)
                if (Degree[i] == 0)
                    que.push(i);
            vector<int> ans;
            while (!que.empty())
            {
                int node = que.front();
                ans.push_back(node);
                Vis[node] = true;
                que.pop();
                for (auto &Child : Graph[node])
                    if (!Vis[Child])
                    {
                        Degree[Child]--;
                        if (Degree[Child] == 0)
                            que.push(Child);
                    }
            }
            return (ans.size() != unsigned(N));
        }
        string __Alien_DictionaryBfs(string Dict[], int N, int K)
        {
            vector<int> Graph[K];
            for (int i = 0; i < N - 1; i++)
            {
                string str = Dict[i];
                string str1 = Dict[i + 1];
                for (int j = 0; j < signed(min(str.length(), str1.length())); j++)
                {
                    if (str[j] != str1[j])
                    {
                        Graph[str[j] - 'a'].push_back(str1[j] - 'a');
                        break;
                    }
                }
            }
            vector<bool> Vis(N, false);
            vector<int> Pos = __TopoSortBfs(Graph, Vis, K);
            string Ans;
            for (auto &&it : Pos)
            {
                Ans.push_back(it + 'a');
            }
            return Ans;
        }
        vector<int> __ShortestPathToposort(int N, int M, vector<vector<int>> &edges)
        {
            vector<pair<int, int>> Graph[N];
            for (int i = 0; i < M; i++)
                Graph[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            vector<int> Vis(N);
            //^ Here There is No need to use the visited array as it is a DAG.
            queue<int> que;
            vector<int> Indegree(N);
            for (int i = 0; i < N; i++)
                for (auto &it : Graph[i])
                    Indegree[it.first]++;
            for (int i = 0; i < N; i++)
                if (Indegree[i] == 0)
                    que.push(i);
            vector<int> Toposort;
            while (!que.empty())
            {
                Toposort.push_back(que.front());
                int x = que.front();
                Vis[x] = true;
                // ^ As in the Child there would never be parent so no need to use Vis array.
                que.pop();
                for (auto &Child : Graph[x])
                    if (!Vis[Child.first])
                    //^ As it would be priorly present in the queue so , as it Child can never be present in the queue so there's no need to check this.
                    {
                        Indegree[Child.first]--;
                        if (Indegree[Child.first] == 0)
                            que.push(Child.first);
                    }
            }
            vector<int> Dist(N, INT_MAX / 2);
            Dist[0] = 0;
            for (auto &it : Toposort)
                for (auto &Child : Graph[it])
                    if (Dist[it] + Child.second < Dist[Child.first])
                        Dist[Child.first] = Dist[it] + Child.second;
            for (auto &&it : Dist)
                if (it >= INT_MAX / 2)
                    it = -1;
            return Dist;
        }
        vector<int> __ShortestPathUnitUndirected(vector<vector<int>> &edges, int N, int M, int src)
        {
            vector<int> Graph[N];
            for (auto &it : edges)
            {
                Graph[it[0]].push_back(it[1]);
                Graph[it[1]].push_back(it[0]);
            };
            vector<bool> Vis(N, false);
            queue<int> que;
            vector<int> Dist(N, -1);
            Dist[src] = 0;
            que.push(src);
            while (!que.empty())
            {
                int x = que.front();
                Vis[x] = true;
                que.pop();
                for (auto &Child : Graph[x])
                    if (!Vis[Child])
                    {
                        if (Dist[Child] == -1)
                            Dist[Child] = Dist[x] + 1;
                        else
                            Dist[Child] = min(Dist[Child], Dist[x] + 1);
                        que.push(Child);
                    }
            }
            return Dist;
        }

    public:
        //~ DECLARE YOUR OWN FUNCTIONS TO CALL THE PRIVATE MEMBERS.
    };

public:
    //~ DECLARE YOUR OWN FUNCTIONS TO CALL THE PRIVATE MEMBERS.
};

// NOTE - BINARY SEARCH.

class __BINARYSEARCH
{
private:
    int __BinarySearchRec(vector<int> &v, int Left, int Right, int Target)
    {
        //^ here left = 0  , and right = n - 1 now we apply bin search.
        while (Left <= Right)
        {
            int Mid = Left + (Right - Left) / 2;
            if (v[Mid] == Target)
                return Mid;
            else if (v[Mid] < Target)
                return __BinarySearchRec(v, Mid + 1, Right, Target);
            else
                return __BinarySearchRec(v, Left, Mid - 1, Target);
        }
        return -1;
    }
    int __BinarySearchItr(vector<int> &v, int Left, int Right, int Target)
    {
        while (Left <= Right)
        {
            int Mid = Left + (Right - Left) / 2;
            if (v[Mid] == Target)
                return Mid;
            else if (v[Mid] < Target)
                Left = Mid + 1;
            else
                Right = Mid - 1;
        }
        return -1;
    }
    int __RevBinarySearchItr(vector<int> &v, int Left, int Right, int Target)
    {
        while (Left <= Right)
        {
            int Mid = Left + (Right - Left) / 2;
            if (v[Mid] == Target)
                return Mid;
            else if (v[Mid] < Target)
                Right = Mid - 1;
            else
                Left = Mid + 1;
        }
        return -1;
    }
    int __BinarySearchLowBnd(vector<int> &v, int Left, int Right, int Target)
    {
        int val = -1;
        while (Left <= Right)
        {
            int Mid = Left + (Right - Left) / 2;
            if (v[Mid] == Target)
                val = Mid, Right = Mid - 1;
            else if (v[Mid] < Target)
                Left = Mid + 1;
            else
                Right = Mid - 1;
        }
        return val;
    }
    int __BinarySearchUpprFlr(vector<int> &v, int Left, int Right, int Target)
    {
        int val = -1;
        while (Left <= Right)
        {
            int Mid = Left + (Right - Left) / 2;
            if (v[Mid] == Target)
                val = Mid, Left = Mid + 1;
            else if (v[Mid] < Target)
                Left = Mid + 1;
            else
                Right = Mid - 1;
        }
        return val;
    }
    int __BinarySearchMinRotSrtArr(vector<int> &v, int Left, int Right)
    {
        while (Left <= Right)
        {
            int Mid = (Left + Right) / 2;
            if (v[Mid] > v[Right])
                Left = Mid + 1;
            else if (v[Mid] < v[Left])
                Right = Mid, Left++;
            else
                Right--;
        }
        return Left;
    }
    bool __BinarySearchCalender_i(int Start, int End, set<pair<int, int>> &S)
    {
        if (S.empty())
        {
            S.insert({Start, End});
            return true;
        }
        auto itr = S.lower_bound({Start, End});
        if (itr != S.end())
        {
            pair<int, int> Curr = *itr;
            if (Curr.first < End)
                return false;
        }
        if (itr != S.begin())
        {
            pair<int, int> Prev = *(--itr);
            if (Prev.second > Start)
                return false;
        }
        S.insert({Start, End});
        return true;
    }
    int __BinarySearchRussDollEnv(vector<vector<int>> &env)
    {
        // sorting by height & if we encounter same height
        // sort by descending order of width
        sort(env.begin(), env.end(), [](vector<int> &a, vector<int> &b)
             {
            if(a[0]==b[0]) return a[1] > b[1];
        return a[0] < b[0]; });

        // e.g. -> env => (3,8) (4,5) (2,1) (2,6) (7,8) (5,3) (5,7)
        // sorted version => (2,6) (2,1) (3,8) (4,5) (5,7) (5,3) (7,8)

        // Now, we only need to care about width
        // So, as of now we only need to look upon v[i][1]
        // [ 6, 1, 8, 5, 7, 3, 8 ]

        // Now, we can only put envolop a in envolop b another if width of a is
        // less than width of b, or we can say we need an envolop whose width
        // is just greater than envolop a ( height we have already handled )
        // So, we can think of lower_bound and Longest Increasing Subsequence

        // because we have sorted all envolopes of a particular height
        // by descending order of width, one envolope will not interfare with
        // another envolop of same height, if we apply lower_bound
        // i.e. first elem greater than equal to itself in lis

        vector<int> lis;

        for (int i = 0; i < signed(env.size()); i++)
        {
            int ele = env[i][1];

            int idx = lower_bound(lis.begin(), lis.end(), ele) - lis.begin();

            if (idx >= signed(lis.size()))
                lis.push_back(ele);
            else
                lis[idx] = ele;
        }

        return lis.size();
    }

    int __BinarySearchPeakEle(vector<int> &v)
    {
        int left = 0;
        int right = v.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (v[mid] < v[mid + 1])
                left = mid + 1;
            else
                right = mid;
        }
        return right;
    }
    double __BinarySearchSqrt(int N)
    {
        double Left = 0;
        double Right = N;
        while ((Right - Left) > 1e-13)
        {
            double Mid = Left + (Right - Left) / 2;
            if (Mid * Mid == N)
                return Mid;
            else if (Mid * Mid < N)
                Left = Mid;
            else
                Right = Mid;
        }
        return Left;
    }
    int __BinarySearchKokoBanana(vector<int> &v, int Hours)
    {
        int start = 1;
        int end = 1000000000;
        while (start < end)
        {
            int mid = start + (end - start) / 2;
            int cnt = 0;
            for (auto it : v)
                cnt += (it / mid) + (it % mid != 0);
            if (cnt <= Hours)
            {
                end = mid;
            }
            else
                start = mid + 1;
        }
        return end;
    }
    int __BinarySearchShipPackage(vector<int> &Weights, int Days)
    {
        int x = accumulate(Weights.begin(), Weights.end(), 0), Left = 1, Right = x;
        while (Left < Right)
        {
            int Mid = Left + (Right - Left) / 2, cnt = 1, sum = 0;
            for (auto &&it : Weights)
            {
                sum += it;
                if (Mid < it)
                    goto label;
                else if (sum > Mid)
                    cnt++, sum = it;
            }
            if (cnt <= Days)
                Right = Mid;
            else
            label:
                Left = Mid + 1;
        }
        return Right;
    }
    int __BinarySearchBloomDay(vector<int> &bloomDay, int m, int k)
    {
        if ((m * k) > signed(bloomDay.size()))
            return -1;
        int left = 1, right = *max_element(bloomDay.begin(), bloomDay.end());
        while (left < right)
        {
            int mid = left + (right - left) / 2, cnt = 0, conti = 0;
            for (auto it : bloomDay)
            {
                if (it <= mid)
                {
                    conti++;
                    if (conti == k)
                        cnt++, conti = 0;
                }
                else
                    conti = 0;
            }
            if (cnt < m)
                left = mid + 1;
            else
                right = mid;
        }
        return right;
    }
    int __BinarySearchMagForce(vector<int> &v, int m)
    {
        sort(v.begin(), v.end());
        int right = v.back();
        int left = 1;
        while (left < right)
        {
            int start = v.front();
            int mid = ceil((left + right) / 2.0);
            int cnt = 1;
            for (auto &it : v)
                if ((it - start) >= mid)
                    cnt++, start = it;
            if (cnt < m)
                right = mid - 1;
            else
                left = mid;
        }
        return left;
    }

public:
};

// NOTE - SLIDING WINDOW.

class __SLIDINGWINDOW
{
private:
public:
};

// NOTE - TWO POINTERS.

class __TWOPOINTERS
{
private:
    int __ContainerWithMaxWater(vector<int> &Height)
    {
        int N = Height.size();
        int Start = 0;
        int End = N - 1;
        int Value = INT_MIN;
        while (Start < End)
        {
            Value = max(Value, min(Height[Start], Height[End]) * (End - Start));
            if (Height[Start] >= Height[End])
                End--;
            else
                Start++;
        }
        return Value;
    }

public:
};

// NOTE - SEGMENT TREES.

class __SEGMENTTREES
{
private:
    class __TreeNode
    {
    private:
    public:
        int value;
        __TreeNode *Left = NULL;
        __TreeNode *Right = NULL;
    };
    __TreeNode *__SegTreeCreationDMA(int CurrLeft, int CurrRight, vector<int> &v)
    {
        auto it = new __TreeNode;
        if (CurrLeft == CurrRight)
        {
            it->value = v[CurrLeft];
            return it;
        }
        else
        {
            int Mid = CurrLeft + (CurrRight - CurrLeft) / 2;
            it->Left = __SegTreeCreationDMA(CurrLeft, Mid, v);
            it->Right = __SegTreeCreationDMA(Mid + 1, CurrRight, v);
            it->value = min(it->Left->value, it->Right->value);
            return it;
        }
    }
    void __UpdateSegTreeDMA(int Left, int Right, int Loc, int Newval, __TreeNode *Node)
    {
        int Mid = Left + (Right - Left) / 2;
        if ((Left == Right) && (Left == Loc))
            Node->value = Newval;
        else if (Mid >= Loc)
            __UpdateSegTreeDMA(Left, Mid, Loc, Newval, Node->Left), Node->value = min(Node->Left->value, Node->Right->value);
        else
            __UpdateSegTreeDMA(Mid + 1, Right, Loc, Newval, Node->Right), Node->value = min(Node->Left->value, Node->Right->value);
    }
    int __SegTreeQueryDMA(int Left, int Right, int TreeLeft, int TreeRight, __TreeNode *Node)
    {
        if (Left > TreeRight || Right < TreeLeft)
            return INT_MAX;
        else if (TreeLeft >= Left && TreeRight <= Right)
            return Node->value;
        else
        {
            int Mid = TreeLeft + (TreeRight - TreeLeft) / 2;
            return (min(__SegTreeQueryDMA(Left, Right, TreeLeft, Mid, Node->Left), __SegTreeQueryDMA(Left, Right, Mid + 1, TreeRight, Node->Right)));
        }
    }
    void __SegTreeTraversal(__TreeNode *Head)
    {
        if (Head == NULL)
            return;
        else
        {
            cout << Head->value << " ";
            __SegTreeTraversal(Head->Left);
            __SegTreeTraversal(Head->Right);
        }
    }
    void __SegTreeCreation(int Ind, int Left, int Right, vector<int> &v, vector<int> &Seg)
    {
        if (Left == Right)
            Seg[Ind] = v[Left];
        else
        {
            int Mid = Left + (Right - Left) / 2;
            __SegTreeCreation(2 * Ind + 1, Left, Mid, v, Seg);
            __SegTreeCreation(2 * Ind + 2, Mid + 1, Right, v, Seg);
            Seg[Ind] = min(Seg[2 * Ind + 1], Seg[2 * Ind + 2]);
        }
    }
    void __UpdateSegTree(int Ind, int TreeLeft, int TreeRight, int Loc, int Newval, vector<int> &Seg)
    {
        int Mid = TreeLeft + (TreeRight - TreeLeft) / 2;
        if ((TreeLeft == TreeRight) && (TreeLeft == Loc))
            Seg[Ind] = Newval;
        else if (Mid >= Loc)
            __UpdateSegTree(Ind * 2 + 1, TreeLeft, Mid, Loc, Newval, Seg), Seg[Ind] = min(Seg[2 * Ind + 1], Seg[2 * Ind + 2]);
        else
            __UpdateSegTree(Ind * 2 + 2, Mid + 1, TreeRight, Loc, Newval, Seg), Seg[Ind] = min(Seg[2 * Ind + 1], Seg[2 * Ind + 2]);
    }
    int __SegTreeQuery(int Ind, int Left, int Right, int TreeLeft, int TreeRight, vector<int> &Seg)
    {
        if (Left > TreeRight || Right < TreeLeft)
            return INT_MAX;
        else if (TreeLeft >= Left && TreeRight <= Right)
            return Seg[Ind];
        else
        {
            int Mid = TreeLeft + (TreeRight - TreeLeft) / 2;
            return (min(__SegTreeQuery(2 * Ind + 1, Left, Right, TreeLeft, Mid, Seg), __SegTreeQuery(2 * Ind + 2, Left, Right, Mid + 1, TreeRight, Seg)));
        }
    }
    // Segment tree GFG
    //  A utility function to get minimum of two numbers
    int minVal(int x, int y) { return (x < y) ? x : y; }

    // A utility function to get the
    // middle index from corner indexes.
    int getMid(int s, int e) { return s + (e - s) / 2; }

    /* A recursive function to get the
    minimum value in a given range
    of array indexes. The following
    are parameters for this function.

        st --> Pointer to segment tree
        index --> Index of current node in the
            segment tree. Initially 0 is
            passed as root is always at index 0
        ss & se --> Starting and ending indexes
                    of the segment represented
                    by current node, i.e., st[index]
        qs & qe --> Starting and ending indexes of query range */
    int RMQUtil(int *st, int ss, int se, int qs, int qe, int index)
    {
        // If segment of this node is a part
        // of given range, then return
        // the min of the segment
        if (qs <= ss && qe >= se)
            return st[index];

        // If segment of this node
        // is outside the given range
        if (se < qs || ss > qe)
            return INT_MAX;

        // If a part of this segment
        // overlaps with the given range
        int mid = getMid(ss, se);
        return minVal(RMQUtil(st, ss, mid, qs, qe, 2 * index + 1),
                      RMQUtil(st, mid + 1, se, qs, qe, 2 * index + 2));
    }

    // Return minimum of elements in range
    // from index qs (query start) to
    // qe (query end). It mainly uses RMQUtil()
    int RMQ(int *st, int n, int qs, int qe)
    {
        // Check for erroneous input values
        if (qs < 0 || qe > n - 1 || qs > qe)
        {
            cout << "Invalid Input";
            return -1;
        }

        return RMQUtil(st, 0, n - 1, qs, qe, 0);
    }

    // A recursive function that constructs
    // Segment Tree for array[ss..se].
    // si is index of current node in segment tree st
    int constructSTUtil(int arr[], int ss, int se,
                        int *st, int si)
    {
        // If there is one element in array,
        // store it in current node of
        // segment tree and return
        if (ss == se)
        {
            st[si] = arr[ss];
            return arr[ss];
        }

        // If there are more than one elements,
        // then recur for left and right subtrees
        // and store the minimum of two values in this node
        int mid = getMid(ss, se);
        st[si] = minVal(constructSTUtil(arr, ss, mid, st, si * 2 + 1),
                        constructSTUtil(arr, mid + 1, se, st, si * 2 + 2));
        return st[si];
    }

    /* Function to construct segment tree
    from given array. This function allocates
    memory for segment tree and calls constructSTUtil() to
    fill the allocated memory */
    int *constructST(int arr[], int n)
    {
        // Allocate memory for segment tree

        // Height of segment tree
        int x = (int)(ceil(log2(n)));

        // Maximum size of segment tree
        int max_size = 2 * (int)pow(2, x) - 1;

        int *st = new int[max_size];

        // Fill the allocated memory st
        constructSTUtil(arr, 0, n - 1, st, 0);

        // Return the constructed segment tree
        return st;
    }

public:
};

// NOTE - STACKS , HEAPS , PRIORITY-QUEUES.

class __STACKS_HEAPS_PRIORITYQUEUES
{
private:
public:
};

// NOTE - MISCELLANEOUS.

class MISCELLANEOUS
{
private:
public:
};

void solve()
{
}

signed main(signed argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    solve();
    return 0;
}
