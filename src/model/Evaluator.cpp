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

// ToPS headers
#include "Evaluator.hpp"
#include "ProbabilisticModel.hpp"

namespace tops {
namespace model {

Evaluator::Evaluator(ProbabilisticModelPtr m, const Sequence &s)
    : _model(m), _sequence(s) {
}

EvaluatorPtr Evaluator::make(ProbabilisticModelPtr m, const Sequence &s) {
  return EvaluatorPtr(new Evaluator(m, s));
}

double Evaluator::probabilityOf(unsigned int begin,
                                unsigned int end,
                                unsigned int phase) const {
  return _model->evaluateSequence(_sequence, begin, end, phase);
}

}  // namespace model
}  // namespace tops