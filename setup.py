__author__ = 'ding'
from distutils.core import setup, Extension

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name="ACAutomation",
    description="ACAutomation python wrapper,support unicode",
    author="Yaguang Ding",
    author_email="dingyaguang117@gmail.com",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="http://github.com/dingyaguang117/ACAutomation",
    packages=['ACAutomation'],
    ext_modules = [
        Extension("_ACAutomation",
            sources=['ACAutomation/wrapper.cpp', 'ACAutomation/_ACAutomation.cpp'],
            include_dirs=['./ACAutomation'],
        )
    ],
    classifiers=[
        "Programming Language :: Python",
    ],
    keywords='ac-automation ac automation',
    python_requires='>=2.6',
    version='1.0.3'

)