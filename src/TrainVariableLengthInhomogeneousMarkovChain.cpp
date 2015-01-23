/*
 *       TrainVariableLengthInhomogeneousMarkovChain.cpp
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

#include "ContextTree.hpp"
#include "TrainVariableLengthInhomogeneousMarkovChain.hpp"
#include "InhomogeneousMarkovChain.hpp"
#include "ProbabilisticModelParameter.hpp"
namespace tops {

ProbabilisticModelPtr TrainVariableLengthInhomogeneousMarkovChain::create(
                ProbabilisticModelParameters & parameters, double & loglikelihood,
                int & sample_size) const {
        ProbabilisticModelParameterValuePtr alphabetpar =
                        parameters.getMandatoryParameterValue("alphabet");
        ProbabilisticModelParameterValuePtr trainingsetpar =
                        parameters.getMandatoryParameterValue("training_set");
        ProbabilisticModelParameterValuePtr cutpar =
                        parameters.getMandatoryParameterValue("cut");
        ProbabilisticModelParameterValuePtr lengthpar =
                        parameters.getMandatoryParameterValue("length");
        ProbabilisticModelParameterValuePtr phasedpar =
                        parameters.getMandatoryParameterValue("phased");

        if ((alphabetpar == NULL) || (trainingsetpar == NULL)
            || (lengthpar == NULL) || (cutpar == NULL) || (phasedpar == NULL)) {
                std::cerr << help() << std::endl;
                exit(-1);
        }
        AlphabetPtr alphabet = AlphabetPtr(new Alphabet());
        alphabet->initializeFromVector(alphabetpar ->getStringVector());
        SequenceEntryList sample_set;
        readSequencesFromFile(sample_set, alphabet, trainingsetpar->getString());
        std::vector<std::string> cuts = cutpar->getStringVector();
        int length = lengthpar->getInt();
        std::vector<ContextTreePtr> positional_distribution;
        int phased = phasedpar->getInt();
        positional_distribution.resize(length);
        sample_size = 0;
        if ((int) cuts.size() < length) {
                std::cerr
                                << "ERROR: The number of cuts is smaller than the sequence length "
                                << std::endl;
                exit(-1);
        }


        for (int i = 0; i < length; i++) {
                SequenceEntryList positionalSample;
                int o = i;
                for (int j = 0; j < (int) sample_set.size(); j++) {
                        if(!phased) {
                          Sequence s;
                          s.resize(o + 1);
                          int l = 0;
                          int m = i - o;
                          if (m < 0)
                            m = 0;

                          while ((m < (int) (sample_set[j]->getSequence()).size()) && (l <= o)) {
                            s[l] = (sample_set[j]->getSequence())[m];
                            l++;
                            m++;
                          }
                          SequenceEntryPtr entry = SequenceEntryPtr (new SequenceEntry(alphabet));
                          entry->setSequence(s);
                          positionalSample.push_back(entry);
                        } else {
                          o = int(log( (double) (sample_set[j]->getSequence()).size()));
                          int m = i - o;
                          if(m < 0) { m = 0; o = o -i;}
                          int last_m = m;
                          while((m < (int) (sample_set[j]->getSequence()).size())) {
                            Sequence s;
                            s.resize(o+1);
                            int l = 0;
                            while ((m < (int) (sample_set[j]->getSequence()).size()) && (l <= o)) {
                              s[l] = (sample_set[j]->getSequence())[m];
                              l++;
                              m++;
                            }
                            m = last_m + length;
                            last_m = m;
                            SequenceEntryPtr entry = SequenceEntryPtr (new SequenceEntry(alphabet));
                            entry->setSequence(s);
                            positionalSample.push_back(entry);
                          }
                        }
                }
                ProbabilisticModelParameterValuePtr c = parameters.getOptionalParameterValue(cuts[i]);
                if(c == NULL){
                  std::cerr << "Undefined cut value for " << cuts[i] << std::endl;
                  exit(-1);
                }
                double delta =
                                (parameters.getOptionalParameterValue(cuts[i]))->getDouble();
                ContextTreePtr tree = ContextTreePtr(new ContextTree(alphabet));
                tree->initializeContextTreeRissanen(positionalSample);
                tree->pruneTree(delta);
                tree->removeContextNotUsed();
                tree->normalize();
                positional_distribution[i] = tree;
        }
        InhomogeneousMarkovChainPtr model = InhomogeneousMarkovChainPtr(new InhomogeneousMarkovChain());
        model->setPositionSpecificDistribution(positional_distribution);
        model->phased(0);
        model->setAlphabet(alphabet);
        model->phased(phased);
        loglikelihood = 0.0;

        for (int j = 0; j < (int) sample_set.size(); j++) {
          sample_size += (sample_set[j]->getSequence()).size();
          loglikelihood += model->evaluate((sample_set[j]->getSequence()), 0, (sample_set[j]->getSequence()).size()
                                           - 1);
        }
        return model;

}
ProbabilisticModelPtr TrainVariableLengthInhomogeneousMarkovChain::create(
                ProbabilisticModelParameters & parameters) const {
        int size;
        double loglikelihood;
        return create(parameters, loglikelihood, size);
}
}
