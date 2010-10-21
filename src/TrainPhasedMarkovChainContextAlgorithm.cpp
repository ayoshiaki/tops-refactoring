/*
 * TrainPhasedMarkovChain.cpp
 *
 *  Created on: 4/Mai/2009
 *      Author: yoshiaki
 */
#include "ContextTree.hpp"
#include "TrainPhasedMarkovChainContextAlgorithm.hpp"
#include "InhomogeneousMarkovChain.hpp"
#include "ProbabilisticModelParameter.hpp"
namespace tops {

ProbabilisticModelPtr TrainPhasedMarkovChainContextAlgorithm::create(
		ProbabilisticModelParameters & parameters, double & loglikelihood,
		int & sample_size) const {
	ProbabilisticModelParameterValuePtr alphabetpar =
			parameters.getMandatoryParameterValue("alphabet");
	ProbabilisticModelParameterValuePtr trainingsetpar =
			parameters.getMandatoryParameterValue("training_set");
	ProbabilisticModelParameterValuePtr cutpar =
			parameters.getMandatoryParameterValue("cut");

	ProbabilisticModelParameterValuePtr number_of_phasespar =
	  parameters.getMandatoryParameterValue("number_of_phases");
	
	if ((alphabetpar == NULL) || (trainingsetpar == NULL)
	    || (number_of_phasespar == NULL)
	    || (cutpar == NULL)) {
	  std::cerr << help() << std::endl;
	  exit(-1);
	}
	AlphabetPtr alphabet = AlphabetPtr(new Alphabet());
	alphabet->initializeFromVector(alphabetpar ->getStringVector());
	SequenceEntryList sample_set;
	readSequencesFromFile(sample_set, alphabet, trainingsetpar->getString());
	int length = number_of_phasespar->getInt() ;
	std::vector<ContextTreePtr> positional_distribution;
	positional_distribution.resize(length);
	sample_size = 0;
	std::vector <std::string> cut = cutpar->getStringVector();
	if((int) cut.size() < length) {
	  std::cerr << "ERROR: The number of cut values  is smaller than the sequence length " << std::endl;
	  exit(-1);
	}

	for (int i = 0; i < length; i++) {
		SequenceEntryList positionalSample;
		for(int j = 0; j < (int)sample_set.size(); j++)
		{
		  int nseq = 0;
		  int order = j;
		  if(order > 10)
		    order = 10;
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
		      SequenceEntryPtr entry = SequenceEntryPtr(new SequenceEntry(alphabet));
		      entry->setSequence(s);
		      positionalSample.push_back(entry);
		      nseq++;
		    }
		}
		double delta = (parameters.getOptionalParameterValue(cut[i])->getDouble());
		ContextTreePtr tree = ContextTreePtr(new ContextTree(alphabet));
		tree->initializeContextTreeRissanen(positionalSample);
		tree->pruneTree(delta);
		tree->removeContextNotUsed();
		tree->normalize();
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
ProbabilisticModelPtr TrainPhasedMarkovChainContextAlgorithm::create(
		ProbabilisticModelParameters & parameters) const {
	int size;
	double loglikelihood;
	return create(parameters, loglikelihood, size);
}
}

