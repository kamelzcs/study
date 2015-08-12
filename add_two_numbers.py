#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.

import re

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
  # @return a ListNode
  def addTwoNumbers(self, l1, l2):
    def reverse(root):
      head = None
      current = root
      while current:
        cached_next = current.next
        current.next = head
        head = current
        current = cached_next
      return head

    l1 = reverse(l1)
    l2 = reverse(l2)
    carry = 0
    ans = tail = ListNode(-1)
    while l1 or l2 or carry:
      first = l1.val if l1 else 0
      second = l2.val if l2 else 0
      value = (first + second + carry) % 10
      carry = (first + second + carry) / 10
      tail.next = ListNode(value)
      tail = tail.next
      if l1:
        l1 = l1.next
      if l2:
        l2 = l2.next
    return ans.next

  def longestConsecutive(self, num):
    cached = {}
    ans = 0
    for element in num:
      if element in cached:
        continue
      cached[element] = element
      right = cached.get(element + 1, element)
      left = cached.get(element - 1, element)
      cached[left] = right
      cached[right] = left
      ans = max(right - left + 1, ans)

    return ans

  def sqrt(self, x):
    if x <= 0:
      return x
    left, right = 1, x
    while left <= right:
      middle = left + (right - left) / 2
      if x / middle >= middle:
        left = middle + 1
      else:
        right = middle - 1
    return left - 1

  def pow(self, x, n):
    if n == 0:
      return 1

    is_negative = False
    if n < 0:
      n = -n
      is_negative = True

    if n & 1:
      ans = x
    else:
      ans = 1.0
    current = 2
    base = x
    while current <= n:
      base = base * base
      if current & n:
        ans = ans * base
      current = current * 2
    return 1.0 / ans if is_negative else ans

  def uniquePaths(self, m, n):
    def combination(n, m):
      if m > n / 2:
        m = n - m
      ans = 1
      for index in range(1, m + 1):
        ans = ans * n
        n = n - 1
        ans = ans / index
      return ans
    if m <= 0 or n <= 0:
      return 0
    return combination(m + n - 2, n - 1)

  def isValid(self, s):
    stack = []
    parent = {"}": "{",
              ")": "(",
              "]": "["}
    for element in s:
      if element in ["{", "(", "["]:
        stack.append(element)
      else:
        if not stack:
          return False
        if stack[-1] is not parent[element]:
          return False
        else:
          stack.pop()
    if not stack:
      return True
    else:
      return False

  def isPalindrome(self, s):
    if not s:
      return True
    s = re.sub(r'\W+', '', s)
    s = s.lower()
    for index in xrange(0, len(s) / 2):
      if s[index] != s[len(s) - 1 - index]:
        return False
    return True

t = Solution()
print t.isPalindrome("A man, a plan, a canal: Panama")
