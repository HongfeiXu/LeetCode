# 回溯法

## 1. 概念

回溯算法实际上一个类似枚举的搜索尝试过程，主要是在搜索尝试过程中寻找问题的解，当发现已不满足求解条件时，就“回溯”返回，尝试别的路径。

回溯法是一种选优搜索法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并不优或达不到目标，就退回一步重新选择，**这种走不通就退回再走的技术为回溯法，而满足回溯条件的某个状态的点称为“回溯点”。**

许多复杂的，规模较大的问题都可以使用回溯法，有“通用解题方法”的美称。

## 2. 基本思想

在包含问题的所有解的解空间树中，按照深度优先搜索的策略，从根结点出发深度探索解空间树。当探索到某一结点时，要先判断该结点是否包含问题的解，如果包含，就从该结点出发继续探索下去，如果该结点不包含问题的解，则逐层向其祖先结点回溯。（其实回溯法就是对隐式图的深度优先搜索算法）。

若用回溯法求问题的所有解时，要回溯到根，且根结点的所有可行的子树都要已被搜索遍才结束。

而若使用回溯法求任一个解时，只要搜索到问题的一个解就可以结束。

还有一些爱混淆的概念：**递归，回溯，DFS。**
回溯是一种找路方法，搜索的时候走不通就回头换路接着走，直到走通了或者发现此山根本不通。
DFS是一种开路策略，就是一条道先走到头，再往回走一步换一条路走到头，这也是回溯用到的策略。在树和图上回溯时人们叫它DFS。
递归是一种行为，回溯和递归如出一辙，都是一言不合就回到来时的路，所以一般回溯用递归实现；当然也可以不用，用栈。
以下以回溯统称，因为这个词听上去很文雅。


## 3. 用回溯法解题的一般步骤：

1. 针对所给问题，确定问题的解空间：首先应明确定义问题的解空间，问题的解空间应至少包含问题的一个（最优）解。
2. 确定结点的扩展搜索规则
3. 以深度优先方式搜索解空间，并在搜索过程中用剪枝函数避免无效搜索。

一般回溯的问题有三种：

1. Find a path to success 有没有解
2. Find all paths to success 求所有解
  - 求所有解的个数
  - 求所有解的具体信息
3. Find the best path to success 求最优解

对于第一类问题(问有没有解)，基本都是长着个样子的，理解了它，其他类别迎刃而解：

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

第二种：

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

第三种：

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

## 4. 例子

### 八皇后 N-Queens

1. 给个n，问有没有解；
2. 给个n，有几种解；([Leetcode N-Queens II](https://github.com/HongfeiXu/LeetCode/blob/master/algorithms/cpp/NQueens2.h))
3. 给个n，给出所有解；([Leetcode N-Queens](https://github.com/HongfeiXu/LeetCode/blob/master/algorithms/cpp/NQueens.h))

### LeetCode 39. Combination Sum

给个n，给出所有解
初始解空间树如下

![](https://github.com/HongfeiXu/LeetCode/blob/master/images/CombinationSum.png?raw=true)

**经过剪枝后的解空间树如下**

![](https://github.com/HongfeiXu/LeetCode/blob/master/images/CombinationSum_2.png?raw=true)

[C++实现](https://github.com/HongfeiXu/LeetCode/blob/master/algorithms/cpp/CombinationSum.h)


## Reference

[回溯全集](https://segmentfault.com/a/1190000006121957)

[Backtracking](https://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html)