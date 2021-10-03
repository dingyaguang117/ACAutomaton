__author__ = 'ding'
__version__ = '1.0.3'

import _ACAutomaton

class ACAutomaton(object):
    def __init__(self):
        '''
        init a ACAutomaton
        :return:
        '''
        self.ac = _ACAutomaton.new()

    def insert(self, string):
        '''
        Insert a string to ac-automaion. Ensure string's type are str, not unicode
        :param string:
        :return: None
        '''
        _ACAutomaton.insert(self.ac, string)

    def build(self):
        '''
        Buid ac-automaion before match*
        :return: None
        '''
        _ACAutomaton.build(self.ac)

    def matchOne(self, string):
        '''
        Match the most front keyword in string which also in inserted keywords. Ensure string's type are str, not unicode
        :param string:
        :return: a tuple (position, 'keyword'). if didn't find one return (-1, None);
        '''
        return _ACAutomaton.matchOne(self.ac, string)

    def matchAll(self, string):
        '''
        Match all keyword in string which also in inserted keywords. Ensure string's type are str, not unicode
        :param string:
        :return: a list of tuple (position, 'keyword'). if didn't find one return empty list [];
        '''
        return _ACAutomaton.matchAll(self.ac, string)