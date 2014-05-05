#include <fstream>
#include <iostream>
#include <random>
//#include <time.h>
#include <ctime>
#include <complex>
#include <cmath>

using namespace std;
typedef complex<double> Complex;
const Complex I(0.0, 1.0);
#define Nx 40
#define Ny 40
#define Nz 3

double energy(double sz[Nx][Ny][Nz], double Jr[Nx][Ny][Nz][3]);
double sz[Nx][Ny][Nz];
double Jr[Nx][Ny][Nz][3];

int main()
{

  double ene;
  double ene1;
  double ene2;
  double temp;
  double random;

  ofstream fout1("result1.txt");
  ofstream fout2("result2.txt");
  ofstream fout3("result3.txt");
  //ofstream fout4("result4.txt");
  //ofstream fout5("result5.txt");
  ofstream fout6("result6.txt");
  std::mt19937 generator;
  generator.seed(0);
  std::normal_distribution<double> nordistribution(0.0, 0.030);
  std::uniform_real_distribution<double> unidistribution(0.0, 1.0);

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              for (int l=0; l<3; l++){
                random=nordistribution(generator);
                Jr[i][j][k][l] = random/abs(random);
                fout6 << i << ' ' << j << ' ' << k << ' ' << l << ' '<< Jr[i][j][k][l] << endl;
              }
            }
        }
              fout6 << endl;
    }

  //std::mt19937 generator;
  generator.seed(time(NULL));
  //std::normal_distribution<double> nordistribution(0.0, 0.030);
  //std::uniform_real_distribution<double> unidistribution(0.0, 1.0);

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              random=nordistribution(generator);
              if ( random >0.0)
                {
                  sz[i][j][k]=1.0;
                }
              else {
                sz[i][j][k]=-1.0;
              }
              fout2 << i << ' ' << j << ' ' << k << ' ' << sz[i][j][k] << endl;
            }
        }
          fout2 << endl;
    }

  ene = energy(sz, Jr);
  fout1 << 0 << ' ' << ene << endl;

  for (int l=0; l<1000; l++)
    {

      //temp=100.000*exp(-l*1.00/10.0);
      temp=10.000*(1000-l)/1000;
      cout << l << ' ' << temp << endl;

      for (int i=0; i<Nx; i++)
        {
          for (int j=0; j<Ny; j++)
            {
              for (int k=0; k<Nz; k++)
                {
                  ene1=energy(sz, Jr);
                  sz[i][j][k]=-1.0*sz[i][j][k];
                  ene2=energy(sz, Jr);

                  //fout4 << l << ' ' << ene1 << ' ' << ene2 << ' ' << ene2-ene1 << endl;

                  double uni=unidistribution(generator);
                  if (uni < 1/(1+exp(-(ene2-ene1)/1.00)))
                    //if (ene2>ene1)
                    {
                      //fout5 << uni << ' ' << 1/(1+exp((ene2-ene1)/temp)) << endl;
                      sz[i][j][k]=-1.0*sz[i][j][k];
                    }
                }
            }
        }

      ene = energy(sz, Jr);
      fout1 << l << ' ' << ene << endl;

    }

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              fout3 << i << ' ' << j << ' ' << k << ' ' << sz[i][j][k] << endl;
            }
        }
          fout3 << endl;
    }

  return 0;
}

double energy(double sz[Nx][Ny][Nz], double Jr[Nx][Ny][Nz][3])
{

  double ene=0.0;
  double J=1.0;
  double H=1.0;

  for (int i=0; i<Nx-1; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              //ene=ene+J*sz[i][j][k]*sz[i+1][j][k];
              ene=ene+Jr[i][j][k][0]*sz[i][j][k]*sz[i+1][j][k];
            }
        }
    }

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny-1; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              //ene=ene+J*sz[i][j][k]*sz[i][j+1][k];
              ene=ene+Jr[i][j][k][1]*sz[i][j][k]*sz[i][j+1][k];
            }
        }
    }

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz-1; k++)
            {
              //ene=ene+J*sz[i][j][k]*sz[i][j][k+1];
              ene=ene+Jr[i][j][k][2]*sz[i][j][k]*sz[i][j][k+1];
            }
        }
    }

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              ene=ene+H*sz[i][j][k];
            }
        }
    }

  return ene;
}

