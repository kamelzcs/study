#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.

import string


class Solution:
    # @return a string
    def convertToTitle(self, num):
        ans = ""
        keys = [i for i in range(26)]
        values = string.uppercase[:26]
        dic = dict([item for item in zip(keys, values)])
        while num:
            num -= 1
            ans = str(dic[num % 26]) + ans
            num /= 26
        return ans

print Solution().convertToTitle(27)
print Solution().convertToTitle(26)
print Solution().convertToTitle(28)
