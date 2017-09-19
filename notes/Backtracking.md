# ���ݷ�

## 1. ����

�����㷨ʵ����һ������ö�ٵ��������Թ��̣���Ҫ�����������Թ�����Ѱ������Ľ⣬�������Ѳ������������ʱ���͡����ݡ����أ����Ա��·����

���ݷ���һ��ѡ������������ѡ��������ǰ�������ԴﵽĿ�ꡣ����̽����ĳһ��ʱ������ԭ��ѡ�񲢲��Ż�ﲻ��Ŀ�꣬���˻�һ������ѡ��**�����߲�ͨ���˻����ߵļ���Ϊ���ݷ������������������ĳ��״̬�ĵ��Ϊ�����ݵ㡱��**

��ิ�ӵģ���ģ�ϴ�����ⶼ����ʹ�û��ݷ����С�ͨ�ý��ⷽ���������ơ�

## 2. ����˼��

�ڰ�����������н�Ľ�ռ����У�����������������Ĳ��ԣ��Ӹ����������̽����ռ�������̽����ĳһ���ʱ��Ҫ���жϸý���Ƿ��������Ľ⣬����������ʹӸý���������̽����ȥ������ý�㲻��������Ľ⣬������������Ƚ����ݡ�����ʵ���ݷ����Ƕ���ʽͼ��������������㷨����

���û��ݷ�����������н�ʱ��Ҫ���ݵ������Ҹ��������п��е�������Ҫ�ѱ�������Ž�����

����ʹ�û��ݷ�����һ����ʱ��ֻҪ�����������һ����Ϳ��Խ�����

����һЩ�������ĸ��**�ݹ飬���ݣ�DFS��**
������һ����·������������ʱ���߲�ͨ�ͻ�ͷ��·�����ߣ�ֱ����ͨ�˻��߷��ִ�ɽ������ͨ��
DFS��һ�ֿ�·���ԣ�����һ�������ߵ�ͷ����������һ����һ��·�ߵ�ͷ����Ҳ�ǻ����õ��Ĳ��ԡ�������ͼ�ϻ���ʱ���ǽ���DFS��
�ݹ���һ����Ϊ�����ݺ͵ݹ����һ�ޣ�����һ�Բ��Ͼͻص���ʱ��·������һ������õݹ�ʵ�֣���ȻҲ���Բ��ã���ջ��
�����Ի���ͳ�ƣ���Ϊ���������ȥ�����š�


## 3. �û��ݷ������һ�㲽�裺

1. ����������⣬ȷ������Ľ�ռ䣺����Ӧ��ȷ��������Ľ�ռ䣬����Ľ�ռ�Ӧ���ٰ��������һ�������ţ��⡣
2. ȷ��������չ��������
3. ��������ȷ�ʽ������ռ䣬���������������ü�֦����������Ч������

һ����ݵ����������֣�

1. Find a path to success ��û�н�
2. Find all paths to success �����н�
  - �����н�ĸ���
  - �����н�ľ�����Ϣ
3. Find the best path to success �����Ž�

���ڵ�һ������(����û�н�)���������ǳ��Ÿ����ӵģ�����������������ӭ�ж��⣺

```java
boolean solve(Node n) {
    if n is a leaf node {
        if the leaf is a goal node, return true
        else return false
    } else {
        for each child c of n {
            if solve(c) succeeds, return true
        }
        return false
    }
}
```

�ڶ��֣�

```java
void solve(Node n) {
    if n is a leaf node {
        if the leaf is a goal node, count++, return;
        else return
    } else {
        for each child c of n {
            solve(c)
        }
    }
}
```

�����֣�

```java
void solve(Node n) {
    if n is a leaf node {
        if the leaf is a goal node, update best result, return;
        else return
    } else {
        for each child c of n {
            solve(c)
        }
    }
}
```

## 4. ����

### �˻ʺ� N-Queens

1. ����n������û�н⣻
2. ����n���м��ֽ⣻([Leetcode N-Queens II](https://github.com/HongfeiXu/LeetCode/blob/master/algorithms/cpp/NQueens2.h))
3. ����n���������н⣻([Leetcode N-Queens](https://github.com/HongfeiXu/LeetCode/blob/master/algorithms/cpp/NQueens.h))

### LeetCode 39. Combination Sum

����n���������н�
��ʼ��ռ�������

![](https://github.com/HongfeiXu/LeetCode/blob/master/images/CombinationSum.png?raw=true)

**������֦��Ľ�ռ�������**

![](https://github.com/HongfeiXu/LeetCode/blob/master/images/CombinationSum_2.png?raw=true)

[C++ʵ��](https://github.com/HongfeiXu/LeetCode/blob/master/algorithms/cpp/CombinationSum.h)


## Reference

[����ȫ��](https://segmentfault.com/a/1190000006121957)

[Backtracking](https://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html)