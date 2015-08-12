#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


class TreeNode:
  def __init__(self, x):
    self.val = x
    self.left = None
    self.right = None
    self.next = None


class Solution:
  # @param root, a tree node
  # @return nothing
  def connect2(self, root):
    head, current = root, None
    while head:
      current = head
      if not current.left:
        return
      while current:
        current.left.next = current.right
        if current.next:
          current.right.next = current.next.left
        current = current.next
      head = head.left

  def connect(self, root):
    def get_next(head, from_left):
      if head is None:
        return None
      if from_left:
        if head.left:
          return head.left
        if head.right:
          return head.right
      else:
        if head.right:
          return head.right
      return get_next(head.next, from_left=True)

    head, current = root, None
    while head:
      current = head
      while current:
        if current.left:
          current.left.next = get_next(current, from_left=False)
        if current.right:
          current.right.next = get_next(current.next, from_left=True)
        current = current.next
      head = get_next(head, from_left=True)

  def uniquePathsWithObstacles(self, obstacleGrid):
    if obstacleGrid is None:
      return 0
    m, n = len(obstacleGrid), len(obstacleGrid[0])
    cached = [[-1] * n for i in xrange(0, m)]
    if obstacleGrid[m - 1][n - 1] == 1:
      cached[m - 1][n - 1] = 0
    else:
      cached[m - 1][n - 1] = 1

    def calculate(x, y):
      if cached[x][y] != -1:
        return cached[x][y]
      ans = 0
      if obstacleGrid[x][y] == 1:
        return ans
      if y + 1 < n:
        ans += calculate(x, y + 1)
      if x + 1 < m:
        ans += calculate(x + 1, y)
      cached[x][y] = ans
      return ans

    return calculate(0, 0)

  def get_maximum_area(self, height_array):
    height_array.append(0)
    stack, ans = [(-1, -1)], 0
    for index in xrange(0, len(height_array)):
      element = height_array[index]
      while element <= stack[-1][1]:
        width = index - stack[-2][0] - 1
        ans = max(ans, width * stack[-1][1])
        stack.pop()
      stack.append((index, element))
    return ans

  def maximalRectangle(self, matrix):
    if not matrix:
      return 0
    m, n = len(matrix), len(matrix[0])
    above_sum = [[0] * n for i in xrange(0, m)]
    for row in xrange(0, m):
      for col in xrange(0, n):
        if matrix[row][col] == "1":
          above_sum[row][col] = above_sum[row - 1][col] + 1 if row else 1
        else:
          above_sum[row][col] = 0
    ans = 0
    for row in xrange(0, m):
      ans = max(ans, self.get_maximum_area(above_sum[row]))
    return ans

t = Solution()
print t.maximalRectangle([
  "11",
])
