#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @param n, an integer
    # @return an integer
    def reverseBits(self, n):
        ans = 0
        for index in range(32):
            if (1 << index) & n:
                ans |= (1 << (31 - index))
        return ans

print Solution().reverseBits(0)
