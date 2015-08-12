#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 zhao <zhao@kamel-ThinkPad-X201>
#
# Distributed under terms of the MIT license.

# <arith_expr>  : <term> {+ <term>}
#               | <term> {- <term>}
#
# <term>        : <number> {* <number>}
#               | <number> {/ <number>}

import re
import operator
token_map = {'+': operator.add, '-': operator.sub,
             '*': operator.mul, '/': operator.div}


class Solution:
    # @param {string} s
    # @return {integer}
    def match(self, number=False):
      if number:
        self.cur = int(self.split_expr[self.pos])
        self.pos += 1
        self.left -= 1
      else:
        ops = self.split_expr[self.pos]
        self.op = token_map[ops]
        self.pos += 1
        self.left -= 1
        return True
      return False

    def eval_term(self):
      self.match(number=True)
      l_term = self.cur
      while self.left:
        if self.match():
            self.match(number=True)
            l_term = self.op(l_term, self.cur)
        else:
            break
      return l_term

    def eval_expr(self):
      l_term = self.eval_term()
      while self.left:
        if self.match():
            value = self.eval_term()
            l_term = self.op(l_term, value)
        else:
            break
      return l_term

    def calculate(self, expr):
        self.split_expr = re.findall('[\d.]+|[%s]' % ''.join(token_map), expr)
        self.pos = 0
        self.left = len(self.split_expr)
        return self.eval_expr()

print Solution().calculate("  3+5 / 2")
print Solution().calculate("  3+2*2")
print Solution().calculate("  10/1/2/3")
