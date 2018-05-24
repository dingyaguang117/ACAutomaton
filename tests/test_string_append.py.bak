__author__ = 'ding'
import timeit
import sys

def string_add():
    s = ''
    for i in xrange(10000000):
        s += '1'
    print sys.getsizeof(s)


def string_append():
    s = []
    for i in xrange(10000000):
        s.append('1')
    print sys.getsizeof(s)

if __name__ == '__main__':
    t = timeit.Timer('string_add()', 'from __main__ import string_add')
    print t.timeit(1)

    t = timeit.Timer('string_append()', 'from __main__ import string_append')
    print t.timeit(1)