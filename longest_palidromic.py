#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @return a string
    def longestPalindrome(self, s):
        ans = ""
        if not s:
            return ans
        ans_start, ans_end = 0, 0
        len_s = len(s)
        cache = [[False] * len_s for i in range(len_s)]
        for i in range(len_s):
            cache[i][i] = True
        for l in range(2, len_s + 1):
            for start in range(0, len_s - l):
                end = start + l - 1
                if s[start] != s[end]:
                    continue
                if l > 2:
                    cache[start][end] = cache[start + 1][end - 1]
                else:
                    cache[start][end] = True
                if cache[start][end]:
                    ans_start, ans_end = start, end
        return s[ans_start: ans_end + 1]

print Solution().longestPalindrome("a" * 1000)
