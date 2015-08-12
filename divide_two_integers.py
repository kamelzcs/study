#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


class Solution:
  def divide(self, dividend, divisor):
    def get_bit(dividend, divisor):
      ans = 0
      while (divisor << ans) <= dividend:
        ans += 1
      return ans - 1

    multiply = 1
    if dividend < 0:
      multiply *= -1
      dividend *= -1
    if divisor < 0:
      multiply *= -1
      divisor *= -1

    ans = 0
    while dividend >= divisor:
      temp = get_bit(dividend, divisor)
      ans |= (1 << temp)
      dividend -= (divisor << temp)
    return ans * multiply

t = Solution()
print t.divide(17, -18)
