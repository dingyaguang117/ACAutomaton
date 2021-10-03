#coding=utf-8
__author__ = 'ding'
from ACAutomaton import ACAutomaton


def test_acauomaton_ascii():
    acautomaton = ACAutomaton()
    acautomaton.insert('11')
    acautomaton.insert('22')
    acautomaton.insert('33')
    acautomaton.build()

    result = acautomaton.matchOne('1011011001010220222200303')
    assert result == (2, '11')

    result = acautomaton.matchAll('1011011001010220222200303')
    assert result == [(2, '11'), (5, '11'), (13, '22'), (16, '22'), (17, '22'), (18, '22')]


def test_acauomaton_unicode():
    acautomaton = ACAutomaton()
    acautomaton.insert('苹果')
    acautomaton.insert('葡萄')
    acautomaton.insert('香蕉')
    acautomaton.build()

    result = acautomaton.matchOne('水果店里有香蕉，没有苹果')
    assert result == (15, '香蕉')

    result = acautomaton.matchAll('水果店里有香蕉，没有苹果')
    assert result == [(15, '香蕉'), (30, '苹果')]


if __name__ == '__main__':
    test_acauomaton_ascii()
    test_acauomaton_unicode()