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
  def match(self, indexS, indexP):
    if indexS >= self.lenS and indexP >= self.lenP:
      return True
    if indexS >= self.lenS or indexP >= self.lenP:
      return False
    #if (indexS, indexP) in self.cache:
      #return True
    if self.s[indexS] == self.p[indexP]:
      return self.match(indexS + 1, indexP + 1)
    elif self.p[indexP] == '?':
      return self.match(indexS + 1, indexP + 1)
    elif self.p[indexP] == '*':
      if indexP + 1 >= self.lenP:
        return True
      for i in xrange(indexS, self.lenS):
        temp = self.match(i, indexP + 1)
        if temp:
          #self.cache.add((i, indexP + 1))
          return True
      return False
    else:
      return False

  def removeDupliStar(self, s):
    ans = ""
    for item in s:
      if item == '*':
        if ans and ans[-1] == '*':
          continue
      ans += item
    return ans

  def isMatch(self, s, p):
    self.cache = set()
    if not (s or p):
      return True
    if not (s and p):
      return False
    p = self.removeDupliStar(p)
    self.s = s
    self.lenS = len(s)
    self.p = p
    self.lenP = len(p)
    return self.match(0, 0)

print Solution().isMatch("aa", "a")
print Solution().isMatch("babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb", "b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a")
