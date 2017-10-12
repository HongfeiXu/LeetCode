# Largest Sum Contiguous Subarray

aka 最大子数列问题

>在计算机科学中，最大子数列问题的目标是在数列的一维方向找到一个连续的子数列，使该子数列的和最大。例如，对一个数列 −2, 1, −3, 4, −1, 2, 1, −5, 4，其连续子数列中和最大的是 4, −1, 2, 1, 其和为6。


![Kadane Algorithm](https://github.com/HongfeiXu/LeetCode/blob/master/images/kadane-Algorithm.png?raw=true)


## Kadane算法

Kadane算法扫描一次整个数列的所有数值，在每一个扫描点计算以该点数值为结束点的子数列的最大和。该子数列由两部分组成：以前一个位置为结束点的最大子数列、该位置的数值。**因为该算法用到了“最佳子结构”（以每个位置为终点的最大子数列都是基于其前一位置的最大子数列计算得出），该算法可看成动态规划的一个例子。**

算法可用如下Python代码实现：
```python
def max_subarray(A):
    max_ending_here = max_so_far = A[0]
    for x in A[1:]:
        max_ending_here = max(x, max_ending_here + x)
        max_so_far = max(max_so_far, max_ending_here)
    return max_so_far
```
该问题的一个变种是：如果数列中含有负数元素，允许返回长度为零的子数列。该问题可用如下代码解决：
```python
def max_subarray(A):
    max_ending_here = max_so_far = A[0]
    for x in A[1:]:
        max_ending_here = max(0, max_ending_here + x)
        max_so_far = max(max_so_far, max_ending_here)
    return max_so_far
```
这种算法稍作修改就可以记录最大子数列的起始位置。Kadane算法时间复杂度为 BigO(n)，空间复杂度为 BigO(1)。

## 例题

- LeetCode 53. Maximum Subarray
- LeetCode 121. Best Time to Buy and Sell Stock

## Reference

- [GeeksForGeeks](http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)
- [Wikipedia](https://zh.wikipedia.org/wiki/%E6%9C%80%E5%A4%A7%E5%AD%90%E6%95%B0%E5%88%97%E9%97%AE%E9%A2%98)
- [my 3 approaches](https://github.com/HongfeiXu/LearnCLRS/blob/master/ch04%20Divide-and-Conquer/FindMaxSubArray.cpp)