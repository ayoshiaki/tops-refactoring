/*
 *       TrainPhasedMarkovChain.cpp
 *
 *       Copyright 2011 Andre Yoshiaki Kashiwabara <akashiwabara@usp.br>
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

/*
 * TrainPhasedMarkovChain.cpp
 *
 *  Created on: 4/Mai/2009
 *      Author: yoshiaki
 */
#include "ContextTree.hpp"
#include "TrainPhasedMarkovChain.hpp"
#include "InhomogeneousMarkovChain.hpp"
#include "ProbabilisticModelParameter.hpp"
#include "ProbabilisticModelCreatorClient.hpp"
namespace tops {

ProbabilisticModelPtr TrainPhasedMarkovChain::create(
                ProbabilisticModelParameters & parameters, double & loglikelihood,
                int & sample_size) const {
        ProbabilisticModelParameterValuePtr alphabetpar =
                        parameters.getMandatoryParameterValue("alphabet");
        ProbabilisticModelParameterValuePtr trainingsetpar =
                        parameters.getMandatoryParameterValue("training_set");
        ProbabilisticModelParameterValuePtr orderpar =
                        parameters.getMandatoryParameterValue("order");
        ProbabilisticModelParameterValuePtr number_of_phasespar =
          parameters.getMandatoryParameterValue("number_of_phases");
    ProbabilisticModelParameterValuePtr pseudocountspar = parameters.getOptionalParameterValue("pseudo_counts");
        ProbabilisticModelParameterValuePtr aprioripar = parameters.getOptionalParameterValue("apriori");
	ProbabilisticModelParameterValuePtr weightspar = parameters.getOptionalParameterValue("weights");
	std::map <std::string, double> weights;
	if(weightspar != NULL) {
	  readMapFromFile(weights, weightspar->getString());
	}

    double pseudocounts = 0;
    if(pseudocountspar != NULL)
        pseudocounts = pseudocountspar->getDouble();
    ProbabilisticModelPtr apriori;
    if(aprioripar != NULL)
        {
            ProbabilisticModelCreatorClient c;
            apriori = c.create(aprioripar->getString());
        }




        if ((alphabetpar == NULL) || (trainingsetpar == NULL)
            || (orderpar == NULL) || (number_of_phasespar == NULL)) {
          std::cerr << help() << std::endl;
          exit(-1);
        }
        AlphabetPtr alphabet = AlphabetPtr(new Alphabet());
        alphabet->initializeFromVector(alphabetpar ->getStringVector());
        SequenceEntryList sample_set;
        readSequencesFromFile(sample_set, alphabet, trainingsetpar->getString());
        int order = orderpar->getInt();
        int length = number_of_phasespar->getInt() ;
        std::vector<ContextTreePtr> positional_distribution;
        positional_distribution.resize(length);
        sample_size = 0;

        for (int i = 0; i < length; i++) {
                SequenceEntryList positionalSample;
                for(int j = 0; j < (int)sample_set.size(); j++)
                {
                  int nseq = 0;
                  while(true)
                    {
                      int start = (length) * nseq - order + i;
                      if(start < 0) {
                        nseq++;
                        continue;
                      }
                      int end = (length) * nseq + i;
                      if(end >= (int)(sample_set[j]->getSequence()).size())
                        break;
                      Sequence s;
                      for(int k = start; k <= end; k++)
                        s.push_back((sample_set[j]->getSequence())[k]);
                      SequenceEntryPtr entry = SequenceEntryPtr (new SequenceEntry(alphabet));
                      entry->setSequence(s);
                      positionalSample.push_back(entry);
                      nseq++;
                    }
                }
                ContextTreePtr tree = ContextTreePtr(new ContextTree(alphabet));

                if(apriori != NULL){
		  tree->initializeCounter(sample_set, orderpar->getInt(), 0, weights);
                    tree->normalize(apriori, pseudocounts, i);
                } else {

		  tree->initializeCounter(sample_set, orderpar->getInt(), pseudocounts, weights);
                    tree->normalize();
                }



                positional_distribution[i] = tree;

        }
        InhomogeneousMarkovChainPtr model = InhomogeneousMarkovChainPtr(
                        new InhomogeneousMarkovChain());
        model->setPositionSpecificDistribution(positional_distribution);
        model->phased(1);
        model->setAlphabet(alphabet);
        loglikelihood = 0.0;

        for (int j = 0; j < (int) sample_set.size(); j++) {
          sample_size += (sample_set[j]->getSequence()).size();

          loglikelihood += model->evaluate((sample_set[j]->getSequence()), 0, (sample_set[j]->getSequence()).size()
                                - 1);
        }
        return model;

}
ProbabilisticModelPtr TrainPhasedMarkovChain::create(
                ProbabilisticModelParameters & parameters) const {
        int size;
        double loglikelihood;
        return create(parameters, loglikelihood, size);
}
}

