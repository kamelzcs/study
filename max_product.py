#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @param A, a list of integers
    # @return an integer
    def maxProduct(self, A):
        len_A = len(A)
        ans = A[0]
        small = ans
        big = ans
        for index in range(1, len_A):
            num = A[index]
            next_small = next_big = num
            candidate_first = big * num
            candidate_second = small * num
            next_big = max(next_big, max(candidate_first, candidate_second))
            next_small = min(next_small, min(candidate_first, candidate_second))
            if next_big > ans:
                ans = next_big
            big, small = next_big, next_small
        return ans

print Solution().maxProduct([2, 0, 3, 0, -2, 4])
