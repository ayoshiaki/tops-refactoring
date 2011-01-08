/*
 *       SmoothedHistogramBurge.hpp
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

#ifndef SMOOTHED_HISTOGRAM_BURGE_HPP
#define SMOOTHED_HISTOGRAM_BURGE_HPP
#include "ProbabilisticModelCreator.hpp"

namespace tops 
{

  //! Creates a smoothed histogram using Burge algorithm
  class SmoothedHistogramBurge:  public ProbabilisticModelCreator {
  public:
    SmoothedHistogramBurge () {}
    virtual ~SmoothedHistogramBurge () {};
    //! Creates a probability model 
    /*! \param parameters is a set of parameters that is utilized to build the model */
    virtual ProbabilisticModelPtr create( ProbabilisticModelParameters & parameters) const;

    //! Provides a help
    virtual std::string help() const {
      std::string s;
      return s;
    }
    virtual std::string factory_name() const {
      return "SmoothedHistogramBurge";
    }

  };
  typedef boost::shared_ptr <SmoothedHistogramBurge> SmoothedHistogramBurgePtr ;


}

#endif
