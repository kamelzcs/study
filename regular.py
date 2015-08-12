#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @return a boolean
    def isMatch(self, s, p):
        s = "!" + s
        p = "!" + p
        len_s, len_p = len(s), len(p)
        dp = [[False] * len_s for i in range(len_p)]
        dp[0][0] = True
        for i in xrange(1, len_p):
            for j in xrange(len_s):
                if p[i] == '.' and j:
                    dp[i][j] = dp[i - 1][j - 1]
                elif p[i] == '*':
                    if i == 1:
                        return False
                    # zero
                    dp[i][j] = dp[i - 2][j]
                    #one
                    dp[i][j] |= dp[i - 1][j]
                    #more
                    if j and ((s[j] == s[j - 1] and p[i - 1] == s[j - 1]) or p[i - 1] == '.'):
                        dp[i][j] |= dp[i][j - 1]
                else:
                    if j and p[i] == s[j]:
                        dp[i][j] = dp[i - 1][j - 1]
        return dp[len_p - 1][len_s - 1]
