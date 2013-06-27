/*
 *       MaximalDependenceDecomposition.hpp
 *
 *       Copyright 2011 Andre Yoshiaki Kashiwabara <akashiwabara@usp.br>
 *                      Ígor Bonadio <ibonadio@ime.usp.br>
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

#ifndef MAXIMAL_DEPENDENCE_DECOMPOSITION_HPP
#define MAXIMAL_DEPENDENCE_DECOMPOSITION_HPP
#include <boost/shared_ptr.hpp>

#include "crossplatform.hpp"
#include "util.hpp"
#include "Sequence.hpp"
#include "Consensus.hpp"
#include "ProbabilisticModel.hpp"

#include <iostream>
#include <string>
#include <vector>


using namespace std;


namespace tops {

  class MaximalDependenceDecompositionNode;
  typedef boost::shared_ptr<MaximalDependenceDecompositionNode> MaximalDependenceDecompositionNodePtr;

  class MaximalDependenceDecompositionNode {
  public:
    MaximalDependenceDecompositionNode(ProbabilisticModelPtr model, int index):_model(model), _index(index) {};

    int getIndex();
    ProbabilisticModelPtr getModel();

    void setChildern(MaximalDependenceDecompositionNodePtr left, MaximalDependenceDecompositionNodePtr right);
    MaximalDependenceDecompositionNodePtr getLeft();
    MaximalDependenceDecompositionNodePtr getRight();
  private:
    vector<int> _otherIndexes;
    ProbabilisticModelPtr _model;
    int _index;
    MaximalDependenceDecompositionNodePtr _left;
    MaximalDependenceDecompositionNodePtr _right;
  };

  class MaximalDependenceDecomposition : public ProbabilisticModel {
  public:
    MaximalDependenceDecomposition() {};
    void setMDDTree(MaximalDependenceDecompositionNodePtr root);
    void setConsensusSequence(ConsensusSequence consensus_sequence);

    virtual double evaluate(const Sequence & s, unsigned int begin, unsigned int end);

    virtual std::string model_name() const {
      return "MaximumDependenceDecomposition";
    }
  private:

    double _evaluateAux(const Sequence & s, MaximalDependenceDecompositionNodePtr node, vector<int> &indexes);

    MaximalDependenceDecompositionNodePtr _mdd_tree;
    ConsensusSequence _consensus_sequence;
  };

  typedef boost::shared_ptr<MaximalDependenceDecomposition> MaximalDependenceDecompositionPtr;
}

#endif
