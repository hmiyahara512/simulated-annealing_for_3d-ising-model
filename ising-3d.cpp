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

  ofstream fout1("result1.txt");
  ofstream fout2("result2.txt");
  ofstream fout3("result3.txt");
  ofstream fout4("result4.txt");

  std::mt19937 generator;
  generator.seed(time(NULL));
  std::normal_distribution<double> nordistribution(0.0, 0.030);
  std::uniform_real_distribution<double> unidistribution(0.0, 1.0);

  double random;

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

  for (int l=0; l<100; l++)
    {

      for (int i=0; i<Nx; i++)
        {
          for (int j=0; j<Ny; j++)
            {
              for (int k=0; k<Nz; k++)
                {
                  ene1=energy(sz);
                  sz[i][j][k]=-1.0*sz[i][j][k];
                  ene2=energy(sz);

                  fout4 << l << ' ' << ene1 << ' ' << ene2 << endl;

                  double uni=unidistribution(generator);
                  if (uni < exp((ene2-ene1)/1.00))
                    {
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

  for (int i=0; i<Nx-1; i++)
    {
      for (int j=0; j<Ny-1; j++)
        {
          for (int k=0; k<Nz-1; k++)
            {
              ene=ene+sz[i][j][k]*sz[i][j][k];
            }
        }
    }

  for (int i=0; i<Nx; i++)
    {
      for (int j=0; j<Ny; j++)
        {
          for (int k=0; k<Nz; k++)
            {
              ene=ene+0.1*sz[i][j][k];
            }
        }
    }

  return ene;
}

