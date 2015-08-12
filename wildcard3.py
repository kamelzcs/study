#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
  # @param s, an input string
  # @param p, a pattern string
  # @return a boolean
  def removeDupliStar(self, s):
    ans = ""
    for item in s:
      if item == '*':
        if ans and ans[-1] == '*':
          continue
      ans += item
    return ans

  def isMatch(self, s, p):
    p = self.removeDupliStar(p)
    if not s:
      if not p or p == "*":
        return True
      else:
        return False
    elif not p:
      return False
    p = "!" + p
    s = "!" + s
    len_s, len_p = len(s), len(p)
    if len_p - p.count('*') > len_s:
      return False
    back_up = [True] + [False] * (len_s - 1)
    for index in xrange(1, len_p):
      current = [False] * len_s
      if p[index] == '*':
        least = 0
        while least < len_s:
          if back_up[least]:
            break
          least += 1
        for y in xrange(least, len_s):
          current[y] = True
      else:
        for y in xrange(1, len_s):
          if p[index] == '?':
            current[y] = back_up[y - 1]
          else:
            current[y] = back_up[y - 1] and p[index] == s[y]
      back_up, current = current, back_up

    return back_up[len_s - 1]

print Solution().isMatch("a", "a*")
