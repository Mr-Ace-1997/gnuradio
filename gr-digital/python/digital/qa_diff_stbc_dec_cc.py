#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2018 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import digital_swig as digital
import numpy as np

class qa_diff_stbc_dec_cc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        data = np.array([1, 0, 0, 1, 0, 1, 0, -1, 0, 1])
        phase_shift = 0.0

        # Build up the test flowgraph.
        src = blocks.vector_source_c(data=data)
        decoder = digital.diff_stbc_dec_cc(phase_shift)
        sink = blocks.vector_sink_c()
        self.tb.connect(src, decoder, sink)
        # Run flowgraph.
        self.tb.run()

        print 'result'
        print sink.data()


if __name__ == '__main__':
    gr_unittest.run(qa_diff_stbc_dec_cc, "qa_diff_stbc_dec_cc.xml")