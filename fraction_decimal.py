#! /usr/bin/env python
# -*- coding: utf-8 -*-

class Solution:
    # @return a string
    def fractionToDecimal(self, numerator, denominator):
      ans = ""
      if numerator * denominator < 0:
        ans += "-"
      numerator, denominator = abs(numerator), abs(denominator)
      ans += str(numerator / denominator)
      remain = numerator % denominator
      if remain:
        ans += "."
      cache = {}
      while remain:
        remain *= 10
        if remain in cache:
          return "%s(%s)" % (ans[:cache[remain]], ans[cache[remain]:])
        cache[remain] = len(ans)
        ans += str(remain / denominator)
        remain = remain % denominator
      return ans

print Solution().fractionToDecimal(1, 2)
print Solution().fractionToDecimal(1, 3)
