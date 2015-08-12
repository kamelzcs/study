#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.

from __future__ import print_function
T = input()
for loop in range(1, T + 1):
  print("Case #%s: " % (loop), end='')
  first = []
  first_row = input()
  for i in range(4):
    first.append(map(int, raw_input().split()))
  second = []
  second_row = input()
  for i in range(4):
    second.append(map(int, raw_input().split()))
  common = set.intersection(set(first[first_row - 1]), set(second[second_row - 1]))
  if not common:
    print("Volunteer cheated!")
  elif len(common) > 1:
    print("Bad magician!")
  else:
    print(iter(common).next())
