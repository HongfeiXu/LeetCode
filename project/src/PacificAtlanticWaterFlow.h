#pragma once

/*

417. Pacific Atlantic Water Flow

Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, 
the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).

Approach:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic
将 mxn 矩阵扩展为 (m+2)x(n+2) 

       0  0   0   0   0   0 INT_MAX 
       0  1   2   2   3  (5) 0
       0  3   2   3  (4) (4) 0
       0  2   4  (5)  3   1  0
       0 (6) (7)  1   4   5  0
       0 (5)  1   1   2   4  0
  INT_MAX 0   0   0   0   0  0

分别从 (0,0) 点 (m+1, n+1) 点出发，进行广度优先搜索，寻找能够到达的节点
能够到达：与当前节点相邻，并且海拔高度大于等于当前节点
得到两组能够到达的节点，取交集，即为可以到达两大洋的水流

Approach v2:
两个广度优先搜索，搜索可以从左边和上边逆流到达的水流，以及可以从右边和下边逆流到达的水流。
即，对于太平洋，左边、上边一开始就放入队列中，并标记为已访问（可到达）
对于大西洋，右边、下边也一开始就放入队列中，并标记为已访问（可到达）
思路是，广度优先搜索不一定非要从一个顶点出发，可以从多个顶点出发。

*/

#include <vector>
#include <utility>
#include <queue>

using namespace std;

//class Solution {
//public:
//	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix)
//	{
//		vector<pair<int, int>> result;
//		if (matrix.empty())
//			return result;
//		int m = matrix.size();
//		int n = matrix[0].size();
//		queue<pair<int, int>> Q_pacific;
//		queue<pair<int, int>> 
//	}
//};