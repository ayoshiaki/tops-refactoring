/*
 *       FactorableModelPrefixSumArray.hpp
 *
 *       Copyright 2011 Andre Yoshiaki Kashiwabara <akashiwabara@usp.br>
 *     
 *       This program is free software; you can redistribute it and/or modify
 *       it under the terms of the GNU  General Public License as published by
 *       the Free Software Foundation; either version 3 of the License, or
 *       (at your option) any later version.
 *     
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *       GNU General Public License for more details.
 *      
 *       You should have received a copy of the GNU General Public License
 *       along with this program; if not, write to the Free Software
 *       Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *       MA 02110-1301, USA.
 */

#ifndef FACTORABLE_PREFIX_SUM_ARRAY_HPP
#define FACTORABLE_PREFIX_SUM_ARRAY_HPP

#include "crossplatform.hpp"

#include <boost/shared_ptr.hpp>
#include "Sequence.hpp"
#include "PrefixSumArray.hpp"
#include "ProbabilisticModel.hpp"
#include "util.hpp"

namespace tops {

//! This class provides an interface for working with the prefix  sum arrays.
  class DLLEXPORT FactorableModelPrefixSumArray : public PrefixSumArray
  {
  private:
    ProbabilisticModel * _model;
    DoubleVector _alpha;
    DoubleVector _precision;
    Sequence _last;
  public:
    virtual ~FactorableModelPrefixSumArray(){};
    FactorableModelPrefixSumArray (ProbabilisticModel * model) : _model(model) {}
    //! Initialize the prefix sum array
    virtual void initialize(const Sequence & s) ;
    
    //! compute the prefix sum array
    virtual double compute(int begin, int end ) const ;
    

  };
  
  typedef boost::shared_ptr <FactorableModelPrefixSumArray> FactorableModelPrefixSumArrayPtr;
}

#endif
