#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH1.h"
using namespace std;

TCanvas *c1=new TCanvas("c","",400,400);
TFile * fout = new TFile("output.root","RECREATE");

const int Nbin=30;
const double Ptmax=1.5,Ptmin=0,pi=3.141592653589793239;
double binw=(Ptmax-Ptmin)/Nbin;

TH1D * h114 = new TH1D("h114"," ",Nbin,Ptmin,Ptmax);
//TH1D * h124 = new TH1D("h124"," ",Nbin,Ptmin,Ptmax);
//TH1D * h214 = new TH1D("h214"," ",Nbin,Ptmin,Ptmax);
//TH1D * h224 = new TH1D("h224"," ",Nbin,Ptmin,Ptmax);
//TH1D * h314 = new TH1D("h314"," ",Nbin,Ptmin,Ptmax);
//TH1D * h324 = new TH1D("h324"," ",Nbin,Ptmin,Ptmax);

void pt()
{
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
		while (!dataFile.fail())
        {

			dataFile >> misc >> misc >> npart >> b;
			dataFile.ignore(256,'\n');
			if (dataFile.eof()) break;

// particle loop begin
            int mult = 0;
			for (int ipart=0; ipart<npart; ipart++)
                {
				dataFile >> pid >> px >> py >> pz >> mass >> x >> y >> z >> t;
                if ( t>0.201 && t<200 &&
			     fabs(x)<100 && fabs(y)<100 && fabs(z)<100 &&
				 fabs(px)<10 && fabs(py)<10 && fabs(pz)<10)
				    {



				pt = sqrt(px * px + py * py);
				mt = sqrt(pt * pt + mass * mass);
				e = sqrt(mt * mt + pz * pz);
				rap = 0.5 * log((e + pz) / (e - pz));

				   if ((pid ==211)&&(fabs(rap)<=0.5))
                      {
                   //mult++;
                       h114->Fill(pt);
                      }

//                    if((pid==-211)&&(fabs(rap)<=1.5))
//                    {
//                       h124->Fill(pt);
//                    }
//                     if((pid==321)&&(fabs(rap)<=1.5))
//                    {
//                       h124->Fill(pt);
//                    }
//                     if((pid==-321)&&(fabs(rap)<=1.5))
//                    {
//                       h124->Fill(pt);
//                    }
//                     if((pid==2212)&&(fabs(rap)<=1.5))
//                    {
//                       h124->Fill(pt);
//                    }
//                     if((pid==-2212)&&(fabs(rap)<=1.5))
//                    {
//                       h124->Fill(pt);
//                    }
				    }
			     }
			nevent++;
          //cout << "event number is " << nevent << endl;


		}

// event loop end
    dataFile.close();
	}



// file loop end
    inputFile.close();

    for(int ibin=1;ibin<=Nbin;ibin++)
            {



					//h111->Fill(px);
					//h112->Fill(py);
					//h113->Fill(pz);
					h114->SetBinContent(ibin,h114->GetBinContent(ibin)/h114->GetBinCenter(ibin)/2./pi/double(nevent));
					h114->SetBinError(ibin,h114->GetBinError(ibin)/h114->GetBinCenter(ibin)/2./pi/double(nevent));

//					h124->SetBinContent(ibin,h124->GetBinContent(ibin)/h124->GetBinCenter(ibin)/2./pi/double(nevent));
//					h124->SetBinError(ibin,h124->GetBinError(ibin)/h124->GetBinCenter(ibin)/2./pi/double(nevent));

//					h214->SetBinContent(ibin,h214->GetBinContent(ibin)/h214->GetBinCenter(ibin)/2./pi/double(nevent));
//					h214->SetBinError(ibin,h214->GetBinError(ibin)/h214->GetBinCenter(ibin)/2./pi/double(nevent));
//
//					h224->SetBinContent(ibin,h224->GetBinContent(ibin)/h224->GetBinCenter(ibin)/2./pi/double(nevent));
//					h224->SetBinError(ibin,h224->GetBinError(ibin)/h224->GetBinCenter(ibin)/2./pi/double(nevent));
//
//					h314->SetBinContent(ibin,h314->GetBinContent(ibin)/h314->GetBinCenter(ibin)/2./pi/double(nevent));
//					h314->SetBinError(ibin,h314->GetBinError(ibin)/h314->GetBinCenter(ibin)/2./pi/double(nevent));
//
//					h324->SetBinContent(ibin,h324->GetBinContent(ibin)/h324->GetBinCenter(ibin)/2./pi/double(nevent));
//					h324->SetBinError(ibin,h324->GetBinError(ibin)/h324->GetBinCenter(ibin)/2./pi/double(nevent));


					//h114->Fill();
					//h115->Fill(rap);
					//h116->Fill(x);
					//h117->Fill(y);
					//h118->Fill(z);
					//h119->Fill(t);


			}
	//fout->Write();
	//fout->Close();
//------------------------------------------pi+
	h114->SetMarkerColor(kRed);
	//h114->SetMarkerColor(kMagenta);
	h114->SetMarkerStyle(20);
