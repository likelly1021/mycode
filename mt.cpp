#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

const int Nbin=30,Nrap=50;
const double mtmax=1.5,mtmin=0,ymax=5,ymin=-5,mass=0.14,pi=3.141592653589793239;
ifstream ljmin;

bool checkend()
{
    int pos=ljmin.tellg();
    char line[256];
    ljmin.getline(line,256);
    string zz(line);
    ljmin.seekg(pos);
    ljmin.clear(ios::goodbit);
    return zz.size()<=2;
}

int main()
{
    double temp,num[Nbin],px,py,pz,y,mt0,mt00[Nbin],E;
    int Nparticle,kind,lable_mt0,ntotal_mt0;
    double binw_mt=(mtmax-mtmin)/Nbin;    //define some parameter
    int Nevent=0;
    for(int ibin=0;ibin<Nbin;ibin++)
    {
        num[ibin]=0;
        mt00[ibin]=0;
    }
	for(int ifile=0;ifile<20;ifile++)
	{
	char fname[300];
	sprintf(fname,"./events/%d.dat",ifile);
   ljmin.open(fname);
	if(ljmin.is_open())
	{
	cout<<"opened "<<fname<<endl;
	}


    //ljmin.open("./events/0.dat");
    for(int ievent=0;!checkend();ievent++) //event loop
        {
            ljmin>>temp>>temp>>Nparticle;
            ljmin.ignore(256,'\n');


			for(int iparticle=0;iparticle<Nparticle;iparticle++) //particle loop
                {
                    ljmin>>kind>>px>>py>>pz;
                    ljmin.ignore(256,'\n');
                    mt0=sqrt(px*px+py*py+mass*mass)-mass;
					E=sqrt((mt0+mass)*(mt0+mass)+pz*pz);
					//Err=pt*sqrt(1/Nevent);
					y=0.5*log((E+pz)/(E-pz));
					//Err_y=y*sqrt(1/Nevent);
					lable_mt0=floor((mt0-mtmin)/binw_mt);
					//lable_y=floor((y-ymin)/binw_y);
                    if((lable_mt0>=0)&&(lable_mt0<Nbin)&&(kind==211)&&(fabs(y)<=0.1))
                        {
                            num[lable_mt0]+=1.0;
							//ntotal_mt++;
							mt00[lable_mt0]+=mt0;
						}

					//if((lable_y>=0)&&(lable_y<=Nrap)&&(kind==211)&&(pt<=1.5))
					//	 {
					//		ntotal_y++;
					//		numy[lable_y]++;
					//	 }


		        }
		        Nevent++;
//	cout<<"ievent="<<ievent<<endl;
	     }
    ljmin.close();
	}
    //cout<<"closed "<<" "<<endl;
	for (int ibin=0;ibin<Nbin;ibin++)
		{
			mt00[ibin]/=num[ibin];
		}

		//output
    ofstream ljmout("./mt.dat");

		ljmout<<Nbin<<"   !the number of bins_pt"<<endl;
		ljmout<<ntotal_mt0<<endl;
		for(int ibin=0;ibin<Nbin;ibin++)
            {
                ljmout<<(ibin+0.5)*binw_mt+mtmin<<"  "<<num[ibin]/Nevent/binw_mt/2/pi/(mt00[ibin]+mass)/0.2
                <<"  "<<sqrt(num[ibin])/Nevent/binw_mt/2/pi/(mt00[ibin]+mass)/0.2
                <<"  "<<num[ibin]<<endl; //d2N/2/pi/pt/dpt/dy...
			}

        ljmout.close();
        cout<<"Nevent="<<Nevent<<endl;


		//ofstream ljm1out("./y.dat");
		//ljm1out<<Nrap<<" !the number of bins_y"<<endl;
		//ljm1out<<ntotal_y<<endl;
		//for(int irap=0;irap<Nrap;irap++)
		//	{
		//		ljm1out<<(irap+0.5)*binw_y+ymin<<" "<<numy[irap]/Nevent/binw_y<<" "<<Err_y<<endl;//dN/dy...
		//
		//	}
		//ljm1out.close();

return 0;

}
