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


class Solution:
  # @param preorder, a list of integers
  # @param inorder, a list of integers
  # @return a tree node
  def buildTree(self, inorder, postorder):
    def buildTree(inorder, postorder):
      if not inorder or not postorder:
        return None
      last_elment = postorder[-1]
      node = TreeNode(last_elment)
      inorder_index = inorder.index(last_elment)
      left_len = inorder_index
      right_len = len(inorder) - 1 - inorder_index
      node.left = buildTree(inorder[:left_len], postorder[:left_len])
      node.right = buildTree(inorder[-right_len:], postorder[-right_len - 1: -1])
      return node
    return buildTree(inorder, postorder)

  def zigzagLevelOrder(self, root):
    ans, temp = [], []
    if not root:
      return ans
    queue = [root]
    from_left, current_last, next_last = 1, root, None
    while queue:
      top = queue.pop(0)
      temp.append(top.val)
      if top.left:
        queue.append(top.left)
        next_last = top.left
      if top.right:
        queue.append(top.right)
        next_last = top.right
      if top == current_last:
        if not from_left:
          ans.append(temp[::-1])
        else:
          ans.append(temp)
        temp = []
        current_last = next_last
        from_left = (from_left + 1) % 2
    return ans

  def numDistinct(self, S, T):
    S = "$" + S
    T = "$" + T
    dp = [[0] * len(T) for i in xrange(len(S))]
    for i in xrange(len(S)):
      dp[i][0] = 1
    for first in xrange(1, len(S)):
      for second in xrange(1, len(T)):
        dp[first][second] += dp[first - 1][second]
        if S[first] == T[second]:
          dp[first][second] += dp[first - 1][second - 1]
    return dp[len(S) - 1][len(T) - 1]

  def matched(self, first, second):
    if first == "(" and second == ")":
      return True
    return False

  def longestValidParentheses2(self, s):
    if not s:
      return 0
    cached = [[0] * len(s) for i in xrange(len(s))]
    for current_len in xrange(2, len(s) + 1):
      for start in xrange(len(s) - current_len + 1):
        matched = start + current_len - 1
        temp = 0
        temp = max(cached[start - 1][matched], cached[start][matched - 1])
        for next_index in xrange(start + 1, matched):
          if self.matched(s[start], s[next_index - 1]) or self.matched(s[next_index], s[matched]):
            temp = max(temp, cached[start][next_index - 1] + cached[next_index][matched])
        if self.matched(s[start], s[matched]):
          temp = max(temp, 2 + cached[start + 1][matched - 1] if current_len > 2 else 2)
        cached[start][matched] = temp
    return cached[0][len(s) - 1]

  def longestValidParentheses(self, s):
    s = ")" + s + "("
    stack, ans = [], 0
    for index in xrange(len(s)):
      element = s[index]
      if element == ")" and stack and stack[-1][1] == "(":
        stack.pop()
        ans = max(ans, index - stack[-1][0])
      else:
        stack.append((index, element))
    return ans

  def generate_list(self, left, right):
    if left >= right:
      return [None]
    ans = []
    for element in xrange(left, right):
      left_array = self.generate_list(left, element)
      right_array = self.generate_list(element + 1, right)
      for left_node in left_array:
        for right_node in right_array:
          root = TreeNode(element)
          root.left = left_node
          root.right = right_node
          ans.append(root)
    return ans

  def generateTrees(self, n):
    return self.generate_list(1, n + 1)

  def maxSubArray(self, A):
    ans = A[0]
    for index in xrange(1, len(A)):
      if A[index - 1] > 0:
        A[index] += A[index - 1]
      ans = max(ans, A[index])
    return ans

t = Solution()
print t.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4])
