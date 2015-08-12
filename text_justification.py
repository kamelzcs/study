#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.

class Solution:
    # @param words, a list of strings
    # @param L, an integer
    # @return a list of strings
    def justify(self, words, L, wordsNum, wordsLen):
      if wordsLen + wordsNum - 1 <= L:
        return [' '.join(words) + (' ' * (L - wordsLen - wordsNum + 1))]
      temp = 0
      for toUse in xrange(wordsNum):
        currentLen = len(words[toUse])
        if temp + toUse + currentLen > L:
          break
        else:
          temp += currentLen

      remain = L - temp
      line = words[0]
      left = toUse - 1
      for index in xrange(1, toUse):
        base = remain / left
        line += ' ' * base
        if remain % left:
          line += ' '
          remain -= 1
        line += words[index]
        remain -= base
        left -= 1

      if remain:
        line += ' ' * remain

      return [line] + self.justify(words[toUse:], L, wordsNum - toUse, wordsLen - temp)

    def fullJustify(self, words, L):
      wordsNum, wordsLen = 0, 0
      for item in words:
        wordsNum += 1
        wordsLen += len(item)
      return self.justify(words, L, wordsNum, wordsLen)

print Solution().fullJustify(["What","must","be","shall","be."], 12)
