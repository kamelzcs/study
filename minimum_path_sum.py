#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


class Solution:
  def minPathSum(self, grid):
    if not grid:
      return -1

    def calculate(row, column):
      if dp[row][column] != 100000000:
        return dp[row][column]
      if row - 1 >= 0:
        dp[row][column] = min(dp[row][column], calculate(row - 1, column) + grid[row][column])
      if column - 1 >= 0:
        dp[row][column] = min(dp[row][column], calculate(row, column - 1) + grid[row][column])
      return dp[row][column]

    row_num = len(grid)
    column_num = len(grid[0])
    dp = [[100000000] * column_num for i in xrange(0, row_num)]
    dp[0][0] = grid[0][0]
    calculate(row_num - 1, column_num - 1)
    return dp[row_num - 1][column_num - 1]

t = Solution()
t.minPathSum([[1,2],[1,2]])
