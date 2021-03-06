/***********************************************************************/
/*  Copyright 2015 ToPS                                                */
/*                                                                     */
/*  This program is free software; you can redistribute it and/or      */
/*  modify it under the terms of the GNU  General Public License as    */
/*  published by the Free Software Foundation; either version 3 of     */
/*  the License, or (at your option) any later version.                */
/*                                                                     */
/*  This program is distributed in the hope that it will be useful,    */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of     */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      */
/*  GNU General Public License for more details.                       */
/*                                                                     */
/*  You should have received a copy of the GNU General Public License  */
/*  along with this program; if not, write to the Free Software        */
/*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,         */
/*  MA 02110-1301, USA.                                                */
/***********************************************************************/

#ifndef TOPS_MODEL_PHASED_INHOMOGENEOUS_MARKOV_CHAIN_
#define TOPS_MODEL_PHASED_INHOMOGENEOUS_MARKOV_CHAIN_

// Standard headers
#include <memory>
#include <vector>

// ToPS headers
#include "model/Matrix.hpp"
#include "model/InhomogeneousMarkovChain.hpp"
#include "model/VariableLengthMarkovChain.hpp"

namespace tops {
namespace model {

class PhasedInhomogeneousMarkovChain;

/**
 * @typedef PhasedInhomogeneousMarkovChainPtr
 * @brief Alias of pointer to PhasedInhomogeneousMarkovChain.
 */
using PhasedInhomogeneousMarkovChainPtr
    = std::shared_ptr<PhasedInhomogeneousMarkovChain>;

/**
 * @class PhasedInhomogeneousMarkovChain
 * @brief Class that represents an inhomogeneous Markov chain.
 *
 * A phased inhomogeneous Markov chain is a model which suports different
 * Markov chains per position. Each Markov chain repeats itsealf per
 * phase.
 */
class PhasedInhomogeneousMarkovChain
    : public ProbabilisticModelCrtp<PhasedInhomogeneousMarkovChain> {
 public:
  // Inner classes
  struct Cache : ProbabilisticModelCrtp<PhasedInhomogeneousMarkovChain>::Cache {
    Matrix prefix_sum_matrix;
  };

  // Tags
  class interpolation_algorithm {};

  // Alias
  using Base = ProbabilisticModelCrtp<PhasedInhomogeneousMarkovChain>;

  using Self = PhasedInhomogeneousMarkovChain;
  using SelfPtr = PhasedInhomogeneousMarkovChainPtr;

  // Constructors
  PhasedInhomogeneousMarkovChain(
      std::vector<VariableLengthMarkovChainPtr> vlmcs);

  // Static methods
  static PhasedInhomogeneousMarkovChainPtr make(
      std::vector<VariableLengthMarkovChainPtr> vlmcs);

  static SelfPtr train(TrainerPtr<Standard, Self> trainer,
                       interpolation_algorithm,
                       unsigned int alphabet_size,
                       unsigned int order,
                       unsigned int nphases,
                       double pseudo_counts,
                       std::vector<double> weights,
                       ProbabilisticModelPtr apriori);

  // Virtual methods
  void initializeCache(CEPtr<Standard> evaluator,
                       unsigned int phase) override;

  Probability evaluateSymbol(SEPtr<Standard> evaluator,
                             unsigned int pos,
                             unsigned int phase) const override;
  Probability evaluateSequence(SEPtr<Standard> evaluator,
                               unsigned int begin,
                               unsigned int end,
                               unsigned int phase) const override;

  Probability evaluateSequence(CEPtr<Standard> evaluator,
                               unsigned int begin,
                               unsigned int end,
                               unsigned int phase) const override;

  Standard<Symbol> drawSymbol(SGPtr<Standard> generator,
                              unsigned int pos,
                              unsigned int phase,
                              const Sequence &context) const override;

 private:
  // Instance variables
  std::vector<VariableLengthMarkovChainPtr> _vlmcs;
};

}  // namespace model
}  // namespace tops

#endif  // TOPS_MODEL_PHASED_INHOMOGENEOUS_MARKOV_CHAIN_
