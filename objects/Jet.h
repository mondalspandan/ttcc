#ifndef JET_H
#define JET_H

#include "TObject.h"
#include "TLorentzVector.h"
#include <iostream>

#define VDEF -666

class Jet : public TObject
{
 public:
   Jet();
            
   virtual ~Jet();

   // static bool sortPtPredicate(Jet lhs, Jet rhs)
//      {return (lhs.pt() > rhs.pt());};
   
   //int ID()    {return _ID;};
   
   //void sel();
   
   //bool _isdata;
   
   // Getters
   float E()         {return _E;};
   float Pt()        {return _pt;};
   float Eta()       {return _eta;};
   float Phi()       {return _phi;};
   float M()         {return _m;};
   float Charge()    {return _charge;};
   float ChargeVec()    {return _chargeVec;};
   
   bool IsLooseJetID()  {return _isLooseJetID;};
   bool IsTightJetID()  {return _isTightJetID;};
   
   int PartonFlavour()  {return _partonFlavour;};
   int HadronFlavour()  {return _hadronFlavour;};
   
   float CSVv2()                    {return _CSVv2;};
   float CMVAv2()                   {return _cMVAv2;};
   float CTagCvsL()                 {return _CTagCvsL;};
   float CTagCvsB()                 {return _CTagCvsB;};
   float DeepCSVProbudsg()          {return _DeepCSVProbudsg;};
   float DeepCSVProbb()             {return _DeepCSVProbb;};
   float DeepCSVProbbb()            {return _DeepCSVProbbb;};
   float DeepCSVProbc()             {return _DeepCSVProbc;};
   float DeepCSVProbcc()            {return _DeepCSVProbcc;};
   float DeepCSVBDiscr()            {return _DeepCSVBDiscr;};
   float DeepCSVCvsL()              {return _DeepCSVCvsL;};
   float DeepCSVCvsB()              {return _DeepCSVCvsB;};
   float DeepFlavourBDiscr()        {return _DeepFlavourBDiscr;};
   float DeepFlavourCvsL()          {return _DeepFlavourCvsL;};
   float DeepFlavourCvsB()          {return _DeepFlavourCvsB;};
   float DeepFlavourProbuds()        {return _DeepFlavourProbuds;};
   float DeepFlavourProbg()        {return _DeepFlavourProbg;};
   float DeepFlavourProbb()        {return _DeepFlavourProbb;};
   float DeepFlavourProbbb()        {return _DeepFlavourProbbb;};
   float DeepFlavourProblepb()        {return _DeepFlavourProblepb;};
   float DeepFlavourProbc()        {return _DeepFlavourProbc;};
   
   bool HasGenJet()                 {return _hasGenJet;};
   float GenJetPt()                 {return _genJetPt;};
   float GenJetEta()                 {return _genJetEta;};
   float GenJetPhi()                 {return _genJetPhi;};
   float GenJetM()                 {return _genJetM;};
   float GenJetE()                 {return _genJetE;};
   float GenJetStatus()                 {return _genJetStatus;};
   float GenJetID()                 {return _genJetID;};
   
   bool HasGenParton()                 {return _hasGenParton;};
   float GenPartonPt()                 {return _genPartonPt;};
   float GenPartonEta()                 {return _genPartonEta;};
   float GenPartonPhi()                 {return _genPartonPhi;};
   float GenPartonM()                 {return _genPartonM;};
   float GenPartonE()                 {return _genPartonE;};
   float GenPartonStatus()                 {return _genPartonStatus;};
   float GenPartonID()                 {return _genPartonID;};
   
