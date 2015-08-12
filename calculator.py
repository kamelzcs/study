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
# <term>        : <number>
#               | ( <arith_expr> )

import re
import operator
token_map = {'+': operator.add, '-': operator.sub,
             '(':'LPAR', ')':'RPAR'}
class Solution:
    # @param {string} s
    # @return {integer}
    def match(self, char=None, number=False):
      if number:
        self.cur = int(self.split_expr[self.pos])
        self.pos += 1
        self.left -= 1
      else:
        if(char == self.split_expr[self.pos]):
          self.pos += 1
          self.left -= 1
          return True

    def eval_term(self):
      if self.match('('):
        ans = self.eval_expr()
        self.match(')')
      else:
        self.match(number=True)
        ans = self.cur
      return ans

    def eval_expr(self):
      l_term = self.eval_term()
      while self.left:
        if self.match('+'):
          l_term += self.eval_term()
        elif self.match('-'):
          l_term -= self.eval_term()
        else:
          break
      return l_term

    def calculate(self, expr):
        self.split_expr = re.findall('[\d]+|[%s]' % ''.join(token_map), expr)
        self.pos = 0
        self.left = len(self.split_expr)
        return self.eval_expr()

print Solution().calculate('(5-(1+(5)))')
print Solution().calculate('2-1 + 2')
