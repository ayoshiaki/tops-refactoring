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

#include <cmath>
#include <vector>

#include "gmock/gmock.h"

#include "model/PhasedRunLengthDistribution.hpp"
#include "model/Sequence.hpp"

#include "helper/PhasedRunLengthDistribution.hpp"
#include "helper/Sequence.hpp"

using ::testing::Eq;
using ::testing::DoubleEq;
using ::testing::DoubleNear;

using tops::model::PhasedRunLengthDistribution;
using tops::model::PhasedRunLengthDistributionPtr;
using tops::model::Sequence;

using tops::helper::generateRandomSequence;
using tops::helper::sequenceOfLengths;
using tops::helper::createLengthDistribution;

class APhasedRunLengthDistribution : public testing::Test {
 protected:
  PhasedRunLengthDistributionPtr distribution = createLengthDistribution();
};

TEST_F(APhasedRunLengthDistribution, ShouldHaveAnAlphabetSize) {
  ASSERT_THAT(distribution->alphabetSize(), Eq(15001));
}

TEST_F(APhasedRunLengthDistribution, ShouldEvaluateASingleSymbol) {
  ASSERT_THAT(distribution->probabilityOf(125), DoubleNear(-4.51625, 1e-04));
  ASSERT_THAT(distribution->probabilityOf(4187), DoubleNear(-9.99687, 1e-04));
  ASSERT_THAT(distribution->probabilityOf(4188), DoubleEq(-HUGE));
}

