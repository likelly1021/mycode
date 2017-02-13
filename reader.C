/* OSCAR Data Reader (ROOT version)

OSCAR format:

event line: id xxx npart b ...

        id: event id
     npart: number of particles in the event
	 	 b: impact parameter

particle line: pid px py pz mass x y z t

	   pid: particle id
px, py, pz: momentum of the particle
	  mass: mass of the particle
   x, y, z: coordinates of the particle
		 t: freeze-out time of the particle

input file: input.txt
	 nfile: number of data files
	 fname: name of data file

output file: output.root
			hxxx: histogram id
			  h1: multiplicity distribution
			h100: pid distribution
			hxx1: px distribution
			hxx2: py distribution
			hxx3: pz distribution
			hxx4: pt distribution
			hxx5: rapidity distribution
			hxx6: x distribution
			hxx7: y distribution
			hxx8: z distribution
			hxx9: freeze-out time distribution
			h11x: pion plus		pid =  211
			h12x; pion minus	pid = -211
			h13x: pion zero		pid =  111
			h21x: kaon plus		pid =  321
			h22x: kaon minus	pid = -321
			h23x: kaon short	pid =  310
			h24x: kaon long		pid =  130
			h31x: proton		pid = 2212
			h32x: anti-proton	pid =-2212
			h33x: neutron		pid = 2112
			h34x: anti-neutron	pid =-2112
*/

#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH1.h"
using namespace std;

TFile * fout = new TFile("output.root","RECREATE");

