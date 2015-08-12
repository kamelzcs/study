#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.
import sys


class Solution:
  # @param triangle, a list of lists of integers
  # @return an integer
  def minimumTotal(self, triangle):
    if triangle is None:
      return None
    pre = []
    now = [0]
    for row in triangle:
      pre = now
      now = []
      for index in range(0, len(row)):
        min_value = 100100100
        if index < len(pre):
          min_value = pre[index]
        if index - 1 >= 0:
          min_value = min(min_value, pre[index - 1])
        now.append(min_value + row[index])
    return min(now)

  def searchInsert(self, A, target):
    A.append(sys.maxint)
    left = 0
    right = len(A) - 1
    while left <= right:
      middle = left + (right - left) / 2
      if A[middle] < target:
        left = middle + 1
      else:
        right = middle - 1
    return left

  def searchRange(self, A, target):
    A.append(200000000)
    left = 0
    right = len(A) - 1
    while left <= right:
      middle = left + (right - left) / 2
      if A[middle] < target:
        left = middle + 1
      else:
        right = middle - 1
    if A[left] != target:
      return [-1, -1]

    first_index = left

    left = 0
    right = len(A) - 1
    while left <= right:
      middle = left + (right - left) / 2
      if A[middle] <= target:
        left = middle + 1
      else:
        right = middle - 1

    second_index = left - 1
    return [first_index, second_index]

  def searchMatrix(self, matrix, target):
    matrix.append([200000000])
    rows = len(matrix)
    left = 0
    right = rows - 1
    while left <= right:
      middle = left + (right - left) / 2
      if matrix[middle][-1] < target:
        left = middle + 1
      else:
        right = middle - 1

    if left >= rows - 1:
      return False
    target_row = matrix[left]
    left = 0
    right = len(target_row) - 1
    while left <= right:
      middle = left + (right - left) / 2
      if target_row[middle] < target:
        left = middle + 1
      elif target_row[middle] > target:
        right = middle - 1
      else:
        return True
    return False

t = Solution()
print t.searchMatrix([
  [1, 3, 5, 7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
], 0)
