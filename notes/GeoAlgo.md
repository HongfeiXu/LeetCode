# Goemetric Algorithms

## 1. Orientation of 3 ordered points

>Ref: https://www.geeksforgeeks.org/orientation-3-ordered-points/

给定三个顶点，(p1,p2,p3)，返回它们的顺序：

1. counterclockwise，逆时针
2. clockwise，顺时针
3. colinear，平行

判定方法如下，利用到了叉乘的性质，
```
l1 = p2 - p1;
l2 = p3 - p1;

k 为 z 轴的单位向量
l1 x l2 = |l1| * |l2| * sin<l1,l2> * k = ((l1.x * l2.y) - (l1.y * l2.x)) * k

若上述叉乘模的结果
	< 0，顺时针
	> 0，逆时针
	= 0，平行  
```
代码实现如下，
```c++
struct Point {
	int x, y;
};

/*
To find orientation of ordered triplet (p1, p2, p3).
The function returns following values
0 --> p1, q2 and r3 are colinear
1 --> Clockwise
2 --> Counterclockwise
*/
int orientation(Point p1, Point p2, Point p3)
{
	int cross_product = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
	if (cross_product < 0)
		return 1;
	else if (cross_product > 0)
		return 2;
	else
		return 0;
}
```

## 2. How to check if two given line segments intersect?

Given two line segments (p1, p2) and (q1, q2), find if the given line segments intersect with each other.

>Ref: CLRS ch33 计算几何学

**两条线段相交当且仅当下面两个条件至少成立一个：**

1. 每条线段都跨越了包含另一条线段的直线。
2. 一条线段的某个端点落在另一条线段上。

```c++
#include <algorithm>
#include <iostream>

using namespace std;

struct Point {
	int x;
	int y;
};

// >0 p1,p2,p3 逆时针
// <0 p1,p2,p3 顺时针
// ==0 p1,p2,p3 共线
int direction(const Point& p1, const Point& p2, const Point& p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// 已知 p1,p2,q共线，
// 判断 顶点 q 是否在 p1,p2 所构成的线段上
bool onSegment(const Point& p1, const Point& p2, const Point& q)
{
	return q.x <= max(p1.x, p2.x) && 
		q.x >= min(p1.x, p2.x) &&
		q.y <= max(p1.y, p2.y) && 
		q.y >= min(p1.y, p2.y);
}

// 判断线段 p1p2 与线段 q1q2 是否相交
bool doIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2)
{
	int d1 = direction(p1, p2, q1);
	int d2 = direction(p1, p2, q2);
	int d3 = direction(q1, q2, p1);
	int d4 = direction(q1, q2, p2);
	
	// 若线段 p1,p2 与线段 q1,q2 相互跨越，则一定相交
	if ((d1 < 0 && d2 > 0 || d1 > 0 && d2 < 0) && (d3 < 0 && d4 > 0 || d3 > 0 && d4 < 0))
		return true;
	// 若存在三个顶点共线的情况，则判断其中一个顶点是否在另两个顶点构成的线段上
	else if (d1 == 0 && onSegment(p1, p2, q1))
		return true;
	else if (d2 == 0 && onSegment(p1, p2, q2))
		return true;
	else if (d3 == 0 && onSegment(q1, q2, p1))
		return true;
	else if (d4 == 0 && onSegment(q1, q2, p2))
		return true;
	else
		return false;
}
```

## 3. Convex Hull

>Ref: https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
>Ref: CLRS ch 33

### Jarvis’s Algorithm or Wrapping

Javis 步进法运用打包的技术来计算一个点集Q的凸包。   
从直观上，可以把Javis步进法看做在集合Q的外面紧紧的包了一层纸。   
Time: O(nh)，其中h是CH(Q)中的顶点数。   

