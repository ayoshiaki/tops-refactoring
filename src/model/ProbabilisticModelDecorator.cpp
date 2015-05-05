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

#include "ProbabilisticModelDecorator.hpp"

namespace tops {
namespace model {

ProbabilisticModelDecoratorPtr ProbabilisticModelDecorator::make(
    ProbabilisticModelPtr model) {
  return ProbabilisticModelDecoratorPtr(new ProbabilisticModelDecorator(model));
}

ProbabilisticModelDecorator::ProbabilisticModelDecorator(
    ProbabilisticModelPtr model) : _model(model) {
}

double ProbabilisticModelDecorator::evaluate(const Sequence &s,
                                             unsigned int pos,
                                             unsigned int phase) const {
  return _model->evaluate(s, pos);
}

Symbol ProbabilisticModelDecorator::choose(const Sequence &s,
                                           unsigned int pos,
                                           unsigned int phase) const {
  return _model->choose(s, pos);
}

Sequence ProbabilisticModelDecorator::chooseSequence(unsigned int size,
                                                     unsigned int phase) const {
  return _model->chooseSequence(size, phase);
}


}  // namespace model
}  // namespace tops