TH1I * h1 = new TH1I("h1", "multiplicity distribution", 100, 1800, 2300);
TH1I * h100 = new TH1I("h100", "pid distribution", 100, -2500, 2500);
TH1D * h101 = new TH1D("h101", "px distribution", 100, -1.5, 1.5);
TH1D * h102 = new TH1D("h102", "py distribution", 100, -1.5, 1.5);
TH1D * h103 = new TH1D("h103", "pz distribution", 100, -2.5, 2.5);
TH1D * h104 = new TH1D("h104", "pt distribution", 100, 0, 1.5);
TH1D * h105 = new TH1D("h105", "rapidity distribution", 100, -5, 5);
TH1D * h106 = new TH1D("h106", "x distribution", 100, -25, 25);
TH1D * h107 = new TH1D("h107", "y distribution", 100, -25, 25);
TH1D * h108 = new TH1D("h108", "z distribution", 100, -35, 35);
TH1D * h109 = new TH1D("h109", "time distribution", 100, 0, 100);
TH1D * h111 = new TH1D("h111", "pion+ px distribution", 100, -1.5, 1.5);
TH1D * h112 = new TH1D("h112", "pion+ py distribution", 100, -1.5, 1.5);
TH1D * h113 = new TH1D("h113", "pion+ pz distribution", 100, -2.5, 2.5);
TH1D * h114 = new TH1D("h114", "pion+ pt distribution", 100, 0, 1.5);
TH1D * h115 = new TH1D("h115", "pion+ rapidity distribution", 100, -5, 5);
TH1D * h116 = new TH1D("h116", "pion+ x distribution", 100, -25, 25);
TH1D * h117 = new TH1D("h117", "pion+ y distribution", 100, -25, 25);
TH1D * h118 = new TH1D("h118", "pion+ z distribution", 100, -35, 35);
TH1D * h119 = new TH1D("h119", "pion+ time distribution", 100, 0, 100);
TH1D * h121 = new TH1D("h121", "pion- px distribution", 100, -1.5, 1.5);
TH1D * h122 = new TH1D("h122", "pion- py distribution", 100, -1.5, 1.5);
TH1D * h123 = new TH1D("h123", "pion- pz distribution", 100, -2.5, 2.5);
TH1D * h124 = new TH1D("h124", "pion- pt distribution", 100, 0, 1.5);
TH1D * h125 = new TH1D("h125", "pion- rapidity distribution", 100, -5, 5);
TH1D * h126 = new TH1D("h126", "pion- x distribution", 100, -25, 25);
TH1D * h127 = new TH1D("h127", "pion- y distribution", 100, -25, 25);
TH1D * h128 = new TH1D("h128", "pion- z distribution", 100, -35, 35);
TH1D * h129 = new TH1D("h129", "pion- time distribution", 100, 0, 100);
TH1D * h131 = new TH1D("h131", "pion0 px distribution", 100, -1.5, 1.5);
TH1D * h132 = new TH1D("h132", "pion0 py distribution", 100, -1.5, 1.5);
TH1D * h133 = new TH1D("h133", "pion0 pz distribution", 100, -2.5, 2.5);
TH1D * h134 = new TH1D("h134", "pion0 pt distribution", 100, 0, 1.5);
TH1D * h135 = new TH1D("h135", "pion0 rapidity distribution", 100, -5, 5);
TH1D * h136 = new TH1D("h136", "pion0 x distribution", 100, -25, 25);
TH1D * h137 = new TH1D("h137", "pion0 y distribution", 100, -25, 25);
TH1D * h138 = new TH1D("h138", "pion0 z distribution", 100, -35, 35);
TH1D * h139 = new TH1D("h139", "pion0 time distribution", 100, 0, 100);
TH1D * h211 = new TH1D("h211", "kaon+ px distribution", 100, -1.5, 1.5);
TH1D * h212 = new TH1D("h212", "kaon+ py distribution", 100, -1.5, 1.5);
TH1D * h213 = new TH1D("h213", "kaon+ pz distribution", 100, -2.5, 2.5);
TH1D * h214 = new TH1D("h214", "kaon+ pt distribution", 100, 0, 1.5);
TH1D * h215 = new TH1D("h215", "kaon+ rapidity distribution", 100, -5, 5);
TH1D * h216 = new TH1D("h216", "kaon+ x distribution", 100, -25, 25);
TH1D * h217 = new TH1D("h217", "kaon+ y distribution", 100, -25, 25);
TH1D * h218 = new TH1D("h218", "kaon+ z distribution", 100, -35, 35);
TH1D * h219 = new TH1D("h219", "kaon+ time distribution", 100, 0, 100);
TH1D * h221 = new TH1D("h221", "kaon- px distribution", 100, -1.5, 1.5);
TH1D * h222 = new TH1D("h222", "kaon- py distribution", 100, -1.5, 1.5);
TH1D * h223 = new TH1D("h223", "kaon- pz distribution", 100, -2.5, 2.5);
TH1D * h224 = new TH1D("h224", "kaon- pt distribution", 100, 0, 1.5);
TH1D * h225 = new TH1D("h225", "kaon- rapidity distribution", 100, -5, 5);
TH1D * h226 = new TH1D("h226", "kaon- x distribution", 100, -25, 25);
TH1D * h227 = new TH1D("h227", "kaon- y distribution", 100, -25, 25);
TH1D * h228 = new TH1D("h228", "kaon- z distribution", 100, -35, 35);
TH1D * h229 = new TH1D("h229", "kaon- time distribution", 100, 0, 100);
TH1D * h231 = new TH1D("h231", "kaon_S px distribution", 100, -1.5, 1.5);
TH1D * h232 = new TH1D("h232", "kaon_S py distribution", 100, -1.5, 1.5);
TH1D * h233 = new TH1D("h233", "kaon_S pz distribution", 100, -2.5, 2.5);
TH1D * h234 = new TH1D("h234", "kaon_S pt distribution", 100, 0, 1.5);
TH1D * h235 = new TH1D("h235", "kaon_S rapidity distribution", 100, -5, 5);
TH1D * h236 = new TH1D("h236", "kaon_S x distribution", 100, -25, 25);
TH1D * h237 = new TH1D("h237", "kaon_S y distribution", 100, -25, 25);
TH1D * h238 = new TH1D("h238", "kaon_S z distribution", 100, -35, 35);
TH1D * h239 = new TH1D("h239", "kaon_S time distribution", 100, 0, 100);
TH1D * h241 = new TH1D("h241", "kaon_L px distribution", 100, -1.5, 1.5);
TH1D * h242 = new TH1D("h242", "kaon_L py distribution", 100, -1.5, 1.5);
TH1D * h243 = new TH1D("h243", "kaon_L pz distribution", 100, -2.5, 2.5);
TH1D * h244 = new TH1D("h244", "kaon_L pt distribution", 100, 0, 1.5);
TH1D * h245 = new TH1D("h245", "kaon_L rapidity distribution", 100, -5, 5);
TH1D * h246 = new TH1D("h246", "kaon_L x distribution", 100, -25, 25);
TH1D * h247 = new TH1D("h247", "kaon_L y distribution", 100, -25, 25);
TH1D * h248 = new TH1D("h248", "kaon_L z distribution", 100, -35, 35);
TH1D * h249 = new TH1D("h249", "kaon_L time distribution", 100, 0, 100);
TH1D * h311 = new TH1D("h311", "proton px distribution", 100, -1.5, 1.5);
TH1D * h312 = new TH1D("h312", "proton py distribution", 100, -1.5, 1.5);
TH1D * h313 = new TH1D("h313", "proton pz distribution", 100, -2.5, 2.5);
TH1D * h314 = new TH1D("h314", "proton pt distribution", 100, 0, 1.5);
TH1D * h315 = new TH1D("h315", "proton rapidity distribution", 100, -5, 5);
TH1D * h316 = new TH1D("h316", "proton x distribution", 100, -25, 25);
TH1D * h317 = new TH1D("h317", "proton y distribution", 100, -25, 25);
TH1D * h318 = new TH1D("h318", "proton z distribution", 100, -35, 35);
TH1D * h319 = new TH1D("h319", "proton time distribution", 100, 0, 100);
TH1D * h321 = new TH1D("h321", "anti-proton px distribution", 100, -1.5, 1.5);
TH1D * h322 = new TH1D("h322", "anti-proton py distribution", 100, -1.5, 1.5);
TH1D * h323 = new TH1D("h323", "anti-proton pz distribution", 100, -2.5, 2.5);
TH1D * h324 = new TH1D("h324", "anti-proton pt distribution", 100, 0, 1.5);
TH1D * h325 = new TH1D("h325", "anti-proton rapidity distribution", 100, -5, 5);
TH1D * h326 = new TH1D("h326", "anti-proton x distribution", 100, -25, 25);
TH1D * h327 = new TH1D("h327", "anti-proton y distribution", 100, -25, 25);
TH1D * h328 = new TH1D("h328", "anti-proton z distribution", 100, -35, 35);
TH1D * h329 = new TH1D("h329", "anti-proton time distribution", 100, 0, 100);
TH1D * h331 = new TH1D("h331", "neutron px distribution", 100, -1.5, 1.5);
TH1D * h332 = new TH1D("h332", "neutron py distribution", 100, -1.5, 1.5);
TH1D * h333 = new TH1D("h333", "neutron pz distribution", 100, -2.5, 2.5);
TH1D * h334 = new TH1D("h334", "neutron pt distribution", 100, 0, 1.5);
TH1D * h335 = new TH1D("h335", "neutron rapidity distribution", 100, -5, 5);
TH1D * h336 = new TH1D("h336", "neutron x distribution", 100, -25, 25);
TH1D * h337 = new TH1D("h337", "neutron y distribution", 100, -25, 25);
TH1D * h338 = new TH1D("h338", "neutron z distribution", 100, -35, 35);
TH1D * h339 = new TH1D("h339", "neutron time distribution", 100, 0, 100);
TH1D * h341 = new TH1D("h341", "anti-neutron px distribution", 100, -1.5, 1.5);
TH1D * h342 = new TH1D("h342", "anti-neutron py distribution", 100, -1.5, 1.5);
TH1D * h343 = new TH1D("h343", "anti-neutron pz distribution", 100, -2.5, 2.5);
TH1D * h344 = new TH1D("h344", "anti-neutron pt distribution", 100, 0, 1.5);
TH1D * h345 = new TH1D("h345", "anti-neutron rapidity distribution", 100, -5, 5);
TH1D * h346 = new TH1D("h346", "anti-neutron x distribution", 100, -25, 25);
TH1D * h347 = new TH1D("h347", "anti-neutron y distribution", 100, -25, 25);
TH1D * h348 = new TH1D("h348", "anti-neutron z distribution", 100, -35, 35);
TH1D * h349 = new TH1D("h349", "anti-neutron time distribution", 100, 0, 100);

