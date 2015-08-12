#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @return an integer
    def lengthOfLongestSubstring(self, s):
        left, cached, ans = 0, set(), 0
        if not s:
            return ans
        len_s = len(s)
        for right in xrange(len_s):
            if s[right] in cached:
                while True:
                    cached.remove(s[left])
                    left += 1
                    if s[left - 1] == s[right]:
                        break
            cached.add(s[right])
            if right - left + 1 > ans:
                ans = right - left + 1
        return ans

print Solution().lengthOfLongestSubstring("aabcc")
