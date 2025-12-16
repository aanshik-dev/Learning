#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int change2(vector<int> &coins, int amount, vector<vector<int>> &dp, int i) {
    if (amount == 0)
      return 1;
    if (i == 0) {
      if (amount % coins[0] == 0)
        return 1;
      else
        return 0;
    }
    if (dp[i][amount] != -1)
      return dp[i][amount];
    int notTake = change2(coins, amount, dp, i - 1);
    int take = 0;
    if (amount >= coins[i]) {
      take = change2(coins, amount - coins[i], dp, i);
    }
    dp[i][amount] = take + notTake;
    return dp[i][amount];
  }

  public:
  int change(int amount, vector<int> &coins) {
    int n = coins.size();
    vector<vector<long long>> dp(n, vector<long long>(amount + 1, 0));

    for (int i = 0; i < n; i++) {
      dp[i][0] = 1;
    }
    for (int i = 0; i <= amount; i++) {
      if (i % coins[0] == 0)
        dp[0][i] = 1;
      else
        dp[0][i] = 0;
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1; j <= amount; j++) {
        long long notTake = dp[i - 1][j];
        long long take = 0;
        if (j >= coins[i]) {
          take = dp[i][j - coins[i]];
        }
        dp[i][j] = take + notTake;
      }
    }
    return dp[n - 1][amount];
  }
};

int main() {
  vector<int> coins = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 254, 256, 258, 260, 262, 264, 266, 268, 270, 272, 274, 276, 278, 280, 282, 284, 286, 288, 290, 292, 294, 296, 298, 300, 302, 304, 306, 308, 310, 312, 314, 316, 318, 320, 322, 324, 326, 328, 330, 332, 334, 336, 338, 340, 342, 344, 346, 348, 350, 352, 354, 356, 358, 360, 362, 364, 366, 368, 370, 372, 374, 376, 378, 380, 382, 384, 386, 388, 390, 392, 394, 396, 398, 400, 402, 404, 406, 408, 410, 412, 414, 416, 418, 420, 422, 424, 426, 428, 430, 432, 434, 436, 438, 440, 442, 444, 446, 448, 450, 452, 454, 456, 458, 460, 462, 464, 466, 468, 470, 472, 474, 476, 478, 480, 482, 484, 486, 488, 490, 492, 494, 496, 498, 500, 502, 504, 506, 508, 510, 512, 514, 516, 518, 520, 522, 524, 526, 528, 530, 532, 534, 536, 538, 540, 542, 544, 546, 548, 550, 552, 554, 556, 558, 560, 562, 564, 566, 568, 570, 572, 574, 576, 578, 580, 582, 584, 586, 588, 780, 936, 1170, 1560, 2340, 4680};
  int amount = 4681;
  int n = coins.size();
  Solution sol;
  vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
  int res = sol.change2(coins, amount, dp, n - 1);
  cout << res << endl;
  int res2 = sol.change(amount, coins);
  cout << res2 << endl;
  return 0;
}
