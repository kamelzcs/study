#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.


class solution:
  def removeElement(self, A, elem):
    ans = 0
    for element in A:
      if elem != element:
        A[ans] = element
        ans = ans + 1
    return ans

t = solution()
print t.removeElement([1,2,2,4,2,2], 2)
