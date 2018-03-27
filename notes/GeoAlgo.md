# Goemetric Algorithms

## 1. Orientation of 3 ordered points

>Ref: https://www.geeksforgeeks.org/orientation-3-ordered-points/

�����������㣬(p1,p2,p3)���������ǵ�˳��

1. counterclockwise����ʱ��
2. clockwise��˳ʱ��
3. colinear��ƽ��

�ж��������£����õ��˲�˵����ʣ�
```
l1 = p2 - p1;
l2 = p3 - p1;

k Ϊ z ��ĵ�λ����
l1 x l2 = |l1| * |l2| * sin<l1,l2> * k = ((l1.x * l2.y) - (l1.y * l2.x)) * k

���������ģ�Ľ��
	< 0��˳ʱ��
	> 0����ʱ��
	= 0��ƽ��  
```
����ʵ�����£�
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

>Ref: CLRS ch33 ���㼸��ѧ

**�����߶��ཻ���ҽ������������������ٳ���һ����**

1. ÿ���߶ζ���Խ�˰�����һ���߶ε�ֱ�ߡ�
2. һ���߶ε�ĳ���˵�������һ���߶��ϡ�

```c++
#include <algorithm>
#include <iostream>

using namespace std;

struct Point {
	int x;
	int y;
};

// >0 p1,p2,p3 ��ʱ��
// <0 p1,p2,p3 ˳ʱ��
// ==0 p1,p2,p3 ����
int direction(const Point& p1, const Point& p2, const Point& p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// ��֪ p1,p2,q���ߣ�
// �ж� ���� q �Ƿ��� p1,p2 �����ɵ��߶���
bool onSegment(const Point& p1, const Point& p2, const Point& q)
{
	return q.x <= max(p1.x, p2.x) && 
		q.x >= min(p1.x, p2.x) &&
		q.y <= max(p1.y, p2.y) && 
		q.y >= min(p1.y, p2.y);
}

// �ж��߶� p1p2 ���߶� q1q2 �Ƿ��ཻ
bool doIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2)
{
	int d1 = direction(p1, p2, q1);
	int d2 = direction(p1, p2, q2);
	int d3 = direction(q1, q2, p1);
	int d4 = direction(q1, q2, p2);
	
	// ���߶� p1,p2 ���߶� q1,q2 �໥��Խ����һ���ཻ
	if ((d1 < 0 && d2 > 0 || d1 > 0 && d2 < 0) && (d3 < 0 && d4 > 0 || d3 > 0 && d4 < 0))
		return true;
	// �������������㹲�ߵ���������ж�����һ�������Ƿ������������㹹�ɵ��߶���
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

### Jarvis��s Algorithm or Wrapping

Javis ���������ô���ļ���������һ���㼯Q��͹����   
��ֱ���ϣ����԰�Javis�����������ڼ���Q����������İ���һ��ֽ��   
Time: O(nh)������h��CH(Q)�еĶ�������   

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
// ��������͹�������ؿյĽ����
vector<Point> convexHullJavis(const vector<Point>& points)
{
	vector<Point> hull;
	// ������Ҫ��3������
	if (points.size() < 3)
		return hull;
	// ��������ڵ�
	int left_most = 0;
	for (int i = 1; i < points.size(); ++i)
	{
		if (points[left_most].x > points[i].x)
			left_most = i;
		// �����ڶ��������Сx����Ľڵ㣬ѡ����ϵ�һ���ڵ� (Ϊ��ȥ����Щ��͹�����ϵĶ���)
		else if (points[left_most].x == points[i].x && points[left_most].y < points[i].y)
			left_most = i;
	}
	int p = left_most;
	int q = 0;
	do {
		// �ѵ�ǰ�ڵ���� hull
		hull.push_back(points[p]);
		// ѡ����һ���ڵ� q��Ҫ��֤���������ڵ㣨����p��q����ʹ��(p,q,r)Ϊ��ʱ�뷽��
		q = (p + 1) % points.size();
		for (int i = 0; i < points.size(); ++i)
		{
			// ��� i �� q ������ʱ�룬��(p,i,q)Ϊ��ʱ�룬���� q
			int ori = orientation(points[p], points[i], points[q]);
			if (ori == 2)
				q = i;
			// ���p,q,i���㹲�ߣ�ѡ��q,i�о���p��Զ�ĵ���� hull (Ϊ��ȥ����Щ��͹�����ϵĶ���)
			else if (ori == 0)
			{
				if (squareDist(points[p], points[q]) < squareDist(points[p], points[i]))
					q = i;
			}
		}
		p = q;
	} while (q != left_most);	// ֱ���ص���һ���ڵ�
								// ���������С��3��˵��������͹�������ؿյĽ����
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

Point p0;	// Graham ɨ�跨�����ĵ�һ�����㣬���� cmp �����У����������ж��㰴�ռ��Ǵ�С����

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

	// ��������������ĵ�� p0 �ļ�����ͬ����ôֱ������ p0 ��Զ���Ǹ���
	int m = 1;	// m Ϊ��ȥ������Щ����󣬻����µĶ�������
	for (int i = 1; i < points.size(); ++i)
	{
		// ɾ�� p[i] �� p[i] �� p[i+1] ����� p0 ����ͬ�ļ���ʱ����һϵ�еĽ����������Լ���¼��ЧԪ�صĸ���m����ɾ��Ԫ�ص�Ч����
		while (i < points.size() - 1 && orientation(p0, points[i], points[i + 1]) == 0)
			++i;
		points[m] = points[i];
		++m;
	}

	// ���޸ĺ���Ч�����������3���򷵻ؿ�
	if (m < 3)
		return hull;

	// ��ջ���г�ʼ������ vector ��ģ��ջ��
	hull.push_back(points[0]);
	hull.push_back(points[1]);
	hull.push_back(points[2]);

	// �������µ� n-3 ������
	for (int i = 3; i < m; ++i)
	{
		// �� NEXT-TO-TOP(hull), TOP(hull), point[i] ����������ת����ɾ��ջ��Ԫ�أ�
		// ֱ�� NEXT-TO-TOP(hull), TOP(hull), point[i] ������תΪֹ
		while (orientation(*(hull.end() - 2), *(hull.end() - 1), points[i]) != 2)
			hull.pop_back();
		// �� NEXT-TO-TOP(hull), TOP(hull), point[i] ������ת����iѹ��ջ��
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

The idea is to pick any point and calculate its distance from rest of the points. Let the picked picked point be ��p��. To form a square, distance of two points must be same from ��p��, let this distance be d. The distance from one point must be different from that d and must be equal to ��2 times d. Let this point with different distance be ��q��.   
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

	// ������������ĸ�����λ����ͬ�����������һ�䣬�᷵�� true
	if (d2 == 0 || d3 == 0 || d4 == 0)
		return false;

	// ��� p1 �� p2,p3������ͬ���룬��Ҫ�γ������Σ�p4��Ҫ������������������
	// 1. p4 �� p1 �ľ��� = sqrt(2) * p1 �� p2 ����
	// 2. p4 �� p2,p3������ͬ����
	// ��һ�������ϣ���
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

�����ⶥ�� p[i]���䷨����Ϊ p[i]p[i-1] cross p[i]p[i+1]�������ж��㷨����������ͬ������Ϊ0�����㹲�ߣ�������һ��͹����Σ������ǡ�

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
		int pre_sign = 0;	// ��¼ǰ��Ķ��㷨����ţ���Ϊ0�򲻸��£�
		for (int i = 0; i < point.size(); ++i)
		{
			// ��ǰ���� point[i] �ķ�������ֵ
			int curr = corssProductLength(point[i], point[(i + point.size() - 1) % point.size()], point[(i + 1) % point.size()]);
			if (curr < 0)
			{
				if (pre_sign == 1)	// ����ǰ����Ĳ�˽��������ǰ��Ĳ�ͬ���򷵻� false
					return false;
				else
					pre_sign = -1;	// ���� ���� pre_sign
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

	// ���� ab X ac���õ� a ��ķ�����
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

ɨ���߷����ܹ�ȷ���Ƿ�����ཻ�߶Σ���������ཻ�㡣

Time: O(nlgn)��nΪ�������߶���Ŀ��

��Ҫ�������裬�߶������ƶ�ɨ���ߡ�

α�������£�����ϸ�ڲο� Ref��

```c++
// S �� n ���߶���ɵļ���
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

���� T Ϊƽ�������������������Ǻ����������֤ÿһ�� INSERT,DELETE,ABOVE,BELOW������ʱ�临�Ӷ�Ϊ O(lgn)�����н��Ϊ�߶���Ϣ�����ؼ��ֵıȽ��滻Ϊ���ڲ���ıȽϣ���ȷ����ǰ�������߶ε�λ�á