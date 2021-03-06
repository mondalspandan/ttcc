#include "Selection.h"
#include "TSystem.h"




using namespace std;

void Selection(std::string infiledirectory, std::string outfilepath, std::string config, std::string triggerfile, Int_t nevents, Int_t firstevt, Int_t lastevt, std::string JESsyst, std::string JERsyst){

    EffectiveAreas* effectiveAreas_ = new EffectiveAreas("/user/smoortga/Analysis/2017/ttcc_Analysis/CMSSW_8_0_25/src/ttcc/selection/config/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt");
    
    std::string JESsyst_ = JESsyst;
    std::string JERsyst_ = JERsyst;

    if (JESsyst != "central" && JESsyst != "Up" && JESsyst != "Down"){
        std::cout << "WARNING: JES systematic variation should either be central, Up or Down! using central as default here" << std::endl;
        JESsyst_ = "central";
    }
    if(JERsyst != "central" && JERsyst != "Up" && JERsyst != "Down"){
        std::cout << "WARNING: JER systematic variation should either be central, Up or Down! using central as default here" << std::endl;
        JERsyst_ = "central";
    }

    // Input files
    std::string filename = GetOutputFileName(outfilepath);
    // see whether the file is data and whether it was ttbar MC
    // IMPORTANT NOTE: the output filename is tested here, so it should be the same as the input!!!
    // This probably needs to be fixed!
    bool isdata_ = false;
    if (filename.find("Run20") != string::npos){ isdata_ = true;}
    TString infiledir(infiledirectory);
    TString outfilename(outfilepath);
    TChain *superTree = new TChain("FlatTree/tree");
    vector<TString> filenames = listfiles(infiledir);
    vector<TString> processed_filenames;
    // Add all the files in the directory until nevents is reached
    for (vector<TString>::iterator it = filenames.begin(); it != filenames.end(); it++){
        std::cout << (*it) << std::endl;
        if (!(*it).BeginsWith("output_")){continue;}
        //TFile * f_ = TFile::Open(infiledir+"/"+(*it));
        //superTree->Add(infiledir+"output_*.root");
        superTree->Add(infiledir+"/"+(*it));
        processed_filenames.push_back((*it));
        if (nevents > 0 && superTree->GetEntries() > nevents) {break;}
    }
    Int_t nEntries = superTree->GetEntries();
    if (nevents > 0 && nevents < nEntries){nEntries = nevents;}
    Int_t events_this_job;
    if (lastevt > firstevt){
        events_this_job = lastevt-firstevt;
    }
    else{
        events_this_job = nEntries;
        firstevt = 0;
        lastevt = nEntries;
    }
    std::cout << "The tree " + filename +" has " << nEntries << " Events" << std::endl;
    std::cout << "This job will process events " << firstevt << " to " << lastevt-1 << " (" << (lastevt - firstevt) << " Events in total)" << std::endl;
    
    
    
    // read in the config
    boost::property_tree::ptree ptree;
    boost::property_tree::ini_parser::read_ini(config, ptree);
    int nmuon_min = ptree.get<int>("muon.n_min");
    int nmuon_max = ptree.get<int>("muon.n_max");
    float muon_pt_min = ptree.get<float>("muon.pt_min");
    float muon_pt_max = ptree.get<float>("muon.pt_max");
    float muon_abseta_min = ptree.get<float>("muon.abseta_min");
    float muon_abseta_max = ptree.get<float>("muon.abseta_max");
    float muon_reliso_max = ptree.get<float>("muon.reliso_max");
    
    int nelectron_min = ptree.get<int>("electron.n_min");
    int nelectron_max = ptree.get<int>("electron.n_max");
    float electron_pt_min = ptree.get<float>("electron.pt_min");
    float electron_pt_max = ptree.get<float>("electron.pt_max");
    float electron_abseta_min = ptree.get<float>("electron.abseta_min");
    float electron_abseta_max = ptree.get<float>("electron.abseta_max");
    float electron_reliso_max = ptree.get<float>("electron.reliso_max");
    
    int nlepton_min = ptree.get<int>("lepton.n_min");
    int nlepton_max = ptree.get<int>("lepton.n_max");
    
    int njet_min = ptree.get<int>("jet.n_min");
    int njet_max = ptree.get<int>("jet.n_max");
    float jet_pt_min = ptree.get<float>("jet.pt_min");
    float jet_pt_max = ptree.get<float>("jet.pt_max");
    float jet_abseta_min = ptree.get<float>("jet.abseta_min");
    float jet_abseta_max = ptree.get<float>("jet.abseta_max");
    
    float met_pt_min = ptree.get<float>("met.pt_min");
    float met_pt_max = ptree.get<float>("met.pt_max");
    
    // Get trigger names from text file
    //boost::property_tree::ptree ptree_trigger;
    std::ifstream stream_trigger;
    stream_trigger.open(triggerfile);
    std::vector<std::string> trigger_names_v;
    std::string line;
    if (stream_trigger.is_open()) {
        while (!stream_trigger.eof()) {
            std::getline(stream_trigger,line);
            trigger_names_v.push_back(line);
        }
    }
    
    
    // Setting address for those branches
    float met_pt = 0;
    float ev_rho = 0;
    
    int el_n = 0;
    std::vector<float> * el_pt = 0;
    std::vector<float> * el_eta = 0;
    std::vector<float> * el_scleta = 0;
    std::vector<float> * el_phi = 0;
    std::vector<int> * el_charge = 0;
    std::vector<float> * el_pfIso_sumChargedHadronPt = 0;
    std::vector<float> * el_pfIso_sumNeutralHadronEt = 0;
    std::vector<float> * el_pfIso_sumPhotonEt = 0;
    
    int mu_n = 0;
    std::vector<float> * mu_pt = 0;
    std::vector<float> * mu_eta = 0;
    std::vector<float> * mu_phi = 0;
    std::vector<int> * mu_charge = 0;
    std::vector<float> * mu_pfIso04_sumChargedHadronPt = 0;
    std::vector<float> * mu_pfIso04_sumNeutralHadronEt = 0;
    std::vector<float> * mu_pfIso04_sumPhotonEt = 0;
    std::vector<float> * mu_pfIso04_sumPUPt = 0;

    int jet_n = 0;
    std::vector<float> * jet_pt = 0;
    std::vector<float> * jet_eta = 0;
    std::vector<float> * jet_phi = 0;
    
    std::vector<std::string> * trigger_name = 0;
    std::vector<bool> * trigger_pass = 0;
    std::vector<int> trigger_indices;

    
    
    superTree->SetBranchAddress("met_pt",&met_pt);
    superTree->SetBranchAddress("ev_rho",&ev_rho);
    
    superTree->SetBranchAddress("el_n",&el_n);
    superTree->SetBranchAddress("el_pt",&el_pt);
    superTree->SetBranchAddress("el_eta",&el_eta);
    superTree->SetBranchAddress("el_superCluster_eta",&el_scleta);
    superTree->SetBranchAddress("el_phi",&el_phi);
    superTree->SetBranchAddress("el_charge",&el_charge);
    superTree->SetBranchAddress("el_pfIso_sumChargedHadronPt",&el_pfIso_sumChargedHadronPt);
    superTree->SetBranchAddress("el_pfIso_sumNeutralHadronEt",&el_pfIso_sumNeutralHadronEt);
    superTree->SetBranchAddress("el_pfIso_sumPhotonEt",&el_pfIso_sumPhotonEt);
    
    superTree->SetBranchAddress("mu_n",&mu_n);
    superTree->SetBranchAddress("mu_pt",&mu_pt);
    superTree->SetBranchAddress("mu_eta",&mu_eta);
    superTree->SetBranchAddress("mu_phi",&mu_phi);
    superTree->SetBranchAddress("mu_charge",&mu_charge);
    superTree->SetBranchAddress("mu_pfIso04_sumChargedHadronPt",&mu_pfIso04_sumChargedHadronPt);
    superTree->SetBranchAddress("mu_pfIso04_sumNeutralHadronEt",&mu_pfIso04_sumNeutralHadronEt);
    superTree->SetBranchAddress("mu_pfIso04_sumPhotonEt",&mu_pfIso04_sumPhotonEt);
    superTree->SetBranchAddress("mu_pfIso04_sumPUPt",&mu_pfIso04_sumPUPt);
    
    
    superTree->SetBranchAddress("jet_n",&jet_n);
    superTree->SetBranchAddress("jet_pt",&jet_pt);
    superTree->SetBranchAddress("jet_eta",&jet_eta);
    superTree->SetBranchAddress("jet_phi",&jet_phi);
    
    superTree->SetBranchAddress("trigger_name",&trigger_name);
    superTree->SetBranchAddress("trigger_pass",&trigger_pass);
    
    // Output Files
    TString outfiledir = TString(outfilename);
    outfiledir.Remove(outfilename.Last('/'));
    //std::cout << outfiledir << std::endl;
    //std::cout << outfilename << std::endl;
    if (!DirExists(outfiledir)){mkdir(outfiledir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);}
    TFile* outfile = new TFile(outfilename,"RECREATE");
    TTree* outtree = (TTree*)superTree->CloneTree(0);

    // Loop over events
    time_t timer_start;
    time_t timer_end;
    timer_start = time(NULL);
    for (Int_t iEvt = firstevt; iEvt < lastevt; iEvt++){
        
        if (events_this_job >= 20){ // Only use the counting for at least 20 events, otherwise it does not make much sense
            if ((iEvt-firstevt) % (Int_t)round(events_this_job/20.) == 0){std::cout << filename + ": Processing event " << iEvt << "/" << nEntries << " (" << round(100.*(iEvt-firstevt)/(float)events_this_job) << " %)" << std::endl;} //
        }
        superTree->GetEntry(iEvt);
        
        
        //****************************************************
        //
        // TRIGGER SELECTION 
        //
        //****************************************************
         
         
         // test code to print out all triggers in the sample
         // if (iEvt == 0){
//              for (int Idx = 0; Idx < trigger_name->size(); Idx++){
//                 std::cout << trigger_name->at(Idx) << std::endl;
//              }
//          }
         // comment this part above out!!!
         
         
        // On the first event, identify the trigger bits corresponding to the desired triggers
        if (iEvt == firstevt){
            std::cout << "************* STARTING TRIGGER SELECTION ******************" << std::endl;
            for (vector<std::string>::iterator it = trigger_names_v.begin(); it != trigger_names_v.end(); it++){
                std::string current_trig= (*it);
                if (current_trig.size() == 0){continue;}
                if ((*it).find("*") != std::string::npos){
                    (*it).pop_back();
                }
                bool found_match = false; 
                for (int Idx = 0; Idx < trigger_name->size(); Idx++){
                    if ((trigger_name->at(Idx)).find(*it) != std::string::npos ){
                        trigger_indices.push_back(Idx);
                        found_match = true;  
                    }
                }
                if (!found_match){
                    std::cout << "NO MATCHING TRIGGER WAS FOUND FOR " << (*it) << std::endl; 
                }
            }
            std::cout << "************* SELECTED TRIGGERS SUMMARY ******************" << std::endl;
            if (trigger_indices.size() == 0){
                std::cout << "NO TRIGGERS WERE SELECTED! AND THEREFORE NO EVENTS WILL BE SELECTED EITHER" << std::endl;
            }
            for (int Idx = 0; Idx < trigger_indices.size(); Idx++){
              std::cout <<  trigger_name->at(trigger_indices.at(Idx)) << std::endl;
            }
            std::cout << "**********************************************************" << std::endl;
        }
        
        // And for each event check whether it passed one of the desired triggers
        bool pass_any_trig = false;
        for (int Idx = 0; Idx < trigger_indices.size(); Idx++){ 
            if (trigger_pass->at(trigger_indices.at(Idx))){
                pass_any_trig = true;
                break;
            }
        }
        if (!pass_any_trig) {continue;}
        
        
        //****************************************************
        //
        // INTITAL TRIVIAL SELECTIONS
        //
        //****************************************************
        if (el_n < nelectron_min){continue;}
        if (mu_n < nmuon_min){continue;}
        if ((el_n+mu_n) < nlepton_min){continue;}
        if (jet_n < njet_min){continue;}
        
        //****************************************************
        //
        // MET SELECTION 
        //
        //****************************************************
        
        if (met_pt < met_pt_min){continue;}
        if (met_pt > met_pt_max){continue;}
        
        //std::cout << "MET passed" << std::endl;
        
        
        //****************************************************
        //
        // JET SELECTION
        //
        //****************************************************
        int n_jet_selected = 0;
        for (int iJet = 0;  iJet < jet_n; iJet++){
            // require a minimal jet pT requirement to get rid of very low pT stuff
            // The actual pT requirement can only be applied afterwards, when JER smearing has been applied in the Converter!
            if (jet_pt->at(iJet) > 10 && jet_pt->at(iJet) < jet_pt_max && fabs(jet_eta->at(iJet)) < jet_abseta_max && fabs(jet_eta->at(iJet)) > jet_abseta_min){
                n_jet_selected++;
            }
        }
        if (n_jet_selected < njet_min || n_jet_selected > njet_max){continue;}
        
        // int n_jet_selected = 0;
//         for (int iJet = 0;  iJet < jet_n; iJet++){
//             if (!isdata_ && (JESsyst != "central" || JERsyst != "central")){
//                 /* 
//                 IMPORTANT NOTE! (only for MC, not important for data)
//                 In the converter step, the Jet Energy Corrections uncertainties are calculated.
//                 you should make sure not to throw away events already at this stage!
//                 Therefore we lower the minimal pT threshold at this stage.
//                 In the converter step however, the corrected jet Pt is used to select the jets!
//                 */
//                 float jet_pt_min_lowered = max(0.,jet_pt_min-5.);
//                 float jet_pt_max_increased = jet_pt_max+5.;
//                 if (jet_pt->at(iJet) > jet_pt_min_lowered && jet_pt->at(iJet) < jet_pt_max_increased && fabs(jet_eta->at(iJet)) < jet_abseta_max && fabs(jet_eta->at(iJet)) > jet_abseta_min){
//                     n_jet_selected++;
//                 }
//             }
//             else{ 
//                 if (jet_pt->at(iJet) > jet_pt_min && jet_pt->at(iJet) < jet_pt_max && fabs(jet_eta->at(iJet)) < jet_abseta_max && fabs(jet_eta->at(iJet)) > jet_abseta_min){
//                     n_jet_selected++;
//                 }
//             }
//             
//         }
//         
//         if (!isdata_ && (JESsyst != "central" || JERsyst != "central")){
//             /*
//             For the same reason as above, we are potentially selecting too many events at this stage 
//             and therefore we only check the lower bound on njets!
//             Again in the Converter step, also the upper bound is checked!
//             */
//             if (n_jet_selected < njet_min){continue;}
//         }
//         else{
//             if (n_jet_selected < njet_min || n_jet_selected > njet_max){continue;}
//         }
        
        //std::cout << "Jet passed" << std::endl;
        
        
        //****************************************************
        //
        // LEPTON SELECTION
        //
        //****************************************************
        int n_elec_selected = 0;
        for (int iElec = 0;  iElec < el_n; iElec++){
            if (el_pt->at(iElec) < electron_pt_min || el_pt->at(iElec) > electron_pt_max || fabs(el_eta->at(iElec)) > electron_abseta_max || fabs(el_eta->at(iElec)) < electron_abseta_min){
                continue;
            }
            float eA = effectiveAreas_->getEffectiveArea(fabs(el_scleta->at(iElec)));
            //Double_t RelIso_elec = (el_pfIso_sumChargedHadronPt->at(iElec) + el_pfIso_sumNeutralHadronEt->at(iElec) + el_pfIso_sumPhotonEt->at(iElec))/el_pt->at(iElec);
            Double_t RelIso_elec = (el_pfIso_sumChargedHadronPt->at(iElec) + std::max(el_pfIso_sumNeutralHadronEt->at(iElec)+el_pfIso_sumPhotonEt->at(iElec)-(eA*ev_rho),0.0f))/el_pt->at(iElec);
            if (RelIso_elec < electron_reliso_max){// && el_pt->at(iElec) > electron_pt_min && el_pt->at(iElec) < electron_pt_max && fabs(el_eta->at(iElec)) < electron_abseta_max && fabs(el_eta->at(iElec)) > electron_abseta_min){
                n_elec_selected++;
            }
        }
        if (n_elec_selected < nelectron_min || n_elec_selected > nelectron_max){continue;}
        
        //std::cout << "Electron passed" << std::endl;
        
        int n_muon_selected = 0;
        for (int iMuon = 0;  iMuon < mu_n; iMuon++){
            //Double_t RelIso_muon = (mu_pfIso04_sumChargedHadronPt->at(iMuon) + mu_pfIso04_sumNeutralHadronEt->at(iMuon) + mu_pfIso04_sumPhotonEt->at(iMuon))/mu_pt->at(iMuon);
            Double_t RelIso_muon = (mu_pfIso04_sumChargedHadronPt->at(iMuon)+std::max(mu_pfIso04_sumNeutralHadronEt->at(iMuon)+mu_pfIso04_sumPhotonEt->at(iMuon)-(float)(0.5*mu_pfIso04_sumPUPt->at(iMuon)),0.0f))/mu_pt->at(iMuon);
            if (RelIso_muon < muon_reliso_max && mu_pt->at(iMuon) > muon_pt_min && mu_pt->at(iMuon) < muon_pt_max && fabs(mu_eta->at(iMuon)) < muon_abseta_max && fabs(mu_eta->at(iMuon)) > muon_abseta_min){
                n_muon_selected++;
            }
        }
        
        if (n_muon_selected < nmuon_min || n_muon_selected > nmuon_max){continue;}
        
        //std::cout << "Muon passed" << std::endl;
        
        if (n_muon_selected + n_elec_selected < nlepton_min || n_muon_selected + n_elec_selected > nlepton_max){continue;}

        
        
        
        
        
        
        outtree->Fill();

    }
    //************** end loop over events *******************
    timer_end = time(NULL);
    double seconds = difftime(timer_end,timer_start);
    
    std::cout << filename + ": Selected " << outtree->GetEntries() << " (" << round(100000*outtree->GetEntries()/events_this_job)/1000 << " %) events from initial " << events_this_job <<" (" << seconds << " seconds)" << std::endl;
    
    
    //************** Convert Tree Format To Object Oriented *******************
    
    TTree* ObjectTree = new TTree("tree","tree");
    
    
    
    bool isttbar_ = false;
    if (filename.find("TTJets") != string::npos || filename.find("TTTo") != string::npos){ isttbar_ = true;}
    bool store_muon = true;
    bool store_elec = true;
    bool store_jets = true;
    bool store_MET = true;
    bool store_Truth = isttbar_;
    bool store_GenTTXJets = isttbar_;
    Converter* conv = new Converter(outtree,ObjectTree, effectiveAreas_, isdata_, config, trigger_indices, store_muon, store_elec, store_jets, store_MET, store_Truth, store_GenTTXJets, -1, JESsyst_, JERsyst_); // store flags: electrons, muons, jets, MET, Truth
    
    
    timer_start = time(NULL);
    conv->Convert();
    timer_end = time(NULL);
    seconds = difftime(timer_end,timer_start);
    
    std::cout << filename + ": DONE CONVERTING (" << seconds << " seconds)" << std::endl;
    
    
    outfile->cd();
    ObjectTree->Write();
    
    std::cout << filename + ": Written to file" << std::endl;
    
    // Copy the hcount and hweight to save the original amount of simulated events
    TH1D* hcount = new TH1D("hcount","hcount",1,0.,1.);
    TH1D* hweight = new TH1D("hweight","hweight",1,0.,1.);
    //vector<TString> filenames = listfiles(infiledir);
    for (vector<TString>::iterator it = processed_filenames.begin(); it != processed_filenames.end(); it++){
        TFile * f_ = TFile::Open(infiledir+"/"+(*it));
        hcount->Add((TH1D*)f_->Get("FlatTree/hcount"));
        hweight->Add((TH1D*)f_->Get("FlatTree/hweight"));
        f_->Close();
    }
    if (events_this_job > 0 && events_this_job < superTree->GetEntries()){
        hcount->SetBinContent(1,events_this_job*hcount->GetBinContent(1)/(float)superTree->GetEntries());
        hweight->SetBinContent(1,events_this_job*hweight->GetBinContent(1)/(float)superTree->GetEntries());
    }
    outfile->cd();
    hcount->Write();
    hweight->Write();
    
    std::cout << filename + ": Written to storage" << std::endl;
    
    outfile->Close();
    
    std::cout << filename + ": DONE" << std::endl;
    
}



