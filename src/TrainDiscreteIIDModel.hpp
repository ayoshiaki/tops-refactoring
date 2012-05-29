/*
 *       TrainDiscreteIIDModel.hpp
 *
 *       Copyright 2011 Andre Yoshiaki Kashiwabara <akashiwabara@usp.br>
 *                      �gor Bon�dio <ibonadio@ime.usp.br>
 *                      Vitor Onuchic <vitoronuchic@gmail.com>
 *                      Alan Mitchell Durham <aland@usp.br>
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

#ifndef TRAIN_FDD_HPP
#define TRAIN_FDD_HPP

#include "crossplatform.hpp"

#include "ProbabilisticModel.hpp"
#include "ProbabilisticModelCreator.hpp"
#include "ConfigurationReader.hpp"


namespace tops {

  //! Creates a Multinomial Distribution
  class DLLEXPORT TrainDiscreteIIDModel : public ProbabilisticModelCreator {
  public:
    TrainDiscreteIIDModel () {}
    virtual ~TrainDiscreteIIDModel () {};
    //! Creates a probability model
    /*! \param parameters is a set of parameters that is utilized to build the model */
    virtual ProbabilisticModelPtr create( ProbabilisticModelParameters & parameters) const ;

    virtual ProbabilisticModelPtr create(
                ProbabilisticModelParameters & parameters, double & loglikelihood,
                int & sample_size) const ;

    //! Creates the model and returns the loglikelihood of the training set
    virtual ProbabilisticModelPtr create( ProbabilisticModelParameters & parameters, const std::vector<std::string> & sample_set, double & loglikelihood, int & sample_size) const ;

    virtual ProbabilisticModelPtr train(const SequenceEntryList & sample_set, AlphabetPtr alphabet) const;
    virtual std::string help() const ;

  };
  typedef boost::shared_ptr <TrainDiscreteIIDModel> TrainDiscreteIIDModelPtr ;
};


#endif