//	h114->SetMarkerStyle(4);
    h114->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    h114->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
    h114->GetXaxis()->CenterTitle();
    h114->GetYaxis()->CenterTitle();
    h114->SetMarkerSize(1.0);
    h114->GetYaxis()->SetTitleOffset(1.2);
    //h114->GetXaxis->SetLimits(0.0,2.0);
    //h114->SetMinimum(0.001);
    //h114->SetMaximum(1000);
    gPad->SetLogy(1);
    h114->SetStats(0);
    h114->Draw("E");
    gPad->Print("ljmpi1.pdf");
//*
 //----------------------------------------pi-
//    h124->SetMarkerColor(kRed);
//	h124->SetMarkerStyle(24);
////	h114->SetMarkerStyle(4);
//    h124->GetXaxis()->SetTitle("p_{T} (GeV/c)");
//    h124->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
//    h124->GetXaxis()->CenterTitle();
//    h124->GetYaxis()->CenterTitle();
//    //h114->GetXaxis->SetLimits(0.0,2.0);
//    //h114->SetMinimum(0.001);
//    //h114->SetMaximum(1000);
//    gPad->SetLogy(1);
//    h214->SetStats(0);
//    h214->Draw("E");
//    gPad->Print("ljmpi2.pdf");

//*
//------------------------------------------K+
//    h214->SetMarkerColor(kBlue);
//	h214->SetMarkerStyle(21);
////	h114->SetMarkerStyle(4);
//    h214->GetXaxis()->SetTitle("p_{T} (GeV/c)");
//    h214->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
//    h214->GetXaxis()->CenterTitle();
//    h214->GetYaxis()->CenterTitle();
//    //h114->GetXaxis->SetLimits(0.0,2.0);
//    //h114->SetMinimum(0.001);
//    //h114->SetMaximum(1000);
//    gPad->SetLogy(1);
//    h214->SetStats(0);
//    h214->Draw("E");
//    gPad->Print("ljmk1.pdf");
//
////*
////-----------------------------------------K-
//    h224->SetMarkerColor(kBlue);
//	h224->SetMarkerStyle(25);
////	h114->SetMarkerStyle(4);
//    h224->GetXaxis()->SetTitle("p_{T} (GeV/c)");
//    h224->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
//    h224->GetXaxis()->CenterTitle();
//    h224->GetYaxis()->CenterTitle();
//    //h114->GetXaxis->SetLimits(0.0,2.0);
//    //h114->SetMinimum(0.001);
//    //h114->SetMaximum(1000);
//    gPad->SetLogy(1);
//    h224->SetStats(0);
//    h224->Draw("E");
//    gPad->Print("ljmk2.pdf");
//
////*
////------------------------------------------p
//    h314->SetMarkerColor(kMagenta);
//	h314->SetMarkerStyle(22);
////	h114->SetMarkerStyle(4);
//    h314->GetXaxis()->SetTitle("p_{T} (GeV/c)");
//    h314->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
//    h314->GetXaxis()->CenterTitle();
//    h314->GetYaxis()->CenterTitle();
//    //h114->GetXaxis->SetLimits(0.0,2.0);
//    //h114->SetMinimum(0.001);
//    //h114->SetMaximum(1000);
//    gPad->SetLogy(1);
//    h314->SetStats(0);
//    h314->Draw("E");
//    gPad->Print("ljmp1.pdf");
//
////*
////-----------------------------------------pba
//    h324->SetMarkerColor(kMagenta);
//	h324->SetMarkerStyle(26);
////	h114->SetMarkerStyle(4);
//    h324->GetXaxis()->SetTitle("p_{T} (GeV/c)");
//    h324->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
//    h324->GetXaxis()->CenterTitle();
//    h324->GetYaxis()->CenterTitle();
//    //h114->GetXaxis->SetLimits(0.0,2.0);
//    //h114->SetMinimum(0.001);
//    //h114->SetMaximum(1000);
//    gPad->SetLogy(1);
//    h324->SetStats(0);
//    h324->Draw("E");
//    gPad->Print("ljmp2.pdf");

/*	TLatex tl;
    tl.SetTextFont(42);
   //tl.SetTextSize(tl.GetTextSize() * 1.5);
    tl.DrawLatexNDC(0.4,0.8, "Au+Au 14.5GeV");
    tl.DrawLatexNDC(0.2,0.2, "---Boltzmann fits");

    double xleg_start = 0.7;
    double xleg_end = 0.8;
    double yleg_start = 0.7;
    double yleg_end = 0.8;
    TLegend leg(xleg_start, yleg_start, xleg_end, yleg_end);
    //leg.AddEntry(ljm1, "#it{m}_{T} spectrum", "plf");
    //leg.AddEntry(ljm1,   "#bar{p}", "p");
    leg.AddEntry(c1, "k^{+}", "p");
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    //leg.SetColor(1)
    leg.Draw("same C");
    h114->DrawClone();
    delete h114;


//	TGraphErrors * gr = new TGraphErrors(h114);
//    for(int i = 0; i < gr->GetN(); i ++)
//    {
//        gr->GetEX()[i] = 0;
//    }
//    h114->Reset();
//    h114->Draw();

//    gr->Draw("same P");
*/




}
