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

    def is_straight(self, left, right):
        middle = (left + right) / 2
        if self.num[right] > self.num[middle] > self.num[left]:
            return True

        if self.num[right] < self.num[middle] < self.num[left]:
            return True

        if self.num[left] == self.num[right]:
            for index in range(left + 1, right):
                if self.num[index] != self.num[left]:
                    return False
            return True
        else:
            return False

    def find_from_index(self, left, right):
        if left > right:
            return
        self.ans = min(self.ans, min(self.num[left], self.num[right]))
        middle = (left + right) / 2
        self.ans = min(self.ans, self.num[middle])
        if self.is_straight(left, middle):
            self.find_from_index(middle + 1, right)
        else:
            self.find_from_index(left, middle - 1)

    def findMin(self, num):
        self.num = num
        if not num:
            return num
        len_num = len(num)
        if len_num <= 1:
            return num[0]
        self.ans = num[0]
        left, right = 0, len_num - 1
        self.find_from_index(left, right)
        return self.ans

print Solution().findMin([4, 5, 6, 7, 0, 1, 2])
print Solution().findMin([2, 2, 1, 2, 2, 2, 2])
print Solution().findMin([2, 0, 1, 1, 1])

print Solution().findMin([1,2,2,2,0,1,1])
