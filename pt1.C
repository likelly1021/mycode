//the picture will be divided in six parts in this code
//there will be six canvas to draw six particles.


#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH1.h"
using namespace std;

TCanvas *c1=new TCanvas("c1","",400,400);
TCanvas *c2=new TCanvas("c2","",400,400);
TCanvas *c3=new TCanvas("c3","",400,400);
TCanvas *c4=new TCanvas("c4","",400,400);
TCanvas *c5=new TCanvas("c5","",400,400);
TCanvas *c6=new TCanvas("c6","",400,400);
//TFile * fout = new TFile("out.root","RECREATE");

//gStyle->SetOptStat(0);
//c1->Divide(3,2);

const int Nbin=30;
const double Ptmax=1.5,Ptmin=0,pi=3.141592653589793239;
double binw=(Ptmax-Ptmin)/Nbin;

TH1D * h114 = new TH1D("h114"," ",Nbin,Ptmin,Ptmax);
TH1D * h124 = new TH1D("h124"," ",Nbin,Ptmin,Ptmax);
TH1D * h214 = new TH1D("h214"," ",Nbin,Ptmin,Ptmax);
TH1D * h224 = new TH1D("h224"," ",Nbin,Ptmin,Ptmax);
TH1D * h314 = new TH1D("h314"," ",Nbin,Ptmin,Ptmax);
TH1D * h324 = new TH1D("h324"," ",Nbin,Ptmin,Ptmax);
/*
ifstream h114in;
ifstream h124in;
ifstream h214in;
ifstream h224in;
ifstream h314in;
ifstream h324in;
*/
void pt1()
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

                    else if((pid==-211)&&(fabs(rap)<=0.5))
                    {
                       h124->Fill(pt);
                    }
                    else if((pid==321)&&(fabs(rap)<=0.5))
                    {
                       h214->Fill(pt);
                    }
                    else if((pid==-321)&&(fabs(rap)<=0.5))
                    {
                       h224->Fill(pt);
                    }
                    else if((pid==2212)&&(fabs(rap)<=0.5))
                    {
                       h314->Fill(pt);
                    }
                    else if((pid==-2212)&&(fabs(rap)<=0.5))
                    {
                       h324->Fill(pt);
                    }
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

					h124->SetBinContent(ibin,h124->GetBinContent(ibin)/h124->GetBinCenter(ibin)/2./pi/double(nevent));
					h124->SetBinError(ibin,h124->GetBinError(ibin)/h124->GetBinCenter(ibin)/2./pi/double(nevent));

					h214->SetBinContent(ibin,h214->GetBinContent(ibin)/h214->GetBinCenter(ibin)/2./pi/double(nevent));
					h214->SetBinError(ibin,h214->GetBinError(ibin)/h214->GetBinCenter(ibin)/2./pi/double(nevent));

					h224->SetBinContent(ibin,h224->GetBinContent(ibin)/h224->GetBinCenter(ibin)/2./pi/double(nevent));
					h224->SetBinError(ibin,h224->GetBinError(ibin)/h224->GetBinCenter(ibin)/2./pi/double(nevent));

					h314->SetBinContent(ibin,h314->GetBinContent(ibin)/h314->GetBinCenter(ibin)/2./pi/double(nevent));
					h314->SetBinError(ibin,h314->GetBinError(ibin)/h314->GetBinCenter(ibin)/2./pi/double(nevent));

					h324->SetBinContent(ibin,h324->GetBinContent(ibin)/h324->GetBinCenter(ibin)/2./pi/double(nevent));
					h324->SetBinError(ibin,h324->GetBinError(ibin)/h324->GetBinCenter(ibin)/2./pi/double(nevent));


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
    c1->cd();
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
    h114->SetMinimum(0.001);
    h114->SetMaximum(1000);
    gPad->SetLogy(1);
    h114->SetStats(0);
    h114->Draw("E");


    TLatex tl;
    tl.SetTextFont(42);
    tl.SetTextSize(tl.GetTextSize() * 1.0);
    tl.DrawLatexNDC(0.35,0.75, "Au+Au 14.5GeV");
    //tl.DrawLatexNDC(0.2,0.2, "---Boltzmann fits");

    double xleg_start = 0.7;
    double xleg_end = 0.8;
    double yleg_start = 0.7;
    double yleg_end = 0.8;
    TLegend leg(xleg_start, yleg_start, xleg_end, yleg_end);
    //leg.AddEntry(ljm1, "#it{m}_{T} spectrum", "plf");
    //leg.AddEntry(ljm1,   "#bar{p}", "p");
    leg.AddEntry(h114, "#pi^{+}", "p");
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    //leg.SetFillColor(0);
    leg.Draw("same C");
    c1->DrawClone();
    delete c1;
    gPad->Print("ljmpi1.pdf");



