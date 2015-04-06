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

#ifndef TOPS_MODEL_LABELING_
#define TOPS_MODEL_LABELING_

// ToPS headers
#include "Sequence.hpp"

namespace tops {
namespace model {

// Inner classes
class Labeling {
 public:
  // Symbols
  enum class Method { bestPath, posteriorDecoding };

  // Constructors
  Labeling();
  Labeling(double probability, const Sequence& sequence);
  Labeling(double probability, Sequence&& sequence);

  // Getters
  double probability() const;

  Sequence& sequence();
  const Sequence& sequence() const;

 private:
  double _probability;
  Sequence _sequence;
};

}  // namespace model
}  // namespace tops

#endif