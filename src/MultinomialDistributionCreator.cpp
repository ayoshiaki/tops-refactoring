/*
 *       MultinomialDistributionCreator.cpp
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

#include "MultinomialDistributionCreator.hpp"
#include "ConfigurationReader.hpp"
#include "MultinomialDistribution.hpp"
#include "Alphabet.hpp"
namespace tops {

  ProbabilisticModelPtr MultinomialDistributionCreator::create(ProbabilisticModelParameters & parameters) const {
    return createMultinomialDistribution(parameters);
  }

  MultinomialDistributionPtr MultinomialDistributionCreator::createMultinomialDistribution(ProbabilisticModelParameters & parameters) const {
    ProbabilisticModelParameterValuePtr probs = parameters.getMandatoryParameterValue("probabilities");
    if(probs == NULL)
      {
        std::cerr << help();
      }
    MultinomialDistributionPtr model = MultinomialDistributionPtr(new MultinomialDistribution());
    model->initialize(parameters);
    return model;
  }
}
