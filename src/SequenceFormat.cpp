/*
 *       SequenceFormat.cpp
 *
 *       Copyright 2011 Andre Yoshiaki Kashiwabara <akashiwabara@usp.br>
 *                      �gor Bon�dio <ibonadio@ime.usp.br>
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

#include "SequenceFormat.hpp"
#include "SequenceEntry.hpp"
#include "SequenceFactory.hpp"
#include "util.hpp"
#include "Alphabet.hpp"
#include "Symbol.hpp"
#include <stdlib.h>
#include <sys/types.h>



namespace tops {

  std::ostream & SequenceFormat::saveSequence (std::ostream & stream, SequenceEntry & out){
    stream << out.getName() << ":\t" ;
    if((out.getAlphabet())->size() > 0)
      for(int i = 0; i < (int)out.getSequence().size(); i+=1){
          stream << (out.getAlphabet())->getSymbol((out.getSequence())[i])->name() << out.getSeparator();
      }
    else
      for(int i = 0; i < (int)out.getSequence().size(); i+=1){
        stream << (out.getSequence())[i] << out.getSeparator();
      }
    stream << std::endl;
    return stream;

  }
  std::istream & SequenceFormat::readSequence (std::istream & stream, SequenceEntry & in) {
    std::string line;
    std::string header;
    std::string sequence;
    SequenceFactory factory(in.getAlphabet());
    in.getSequence() = factory.createSequence(sequence);

    if(stream.bad()){
      return stream;
    }
    while(!stream.eof()){
      getline(stream,line,'\n');

      // Ignores blank lines
      unsigned int i;
      for(i = 0; i < line.length();  i++)
        if(!isspace(line[i]) && line[i] != '\n'){
          break;
        }
      if(line[i] == '\0'){
        continue;
      }
      trim_spaces(line);

      std::vector<std::string> seq_entry;
      boost::regex separator(":");
      split_regex(line, seq_entry, separator);
      if(seq_entry.size() < 2)
        {
          std::cerr << "Warning: Invalid or empty sequence !" << std::endl;
          //exit(-1);
        }
      std::string seqname = "";
      int last = seq_entry.size()-1;
      if(seq_entry.size() >= 2)
          {
              seqname = seq_entry[0];
          }

      boost::regex sep(" ");
      in.setName( seqname);
      std::string description;
      trim_spaces(seq_entry[last]);
      std::vector<int> invalid;
      in.setSequence(factory.createSequence(seq_entry[last], invalid));
      in.setInvalidPositions(invalid);
      return stream;
    }
    return stream;
  }
  std::ostream & FastaSequenceFormat::saveSequence (std::ostream & stream, SequenceEntry & out)
  {
    stream << ">" << out.getName() << std::endl;
    if((out.getAlphabet())->size() > 0)
      for(int i = 0; i < (int)out.getSequence().size(); i+=1){
        stream << (out.getAlphabet())->getSymbol((out.getSequence())[i])->name() ;
      }
    else
      for(int i = 0; i < (int)out.getSequence().size(); i+=1)
        stream << (out.getSequence())[i] << out.getSeparator();
    stream << std::endl;
    return stream;
  }
  std::istream & FastaSequenceFormat::readSequence (std::istream & stream, SequenceEntry & in)
  {
    std::string line;
    std::string sequence ;
    bool firstSeq = true;
    if(_nextFastaHeader.length() > 0) {
      _currentFastaHeader = _nextFastaHeader;
      firstSeq = false;
    }
    while (!stream.eof()) {
      if(!std::getline(stream, line, '\n'))
         continue;
      unsigned int i;
      for (i = 0; i < line.length(); i++)
        if(!isspace(line[i]) && (line[i] != '\n'))
          break;
      if(line.length() <= 0 || i == line.length())
        continue;

      if(line[0] == '>') {
        if(firstSeq == true){
          _currentFastaHeader = line;
          firstSeq =false;
          continue;
        }
        else {
          _nextFastaHeader = line;
          break;
        }
      }
      sequence += line;
    }
    int j = 0;
    for (int i = 0; i < (int)sequence.length(); i++)
      {
        if(isspace(sequence[i]) || (sequence[i] == '\n') )
           continue;
        sequence[j] = sequence[i];
        j++;
      }
    sequence = sequence.substr(0,j);
    if(sequence.length () <= 0)
        return stream;

    SequenceFactory factory(in.getAlphabet());
    trim_spaces(sequence);
    std::vector <int> invalid;
    in.setSequence(factory.createSequenceRemovedSpaces(sequence, invalid));
    in.setInvalidPositions(invalid);
    boost::regex sep(" ");
    std::vector <std::string> name_and_description;
    split_regex(_currentFastaHeader, name_and_description, sep);

    in.setName( name_and_description[0].substr(1, name_and_description[0].length()-1));
    std::string description;
    for(int i = 1; i < (int)name_and_description.size(); i++)
      description += name_and_description[i];
    in.setDescription ( description );

    return stream;
  }

  SequenceFormatManagerPtr SequenceFormatManager::_inst ;
  SequenceFormatManagerPtr SequenceFormatManager::instance() {
    if(!_inst) {
      _inst = SequenceFormatManagerPtr(new SequenceFormatManager());
    }
    return _inst;
  }
}