//    ofstream h114out("ljmpi1.dat");
//        h114out<<Nbin<<"   !the number of bins_pt"<<endl;
//        h114out<<(h114->SetBinContent(ibin,h114->GetBinContent(ibin)/h114->GetBinCenter(ibin)/2./pi/double(nevent)))<<"  "
//               <<(h114->SetBinError(ibin,h114->GetBinError(ibin)/h114->GetBinCenter(ibin)/2./pi/double(nevent)))<<endl;
//    h114out.close();


 //----------------------------------------pi-
    c2->cd();
    h124->SetMarkerColor(kRed);
	h124->SetMarkerStyle(24);
	//h114->SetMarkerStyle(4);
    h124->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    h124->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
    h124->GetXaxis()->CenterTitle();
    h124->GetYaxis()->CenterTitle();
    h124->GetYaxis()->SetTitleOffset(1.2);
    //h114->GetXaxis->SetLimits(0.0,2.0);
    h124->SetMinimum(0.001);
    h124->SetMaximum(1000);
    gPad->SetLogy(1);
    h124->SetStats(0);
    h124->Draw("E");

    TLatex t2;
    t2.SetTextFont(42);
    t2.SetTextSize(t2.GetTextSize() * 1.0);
    t2.DrawLatexNDC(0.35,0.75, "Au+Au 14.5GeV");
    //tl.DrawLatexNDC(0.2,0.2, "---Boltzmann fits");

    double xleg_start = 0.7;
    double xleg_end = 0.8;
    double yleg_start = 0.7;
    double yleg_end = 0.8;
    TLegend leg2(xleg_start, yleg_start, xleg_end, yleg_end);
    //leg.AddEntry(ljm1, "#it{m}_{T} spectrum", "plf");
    //leg.AddEntry(ljm1,   "#bar{p}", "p");
    leg2.AddEntry(h124, "#pi^{-}", "p");
    leg2.SetFillStyle(0);
    leg2.SetBorderSize(0);
    //leg.SetFillColor(0);
    leg2.Draw("same C");
    c2->DrawClone();
    delete c2;
    //ofstream ljmout("ljmpi2.dat");
    gPad->Print("ljmpi2.pdf");


//------------------------------------------K+

    c3->cd();
    h214->SetMarkerColor(kBlue);
	h214->SetMarkerStyle(21);
////	h114->SetMarkerStyle(4);
    h214->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    h214->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
    h214->GetXaxis()->CenterTitle();
    h214->GetYaxis()->CenterTitle();
    h214->GetYaxis()->SetTitleOffset(1.2);
    //h114->GetXaxis->SetLimits(0.0,2.0);
    h214->SetMinimum(0.001);
    h214->SetMaximum(1000);
    gPad->SetLogy(1);
    h214->SetStats(0);
    h214->Draw("E");

    TLatex t3;
    t3.SetTextFont(42);
    t3.SetTextSize(t3.GetTextSize() * 1.0);
    t3.DrawLatexNDC(0.35,0.75, "Au+Au 14.5GeV");
    //tl.DrawLatexNDC(0.2,0.2, "---Boltzmann fits");

    double xleg_start = 0.7;
    double xleg_end = 0.8;
    double yleg_start = 0.7;
    double yleg_end = 0.8;
    TLegend leg3(xleg_start, yleg_start, xleg_end, yleg_end);
    //leg.AddEntry(ljm1, "#it{m}_{T} spectrum", "plf");
    //leg.AddEntry(ljm1,   "#bar{p}", "p");
    leg3.AddEntry(h214, "k^{+}", "p");
    leg3.SetFillStyle(0);
    leg3.SetBorderSize(0);
    //leg.SetFillColor(0);
    leg3.Draw("same C");
    c3->DrawClone();
    delete c3;
    gPad->Print("ljmk1.pdf");//    h214->SetMarkerColor(kBlue);

////-----------------------------------------K-

    c4->cd();
    h224->SetMarkerColor(kBlue);
	h224->SetMarkerStyle(25);
