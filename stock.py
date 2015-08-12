#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 zhao


class Solution:
  # @param prices, a list of integer
  # @return an integer
  def maxProfit(self, prices):
    if not prices or len(prices) < 2:
      return 0
    profit_from_start = [0]
    min_value = prices[0]
    for element in prices:
      min_value = min(min_value, element)
      profit_from_start.append(max(profit_from_start[-1], element - min_value))
    profit_from_start.pop(0)
    profile_from_end = [0]
    max_value = prices[-1]
    for element in reversed(prices):
      max_value = max(max_value, element)
      profile_from_end.append(max(profile_from_end[-1], max_value - element))
    profile_from_end.reverse()
    profile_from_end.pop()
    ans = profit_from_start[-1]
    for index in xrange(len(prices) - 1):
      ans = max(ans, profit_from_start[index] + profile_from_end[index + 1])
    return ans

  def is_pali(self, s):
    if len(s) <= 1:
      return True
    for index in xrange(len(s) / 2 + 1):
      if s[index] != s[-1 - index]:
        return False
    return True

  def partition(self, s):
    if not s:
      return []
    ans = []
    for index in xrange(1, len(s)):
      if self.is_pali(s[index:]):
        temp = self.partition(s[:index])
        for element in temp:
          ans.append(element + [s[index:]])
    if self.is_pali(s):
      ans.append([s])
    return ans
t = Solution()
print t.partition("aab")
