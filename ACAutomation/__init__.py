__author__ = 'ding'
__version__ = '0.1'

import _ACAutomation

class ACAutomation(object):
    def __init__(self):
        '''
        init a ACAutomation
        :return:
        '''
        self.ac = _ACAutomation.new()

    def insert(self, string):
        '''
        Insert a string to ac-automaion. Ensure string's type are str, not unicode
        :param string:
        :return: None
        '''
        _ACAutomation.insert(self.ac, string)

    def build(self):
        '''
        Buid ac-automaion before match*
        :return: None
        '''
        _ACAutomation.build(self.ac)

    def matchOne(self, string):
        '''
        Match the most front keyword in string which also in inserted keywords. Ensure string's type are str, not unicode
        :param string:
        :return: a tuple (position, 'keyword'). if didn't find one return (-1, None);
        '''
        return _ACAutomation.matchOne(self.ac, string)

    def matchAll(self, string):
        '''
        Match all keyword in string which also in inserted keywords. Ensure string's type are str, not unicode
        :param string:
        :return: a list of tuple (position, 'keyword'). if didn't find one return empty list [];
        '''
        return _ACAutomation.matchAll(self.ac, string)