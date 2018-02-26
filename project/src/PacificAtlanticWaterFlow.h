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
�� mxn ������չΪ (m+2)x(n+2) 

       0  0   0   0   0   0 INT_MAX 
       0  1   2   2   3  (5) 0
       0  3   2   3  (4) (4) 0
       0  2   4  (5)  3   1  0
       0 (6) (7)  1   4   5  0
       0 (5)  1   1   2   4  0
  INT_MAX 0   0   0   0   0  0

�ֱ�� (0,0) �� (m+1, n+1) ����������й������������Ѱ���ܹ�����Ľڵ�
�ܹ�����뵱ǰ�ڵ����ڣ����Һ��θ߶ȴ��ڵ��ڵ�ǰ�ڵ�
�õ������ܹ�����Ľڵ㣬ȡ��������Ϊ���Ե����������ˮ��

Approach v2:
������������������������Դ���ߺ��ϱ����������ˮ�����Լ����Դ��ұߺ��±����������ˮ����
��������̫ƽ����ߡ��ϱ�һ��ʼ�ͷ�������У������Ϊ�ѷ��ʣ��ɵ��
���ڴ������ұߡ��±�Ҳһ��ʼ�ͷ�������У������Ϊ�ѷ��ʣ��ɵ��
˼·�ǣ��������������һ����Ҫ��һ��������������ԴӶ�����������

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