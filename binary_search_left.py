#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


def search(A, target):
  left = 0
  right = len(A) - 1
  while left <= right:
    middle = left + (right - left) / 2
    if A[middle] <= target:
      left = middle + 1
    else:
      right = middle - 1
  return right

print search([1,2,2,3,3,3,4], 2)
