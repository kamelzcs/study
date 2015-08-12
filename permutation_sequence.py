#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @return a string
    def intGetPermutation(self, n, k):
        if k == 1:
            return [i + 1 for i in range(n)]
        index, base = 1, 1
        while index < n:
            base *= index
            index += 1

        start = (k - 1) / base + 1
        left = k - (start - 1) * base
        part = self.intGetPermutation(n - 1, left)
        return [start] + [item + 1 if item >= start else item for item in part]

    def getPermutation(self, n, k):
        return ''.join(map(str, self.intGetPermutation(n, k)))

print [Solution().getPermutation(3, i + 1) for i in range(6)]
