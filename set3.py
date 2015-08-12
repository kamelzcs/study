#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 zhao


class Point:
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Interval:
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e


class Solution:
  # @param num, a list of integer
  # @return a list of lists of integer
  def subsetsWithDup(self, S):
    f = lambda x: [[y for j, y in enumerate(x) if (i >> j) & 1] for i in range(2 ** len(x))]
    f2 = lambda l: reduce(lambda z, x: z + [y + [x] for y in z], l, [[]])
    unique_data = [list(x) for x in set(tuple(sorted(x)) for x in f2(S))]
    return [list(row) for row in unique_data]
  def romanToInt(self, s):
    table = {"I": 1,
             "V": 5,
             "X": 10,
             "L": 50,
             "C": 100,
             "D": 500,
             "M": 1000}
    s = s + "I"
    ans = 0
    index = 0
    while index < len(s) - 1:
      if table[s[index]] >= table[s[index + 1]]:
        ans += table[s[index]]
        index += 1
      else:
        ans += table[s[index + 1]] - table[s[index]]
        index += 2
    return ans

  def transform(self, intermidiate):
    ans = []
    if not intermidiate:
      return []
    size = len(intermidiate[0])
    for element in intermidiate:
      tp = []
      for each in element:
        temp = ["."] * size
        temp[each] = 'Q'
        tp.append("".join(temp))
      ans.append(tp)
    return ans

  def find(self, n, position, minus, plus, left, temp):
    ans = []
    if left == 0:
      return [temp]
    for index in xrange(n):
      bit = (1 << index)
      if (bit & position) == 0:
        continue
      minus_bit = 1 << (n + left - index)
      if minus & minus_bit:
        continue
      plus_bit = 1 << (left + index)
      if plus_bit & plus:
        continue
      last = self.find(n, position ^ bit, minus | minus_bit, plus | plus_bit, left - 1, temp + [index])
      if last:
        for element in last:
          ans.append(element)
    return ans

  def solutionNQueens(self, n):
    intermidiate = self.find(n, (1 << n) - 1, 0, 0, n, [])
    print intermidiate
    return self.transform(intermidiate)

  def dfs(self, h, l, r):
    if h == self.MASK:
      self.ans += 1
    pos = self.MASK & (~(h | l | r))
    while pos:
      p = pos & (-pos)
      self.dfs(h | p, (l | p) >> 1, (r | p) << 1)
      pos ^= p

  def totalNQueens(self, n):
    self.MASK = (1 << n) - 1
    self.ans = 0
    self.dfs(0, 0, 0)
    return self.ans

  def setZeroes(self, matrix):
    if not matrix:
      return matrix
    zero_first_row, zero_first_col = False, False
    m, n = len(matrix), len(matrix[0])
    for index in xrange(n):
      if matrix[0][index] == 0:
        zero_first_row = True
        break
    for index in xrange(m):
      if matrix[index][0] == 0:
        zero_first_col = True
        break
    for row in xrange(1, m):
      for col in xrange(1, n):
        if matrix[row][col] == 0:
          matrix[0][col] = 0
          matrix[row][0] = 0

    for row in xrange(1, m):
      for col in xrange(1, n):
        if matrix[row][0] == 0 or matrix[0][col] == 0:
          matrix[row][col] = 0

    if zero_first_row:
      for index in xrange(n):
        matrix[0][index] = 0

    if zero_first_col:
      for index in xrange(m):
        matrix[index][0] = 0

  def search(self, A, target):
    left = 0
    right = len(A) - 1
    while left <= right:
      middle = left + (right - left) / 2
      if target == A[middle]:
        return True
      if A[left] == A[right]:
        right -= 1
        continue
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
    return False

  def lengthOfLastWord(self, s):
    ans = 0
    if not s:
      return ans
    str_len = len(s)
    current, nxt = 0, 0
    while current < str_len and s[current] == ' ':
      current += 1
    if current >= str_len:
      return ans
    while current < str_len:
      nxt = current + 1
      while nxt < str_len and s[nxt] != ' ':
        nxt += 1
      ans = nxt - current
      while nxt < str_len and s[nxt] == ' ':
        nxt += 1
      current = nxt
    return ans

  def longestCommonPrefix(self, strs):
    ans = ""
    if not strs:
      return strs
    shortest = 100000000
    for each in strs:
      if not each:
        return each
      shortest = min(shortest, len(each))
    for index in xrange(shortest):
      for row in xrange(len(strs)):
        if row:
          if strs[row][index] != strs[row - 1][index]:
            return ans
      ans += strs[0][index]
    return ans

  def combinationSum(self, candidates, target):
    if not candidates:
      return []
    candidates = list(set(candidates))
    candidates.sort()
    ans = [[] for each in xrange(target + 1)]
    for index in xrange(len(candidates)):
      element = candidates[index]
      if element > target:
        break
      ans[element].append([index])
    for index in xrange(target):
      for each in ans[index]:
        last = each[-1]
        for nxt in xrange(last, len(candidates)):
          nxt_value = index + candidates[nxt]
          if nxt_value <= target:
            ans[nxt_value].append(each + [nxt])
          else:
            break
    return [[candidates[index] for index in elem] for elem in ans[target]]

  def letterCombinations(self, digits):
    theGrid = ["", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
    f = lambda l: reduce(lambda z, x: [y + p for p in theGrid[int(x) - 1] for y in z], l, [""])
    return f(digits)

  def largest(self, root):
    left, right, ans = -10000000, -10000000, -10000000
    if not root:
      return left, ans, right
    ans = root.val
    ll, lv, lr = self.largest(root.left)
    rl, rv, rr = self.largest(root.right)
    lmax = max(ll, lr)
    rmax = max(rl, rr)
    left = ans + lmax if lmax > 0 else ans
    right = ans + rmax if rmax > 0 else ans
    middle = ans
    if lmax > 0:
      middle += lmax
    if rmax > 0:
      middle += rmax
    return left, max(middle, max(lv, rv)), right

  def maxPathSum(self, root):
    ans = -10000000
    if not root:
      return ans
    left, middle, right = self.largest(root)
    return middle

  def minDistance(self, word1, word2):
    n, m = len(word1), len(word2)
    dp = [[n + m + 1] * (m + 1) for each in xrange(n + 1)]
    for index in xrange(n + 1):
      dp[index][0] = index
    for index in xrange(m + 1):
      dp[0][index] = index
    for first in xrange(1, n + 1):
      for second in xrange(1, m + 1):
        if word1[first - 1] == word2[second - 1]:
          dp[first][second] = min(dp[first][second], dp[first - 1][second - 1])
        else:
          temp = dp[first][second]
          # add in
          temp = min(temp, dp[first][second - 1] + 1)
          # modify
          temp = min(temp, dp[first - 1][second - 1] + 1)
          # delete
          temp = min(temp, dp[first - 1][second] + 1)
          dp[first][second] = temp
    return dp[n][m]

  def isInterleave(self, s1, s2, s3):
    l1, l2, l3 = len(s1), len(s2), len(s3)
    if l1 + l2 != l3:
      return False
    dp = [[0] * (l1 + 1) for index in xrange(l3 + 1)]
    dp[0][0] = 1
    for index in xrange(1, min(l3 + 1, l2 + 1)):
      dp[index][0] = 1 if s3[:index] == s2[:index] else 0
    for index in xrange(1, min(l3 + 1, l1 + 1)):
      dp[index][index] = 1 if s3[:index] == s1[:index] else 0
    for third in xrange(1, l3 + 1):
      for first in xrange(1, l1 + 1):
        second = third - first
        if second <= 0 or second > l2:
          continue
        if s3[third - 1] == s1[first - 1]:
          dp[third][first] |= dp[third - 1][first - 1]
        if s3[third - 1] == s2[second - 1]:
          dp[third][first] |= dp[third - 1][first]

    ans = 0
    for index in xrange(l1 + 1):
      ans |= dp[l3][index]
    return True if ans else False

  def nextPermutation(self, num):
    if not num:
      return []
    n = len(num)
    current = n - 2
    while current >= 0:
      if num[current] >= num[current + 1]:
        current -= 1
      else:
        break
    if current < 0:
      # num.sort()
      return None
    back = n - 1
    while num[back] <= num[current]:
      back -= 1
    num[current], num[back] = num[back], num[current]
    num[current + 1:] = reversed(num[current + 1:])
    return num

  def permuteUnique(self, num):
    ans = []
    if not num:
      return ans
    num.sort()
    ans.append(num[:])
    while True:
      num = self.nextPermutation(num)
      if num:
        ans.append(num[:])
      else:
        break
    return ans

  def combinationSum2(self, candidates, target):
    if not candidates:
      return []
    candidates.sort()
    ans = [[] for each in xrange(target + 1)]
    for index in xrange(len(candidates)):
      element = candidates[index]
      if element > target:
        break
      ans[element].append([index])
    for index in xrange(target):
      for each in ans[index]:
        last = each[-1]
        for nxt in xrange(last + 1, len(candidates)):
          nxt_value = index + candidates[nxt]
          if nxt_value <= target:
            ans[nxt_value].append(each + [nxt])
          else:
            break
    ans = [[candidates[index] for index in elem] for elem in ans[target]]
    temp = set()
    for each in ans:
      temp.add(tuple(each))
    ans = [list(each) for each in temp]
    return ans

  def firstMissingPositive(self, A):
    if not A:
      return 1
    n = len(A)
    for index in xrange(n):
      element = A[index]
      if element <= 0 or element > n:
        A[index] = 0
      elif element == index + 1:
        continue
      else:
        A[index] = 0
        while True:
          if element <= 0 or element > n or element == A[element - 1]:
            break
          A[element - 1], element = element, A[element - 1]
    for index in xrange(n):
      if A[index] == 0:
        return index + 1
    return n + 1

  def flood(self, board, row, col, origin, after):
    m, n = len(board), len(board[0])
    direct = [(-1, 0), (0, 1), (1, 0), (0, -1)]
    queue = [(row, col)]
    board[row][col] = after
    while queue:
      top = queue.pop(0)
      for index in xrange(4):
        nxt = (top[0] + direct[index][0], top[1] + direct[index][1])
        if nxt[0] < 0 or nxt[0] >= m:
          continue
        if nxt[1] < 0 or nxt[1] >= n:
          continue
        if board[nxt[0]][nxt[1]] == origin:
          board[nxt[0]][nxt[1]] = after
          queue.append(nxt)

  def solve(self, board):
    if not board:
      return
    m, n = len(board), len(board[0])
    for row in xrange(m):
      for col in (0, n - 1):
        if board[row][col] == 'O':
          self.flood(board, row, col, 'O', '.')

    for row in (0, m - 1):
      for col in xrange(n):
        if board[row][col] == 'O':
          self.flood(board, row, col, 'O', '.')

    for row in xrange(m):
      for col in xrange(n):
        if board[row][col] == 'O':
          board[row][col] = 'X'

    for row in xrange(m):
      for col in xrange(n):
        if board[row][col] == '.':
          board[row][col] = 'O'

  def minWindow(self, S, T):
    now, table = [0] * 256, [0] * 256
    for each in T:
      table[ord(each)] += 1
    total_bit = 0
    for index in xrange(256):
      if table[index]:
        total_bit += 1
    start, end = 0, -1
    index, now_bit = 0, 0
    while index < len(S):
      bit = ord(S[index])
      if table[bit] == 0:
        index += 1
        continue
      now[bit] += 1
      if now[bit] == table[bit]:
        now_bit += 1
        if now_bit == total_bit:
          break
      index += 1
    if index >= len(S) or not T:
      return ""
    end = index
    while True:
      if table[ord(S[start])]:
        if now[ord(S[start])] == table[ord(S[start])]:
          break
      now[ord(S[start])] -= 1
      start += 1
    ans = S[start: end + 1]
    while end < len(S) - 1:
      end += 1
      if table[ord(S[end])] == 0:
        continue
      now[ord(S[end])] += 1
      while True:
        if table[ord(S[start])]:
          if now[ord(S[start])] == table[ord(S[start])]:
            break
        now[ord(S[start])] -= 1
        start += 1
      if end - start + 1 < len(ans):
        ans = S[start: end + 1]

    return ans

  def dfs2(self, x, y, now_len):
    if now_len == len(self.word):
      self.ans = True
      return
    for index in xrange(4):
      nxt = (x + self.direct[index][0], y + self.direct[index][1])
      if nxt[0] < 0 or nxt[0] >= self.m:
        continue
      if nxt[1] < 0 or nxt[1] >= self.n:
        continue
      if self.visited[nxt[0]][nxt[1]]:
        continue
      if self.board[nxt[0]][nxt[1]] != self.word[now_len]:
        continue
      cached, self.board[x][y] = self.board[x][y], '#'
      self.dfs2(nxt[0], nxt[1], now_len + 1)
      self.board[x][y] = cached
      if self.ans:
        return

  def exist(self, board, word):
    if not word:
      return True
    if not board:
      return False
    m, n = len(board), len(board[0])
    self.direct = (-1, 0), (1, 0), (0, -1), (0, 1)
    self.word = word
    self.ans = False
    self.board = board
    self.m, self.n = m, n
    for row in xrange(m):
      for col in xrange(n):
        if board[row][col] != word[0]:
          continue
        cached, self.board[row][col] =self.board[row][col], '#'
        self.dfs2(row, col, 1)
        self.board[row][col] = cached
        if self.ans:
          return self.ans
    return self.ans

  def merge(self, intervals):
    if not intervals:
      return []
    ans = []
    intervals.sort()
    start, end, index = intervals[0][0], intervals[0][1], 1
    while index < len(intervals):
      if intervals[index][0] <= end:
        end = max(end, intervals[index][1])
      else:
        ans.append([start, end])
        start, end = intervals[index][0], intervals[index][1]
      index += 1
    ans.append([start, end])
    return ans

  def find_interval(self, intervals, point):
    if point < intervals[0].start:
      return -1
    if point > intervals[-1].end:
      return 2 * len(intervals) - 1
    for index in xrange(len(intervals)):
      if point >= intervals[index].start and point <= intervals[index].end:
        return 2 * index
      if point > intervals[index].end and point < intervals[index + 1].start:
        return 2 * index + 1

  def insert(self, intervals, newInterval):
    if not newInterval:
      return intervals
    if not intervals:
      return [newInterval]
    start, end = self.find_interval(intervals, newInterval.start), self.find_interval(intervals, newInterval.end)
    ans = []
    index = 0
    start_point, end_point = -1, -1
    while index < start / 2:
      ans.append(intervals[index])
      index += 1
    if (start & 1) == 0:
      start_point = intervals[start / 2].start
    else:
      start_point = newInterval.start
      ans.append(intervals[index])
    if (end & 1) == 0:
      end_point = intervals[end / 2].end
    else:
      end_point = newInterval.end
    ans.append([start_point, end_point])
    index = end / 2 + 1
    while index < len(intervals):
      ans.append(intervals[index])
      index += 1
    return ans

  def simplifyPath(self, path):
    if not path:
      return "/"
    now_path, index = [], 0
    while index < len(path):
      while index < len(path) and path[index] == '/':
        index += 1
      if index >= len(path):
        break
      nxt = index + 1
      while nxt < len(path) and path[nxt] != '/':
        nxt += 1
      if path[index] != '.':
        now_path.append(path[index: nxt])
      else:
        temp = nxt - index
        if temp == 2:
          if now_path:
            now_path.pop()
        elif temp > 2:
          now_path.append(path[index: nxt])

      if nxt < len(path) - 1 and path[nxt + 1] == '/':
        nxt += 1
      index = nxt
    return '/' + '/'.join(now_path)

  def maxNumber(self, points):
    ans = 0
    points.sort(cmp=lambda first, second: first.y * second.x - first.x * second.y)
    now, nxt = 0, 1
    while now < len(points):
      nxt = now + 1
      while nxt < len(points):
        if points[now].y * points[nxt].x != points[now].x * points[nxt].y:
          break
        nxt += 1
      ans = max(ans, nxt - now)
      now = nxt
    return ans

  def construct(self, point, points):
    origin_number, remain_points = 0, []
    for each in points:
      if each.x == point.x and each.y == point.y:
        origin_number += 1
      else:
        remain_points.append(Point(each.x - point.x, each.y - point.y))
    return origin_number, remain_points

  def maxPoints(self, points):
    if not points:
      return 0
    ans = 1
    for each in points:
      exist, new_point = self.construct(each, points)
      ans = max(ans, exist + self.maxNumber(new_point))
    return ans

t = Solution()
print t.maxPoints([Point(0, 0), Point(1, 1), Point(1, -1)])
