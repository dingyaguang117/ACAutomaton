# About
ACAutomation Python Lib Wrapper


# Install
    pip install ACAutomation

# Usage
    >>> from ACAutomation import ACAutomation
    >>> a = ACAutomation()
    >>> a.insert('11')
    >>> a.insert('22')
    >>> a.insert('33')
    >>> a.build()
    >>> a.matchOne('0011222333')
    (2, '11')
    >>> a.matchOne('00')
    (-1, None)
    >>> a.matchAll('0011222333')
    [(2, '11'), (4, '22'), (5, '22'), (7, '33'), (7, '33'), (8, '33'), (8, '33')]


