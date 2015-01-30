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

#include <math.h>
#include <vector>

#include "gmock/gmock.h"

#include "model/HiddenMarkovModel.hpp"
#include "model/DiscreteIIDModel.hpp"
#include "model/Sequence.hpp"

#include "helper/HiddenMarkovModel.hpp"

using ::testing::Eq;
using ::testing::DoubleEq;
using ::testing::DoubleNear;
using ::testing::ContainerEq;

using tops::model::HiddenMarkovModel;
using tops::model::HiddenMarkovModelPtr;
using tops::model::Sequence;

using tops::helper::createDishonestCoinCasinoHMM;

class AHiddenMarkovModel : public testing::Test {
 protected:
  HiddenMarkovModelPtr hmm = createDishonestCoinCasinoHMM();
};

TEST_F(AHiddenMarkovModel, ShouldFindTheBestPath) {
  Sequence path;
  tops::Matrix matrix;
  ASSERT_THAT(hmm->viterbi({0, 0}, path, matrix), DoubleEq(log(0.0625)));
  ASSERT_THAT(path, ContainerEq(Sequence{0, 0}));
  ASSERT_THAT(hmm->viterbi({0, 0, 0, 0, 0, 0, 0}, path, matrix), DoubleNear(log(0.000061035188), 0.000001));
  ASSERT_THAT(path, ContainerEq(Sequence{0, 0, 0, 0, 0, 0, 0}));
  ASSERT_THAT(hmm->viterbi({1, 1, 1, 1, 1, 1}, path, matrix), DoubleNear(log(0.0429), 0.01));
  ASSERT_THAT(path, ContainerEq(Sequence{1, 1, 1, 1, 1, 1}));
}
