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

#include "Vertex.hpp"

#include <vector>

namespace tops {
namespace model {

VertexPtr Vertex::connect(VertexPtr vertex) {
  addNextVertex(vertex);
  vertex->addPreviousVertex(VertexPtr(this));
  return vertex;
}

void Vertex::addNextVertex(VertexPtr vertex) {
  next_vertexes.push_back(vertex);
}

void Vertex::addPreviousVertex(VertexPtr vertex) {
  previous_vertexes.push_back(vertex);
}

std::vector<VertexPtr> Vertex::nextVertexes() {
  return next_vertexes;
}

std::vector<VertexPtr> Vertex::previousVertexes() {
  return previous_vertexes;
}

}  // namespace model
}  // namespace tops