   float SfIterativeFitCentral()	 	 	{return _SfIterativeFitCentral;};
   float SfIterativeFitJesUp()	 	 	{return _SfIterativeFitJesUp;};
   float SfIterativeFitJesDown()	 	 	{return _SfIterativeFitJesDown;};
   float SfIterativeFitLfUp()	 	 	{return _SfIterativeFitLfUp;};
   float SfIterativeFitLfDown()	 	 	{return _SfIterativeFitLfDown;};
   float SfIterativeFitHfUp()	 	 	{return _SfIterativeFitHfUp;};
   float SfIterativeFitHfDown()	 	 	{return _SfIterativeFitHfDown;};
   float SfIterativeFitHfstats1Up()	 	 	{return _SfIterativeFitHfstats1Up;};
   float SfIterativeFitHfstats1Down()	 	 	{return _SfIterativeFitHfstats1Down;};
   float SfIterativeFitHfstats2Up()	 	 	{return _SfIterativeFitHfstats2Up;};
   float SfIterativeFitHfstats2Down()	 	 	{return _SfIterativeFitHfstats2Down;};
   float SfIterativeFitLfstats1Up()	 	 	{return _SfIterativeFitLfstats1Up;};
   float SfIterativeFitLfstats1Down()	 	 	{return _SfIterativeFitLfstats1Down;};
   float SfIterativeFitLfstats2Up()	 	 	{return _SfIterativeFitLfstats2Up;};
   float SfIterativeFitLfstats2Down()	 	 	{return _SfIterativeFitLfstats2Down;};
   float SfIterativeFitCferr1Up()	 	 	{return _SfIterativeFitCferr1Up;};
   float SfIterativeFitCferr1Down()	 	 	{return _SfIterativeFitCferr1Down;};
   float SfIterativeFitCferr2Up()	 	 	{return _SfIterativeFitCferr2Up;};
   float SfIterativeFitCferr2Down()         {return _SfIterativeFitCferr2Down;};
   
   float SfDeepCSVTCentral()                {return _SfDeepCSVTCentral;};
   float SfDeepCSVTUp()                     {return _SfDeepCSVTUp;};
   float SfDeepCSVTDown()                   {return _SfDeepCSVTDown;};
   float SfDeepCSVMCentral()                {return _SfDeepCSVMCentral;};
   float SfDeepCSVMUp()                     {return _SfDeepCSVMUp;};
   float SfDeepCSVMDown()                   {return _SfDeepCSVMDown;};
   float SfDeepCSVLCentral()                {return _SfDeepCSVLCentral;};
   float SfDeepCSVLUp()                     {return _SfDeepCSVLUp;};
   float SfDeepCSVLDown()                   {return _SfDeepCSVLDown;};
   

   TLorentzVector p4()  {return _p4;};
   TLorentzVector p4_jesTotalUp()  {return _p4_jesTotalUp;};
   TLorentzVector p4_jesTotalDown()  {return _p4_jesTotalDown;};
   TLorentzVector p4_jerTotalUp()  {return _p4_jerTotalUp;};
   TLorentzVector p4_jerTotalDown() {return _p4_jerTotalDown;};
   
   
   // Setters
   void setE(float E)         {_E = E;};
   void setPt(float pt)        {_pt = pt;};
   void setEta(float eta)       {_eta = eta;};
   void setPhi(float phi)       {_phi = phi;};
   void setM(float m)         {_m = m;};
   void setCharge(float charge)    {_charge = charge;};
   void setChargeVec(float chargevec)    {_chargeVec = chargevec;};
   
   void setIsLooseJetID(bool isloosejetid)  { _isLooseJetID = isloosejetid;};
   void setIsTightJetID(bool istightjetid)  { _isTightJetID = istightjetid;};
   
   void setPartonFlavour(int partonflavour) { _partonFlavour = partonflavour;};
   void setHadronFlavour(int hadronflavour) { _hadronFlavour = hadronflavour;};
   
