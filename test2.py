#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 zhao

"""

"""

ACCEPT_CLASSES = [
  (1, u'レディース'),
  (2, u'オープン'),
  (3, u'ビギナー'),
  (4, u'スーパービギナー'),
  (5, u'ウルトラビギナー'),
  (6, u'エンジョイ'),
  (7, u'ミックス'),
  (8, u'ファミリー'),
  (9, u'ミックス＆ファミリー'),
  (10, u'Over30'),
  (12, u'Over35'),
  (13, u'Over40'),
  (11, u'学生'),
]
print max(_[0] for _ in ACCEPT_CLASSES)
print max(zip(*ACCEPT_CLASSES)[0])
