#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.

from collections import deque


class LRUCache:

    # @param capacity, an integer
    def __init__(self, capacity):
      self.lru_dict = {}
      self.capacity = capacity
      self.lru = deque()

    # @return an integer
    def get(self, key):
      if key in self.lru_dict:
        return self.

    # @param key, an integer
    # @param value, an integer
    # @return nothing
    def set(self, key, value):
