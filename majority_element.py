#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @param num, a list of integers
    # @return an integer

    def majorityElement(self, num):
        major, count = num[0], 0
        for item in num:
            if not count:
                major = item
                count = 1
            else:
                if item != major:
                    count -= 1
                else:
                    count += 1
        return major

print Solution().majorityElement([1, 1, 1, 2, 3, 1, 4])
print Solution().majorityElement([1])
