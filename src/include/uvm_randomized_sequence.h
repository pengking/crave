/****************************************************************************************
//	MIT License
//***************************************************************************************
//	Copyright (c) 2012-2020 University of Bremen, Germany. 
//  	Copyright (c) 2015-2020 DFKI GmbH Bremen, Germany.
//  	Copyright (c) 2020 Johannes Kepler University Linz, Austria.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
****************************************************************************************/


#pragma once

#include <crave/experimental/SystemC.hpp>
#include <crave/ConstrainedRandom.hpp>
#include <crave/frontend/Constraint.hpp>
#include <crave/experimental/Experimental.hpp>

#include <uvm>
/**
 * \brief Overrides uvm_sequence and crv_sequence_item to merge its functionality.
 *
 * This class is intendant as an adapter to merge CRAVE functionality into UVM-SystemC
 * processes without harming them. To use it, simply inherit from this class instead from
 * uvm_sequence. You may now use CRAVE variables and constraints in your UVM-Sequence.
 */

template<typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class uvm_randomized_sequence : public uvm::uvm_sequence<REQ, RSP>, public crave::crv_sequence_item {
public:
    /**
     * \brief Register uvm_randomized_sequence with UVM-SystemC.
     */
    UVM_OBJECT_UTILS(uvm_randomized_sequence);

    /**
     * \brief Creates a new sequence with given name.
     *
     * Since both CRAVE and UVM-SystemC are using some kind of name for theier objects
     * , both parent will be named the same. std::string is the lowest common denominator
     * between the nameing type of CRAVE and of UVM-SystemC. Therefore you may pass a
     * std::string or a crave::crv_object_name as argument.
     *
     * \param name Name of this sequence.
     */
    uvm_randomized_sequence(crave::crv_object_name name)
    : uvm::uvm_sequence<REQ, RSP>(name()) {
    };

    virtual ~uvm_randomized_sequence() {
    };
};

/**
 * \example same_flavored_jelly_beans_sequence.h
 *
 * Demonstrates how to inherit from this class and use CRAVE to ensure that a special
 * attribute remains the same wihthin this sequence.
 */
/**
 * \example gift_boxed_jelly_beans_sequence.h
 *
 * Shows how to randomize the amount of sequences within a sequence with CRAVE.
 */