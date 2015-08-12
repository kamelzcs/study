#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


class Solution:
  def merge(self, A, m, B, n):
    last_index = m + n - 1
    index_A = m - 1
    index_B = n - 1
    while last_index >= 0:
      if index_A >= 0 and index_B >= 0:
        if A[index_A] > B[index_B]:
          A[last_index] = A[index_A]
          index_A = index_A - 1
        else:
          A[last_index] = B[index_B]
          index_B = index_B - 1
      else:
        if index_A < 0:
          A[last_index] = B[index_B]
          index_B = index_B - 1
        else:
          A[last_index] = A[index_A]
          index_A = index_A - 1
      last_index = last_index - 1
    return A
