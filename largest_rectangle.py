#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.

import sys

class NodeElement:
  def __init__(self, index, height):
    self.index = index
    self.height = height

class Solution:
  # @param height, a list of integer
  # @return an integer
  def largestRectangleArea(self, height):
    def get_largest_area(arrays, tempArray):
        stack = []
        stack.append(NodeElement(-1, -1))
        ans = 0
        for i in xrange(0, len(arrays)):
            data = arrays[i]
            while stack[-1].height >= data:
                stack.pop()
            tempArray.append((i - stack[-1].index) * data)
            stack.append(NodeElement(i, data))
        return ans
    leftArray = []
    rightArray = []
    get_largest_area(height, leftArray)
    get_largest_area(height[::-1], rightArray)
    ans = 0
    for i in xrange(0, len(height)):
      ans = max(ans, leftArray[i] + rightArray[len(height) -1  - i] -height[i])
    return ans

  # @param root, a tree node
  # @return a list of integers
  def inorderTraversal(self, root):
    stack = []
    ans = []
    if root is None:
      return ans
    current = root.left
    stack.append(root)
    while stack or current:
      if current is None:
        top = stack.pop()
        ans.append(top.val)
        if top.right:
          current = top.right.left
          stack.append(top.right)
      else:
        stack.append(current)
        current = current.left

    return ans

  def isValidBST(self, root):
    def isValidBST(root, min_value, max_value):
      if root is None:
        return True
      if root.val < min_value or root.val >= max_value:
        return False
      return isValidBST(root.left, min_value, root.val) and isValidBST(root.right, root.val+1, max_value)
    max_value = sys.maxint
    min_value = -max_value-1
    return isValidBST(root, min_value, max_value)

  def subsets(self, S):
    ans = []
    total_len = len(S)
    for i in xrange(0, (1<<total_len)):
      temp = []
      for j in xrange(0, total_len):
        if i&(1<<j):
          temp.append(S[j])
      temp.sort()
      ans.append(temp)
    return ans

  # @param A, a list of integers
  # @param target, an integer to be searched
  # @return an integer
  def search(self, A, target):
    left = 0
    right = len(target) - 1
    while left <= right:
      middle = left + (right - left)/2


height = [2,1,2,1]
t = Solution()
print t.isValidBST(height)
