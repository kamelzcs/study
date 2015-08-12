#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-Desktop>
#
# Distributed under terms of the MIT license.

from collections import deque
import string


class Solution:
    # @param start, a string
    # @param end, a string
    # @param dict, a set of string
    # @return an integer
    def buildPath(self, end, start):
        if end == start:
            return [[start]]
        return [x + [end] for y in self.track[end] for x in self.buildPath(y, start)]

    def findLadders(self, start, end, dict):
        self.wordHash = {}
        self.intHash = {}
        self.total = 0
        self.length = len(start)
        dict.add(start)
        dict.add(end)
        for item in dict:
            self.wordHash[self.total] = item
            self.intHash[item] = self.total
            self.total += 1
        startIndex = self.intHash[start]
        endIndex = self.intHash[end]

        self.reachable = [set([]) for x in range(self.total)]
        self.track = [set([]) for x in range(self.total)]
        for x in xrange(self.total):
            base = self.wordHash[x]
            for index in xrange(self.length):
                pre = base[:index]
                back = base[index + 1:]
                current = base[index]
                for single in string.lowercase:
                    if single == current:
                        continue
                    nxt = pre + single + back
                    if nxt not in self.intHash:
                        continue
                    nxtIndex = self.intHash[nxt]
                    self.reachable[x].add(nxtIndex)

        visited = [100000 for x in range(self.total)]
        q = deque()
        q.append(startIndex)
        visited[startIndex] = 1
        ans, steps = [], 100000
        while q:
            wordIndex = q.popleft()
            ops = visited[wordIndex]
            if ops >= steps:
                break
            for item in self.reachable[wordIndex]:
                if item == endIndex:
                    steps = ops + 1
                    self.track[endIndex].add(wordIndex)
                else:
                    if visited[item] >= ops + 1:
                        if visited[item] > ops + 1:
                            q.append(item)
                        visited[item] = ops + 1
                        self.track[item].add(wordIndex)

        ans = self.buildPath(endIndex, startIndex)
        return [[self.wordHash[x] for x in step] for step in ans]

print Solution().findLadders("red", "tax", set(["ted","tex","red","tax","tad","den","rex","pee"]))
