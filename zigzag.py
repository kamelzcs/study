#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.


class Solution:
    # @return a string
    def pre_convert(self, s, nRows):
        if not s:
            return ""
        if nRows == 1:
            return s
        rows = ["" for i in range(nRows)]
        rows[0] += s[0]
        index = 1
        lent_s = len(s)
        next_column = 1
        while True:
            if index >= lent_s:
                break
            while True:
                rows[next_column] += s[index]
                index += 1
                if index >= lent_s:
                    break
                if next_column >= nRows - 1:
                    next_column -= 1
                    break
                next_column += 1
            if index >= lent_s:
                break
            while True:
                rows[next_column] += s[index]
                index += 1
                if index >= lent_s:
                    break
                if next_column <= 0:
                    next_column = 1
                    break
                next_column -= 1
        return ''.join(rows)

    def convert(self, s, nRows):
        if nRows == 1:
            return s
        rows = ["" for i in range(nRows)]
        step, col = 1, 0
        for item in s:
            rows[col] += item
            col += step
            if col == 0 or col == nRows - 1:
                step *= -1
        return ''.join(rows)

print Solution().convert("PAYPALISHIRING", 3)
