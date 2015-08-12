#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @param num, a list of integer
    # @return an integer
    def find(self, left, right):
        while left < right:
            middle = left + (right - left) / 2
            if self.num[middle] < self.num[middle + 1]:
                left = middle + 1
            else:
                right = middle
        return left

    def findPeakElement(self, num):
        self.num = num
        return self.find(0, len(num) - 1)

print Solution().findPeakElement([1])