```c++
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
	int x, y;
};

int orientation(const Point& p1, const Point& p2, const Point& p3);
int squareDist(const Point& p1, const Point& p2);

// Get convex hull of a set of points
// 若不存在凸包，返回空的结果。
vector<Point> convexHullJavis(const vector<Point>& points)
{
	vector<Point> hull;
	// 至少需要有3个顶点
	if (points.size() < 3)
		return hull;
	// 查找最左节点
	int left_most = 0;
	for (int i = 1; i < points.size(); ++i)
	{
		if (points[left_most].x > points[i].x)
			left_most = i;
		// 若存在多个具有最小x坐标的节点，选择最靠上的一个节点 (为了去除那些在凸包边上的顶点)
		else if (points[left_most].x == points[i].x && points[left_most].y < points[i].y)
			left_most = i;
	}
	int p = left_most;
	int q = 0;
	do {
		// 把当前节点加入 hull
		hull.push_back(points[p]);
		// 选择下一个节点 q，要保证所有其他节点（除了p，q）都使得(p,q,r)为逆时针方向
		q = (p + 1) % points.size();
		for (int i = 0; i < points.size(); ++i)
		{
			// 如果 i 比 q 更加逆时针，即(p,i,q)为逆时针，更新 q
			int ori = orientation(points[p], points[i], points[q]);
			if (ori == 2)
				q = i;
			// 如果p,q,i三点共线，选择q,i中距离p最远的点加入 hull (为了去除那些在凸包边上的顶点)
			else if (ori == 0)
			{
				if (squareDist(points[p], points[q]) < squareDist(points[p], points[i]))
					q = i;
			}
		}
		p = q;
	} while (q != left_most);	// 直到回到第一个节点
								// 如果结点个数小于3，说明不存在凸包，返回空的结果。
	if (hull.size() < 3)
	{
		hull.clear();
		return hull;
	}
	return hull;
}

/*
To find orientation of ordered triplet (p1, p2, p3).
The function returns following values
0 --> p1, p2 and p3 are colinear
1 --> Clockwise
2 --> Counterclockwise
*/
int orientation(const Point& p1, const Point& p2, const Point& p3)
{
	int cross_product = (p2.x - p1.x) * (p3.y - p1.y) -
		(p2.y - p1.y) * (p3.x - p1.x);
	if (cross_product < 0)
		return 1;
	else if (cross_product > 0)
		return 2;
	else
		return 0;
}

int squareDist(const Point& p1, const Point& p2)
{
	return (p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x);
}

```

### Graham Scan

>Ref: https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
>Ref: CLRS ch 33

Time: O(nlgn)

```c++
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
	int x, y;
};

int orientation(const Point& p1, const Point& p2, const Point& p3);
int squareDist(const Point& p1, const Point& p2);
bool cmp(const Point& lhs, const Point& rhs);

Point p0;	// Graham 扫描法出发的第一个顶点，传入 cmp 函数中，用来给所有顶点按照极角大小排序

vector<Point> convexHullGrahamScan(vector<Point> points)
{
	vector<Point> hull;

	// Find point with the minimum y-coordinate
	int min = 0;
	for (int i = 1; i < points.size(); ++i)
	{
		// Pick the bottom-most or chose the left
		// most point in case of tie
		if (points[i].y < points[min].y)
			min = i;
		else if (points[i].y == points[min].y && points[i].x < points[min].x)
			min = i;
	}

	// Place the bottom-most point at the first position
	swap(points[0], points[min]);

	// Sort n-1 points with respect to the first point.
	// A point p1 comes before p2 in sorted output if p2 
	// has larger polar angle(in counterclockwise 
	// direction) than p1
	p0 = points[0];

	sort(points.begin(), points.end(), cmp);

	// 如果有两个或更多的点对 p0 的极角相同，那么直保留距 p0 最远的那个点
	int m = 1;	// m 为出去上述那些顶点后，还余下的顶点数量
	for (int i = 1; i < points.size(); ++i)
	{
		// 删除 p[i] 当 p[i] 与 p[i+1] 相对于 p0 有相同的极角时（用一系列的交换操作，以及记录有效元素的个数m来起到删除元素的效果）
		while (i < points.size() - 1 && orientation(p0, points[i], points[i + 1]) == 0)
			++i;
		points[m] = points[i];
		++m;
	}

	// 若修改后，有效顶点个数少于3，则返回空
	if (m < 3)
		return hull;

	// 对栈进行初始化（用 vector 来模拟栈）
	hull.push_back(points[0]);
	hull.push_back(points[1]);
	hull.push_back(points[2]);

	// 处理余下的 n-3 个顶点
	for (int i = 3; i < m; ++i)
	{
		// 若 NEXT-TO-TOP(hull), TOP(hull), point[i] 不构成向左转，则删除栈顶元素，
		// 直到 NEXT-TO-TOP(hull), TOP(hull), point[i] 构成左转为止
		while (orientation(*(hull.end() - 2), *(hull.end() - 1), points[i]) != 2)
			hull.pop_back();
		// 若 NEXT-TO-TOP(hull), TOP(hull), point[i] 构成左转，则将i压入栈中
		hull.push_back(points[i]);
	}

	return hull;
}

/*
To find orientation of ordered triplet (p1, p2, p3).
The function returns following values
0 --> p1, p2 and p3 are colinear
1 --> Clockwise
2 --> Counterclockwise
*/
int orientation(const Point& p1, const Point& p2, const Point& p3)
{
	int cross_product = (p2.x - p1.x) * (p3.y - p1.y) -
		(p2.y - p1.y) * (p3.x - p1.x);
	if (cross_product < 0)
		return 1;
	else if (cross_product > 0)
		return 2;
	else
		return 0;
}

int squareDist(const Point& p1, const Point& p2)
{
	return (p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x);
}

bool cmp(const Point& lhs, const Point& rhs)
{
	int ori = orientation(p0, lhs, rhs);
	if (ori == 2)
		return true;
	else if (ori == 0)
		return squareDist(p0, lhs) < squareDist(p0, rhs);
	else
		return false;
}

```

## 4. How to check if given four points form a square

>Ref: https://www.geeksforgeeks.org/check-given-four-points-form-square/

