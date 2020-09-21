{

TFile f("2.5MeVBP.root");
TDirectory *dir= (TDirectory *) f.Get("GammaVertex"); 
TDirectory *dir1= (TDirectory *) f.Get("ProtonEkin"); 

int numberOfBinsX = 1000;
int numberOfBinsY = 1000;
int numberOfBinsZ = 1000;

int Xmin = 0;
int Xmax = 10;
int Ymin = 0;
int Ymax = 1000;
int Zmin = 0;
int Zmax = 1000;

//the type of histogram, how many variable, min and max values plus size of bins
TH1F *edep1Distribution = new TH1F("h0", "Primary Particle Energy Spectrum; Energy (Mev);Frequency", numberOfBinsX, Xmin, Xmax);       //Edep // binning, xmin, xmax, along x direction

//the type of histogram, how many variable, min and max values plus size of bins
TH1F *edep11Distribution = new TH1F("h1", "Energy deposition; Edep (kev);Frequency", numberOfBinsX, Xmin, Xmax);       //Edep // binning, xmin, xmax, along x direction


TH2F* edep2DDistribution = new TH2F("h2", "Energy of Proton; Position Z; Edep (keV)", numberOfBinsX, Xmin, Xmax,numberOfBinsY, Ymin, Ymax);   
	 // Z     // binning, xmin, xmax, along x direction
 	//Edep   // binning, xmin, xmax, along y direction


TH3F *edep3DDistribution = new TH3F("h3", "3Dedep; Edep (keV) ; A; Z", numberOfBinsX, Xmin, Xmin, numberOfBinsY, Ymin, Ymax,  numberOfBinsZ, Zmin, Zmax); 
// edep  // binning, xmin, xmax, along x direction
// A     //binning, xmin, xmax, along y direction
// Z     //binning, xmin, xmax, along z direction


//Plot Primary Energy of Incident Particle
//GammaVertex->Draw("Ekin>>h0","","");
//Plot Energy Deposition within SV
//GammaVertex->Draw("EkinProton>>h1", "", "");
//Plot 2D/3D Histogram of energy with particle type using A and Z
//GammaVertex->Draw("Step:EkinProton>>h2", "", "");
ProtonEkin->Draw("PositionZ:Ekin>>h2", "", "");
//GammaVertex->Draw("FinalZ:FinalA:EkinProton>>h3", "", "");

}			
