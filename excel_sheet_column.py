#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @param s, a string
    # @return an integer
    def titleToNumber(self, s):
        if not s:
            return 0
        return 26 * self.titleToNumber(s[: -1]) + ord(s[-1]) - ord('A') + 1

print Solution().titleToNumber("AC")
print Solution().titleToNumber("Z")