   void setCSVv2(float csvv2)                           {_CSVv2 = csvv2;};
   void setCMVAv2(float cmvav2)                         {_cMVAv2 = cmvav2;};
   void setCTagCvsL(float ctagcvsl)                     {_CTagCvsL = ctagcvsl;};
   void setCTagCvsB(float ctagcvsb)                     {_CTagCvsB = ctagcvsb;};
   void setDeepCSVProbudsg(float deepcsvprobudsg)       {_DeepCSVProbudsg = deepcsvprobudsg;};
   void setDeepCSVProbb(float deepcsvprobb)             {_DeepCSVProbb = deepcsvprobb;};
   void setDeepCSVProbbb(float deepcsvprobbb)           {_DeepCSVProbbb = deepcsvprobbb;};
   void setDeepCSVProbc(float deepcsvprobc)             {_DeepCSVProbc = deepcsvprobc;};
   void setDeepCSVProbcc(float deepcsvprobcc)           {_DeepCSVProbcc = deepcsvprobcc;};
   void setDeepCSVBDiscr(float deepcsvbdiscr)           {_DeepCSVBDiscr = deepcsvbdiscr;};
   void setDeepCSVCvsL(float deepcsvcvsl)               {_DeepCSVCvsL = deepcsvcvsl;};
   void setDeepCSVCvsB(float deepcsvcvsb)               {_DeepCSVCvsB = deepcsvcvsb;};
   void setDeepFlavourBDiscr(float deepflavourbdiscr)   {_DeepFlavourBDiscr = deepflavourbdiscr;};
   void setDeepFlavourCvsL(float deepflavourcvsl)       {_DeepFlavourCvsL = deepflavourcvsl;};
   void setDeepFlavourCvsB(float deepflavourcvsb)       {_DeepFlavourCvsB = deepflavourcvsb;};
   void setDeepFlavourProbuds(float deepflavourprobuds) {_DeepFlavourProbuds = deepflavourprobuds;};
   void setDeepFlavourProbg(float deepflavourprobg)     {_DeepFlavourProbg = deepflavourprobg;};
   void setDeepFlavourProbb(float deepflavourprobb)     {_DeepFlavourProbb = deepflavourprobb;};
   void setDeepFlavourProbbb(float deepflavourprobbb)   {_DeepFlavourProbbb = deepflavourprobbb;};
   void setDeepFlavourProblepb(float deepflavourproblepb){_DeepFlavourProblepb = deepflavourproblepb;};
   void setDeepFlavourProbc(float deepflavourprobc)     {_DeepFlavourProbc = deepflavourprobc;};
   
   void setHasGenJet(bool hasgenjet)                    {_hasGenJet = hasgenjet;};
   void setGenJetPt(float genjetpt)                     {_genJetPt = genjetpt;};
   void setGenJetEta(float genjeteta)                   {_genJetEta = genjeteta;};
   void setGenJetPhi(float genjetphi)                   {_genJetPhi = genjetphi;};
   void setGenJetM(float genjetm)                       {_genJetM = genjetm;};
   void setGenJetE(float genjete)                       {_genJetE = genjete;};
   void setGenJetStatus(int genjetstatus)               {_genJetStatus = genjetstatus;};
   void setGenJetID(int genjetid)                       {_genJetID = genjetid;};
   
   void setHasGenParton(bool hasgenparton)              {_hasGenParton = hasgenparton;};
   void setGenPartonPt(float genpartonpt)               {_genPartonPt = genpartonpt;};
   void setGenPartonEta(float genpartoneta)             {_genPartonEta = genpartoneta;};
   void setGenPartonPhi(float genpartonphi)             {_genPartonPhi = genpartonphi;};
   void setGenPartonM(float genpartonm)                 {_genPartonM = genpartonm;};
   void setGenPartonE(float genpartone)                 {_genPartonE = genpartone;};
   void setGenPartonStatus(int genpartonstatus)         {_genPartonStatus = genpartonstatus;};
   void setGenPartonID(int genpartonid)                 {_genPartonID = genpartonid;};
   
