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
    right = len(target) - 1
    while left <= right:
      middle = left + (right - left)/2
      if target == A[middle]:
        return middle
      if (A[left] - target) * (A[middle] - target) > 0:
        left = middle
      else:
        right = middle
