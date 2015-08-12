#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.

class Solution:
    # @param A, a list of integers
    # @param target, an integer to be searched
    # @return an integer
  def search(self, A, target):
    left = 0
    right = len(A) - 1
    while left <= right:
      middle = left + (right - left) / 2
      if target == A[middle]:
        return middle
      if A[left] <= A[middle]:
        if target >= A[left] and target < A[middle]:
          right = middle - 1
        else:
          left = middle + 1
      else:
        if target > A[middle] and target <= A[right]:
          left = middle + 1
        else:
          right = middle - 1
    return -1

t = Solution()
print t.search([4,5,1,2,3], 1)
