__author__ = 'ding'
from distutils.core import setup, Extension

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name="ACAutomaton",
    description="ACAutomaton python wrapper,support unicode",
    author="Yaguang Ding",
    author_email="dingyaguang117@gmail.com",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="http://github.com/dingyaguang117/ACAutomaton",
    packages=['ACAutomaton'],
    ext_modules = [
        Extension("_ACAutomaton",
            sources=['ACAutomaton/wrapper.cpp', 'ACAutomaton/_ACAutomaton.cpp'],
            include_dirs=['./ACAutomaton'],
        )
    ],
    classifiers=[
        "Programming Language :: Python",
    ],
    keywords='ac-automation ac automation',
    python_requires='>=2.6',
    version='1.0.3'

)