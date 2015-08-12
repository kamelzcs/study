#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 zhao


class TreeNode:
  def __init__(self, x):
    self.val = x
    self.left = None
    self.right = None


class Solution:
  # @param root, a tree node
  # @return a tree node
  def recoverTree(self, root):
    INF = 1000000
    left_valid = self.check(root.left, -INF, root.val) if root.left else True
    right_valid = self.check(root.right, root.val, INF) if root.right else True
    if left_valid == False and right_valid == False:
