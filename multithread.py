#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 luxeys <info@luxeys.com>
#
# Distributed under terms of the MIT license.

"""
multithread sample code.
"""
import Queue
import threading
import urllib2

# called by each thread
def get_url(q, url):
    q.put(urllib2.urlopen(url).read())

theurls = '''http://labola.jp http://yahoo.com'''.split()

q = Queue.Queue()

for u in theurls:
    t = threading.Thread(target=get_url, args=(q, u))
    t.daemon = True
    t.start()

s = q.get()
print s
