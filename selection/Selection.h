#ifndef __SELECTION_H__
#define __SELECTION_H__

#include <TCanvas.h>
#include <TSystem.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include "TLorentzVector.h"
#include <iostream>
#include <TMath.h>
#include <math.h> 
#include <sstream>
#include <fstream>
#include <TLegend.h>
#include <TString.h>
#include <vector>
#include <map>
#include <dirent.h>
#include <sys/stat.h>
#include "Converter.h"
#include <time.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include <json/value.h>

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"


void Selection(std::string infilename, std::string outfilename, std::string config, std::string triggerfile, Int_t nevents = -1, Int_t firstevt = -1, Int_t lastevt = -1, std::string JESsyst = "central", std::string JERsyst = "central");

std::vector<TString> listfiles(TString indir);
bool DirExists(TString indir);
std::vector<std::string> split(const std::string &s, char delim);
std::string GetOutputFileName(std::string output);






#endif