std::vector<TString> listfiles(TString indir){
    DIR *dir;
    struct dirent *ent;
    std::vector<TString> filenames;
    if ((dir = opendir (indir)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        TString name = ent->d_name;
        if (name.BeginsWith("output_")){
            filenames.push_back(name);
        }
      }
      closedir (dir);
    }
    return filenames;
}


bool DirExists(TString indir){
    DIR *dir;
    return ((dir = opendir (indir)) != NULL);
}


std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::string GetOutputFileName(std::string output){
    std::vector<std::string> sample_name_v = split(output, '/');
    for (std::vector<std::string>::iterator it = sample_name_v.begin(); it != sample_name_v.end(); it++){
        TString buffer(*it);
        if (buffer.EndsWith(".root")) return split(*it, '.')[0];
    }
    return "NOTFOUND";
}

// template <typename T>
// std::vector<T> as_vector(boost::property_tree::ptree const& pt, boost::property_tree::ptree::key_type const& key)
// {
//     std::vector<T> r;
//     for (auto& item : pt.get_child(key))
//         r.push_back(item.second.get_value<T>());
//     return r;
// }




int main(int argc, char *argv[])
{
   if( argc < 4 )
     {
	std::cout << "NtupleProducer usage:" << std::endl;
	std::cout << "--infiledirectory: input directory" << std::endl;
	std::cout << "--outfilepath: output file" << std::endl;
	std::cout << "--config: config file" << std::endl;
	std::cout << "--triggers: trigger list txt file" << std::endl;
	std::cout << "--nevents : Number of total events in the entire sample (not only this job)" << std::endl;
	std::cout << "--firstevt : starting event number in this job" << std::endl;
	std::cout << "--lastevt : last event number in this job" << std::endl;
	std::cout << "--JESsyst : JES central, Up or Down" << std::endl;
	std::cout << "--JERsyst : JER central, Up or Down" << std::endl;
	exit(1);
     }
   
   std::string infiledirectory_str = "";
   std::string outfilepath_str = "";
   std::string config_str = "";
   std::string trigger_str = "";
   Int_t nevents=-1;
   Int_t firstevt=-1;
   Int_t lastevt=-1;
   std::string jessyst = "";
   std::string jersyst = "";
   
   //std::cout << argc << std::endl;
   
   for(int i=0;i<argc;i++)
     {
	if( ! strcmp(argv[i],"--infiledirectory") ) infiledirectory_str = argv[i+1];
	if( ! strcmp(argv[i],"--outfilepath") ) outfilepath_str = argv[i+1];
	if( ! strcmp(argv[i],"--config") ) config_str = argv[i+1];
	if( ! strcmp(argv[i],"--triggers") ) trigger_str = argv[i+1];
	if( ! strcmp(argv[i],"--nevents") ) nevents = atof(argv[i+1]);
	if( ! strcmp(argv[i],"--firstevt") ) firstevt = atof(argv[i+1]);
	if( ! strcmp(argv[i],"--lastevt") ) lastevt = atof(argv[i+1]);
	if( ! strcmp(argv[i],"--JESsyst") ) jessyst = argv[i+1];
	if( ! strcmp(argv[i],"--JERsyst") ) jersyst = argv[i+1];
     }   
    
    // std::cout << "infiledirectory: " << infiledirectory_str << std::endl;
//     std::cout << "outfilepath: " << outfilepath_str << std::endl;
//     std::cout << "nevents: " << nevents << std::endl;
   
   Selection(infiledirectory_str, outfilepath_str, config_str, trigger_str, nevents, firstevt, lastevt, jessyst, jersyst);

}