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
    >>> a.matchOne('1111111')
    (0, '11')
    >>> a.matchAll('1111111')
    [(0, '11'), (1, '11'), (2, '11'), (3, '11'), (4, '11'), (5, '11')]

