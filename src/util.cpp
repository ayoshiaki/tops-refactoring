/*
 *       util.cpp
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

#include "util.hpp"
namespace tops {


  /* Epanechnikov kernel */
  double epanechnikov(double x, double h){
    double a = h * sqrt(5.0);
    double absx = fabs(x);
    if(absx < a ) {
      return (3.0/4.0) * (1.0 - (absx/a)*(absx/a))/a;
    } else {
      return 0.0;
    }
  }

  /* normal kernel */
  double kernel_normal(double x, double h){
      double y = (x/h) * (x/h) ;
      double f = 1.0/(sqrt(2*M_PI));
      double v =  (f/h) * exp (- y/2);
      return v;
  }


// code from R-1.7.0/src/appl/bandwidths.c
#define abs9(a) (a > 0 ? a:-a)
  void band_den_bin(int n, int nb, double *d, const DoubleVector &x,  DoubleVector &cnt)
  {
    int   i, j,  nn = n;
    int ii, jj, iij;
    double xmin, xmax, rang, dd;
    for (i = 0; i < nb; i++)
      cnt.push_back(0);
    xmin = xmax = x[0];
    for (i = 1; i < nn; i++) {
      xmin = _min(xmin, x[i]);
      xmax = _min(xmax, x[i]);
    }
    rang = (xmax - xmin) * 1.01;
    *d = dd = rang / (nb);
    for (i = 1; i < nn; i++) {
      ii = (int)(x[i] / dd);
      for (j = 0; j < i; j++) {
        jj = (int)(x[j] / dd);
        iij = abs9((ii - jj));
        cnt[iij]++;
      }
    }
  }
  void band_phi6_bin(int n, int nb, double d, DoubleVector &x, double h, double *u)
  {
    int   i, nn = n, nbin = nb;
    double delta, sum, term;
    sum = 0.0;
    for (i = 0; i < nbin; i++) {
      delta = i * (d) / (h);
      delta *= delta;
      if (delta >= 1000) break;
      term = exp(-delta / 2) *
        (delta * delta * delta - 15 * delta * delta + 45 * delta - 15);
      sum += term * x[i];
    }
    sum = 2 * sum - 15 * nn;    /* add in diagonal */
    *u = sum / (nn * (nn - 1) * pow(h, 7.0) * sqrt(2 * M_PI));
  }
  void
  band_phi4_bin(int n, int nb, double d, DoubleVector x, double h, double *u)
  {
    int   i, nn = n, nbin = nb;
    double delta, sum, term;

    sum = 0.0;
    for (i = 0; i < nbin; i++) {
      delta = i * (d) / (h);
      delta *= delta;
      if (delta >= 1000) break;
      term = exp(-delta / 2) * (delta * delta - 6 * delta + 3);
      sum += term * x[i];
    }
    sum = 2 * sum + nn * 3;     /* add in diagonal */
    *u = sum / (nn * (nn - 1) * pow(h, 5.0) * sqrt(2 * M_PI));
  }


  double mean(const DoubleVector &data){
    double sum = 0.0;
    for(unsigned int i = 0; i < data.size(); i++){
      sum += data[i];
    }
    return sum/(double)data.size();
  }

  double var(const DoubleVector &data){
    double data_mean = mean(data);
    double sum = 0.0;
    for(unsigned int i = 0; i < data.size(); i++){
      sum += (data[i] - data_mean)*(data[i] - data_mean);
    }
    return sum/( (double) data.size() -1.0);
  }

  /* quantile */
  double quantile (DoubleVector data, double q){
    int low_index = (int)floor(q * ((double)data.size()-1));
    int high_index = (int)ceil(q * ((double)data.size()-1));
    double h =  q * ((double)data.size() -1) - (double)low_index;
    sort(data.begin(), data.end());
    return (1-h)*data[low_index] + h * data[high_index];
  }

  /* interquantile */
  double iqr (const DoubleVector &data){
    double q1=  quantile(data, 0.25);
    double q2 = quantile(data, 0.75);
    return q2 - q1;
  }



  void readSequencesFromFile(SequenceEntryList & s,
                             AlphabetPtr alphabet,
                             std::string  file_name)
  {
    std::ifstream input(file_name.c_str());
    if(!input.good())
      {
        std::cerr << "Can not open file " << file_name << std::endl;
        exit(-1);
      }
    while(!input.eof())
      {
        SequenceEntryPtr  inseq = SequenceEntryPtr(new SequenceEntry(alphabet));
        input >> *inseq;
     //   if((inseq->getSequence()).size() > 0)
        if (inseq->getName().size() > 0)
          s.push_back(inseq);
      }
    input.close();
  }

  void readSequencesFromFile(SequenceList & s,
                             AlphabetPtr alphabet,
                             std::string  file_name)
  {
    std::ifstream input(file_name.c_str());
    if(!input.good())
      {
        std::cerr << "Can not open file " << file_name << std::endl;
        exit(-1);
      }
    while(!input.eof())
      {
        SequenceEntry  inseq(alphabet);
        input >> inseq;
        //   if((inseq.getSequence()).size() > 0)
        if (inseq.getName().size() > 0)
          s.push_back(inseq.getSequence());
      }
    input.close();
  }

  void readMapFromFile(std::map<std::string, double> & s,
                       std::string  file_name)
  {
    std::ifstream input(file_name.c_str());
    if(!input.good())
      {
        std::cerr << "Can not open file " << file_name << std::endl;
        exit(-1);
      }
    std::string line;
    while(!input.eof())
      {
        std::getline(input, line, '\n');
        std::vector <std::string> x;
        boost::regex separator("\t");
        split_regex(line, x, separator);
        if(x.size() >= 2) {
          std::string key = x[0];
          int value = atof((x[1]).c_str());
          s[key] = value;
        }
      }
    input.close();
  }



  int mod(int D, int d) {
    int r = D%d;
    if (r < 0) {
      if (d > 0) r = r + d;
      else r = r - d;
    }
    return r;
  }

  void trim_spaces (std::string & s) {
    int k;
    for(k = s.size() - 1; k >= 0; k--)
      {
        if(!isspace(s[k]))
          break;
      }
    s = s.substr(0, k+1);
    for(k = 0; k < (int)(s.size()); k++)
      {
        if(!isspace(s[k]))
          break;
      }
    s = s.substr(k, (s.size()) - k);
  }
  void split_regex (const std::string & s, std::vector <std::string> & result, const boost::regex & re)
  {
    boost::sregex_token_iterator i(s.begin(), s.end(), re, -1);
    boost::sregex_token_iterator j;
    while(i != j)
      result.push_back(*i++);
  }

  double lookup (double x){
    assert (x >= 0.00f);
    assert (x <= 7.5);
    //return ((-0.00653779113685f * x + 0.09537236626558f) * x + 0.55317574459331f) * x + 0.68672959851568f;
    if (x <= 1.00f) return ((-0.009350833524763f * x + 0.130659527668286f) * x + 0.498799810682272f) * x + 0.693203116424741f;
    if (x <= 2.50f) return ((-0.014532321752540f * x + 0.139942324101744f) * x + 0.495635523139337f) * x + 0.692140569840976f;
    if (x <= 4.50f) return ((-0.004605031767994f * x + 0.063427417320019f) * x + 0.695956496475118f) * x + 0.514272634594009f;
    assert (x <= 7.5);
    return ((-0.000458661602210f * x + 0.009695946122598f) * x + 0.930734667215156f) * x + 0.168037164329057f;
    
    //return (((0.00089738532761f * x - 0.01859488697982f) * x + 0.14415772028626f) * x + 0.49515490689159f) * x + 0.69311928966454f;
  }

  double log_sum (double x, double y){
    if (x < y) return (x <= -2e20 || y - x >= 7.5) ? y : lookup(y-x) + x;
    return (y <= -2e20 || x - y >= 7.5) ? x : lookup(x-y) + y;
  }


  double log_sum_2( double log_a, double log_b)
  {
    double min = log_a;
    double diff;
    if(min > log_b)
      {
        diff = log_b - log_a;
        if(diff != diff)
          return log_a;
        return log_a + log(1 + exp(diff));
      }
    else
      {
        diff = log_a - log_b;
        if(diff != diff)
          return log_b;
	return log_b + log(1 + exp(diff));
      }
   }


  double safe_division(double a, double b)
  {
    if((b < 1) && (a > b * (std::numeric_limits<double>::max)()))
      {
        return (std::numeric_limits<double>::max)();
      }
    else if (((b > 1) && (a < b*(std::numeric_limits<double>::min)()) )|| (a == 0))
      {
        return 0;
      }
    else
      {
        return a/b;
      }

  }


  bool close(double a, double b, double tolerance)
  {
    double diff = fabs(a-b);

    double div1 = safe_division(diff, fabs(a));
    double div2 = safe_division(diff, fabs(b));
    if( (div1 <= tolerance) && (div2 <= tolerance))
      {
        return true;
      }
    return false;
  }




  double kernel_density_estimation(double x, double bw, const DoubleVector &data){
    double result = 0.0;
    for(unsigned int i = 0; i < data.size(); i++) {
      double x_xi = (double)(x) - (double)data[i];
      result += epanechnikov(x_xi, bw);
    }
    result /= data.size();
    return result;
  }


  double kernel_density_estimation_gaussian(double x, double bw, const DoubleVector &data){
    double result = 0.0;
    for(unsigned int i = 0; i < data.size(); i++) {
      double x_xi = (double)(x) - (double)data[i];
      double y = (x_xi / bw);
      result += 1/sqrt(2*M_PI) * exp( -y*y/2) ;
    }
    result /= data.size()*bw;
    return result;
  }

  double sj_bandwidth(const DoubleVector &data){
    double n = (double) data.size();
    int nb = 1000;
    double d = 1.0;
    double variance =  var(data);
  DoubleVector count;
  band_den_bin ((int)n, nb, &d, data, count);
  double scale = _min(std::sqrt(variance), iqr(data)/1.349);
  double b = 1.23 * scale * pow(n, (-1.0/9.0));
  double c1 = 1.0 / (2.0*sqrt(M_PI) * n);
  double td;
  band_phi6_bin((int)n, (int)count.size(), d, count, b, &td);
  td = -td;
  if(td < 0 || td != td){
    //    cerr << "sj_bandwidth (WARNING). Dataset very sparse !!!\n" << endl;
    return 0.001;
  }
  double sdh ;
  band_phi4_bin((int)n, (int)count.size(), d, count, pow(2.394/(n*td), (1.0/7.0)), &sdh);
  return pow((c1/sdh), 1.0/5.0);
  }


  /*========*/


}
