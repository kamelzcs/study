#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 zhao
import sys


class RandomListNode:
  def __init__(self, x):
    self.label = x
    self.next = None
    self.random = None


class Solution:
  # @param head, a RandomListNode
  # @return a RandomListNode
  def copyRandomList(self, head):
    if head is None:
      return None
    mixed = RandomListNode(-1)
    current, prev = head, mixed
    while current:
      new_node = RandomListNode(current.label)
      new_node.random = current.random
      current.random = new_node
      prev.next = new_node
      prev = new_node
      current = current.next
    mixed = mixed.next

    ans = RandomListNode(-1)
    current, prev = mixed, ans
    while current:
      new_node = RandomListNode(current.label)
      cached = current.next
      current.next = new_node
      prev.next = new_node
      prev = new_node
      current = cached
    ans = ans.next

    current = head
    while current:
      current.random.next.random = \
        current.random.random.random.next if current.random.random else None
      current = current.next

    current = head
    while current:
      current.random = current.random.random
      current = current.next
    return ans
