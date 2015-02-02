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

#ifndef TOPS_MODEL_VARIABLE_LENGTH_MARKOV_CHAIN_
#define TOPS_MODEL_VARIABLE_LENGTH_MARKOV_CHAIN_

// Standard headers
#include <memory>

// ToPS headers
#include "model/FactorableModel.hpp"
#include "model/ContextTree.hpp"

namespace tops {
namespace model {

class VariableLengthMarkovChain;
using VariableLengthMarkovChainPtr = std::shared_ptr<VariableLengthMarkovChain>;

class VariableLengthMarkovChain : public FactorableModel {
 public:
  // Static methods
  static VariableLengthMarkovChainPtr make(ContextTreePtr context_tree);

  // Virtual methods
  virtual int alphabetSize() const;
  virtual double evaluatePosition(const Sequence &s, unsigned int i) const;
  virtual int choosePosition(const Sequence &s, unsigned int i) const;

 private:
  // Instance variables
  ContextTreePtr _context_tree;

  // Constructors
  explicit VariableLengthMarkovChain(ContextTreePtr context_tree);
};

}  // namespace model
}  // namespace tops

#endif  // TOPS_MODEL_VARIABLE_LENGTH_MARKOV_CHAIN_
