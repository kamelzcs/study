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
    def buildTree(self, preorder, inorder):
      def buildTree(preorder, inorder):
        if not preorder or not inorder:
          return None
        first_element = preorder[0]
        second_index = inorder.index(first_element)
        node = TreeNode(first_element)
        node.left = buildTree(preorder[1: 1 + second_index], inorder[:second_index])
        right_len = len(preorder) - second_index - 1
        node.right = buildTree(preorder[-right_len:], inorder[-right_len:]) if right_len > 0 else None
        return node
      return buildTree(preorder, inorder)

t = Solution()
print t.buildTree([-1], [-1])