Approach:

The idea is to pick any point and calculate its distance from rest of the points. Let the picked picked point be ‘p’. To form a square, distance of two points must be same from ‘p’, let this distance be d. The distance from one point must be different from that d and must be equal to √2 times d. Let this point with different distance be ‘q’.   
The above condition is not good enough as the the point with different distance can be on the other side. We also need to check that q is at same distance from 2 other points and this distance is same as d.

Below is C++ implementation of above idea.

```c++
#include <iostream>
#include <vector>

using namespace std;

struct Point {
	int x;
	int y;
};

int squareDist(const Point& p1, const Point& p2)
{
	return (p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x);
}

bool isSquare(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	int d2 = squareDist(p1, p2);	// from p1 to p2
	int d3 = squareDist(p1, p3);	// from p1 to p3
	int d4 = squareDist(p1, p4);	// from p1 to p4

	// 特殊情况：若四个顶点位置相同，如果不加这一句，会返回 true
	if (d2 == 0 || d3 == 0 || d4 == 0)
		return false;

	// 如果 p1 到 p2,p3具有相同距离，则要形成正方形，p4需要满足下面两个条件：
	// 1. p4 到 p1 的距离 = sqrt(2) * p1 到 p2 距离
	// 2. p4 到 p2,p3具有相同距离
	// 有一个不符合，则
	if (d2 == d3)
	{
		return 2 * d2 == squareDist(p1, p4) &&
			squareDist(p4, p2) == squareDist(p4, p3);
	}

	if (d2 == d4)
	{
		return 2 * d2 == squareDist(p1, p3) &&
			squareDist(p3, p2) == squareDist(p3, p4);
	}
	
	if (d3 == d4)
	{
		return 2 * d3 == squareDist(p1, p2) &&
			squareDist(p2, p3) == squareDist(p2, p4);
	}

	return false;
}
```

## 5. How to check if given polyton is convex

Approach:

对任意顶点 p[i]，其法向量为 p[i]p[i-1] cross p[i]p[i+1]，若所有顶点法向量方向相同（或者为0，三点共线），则是一个凸多边形，否则不是。

```c++
#include <vector>

using namespace std;

class Solution {
public:
	/**
	* @param point: a list of two-tuples
	* @return: a boolean, denote whether the polygon is convex
	*/
	bool isConvex(vector<vector<int>> &point) {
		// write your code here
		int pre_sign = 0;	// 记录前面的顶点法向符号（若为0则不跟新）
		for (int i = 0; i < point.size(); ++i)
		{
			// 当前顶点 point[i] 的法向量的值
			int curr = corssProductLength(point[i], point[(i + point.size() - 1) % point.size()], point[(i + 1) % point.size()]);
			if (curr < 0)
			{
				if (pre_sign == 1)	// 若当前计算的叉乘结果符号与前面的不同，则返回 false
					return false;
				else
					pre_sign = -1;	// 否则， 更新 pre_sign
			}
			else if (curr > 0)
			{
				if (pre_sign == -1)
					return false;
				else
					pre_sign = 1;
			}
		}
		return true;
	}

	// 计算 ab X ac，得到 a 点的法向量
	int corssProductLength(const vector<int>& a, const vector<int>& b, const vector<int>& c)
	{
		return (b.front() - a.front()) * (c.back() - a.back()) - (b.back() - a.back()) * (c.front() - a.front());
	}
};
```

## 6. Given n line segments, find if any two segments intersect

>Ref: CLRS Ch 33
>Ref: http://jeffe.cs.illinois.edu/teaching/373/notes/x06-sweepline.pdf
>Ref: https://www.geeksforgeeks.org/given-a-set-of-line-segments-find-if-any-two-segments-intersect/

扫除线法。能够确定是否存在相交线段，但不输出相交点。

Time: O(nlgn)，n为给定的线段数目。

主要两个步骤，线段排序，移动扫描线。

伪代码如下，具体细节参考 Ref。

```c++
// S 是 n 条线段组成的集合
ANY-SEGMENTS-INTERSECT(S)
{
    T = NIL
    sort the endpoints of segments in S from left to right,
    breaking ties by putting left endpoints before right endpoints
    and breaking further ties by putting points with lower
    y-coordinates first
    for each point p in the sorted list of endpoints
        if p is the left endpoint of a segment s
            INSERT(T, s)
            if (ABOVE(T, s) exists and intersect s)
                or (BELOW(T, s) exists and intersect s)
                return TRUE
        if p is the right endpoint of a segment s
            if both ABOVE(T, s) and BELOW(T, s) exists
                and ABOVE(T, s) intersects BELOW(T, s)
                return TRUE
            DELETE(T, s)
    return FALSE
}
```

其中 T 为平衡二叉搜索树（亦可以是红黑树），保证每一次 INSERT,DELETE,ABOVE,BELOW操作的时间复杂度为 O(lgn)。树中结点为线段信息，将关键字的比较替换为基于叉积的比较，以确定当前新增的线段的位置。