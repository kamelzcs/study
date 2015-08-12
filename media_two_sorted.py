#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.

class Solution:
    # @return a float
    def upper_bound(self, data, start, end, pivot):
        while start <= end:
            middle = (start + end) / 2
            if data[middle] > pivot:
                end = middle - 1
            else:
                start = middle + 1
        return end

    def find(self, nth, start_A, end_A, start_B, end_B):
        if end_A < start_A:
            return self.B[start_B + nth - 1]
        if end_B < start_B:
            return self.A[start_A + nth - 1]
        if nth == 1:
            return min(self.A[start_A], self.B[start_B])
        total_A, total_B = end_A - start_A + 1, end_B - start_B + 1
        if total_A == 1 and total_B == 1:
            return max(self.A[start_A], self.B[start_B])
        if total_A > total_B:
            middle_A = start_A + (total_A - 1) / 2
            middle_B = self.upper_bound(self.B, start_B, end_B, self.A[middle_A])
        else:
            middle_B = start_B + (total_B - 1) / 2
            middle_A = self.upper_bound(self.A, start_A, end_A, self.B[middle_B])

        in_A, in_B = middle_A - start_A + 1, middle_B - start_B + 1
        if in_A + in_B >= nth:
            return self.find(nth, start_A, middle_A, start_B, middle_B)
        else:
            return self.find(nth - in_A - in_B, middle_A + 1, end_A, middle_B + 1, end_B)

    def findMedianSortedArrays(self, A, B):
        len_A, len_B = len(A), len(B)
        self.A, self.B = A, B
        total = len_A + len_B
        if total % 2:
            return self.find(total / 2 + 1, 0, len_A - 1, 0, len_B - 1)
        else:
            return (self.find(total / 2, 0, len_A - 1, 0, len_B - 1) + self.find(total / 2 + 1, 0, len_A - 1, 0, len_B - 1)) / 2.0

print Solution().findMedianSortedArrays([3, 4], [1, 2, 5, 6])
print Solution().findMedianSortedArrays([1, 1, 10], [1, 2, 3, 4])
print Solution().findMedianSortedArrays([1, 1], [2, 3])
print Solution().findMedianSortedArrays([2, 3], [1, 1])
print Solution().findMedianSortedArrays([], [2, 3])
print Solution().findMedianSortedArrays([1], [2, 3])
