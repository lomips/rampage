'''
This source code is distributed under the MIT License

Copyright (c) 2010, Jens Neuhalfen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
'''

import struct
from ctypes import *
import fcntl

import mmap

class FrameStatus(Structure):
    '''
    classdocs
    '''
    
    _fields_ = [("last_successful_test",            c_uint64),
                ("last_failed_test",                c_uint64),
                ("last_claiming_time_jiffies",      c_uint64),
                ("last_claiming_attempt",           c_uint64),
                ("num_errors",                      c_uint32),
                ("last_successful_claiming_method", c_uint32)]
    
    def __str__(self):
        return " num_errors: %4.d, last_successful_test: %10.d" %(self.num_errors, self.last_successful_test)
   
    def __init__(self):
        self.pfn  = 0
        self.flags = None
        self.mapcount = 0
