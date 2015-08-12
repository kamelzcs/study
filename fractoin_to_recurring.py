#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @return a string
    def fractionToDecimal(self, numerator, denominator):
        ans = ""
        dic = {}
        if numerator * denominator < 0:
            ans += "-"
        if numerator < 0:
            numerator *= -1
        if denominator < 0:
            denominator *= -1

        dic[numerator] = len(ans)
        ans += str(numerator / denominator)
        numerator = (numerator % denominator) * 10
        if numerator:
            ans += "."
        while numerator:
          if numerator in dic:
            first, second = ans[:dic[numerator]], ans[dic[numerator]:]
            ans = "%s(%s)" % (first, second)
            break
          dic[numerator] = len(ans)
          ans += str(numerator / denominator)
          numerator = (numerator % denominator) * 10
        return ans

print Solution().fractionToDecimal(1, 2)
print Solution().fractionToDecimal(2, 2)
print Solution().fractionToDecimal(5, 3)
print Solution().fractionToDecimal(0, 3)
print Solution().fractionToDecimal(-50, 8)
print Solution().fractionToDecimal(-50, -8)
print Solution().fractionToDecimal(50, -8)
