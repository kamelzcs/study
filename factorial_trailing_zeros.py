#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @return an integer
    def calc(self, n, denomi):
      if not n:
        return 0
      return self.calc(n / denomi, denomi) + n / denomi

    def trailingZeroes(self, n):
        fives, twos = 0, 0
        fives = self.calc(n, 5)
        twos = self.calc(n, 2)
        return min(fives, twos)

print Solution().trailingZeroes(12)
