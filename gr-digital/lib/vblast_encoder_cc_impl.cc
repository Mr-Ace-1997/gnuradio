/* -*- c++ -*- */
/* 
 * Copyright 2018 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "vblast_encoder_cc_impl.h"

namespace gr {
  namespace digital {

    vblast_encoder_cc::sptr
    vblast_encoder_cc::make(uint16_t num_outputs)
    {
      return gnuradio::get_initial_sptr
        (new vblast_encoder_cc_impl(num_outputs));
    }

    /*
     * The private constructor
     */
    vblast_encoder_cc_impl::vblast_encoder_cc_impl(uint16_t num_outputs)
      : gr::sync_decimator("vblast_encoder_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(num_outputs, num_outputs, sizeof(gr_complex)), num_outputs),
        d_num_outputs(num_outputs)
    {}

    /*
     * Our virtual destructor.
     */
    vblast_encoder_cc_impl::~vblast_encoder_cc_impl()
    {
    }

    int
    vblast_encoder_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];

      // Iterate over output ports.
      for (int i = 0; i < d_num_outputs; ++i) {
        gr_complex *out = (gr_complex *) output_items[i];
        // Write output data to current output port.
        for (int j = 0; j < noutput_items; ++j) {
          out[j] = in[j*d_num_outputs + i];
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace digital */
} /* namespace gr */

