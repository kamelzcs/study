#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


class Solution:
  # @param root, a tree node
  # @param sum, an integer
  # @return a list of lists of integers
  def pathSum(self, root, sum):
    def pathSum(root, sum, sum_list, ans):
      if not root.left and not root.right:
        if sum == root.val:
          ans.append(sum_list + [root.val])
        return
      if root.left:
        pathSum(root.left, sum - root.val, sum_list + [root.val], ans)
      if root.right:
        pathSum(root.right, sum - root.val, sum_list + [root.val], ans)

    if not root:
      return []
    ans = []
    sum_list = []
    pathSum(root, sum, sum_list, ans)
    return ans
