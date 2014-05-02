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
#define Nx 10
#define Ny 10
#define Nz 2

double energy(double sz[Nx][Ny][Nz]);
double sz[Nx][Ny][Nz];

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
  ofstream fout4("result4.txt");
  ofstream fout5("result5.txt");

  std::mt19937 generator;
  generator.seed(time(NULL));
  std::normal_distribution<double> nordistribution(0.0, 0.030);
  std::uniform_real_distribution<double> unidistribution(0.0, 1.0);

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
      }

  ene = energy(sz);
  fout1 << 0 << ' ' << ene << endl;

  for (int l=0; l<1000; l++)
    {

      temp=10.000*exp(-l/100);

      for (int i=0; i<Nx; i++)
        {
          for (int j=0; j<Ny; j++)
            {
              for (int k=0; k<Nz; k++)
                {
                  ene1=energy(sz);
                  sz[i][j][k]=-1.0*sz[i][j][k];
                  ene2=energy(sz);

                  fout4 << l << ' ' << ene1 << ' ' << ene2 << ' ' << ene2-ene1 << endl;

                  double uni=unidistribution(generator);
                  if (uni < 1/(1+exp(-(ene2-ene1)/1.00)))
                    //if (ene2>ene1)
                    {
                      fout5 << uni << ' ' << 1/(1+exp((ene2-ene1)/temp)) << endl;
                      sz[i][j][k]=-1.0*sz[i][j][k];
                    }
                }
            }
        }

      ene = energy(sz);
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
      }

  return 0;
}

double energy(double sz[Nx][Ny][Nz])
{

  double ene=0.0;
  double J=1.0;
  double H=1.0;

  std::mt19937 generator;
  //  generator.seed(0);
  std::normal_distribution<double> nordistribution(0.0, 0.030);
  std::uniform_real_distribution<double> unidistribution(0.0, 1.0);

  for (int i=0; i<Nx-1; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              generator.seed(i+j+k+1);
              double  random=nordistribution(generator);
              //cout << i << ' ' << j << ' ' << k << ' ' << random/abs(random) << endl;
              ene=ene+J*random/abs(random)*sz[i][j][k]*sz[i+1][j][k];
            }
        }
    }

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny-1; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              generator.seed(i+j+k+2);
              double  random=nordistribution(generator);
              //cout << i << ' ' << j << ' ' << k << ' ' << random/abs(random) << endl;
              ene=ene+J*random/abs(random)*sz[i][j][k]*sz[i+1][j][k];
            }
        }
    }

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz-1; k++)
            {
              generator.seed(i+j+k+3);
              double  random=nordistribution(generator);
              //cout << i << ' ' << j << ' ' << k << ' ' << random/abs(random) << endl;
              ene=ene+J*random/abs(random)*sz[i][j][k]*sz[i+1][j][k];
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