   void setSfIterativeFitCentral(float SfIterativeFitCentral)	 	 	    {_SfIterativeFitCentral = SfIterativeFitCentral;};
   void setSfIterativeFitJesUp(float SfIterativeFitJesUp)	 	 	        {_SfIterativeFitJesUp = SfIterativeFitJesUp;};
   void setSfIterativeFitJesDown(float SfIterativeFitJesDown)	 	 	    {_SfIterativeFitJesDown = SfIterativeFitJesDown;};
   void setSfIterativeFitLfUp(float SfIterativeFitLfUp)	 	 	        {_SfIterativeFitLfUp = SfIterativeFitLfUp;};
   void setSfIterativeFitLfDown(float SfIterativeFitLfDown)	 	 	    {_SfIterativeFitLfDown = SfIterativeFitLfDown;};
   void setSfIterativeFitHfUp(float SfIterativeFitHfUp)	 	 	        {_SfIterativeFitHfUp = SfIterativeFitHfUp;};
   void setSfIterativeFitHfDown(float SfIterativeFitHfDown)	 	 	    {_SfIterativeFitHfDown = SfIterativeFitHfDown;};
   void setSfIterativeFitHfstats1Up(float SfIterativeFitHfstats1Up)	    {_SfIterativeFitHfstats1Up = SfIterativeFitHfstats1Up;};
   void setSfIterativeFitHfstats1Down(float SfIterativeFitHfstats1Down)    {_SfIterativeFitHfstats1Down = SfIterativeFitHfstats1Down;};
   void setSfIterativeFitHfstats2Up(float SfIterativeFitHfstats2Up)	    {_SfIterativeFitHfstats2Up = SfIterativeFitHfstats2Up;};
   void setSfIterativeFitHfstats2Down(float SfIterativeFitHfstats2Down)    {_SfIterativeFitHfstats2Down = SfIterativeFitHfstats2Down;};
   void setSfIterativeFitLfstats1Up(float SfIterativeFitLfstats1Up)	    {_SfIterativeFitLfstats1Up = SfIterativeFitLfstats1Up;};
   void setSfIterativeFitLfstats1Down(float SfIterativeFitLfstats1Down)    {_SfIterativeFitLfstats1Down = SfIterativeFitLfstats1Down;};
   void setSfIterativeFitLfstats2Up(float SfIterativeFitLfstats2Up)	    {_SfIterativeFitLfstats2Up = SfIterativeFitLfstats2Up;};
   void setSfIterativeFitLfstats2Down(float SfIterativeFitLfstats2Down)    {_SfIterativeFitLfstats2Down = SfIterativeFitLfstats2Down;};
   void setSfIterativeFitCferr1Up(float SfIterativeFitCferr1Up)	        {_SfIterativeFitCferr1Up = SfIterativeFitCferr1Up;};
   void setSfIterativeFitCferr1Down(float SfIterativeFitCferr1Down)        {_SfIterativeFitCferr1Down = SfIterativeFitCferr1Down;};
   void setSfIterativeFitCferr2Up(float SfIterativeFitCferr2Up)	 	 	{_SfIterativeFitCferr2Up = SfIterativeFitCferr2Up;};
   void setSfIterativeFitCferr2Down(float SfIterativeFitCferr2Down)        {_SfIterativeFitCferr2Down = SfIterativeFitCferr2Down;};
   
   void setSfDeepCSVTCentral(float SfDeepCSVTCentral)           {_SfDeepCSVTCentral = SfDeepCSVTCentral;};
   void setSfDeepCSVTUp(float SfDeepCSVTUp)                     {_SfDeepCSVTUp = SfDeepCSVTUp;};
   void setSfDeepCSVTDown(float SfDeepCSVTDown)                 {_SfDeepCSVTDown = SfDeepCSVTDown;};
   void setSfDeepCSVMCentral(float SfDeepCSVMCentral)           {_SfDeepCSVMCentral = SfDeepCSVMCentral;};
   void setSfDeepCSVMUp(float SfDeepCSVMUp)                     {_SfDeepCSVMUp = SfDeepCSVMUp;};
   void setSfDeepCSVMDown(float SfDeepCSVMDown)                 {_SfDeepCSVMDown = SfDeepCSVMDown;};
   void setSfDeepCSVLCentral(float SfDeepCSVLCentral)           {_SfDeepCSVLCentral = SfDeepCSVLCentral;};
   void setSfDeepCSVLUp(float SfDeepCSVLUp)                     {_SfDeepCSVLUp = SfDeepCSVLUp;};
   void setSfDeepCSVLDown(float SfDeepCSVLDown)                 {_SfDeepCSVLDown = SfDeepCSVLDown;};
   
   
   void setp4()  
   {
    if(_pt > 0.) _p4.SetPtEtaPhiE(_pt,_eta,_phi,_E);
    else{
        std::cout << "WARNING: pT < 0 (" << _pt << "), p4 not filled!!!" << std::endl;
        std::cout << "Did you perhaps forget to initialize pt, eta, phi and E?" << std::endl;
    }
   };
   
   void setp4(float pt,float eta,float phi,float E)  
   {
    if(pt > 0.) _p4.SetPtEtaPhiE(pt,eta,phi,E);
    else{
        std::cout << "WARNING: pT < 0 (" << pt << "), p4 not filled!!!" << std::endl;
    }
   };
   
   void setp4_jesTotalUp(float pt,float eta,float phi,float E)  
   {
    if(pt > 0.) _p4_jesTotalUp.SetPtEtaPhiE(pt,eta,phi,E);
    else{
        std::cout << "WARNING: pT < 0 (" << pt << "), p4_jesTotalUp not filled!!!" << std::endl;
    }
   };
   
