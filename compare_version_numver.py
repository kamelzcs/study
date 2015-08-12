#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.

import re


class Solution:
    # @param version1, a string
    # @param version2, a string
    # @return an integer
    def compareVersion(self, version1, version2):
        if not version1 or not version2:
            reg = re.compile('^[0\.]+$')
            if not version1:
                if not version2:
                    return 0
                else:
                    if reg.match(version2):
                        return 0
                    return -1
            else:
                if reg.match(version1):
                    return 0
                return 1
        index1, index2 = version1.find('.'), version2.find('.')
        if index1 >= 0:
            num1 = int(version1[:index1])
        else:
            num1 = int(version1)
        if index2 >= 0:
            num2 = int(version2[:index2])
        else:
            num2 = int(version2)
        if num1 > num2:
            return 1
        elif num1 < num2:
            return -1
        else:
            if index1 < 0:
                version1 = ""
            else:
                version1 = version1[index1 + 1:]
            if index2 < 0:
                version2 = ""
            else:
                version2 = version2[index2 + 1:]
        return self.compareVersion(version1, version2)

print Solution().compareVersion("1.0", "1.1")
print Solution().compareVersion("1.0", "1")
print Solution().compareVersion("1.0.0.0", "1")
