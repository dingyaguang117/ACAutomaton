__author__ = 'ding'
import _ACAutomation

class ACAutomation(object):
    def __init__(self):
        self.ac = _ACAutomation.new()

    def insert(self, str):
        _ACAutomation.insert(self.ac, str)

    def build(self):
        _ACAutomation.build(self.ac)

    def matchOne(self, str):
        return _ACAutomation.matchOne(self.ac, str)

    def matchAll(self, str):
        return _ACAutomation.matchAll(self.ac, str)