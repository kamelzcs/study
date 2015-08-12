#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


class Solution():
  def addBinary(self, a, b):
    def addBinary(x, y, carry):
      bit = x ^ y ^ carry
      carry = (x + y + carry) // 2
      return bit, carry
    a = a[::-1]
    b = b[::-1]
    if len(b) > len(a):
      a, b = b, a
    ans = ""
    carry = 0
    for index in xrange(0, len(a)):
      bit, carry = addBinary(int(a[index], 2) if index < len(a) else 0, int(b[index], 2) if index < len(b) else 0, carry)
      ans += str(bit)
    if carry == 1:
      ans += "1"
    return ans[::-1]

t = Solution()
print t.addBinary("0", "0")