   void setp4_jesTotalDown(float pt,float eta,float phi,float E)  
   {
    if(pt > 0.) _p4_jesTotalDown.SetPtEtaPhiE(pt,eta,phi,E);
    else{
        std::cout << "WARNING: pT < 0 (" << pt << "), p4_jesTotalDown not filled!!!" << std::endl;
    }
   };
   
   void setp4_jerTotalUp(float pt,float eta,float phi,float E)  
   {
    if(pt > 0.) _p4_jerTotalUp.SetPtEtaPhiE(pt,eta,phi,E);
    else{
        std::cout << "WARNING: pT < 0 (" << pt << "), p4_jerTotalUp not filled!!!" << std::endl;
    }
   };
   
   void setp4_jerTotalDown(float pt,float eta,float phi,float E)  
   {
    if(pt > 0.) _p4_jerTotalDown.SetPtEtaPhiE(pt,eta,phi,E);
    else{
        std::cout << "WARNING: pT < 0 (" << pt << "), p4_jerTotalDown not filled!!!" << std::endl;
    }
   };
   
   //void read();
   void init();
	
 protected:

   //std::pair<float,float> getSF(float eta,float pt);
   
   float _E;
   float _pt;
   float _eta;
   float _phi;
   float _m;
   float _charge;
   float _chargeVec;
   
   bool _isLooseJetID;
   bool _isTightJetID;
   
   int _partonFlavour;
   int _hadronFlavour;
   
   float _CSVv2;
   float _cMVAv2;
   float _CTagCvsL;
   float _CTagCvsB;
   float _DeepCSVProbudsg;
   float _DeepCSVProbb;
   float _DeepCSVProbbb;
   float _DeepCSVProbc;
   float _DeepCSVProbcc;
   float _DeepCSVBDiscr;
   float _DeepCSVCvsL;
   float _DeepCSVCvsB;
   float _DeepFlavourBDiscr;
   float _DeepFlavourCvsL;
   float _DeepFlavourCvsB;
   float _DeepFlavourProbuds;
   float _DeepFlavourProbg;
   float _DeepFlavourProbb;
   float _DeepFlavourProbbb;
   float _DeepFlavourProblepb;
   float _DeepFlavourProbc;
   
   bool _hasGenJet;
   float _genJetPt;
   float _genJetEta;
   float _genJetPhi;
   float _genJetE;
   float _genJetM;
   int _genJetStatus;
   int _genJetID;
   
   bool _hasGenParton;
   float _genPartonPt;
   float _genPartonEta;
   float _genPartonPhi;
   float _genPartonE;
   float _genPartonM;
   int _genPartonStatus;
   int _genPartonID;
   
   float _SfIterativeFitCentral;
   float _SfIterativeFitJesUp;
   float _SfIterativeFitJesDown;
   float _SfIterativeFitLfUp;
   float _SfIterativeFitLfDown;
   float _SfIterativeFitHfUp;
   float _SfIterativeFitHfDown;
   float _SfIterativeFitHfstats1Up;
   float _SfIterativeFitHfstats1Down;
   float _SfIterativeFitHfstats2Up;
   float _SfIterativeFitHfstats2Down;
   float _SfIterativeFitLfstats1Up;
   float _SfIterativeFitLfstats1Down;
   float _SfIterativeFitLfstats2Up;
   float _SfIterativeFitLfstats2Down;
   float _SfIterativeFitCferr1Up;
   float _SfIterativeFitCferr1Down;
   float _SfIterativeFitCferr2Up;
   float _SfIterativeFitCferr2Down;
   float _SfDeepCSVTCentral;
   float _SfDeepCSVTUp;
   float _SfDeepCSVTDown;
   float _SfDeepCSVMCentral;
   float _SfDeepCSVMUp;
   float _SfDeepCSVMDown;
   float _SfDeepCSVLCentral;
   float _SfDeepCSVLUp;
   float _SfDeepCSVLDown;
   

   TLorentzVector _p4;
   TLorentzVector _p4_jesTotalUp;
   TLorentzVector _p4_jesTotalDown;
   TLorentzVector _p4_jerTotalUp;
   TLorentzVector _p4_jerTotalDown;
   
  
   ClassDef(Jet,1)
};

#endif
