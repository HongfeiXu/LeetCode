# Bit Algorithms

## Position of rightmost set bit

>Ref: https://www.geeksforgeeks.org/position-of-rightmost-set-bit/

I/P    18,   Binary Representation 010010   
O/P   2   
I/P    19,   Binary Representation 010011   
O/P   1   

Algorithm:
Let I/P be 12 (1100)

1. Take two's complement of the given no as all bits are reverted except the first '1' from right to left (10111)

2. Do an bit-wise & with original no, this will return no with the required one only (00010)

3. Take the log2 of the no, you will get position-1 (1)

4. Add 1 (2)


```c++
#include<stdio.h>
#include<math.h>
 
unsigned int getFirstSetBitPos(int n)
{
   return log2(n&-n)+1;
}
 
int main()
{
    int n = 12;
    printf("%u", getFirstSetBitPos(n));
    getchar();
    return 0;
}
```

## Single Number

**136. Single Number**

Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**137. Single Number II**

Given an array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**260. Single Number III**

Given an array of numbers nums, in which exactly two elements appear 
only once and all the other elements appear exactly twice. 
Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
