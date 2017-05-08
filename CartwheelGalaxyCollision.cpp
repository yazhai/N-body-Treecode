// CartwheelGalaxyCollision.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include "CelestialBody.h"
#include "TreeCodeNode.h"
#include "TreeOfStars.h"
#include "param.h"

string READINDIST;
double distcrit; // the criterion if a node is "far" from another (In fact this value is changed as readin parameter)
double soften;  // soften factor (This value is changed as readin parameter
const char* FILEPRE = "Output";  // The prefix of output file name


void ReadInInitialConditions(vector<CelestialBody*>& bodylist);
void ConstructTree(vector<CelestialBody*>& bodylsit, TreeOfStars*& tree);
void LeapFrogStep(int _nstep, double dt, vector<CelestialBody*>& bodylist, double distcrit, double soften);

int main(int argc, char* argv[])
{
	std::cout << "Hello Galaxy Collision" << "\n";
     int nstep;
     double dt;
     vector<int> numofbodies;

     if (argc <= 6) {
          cout << "Invalid number of arguments.\n"
               << "Usage: ./THISPROGRAM Inputfile SoftenFactor distcriterion TotalStepNum dt [particle num in each celetial body]\n";
          return -1;
     }
     else {
          READINDIST = argv[1];
          soften = atof(argv[2]);
          distcrit = atof(argv[3]);
          nstep = atoi(argv[4]);
          dt = atof(argv[5]);
          for (int i = 6; i < argc; i++) {
               int temp = atoi(argv[i]);
               numofbodies.push_back(temp);
          }
     }

     cout << "Number of particles in each celetial body is: ";
     for (int i = 0; i < numofbodies.size(); i++) {
          cout << " " << numofbodies[i];
     };
     cout << endl;

     // Create a list containing all galaxies.
     vector<CelestialBody*> all;
     for (int i = 0;i < numofbodies.size();i++) {
          CelestialBody* tmp = new CelestialBody(numofbodies[i]);
          all.push_back(tmp);
     }
     
     ReadInInitialConditions(all);
    
     LeapFrogStep(nstep, dt, all, distcrit, soften);

	
	std::cout << "Bye Galaxy Collision" << "\n";
     return 0;
}


void ReadInInitialConditions(vector<CelestialBody*> & bodylist) {
     std::ifstream infile(READINDIST);

     if (!infile.is_open()) {
          std::cout << "Error in opening file! \n";
          exit(1);
     }

     // For all objects
     for (int j = 0; j < bodylist.size(); j++) {
          for (int l = 0; l < bodylist[j]->celestialbodynum; l++) {
               // Read in each row in the sequence of m x y z vx vy vz
               infile >> bodylist[j]->mpt[l];
               infile >> bodylist[j]->x[l];
               infile >> bodylist[j]->y[l];
               infile >> bodylist[j]->z[l];
               infile >> bodylist[j]->vx[l];
               infile >> bodylist[j]->vy[l];
               infile >> bodylist[j]->vz[l];
          }
     }
}

void ConstructTree(vector<CelestialBody*>& bodylist, TreeOfStars*& tree) {
     tree->erase();
     for (int i = 0; i < bodylist.size(); i++) {
          for (int l = 0; l < bodylist[i]->celestialbodynum; l++) {
               tree->insertnode(bodylist[i]->x[l], bodylist[i]->y[l], bodylist[i]->z[l], bodylist[i]->mpt[l], tree->root);
          }
     }
}

void LeapFrogStep(int _nstep, double dt, vector<CelestialBody*> & bodylist, double distcrit, double soften) {

     // output the initial location
     int frame = 0;
     char filename[20];
     sprintf(filename, "%s_%04d.txt", FILEPRE, frame);
     string file_s = filename;
     ofstream OutFile;
     OutFile.open(file_s);
     for (int j = 0; j < bodylist.size(); j++) {
          bodylist[j]->WriteStateToFileM1(OutFile);
     }
     OutFile << "\n";
     OutFile.close();

     // Initialize a tree : at (0,0,0) with dim (100,100,100)
     TreeOfStars* startree = new TreeOfStars(0, 0, 0, 100, 100, 100);

     // Leapfrog start here
     ConstructTree(bodylist,startree);
     for (int i = 0; i < bodylist.size(); i++) {
          bodylist[i]->UpdateA(startree, distcrit, soften);
     }


     for (int n = 0; n <= _nstep; n++) {
          frame++;
          //cout << "leapfrog on step " << n+1 << endl;
          
          // First, calculate v at t+0.5dt;
          for (int j = 0; j < bodylist.size(); j++) {
               bodylist[j]->UpdateV(0.5*dt);
          }
        
          // Caluclate r at t+dt by v_0.5 * dt
          for (int j = 0; j < bodylist.size(); j++) {
               bodylist[j]->UpdateR(1.0*dt);
          }
          // The tree is updated everytime the V is calculated
         
          //update acceleration
          ConstructTree(bodylist, startree);
          for (int i = 0; i < bodylist.size(); i++) {
               bodylist[i]->UpdateA(startree, distcrit, soften);
          }

          //update v at t+dt;
          for (int j = 0; j < bodylist.size(); j++) {
               bodylist[j]->UpdateV(0.5*dt);
          }


          if (frame % 10 == 0) {
               char filename2[20];
               sprintf(filename2, "%s_%04d.txt", FILEPRE, frame);
               file_s = filename2;
               OutFile.open(file_s);

               for (int j = 0; j < bodylist.size(); j++) {
                    bodylist[j]->WriteStateToFileM1(OutFile);
               }
               OutFile.close();
          }
     };
}