void reader() {

	int nfile, npart, misc;
	char dataFileName[256];

	ifstream inputFile;
	ifstream dataFile;

	Int_t pid;
	Double_t b;
    Double_t px, py, pz, mass, x, y, z, t;
	Double_t pt, mt, e, rap;

    ifstream inputFile("./input.txt");
	inputFile >> nfile;
	cout << "Reading " << nfile << " data files!" << endl;

// file loop begin
    int nevent = 0;
	for (int ifile=0; ifile<nfile; ifile++) {

		inputFile >> dataFileName;
 		dataFile.open(dataFileName);
		cout << "Reading data file " << dataFileName << endl;

// event loop begin
		while (!dataFile.fail()) {
					
			dataFile >> misc >> misc >> npart >> b;
			dataFile.ignore(256,'\n');
			if (dataFile.eof()) break;
// particle loop begin
            int mult = 0;
			for (int ipart=0; ipart<npart; ipart++) {
				dataFile >> pid >> px >> py >> pz >> mass >> x >> y >> z >> t;
            if ( t>0.201 && t<200 &&
			     fabs(x)<100 && fabs(y)<100 && fabs(z)<100 &&
				 fabs(px)<10 && fabs(py)<10 && fabs(pz)<10) {

                mult++;

				pt = sqrt(px * px + py * py);
				mt = sqrt(pt * pt + mass * mass);
				e = sqrt(mt * mt + pz * pz);
				rap = 0.5 * log((e + pz) / (e - pz));

				h100->Fill(pid);
				h101->Fill(px);
				h102->Fill(py);
				h103->Fill(pz);
				h104->Fill(pt);
				h105->Fill(rap);
				h106->Fill(x);
				h107->Fill(y);
				h108->Fill(z);
				h109->Fill(t);

				if (pid == 211) {
					h111->Fill(px);
					h112->Fill(py);
					h113->Fill(pz);
					h114->Fill(pt);
					h115->Fill(rap);
					h116->Fill(x);
					h117->Fill(y);
					h118->Fill(z);
					h119->Fill(t);
				} else if (pid == -211) {
					h121->Fill(px);
					h122->Fill(py);
					h123->Fill(pz);
					h124->Fill(pt);
					h125->Fill(rap);
					h126->Fill(x);
					h127->Fill(y);
					h128->Fill(z);
					h129->Fill(t);
				} else if (pid == 111) {
					h131->Fill(px);
					h132->Fill(py);
					h133->Fill(pz);
					h134->Fill(pt);
					h135->Fill(rap);
					h136->Fill(x);
					h137->Fill(y);
					h138->Fill(z);
					h139->Fill(t);
				} else if (pid == 321) {
					h211->Fill(px);
					h212->Fill(py);
					h213->Fill(pz);
					h214->Fill(pt);
					h215->Fill(rap);
					h216->Fill(x);
					h217->Fill(y);
					h218->Fill(z);
					h219->Fill(t);
				} else if (pid == -321) {
					h221->Fill(px);
					h222->Fill(py);
					h223->Fill(pz);
					h224->Fill(pt);
					h225->Fill(rap);
					h226->Fill(x);
					h227->Fill(y);
					h228->Fill(z);
					h229->Fill(t);
				} else if (pid == 310) {
					h231->Fill(px);
					h232->Fill(py);
					h233->Fill(pz);
					h234->Fill(pt);
					h235->Fill(rap);
					h236->Fill(x);
					h237->Fill(y);
					h238->Fill(z);
					h239->Fill(t);
				} else if (pid == 130) {
					h241->Fill(px);
					h242->Fill(py);
					h243->Fill(pz);
					h244->Fill(pt);
					h245->Fill(rap);
					h246->Fill(x);
					h247->Fill(y);
					h248->Fill(z);
					h249->Fill(t);
				} else if (pid == 2212) {
					h311->Fill(px);
					h312->Fill(py);
					h313->Fill(pz);
					h314->Fill(pt);
					h315->Fill(rap);
					h316->Fill(x);
					h317->Fill(y);
					h318->Fill(z);
					h319->Fill(t);
				} else if (pid == -2212) {
					h321->Fill(px);
					h322->Fill(py);
					h323->Fill(pz);
					h324->Fill(pt);
					h325->Fill(rap);
					h326->Fill(x);
					h327->Fill(y);
					h328->Fill(z);
					h329->Fill(t);
				} else if (pid == 2112) {
					h331->Fill(px);
					h332->Fill(py);
					h333->Fill(pz);
					h334->Fill(pt);
					h335->Fill(rap);
					h336->Fill(x);
					h337->Fill(y);
					h338->Fill(z);
					h339->Fill(t);
				} else if (pid == -2112) {
					h341->Fill(px);
					h342->Fill(py);
					h343->Fill(pz);
					h344->Fill(pt);
					h345->Fill(rap);
					h346->Fill(x);
					h347->Fill(y);
					h348->Fill(z);
					h349->Fill(t);
				}
			}
			}
// particle loop end
			h1->Fill(mult);
			nevent++;
			cout << "event number is " << nevent << endl;
		}
// event loop end
		dataFile.close();
	}
// file loop end
    inputFile.close();
	fout->Write();
	fout->Close();
}