//	h114->SetMarkerStyle(4);
    h224->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    h224->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
    h224->GetXaxis()->CenterTitle();
    h224->GetYaxis()->CenterTitle();
    h224->GetYaxis()->SetTitleOffset(1.2);
    //h114->GetXaxis->SetLimits(0.0,2.0);
    h224->SetMinimum(0.001);
    h224->SetMaximum(1000);
    gPad->SetLogy(1);
    h224->SetStats(0);
    h224->Draw("E");

    TLatex t4;
    t4.SetTextFont(42);
    t4.SetTextSize(t4.GetTextSize() * 1.0);
    t4.DrawLatexNDC(0.35,0.75, "Au+Au 14.5GeV");
    //tl.DrawLatexNDC(0.2,0.2, "---Boltzmann fits");

    double xleg_start = 0.7;
    double xleg_end = 0.8;
    double yleg_start = 0.7;
    double yleg_end = 0.8;
    TLegend leg4(xleg_start, yleg_start, xleg_end, yleg_end);
    //leg.AddEntry(ljm1, "#it{m}_{T} spectrum", "plf");
    //leg.AddEntry(ljm1,   "#bar{p}", "p");
    leg4.AddEntry(h224,"k^{-}", "p");
    leg4.SetFillStyle(0);
    leg4.SetBorderSize(0);
    //leg.SetFillColor(0);
    leg4.Draw("same C");
    c4->DrawClone();
    delete c4;
    gPad->Print("ljmk2.pdf");

////*
////------------------------------------------p
    c5->cd();
    h314->SetMarkerColor(kMagenta);
	h314->SetMarkerStyle(22);
	//h114->SetMarkerStyle(4);
    h314->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    h314->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
    h314->GetXaxis()->CenterTitle();
    h314->GetYaxis()->CenterTitle();
    h314->GetYaxis()->SetTitleOffset(1.2);
   //h114->GetXaxis->SetLimits(0.0,2.0);
    h314->SetMinimum(0.001);
    h314->SetMaximum(1000);
    gPad->SetLogy(1);
    h314->SetStats(0);
    h314->Draw("E");

    TLatex t5;
    t5.SetTextFont(42);
    t5.SetTextSize(t5.GetTextSize() * 1.0);
    t5.DrawLatexNDC(0.35,0.75, "Au+Au 14.5GeV");
    //tl.DrawLatexNDC(0.2,0.2, "---Boltzmann fits");

    double xleg_start = 0.7;
    double xleg_end = 0.8;
    double yleg_start = 0.7;
    double yleg_end = 0.8;
    TLegend leg5(xleg_start, yleg_start, xleg_end, yleg_end);
    //leg.AddEntry(ljm1, "#it{m}_{T} spectrum", "plf");
    //leg.AddEntry(ljm1,   "#bar{p}", "p");
    leg5.AddEntry(h314, "p", "p");
    leg5.SetFillStyle(0);
    leg5.SetBorderSize(0);
    //leg.SetFillColor(0);
    leg5.Draw("same C");
    c5->DrawClone();
    delete c5;
    gPad->Print("ljmp1.pdf");

////*
////-----------------------------------------pba
    c6->cd();
    h324->SetMarkerColor(kMagenta);
	h324->SetMarkerStyle(26);
//	h114->SetMarkerStyle(4);
    h324->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    h324->GetYaxis()->SetTitle("d^{2}N/2#pip_{T}dp_{T}dy (GeV/c)^{-2}");
    h324->GetXaxis()->CenterTitle();
    h324->GetYaxis()->CenterTitle();
    h324->GetYaxis()->SetTitleOffset(1.2);
    //h114->GetXaxis->SetLimits(0.0,2.0);
    h324->SetMinimum(0.001);
    h324->SetMaximum(1000);
    gPad->SetLogy(1);
    h324->SetStats(0);
    h324->Draw("E");

    TLatex t6;
    t6.SetTextFont(42);
    t6.SetTextSize(t6.GetTextSize() * 1.0);
    t6.DrawLatexNDC(0.35,0.75, "Au+Au 14.5GeV");
    //tl.DrawLatexNDC(0.2,0.2, "---Boltzmann fits");

    double xleg_start = 0.7;
    double xleg_end = 0.8;
    double yleg_start = 0.7;
    double yleg_end = 0.8;
    TLegend leg6(xleg_start, yleg_start, xleg_end, yleg_end);
    //leg.AddEntry(ljm1, "#it{m}_{T} spectrum", "plf");
    //leg.AddEntry(ljm1,   "#bar{p}", "p");
    leg6.AddEntry(h324, "#bar{p}", "p");
    leg6.SetFillStyle(0);
    leg6.SetBorderSize(0);
    //leg.SetFillColor(0);
    leg6.Draw("same C");
    c6->DrawClone();
    delete c6;
    gPad->Print("ljmp2.pdf");








}
