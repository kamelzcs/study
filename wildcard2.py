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
  def quesionMatch(self, start, index):
    l, s = self.lst[index]
    if l > self.lenS - start:
      return False
    for index in xrange(start, start + l):
      if s[index - start] == '?':
        continue
      if s[index - start] != self.s[index]:
        return False
    return True

  def match(self, indexS, indexP):
    if indexS >= self.lenS and indexP >= self.lenLst:
      return True

    if indexS >= self.lenS or indexP >= self.lenLst:
      return True

    for index in xrange(indexS, self.lenS):
      if self.quesionMatch(index, indexP):
        return self.match(index + self.lst[indexP][0], indexP + 1)
    return False

  def removeDupliStar(self, s):
    ans = ""
    for item in s:
      if item == '*':
        if ans and ans[-1] == '*':
          continue
      ans += item
    return ans

  def normal_match(self, s, t):
    if len(s) != len(t):
      return False
    for index in xrange(len(s)):
      if t[index] == '?':
        continue
      elif s[index] == t[index]:
        continue
      else:
        return False
    return True

  def isMatch(self, s, p):
    self.cache = set()
    if not (s or p):
      return True
    if not (s and p):
      return False
    if '*' not in p:
      return self.normal_match(s, p)
    p = self.removeDupliStar(p)
    if s[0] == '*':
      s = s[::-1]
      p = p[::-1]
    self.s = s
    self.lenS = len(s)
    self.lst = [(len(x), x) for x in p.split('*')]
    self.lenLst = len(self.lst)
    return self.match(0, 0)

print Solution().isMatch("aa", "aa")
print Solution().isMatch("aa", "*")
