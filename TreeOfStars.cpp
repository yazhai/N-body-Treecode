#include "stdafx.h"
#include <iostream>

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include "TreeCodeNode.h"
#include "TreeOfStars.h"
#include "param.h"

using namespace std;

//private functions

void TreeOfStars::deletenodechildren(TreeCodeNode* & todelete) {
     if (todelete->child_111) {
          deletenodeself(todelete->child_111);
     }
     if (todelete->child_112) {
          deletenodeself(todelete->child_112);
     }
     if (todelete->child_121) {
          deletenodeself(todelete->child_121);
     }
     if (todelete->child_122) {
          deletenodeself(todelete->child_122);
     }
     if (todelete->child_211) {
          deletenodeself(todelete->child_211);
     }
     if (todelete->child_212) {
          deletenodeself(todelete->child_212);
     }
     if (todelete->child_221) {
          deletenodeself(todelete->child_221);
     }
     if (todelete->child_222) {
          deletenodeself(todelete->child_222);
     }
     return;
}

void TreeOfStars::deletenodeself(TreeCodeNode*& todelete) {
     // delete the node itself:
     // first, delete all its children
     // second, its parent->numofchildren --, possible ptr towards itself in CelestialBody is set as null
     // thirdly, delete it completely

     if (todelete->numofchild > 0) {
          deletenodechildren(todelete);
     }

     //if ((todelete->whichstaristhisnode)) { *(todelete->whichstaristhisnode) = nullptr; };

     if (todelete->parent) {
          // if this is a leaf, its parent children's number --, and delete this node
          auto tmpp = todelete->parent;
          tmpp->numofchild--;
          tmpp->numofallleaf -= todelete->numofallleaf;
          while (tmpp->parent) {
               tmpp = tmpp->parent;
               tmpp->numofallleaf -= todelete->numofallleaf;
          }
          tmpp = todelete->parent;
          if (todelete->childidx == 1) {
               delete todelete;
               //delete todelete->parent->child_111;
               tmpp->child_111 = nullptr;
          }
          else if (todelete->childidx == 2) {
               delete todelete;
               //delete todelete->parent->child_112;
               tmpp->child_112 = nullptr;
          }
          else if (todelete->childidx == 3) {
               delete todelete;
               //delete todelete->parent->child_121;
               tmpp->child_121 = nullptr;
          }
          else if (todelete->childidx == 4) {
               delete todelete;
               //delete todelete->parent->child_122;
               tmpp->child_122 = nullptr;
          }
          else if (todelete->childidx == 5) {
               delete todelete;
               //delete todelete->parent->child_211;
               tmpp->child_211 = nullptr;
          }
          else if (todelete->childidx == 6) {
               delete todelete;
               //delete todelete->parent->child_212;
               tmpp->child_212 = nullptr;
          }
          else if (todelete->childidx == 7) {
               delete todelete;
               //delete todelete->parent->child_221;
               tmpp->child_221 = nullptr;
          }
          else if (todelete->childidx == 8) {
               delete todelete;
               //delete todelete->parent->child_222;
               tmpp->child_222 = nullptr;
          }
     }
     else {
          delete todelete;
     }
}

//public functions
TreeOfStars::TreeOfStars(double iox, double ioy, double ioz, double idx, double idy, double idz) {
     // initialize the Tree in the region with input parameters.
     root = new TreeCodeNode(iox, ioy, ioz, idx, idy, idz);
}

TreeOfStars::~TreeOfStars() {
     // default destructor
     deletenodeself(root);
}


bool TreeOfStars::erase() {
     deletenodechildren(root);
     root->cmx = 0;
     root->cmy = 0;
     root->cmz = 0;
     root->tm = 0;
     root->numofchild = -1;
     root->numofallleaf = 0;
     root->childidx = 0;

     return true;
}


bool TreeOfStars::insertnode(double x, double y, double z, double m, TreeCodeNode* & targetnode) {

     // if the object is out of the range, return false
     if ((x < targetnode->ox - targetnode->dx / 2) || (x > targetnode->ox + targetnode->dx / 2) || (y < targetnode->oy - targetnode->dy / 2) || (y > targetnode->oy + targetnode->dy / 2) || (z < targetnode->oz - targetnode->dz / 2) || (z > targetnode->oz + targetnode->dz / 2)) {
          return false;
     }

     // target node is an unoccupied leaf : save mass point info to this leaf
     // all parents numofallleaf ++
     if ((targetnode->numofchild == -1) && (targetnode->numofallleaf == 0)) {
          targetnode->numofchild++;
          targetnode->numofallleaf++;
          targetnode->tm = m;
          targetnode->cmx = x;
          targetnode->cmy = y;
          targetnode->cmz = z;

          TreeCodeNode* curr = targetnode;
          while (curr->parent) {
               curr = curr->parent;
               curr->numofallleaf++;
          }

          return true;
     }
     else {

          // check if this is an occupied leaf
          if ((targetnode->numofchild == 0) && (targetnode->numofallleaf == 1)) {

               // if so, create child and move current star to that cild
               targetnode->numofchild++;
               TreeCodeNode* towhich2 = nullptr;
               if (targetnode->cmx < targetnode->ox) {
                    if (targetnode->cmy < targetnode->oy) {
                         if (targetnode->cmz < targetnode->oz) {
                              targetnode->child_111 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 1);
                              towhich2 = (targetnode->child_111);
                         }
                         else {
                              targetnode->child_112 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 2);
                              towhich2 = (targetnode->child_112);
                         }
                    }
                    else {
                         if (targetnode->cmz < targetnode->oz) {
                              targetnode->child_121 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 3);
                              towhich2 = (targetnode->child_121);
                         }
                         else {
                              targetnode->child_122 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 4);
                              towhich2 = (targetnode->child_122);
                         }
                    }
               }
               else {
                    if (targetnode->cmy < targetnode->oy) {
                         if (targetnode->cmz < targetnode->oz) {
                              targetnode->child_211 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 5);
                              towhich2 = (targetnode->child_211);
                         }
                         else {
                              targetnode->child_212 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 6);
                              towhich2 = (targetnode->child_212);
                         }
                    }
                    else {
                         if (targetnode->cmz < targetnode->oz) {
                              targetnode->child_221 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 7);
                              towhich2 = (targetnode->child_221);
                         }
                         else {
                              targetnode->child_222 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 8);
                              towhich2 = (targetnode->child_222);
                         }
                    }
               }
               // moving the object out of the target node needs to maintain the allleaf num
               TreeCodeNode* curr = targetnode;
               curr->numofallleaf--;
               while (curr->parent) {
                    curr = curr->parent;
                    curr->numofallleaf--;
               }
               // reinsert the info in the targetnode to its child
               insertnode(targetnode->cmx, targetnode->cmy, targetnode->cmz, targetnode->tm, towhich2);
          }

          // after moving possible existing star, the leaf becomes a node. 
          // This time it comes to the inserting star
          // check which child should be inserted;
          // if that child does not exist, create a new child and increase its child count by 1
          // insert the star to that child
          TreeCodeNode*  towhich = nullptr;
          if (x < targetnode->ox) {
               if (y < targetnode->oy) {
                    if (z < targetnode->oz) {
                         towhich = (targetnode->child_111);
                         if (towhich == nullptr) {
                              targetnode->child_111 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 1);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_111);
                         }
                    }
                    else {
                         towhich = (targetnode->child_112);
                         if (towhich == nullptr) {
                              targetnode->child_112 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 2);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_112);
                         }
                    }
               }
               else {
                    if (z < targetnode->oz) {
                         towhich = (targetnode->child_121);
                         if (towhich == nullptr) {
                              targetnode->child_121 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 3);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_121);
                         }
                    }
                    else {
                         towhich = (targetnode->child_122);
                         if (towhich == nullptr) {
                              targetnode->child_122 = new TreeCodeNode(targetnode->ox - targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 4);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_122);
                         }
                    }
               }
          }
          else {
               if (y < targetnode->oy) {
                    if (z < targetnode->oz) {
                         towhich = (targetnode->child_211);
                         if (towhich == nullptr) {
                              targetnode->child_211 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 5);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_211);
                         }
                    }
                    else {
                         towhich = (targetnode->child_212);
                         if (towhich == nullptr) {
                              targetnode->child_212 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy - targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 6);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_212);
                         }
                    }
               }
               else {
                    if (z < targetnode->oz) {
                         towhich = (targetnode->child_221);
                         if (towhich == nullptr) {
                              targetnode->child_221 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz - targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 7);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_221);
                         }
                    }
                    else {
                         towhich = (targetnode->child_222);
                         if (towhich == nullptr) {
                              targetnode->child_222 = new TreeCodeNode(targetnode->ox + targetnode->dx / 4, targetnode->oy + targetnode->dy / 4, targetnode->oz + targetnode->dz / 4, targetnode->dx / 2, targetnode->dy / 2, targetnode->dz / 2, targetnode, 8);
                              targetnode->numofchild++;
                              towhich = (targetnode->child_222);
                         }
                    }
               }
          }
          return insertnode(x, y, z, m, towhich); // insert the star to the target
     };

}

//
//bool TreeOfStars::removenode(double x, double y, double z, TreeCodeNode* & toremove) {
//     double detx = x - toremove->ox;
//     double dety = y - toremove->oy;
//     double detz = z - toremove->oz;
//
//     // check if the object a leaf
//     if (toremove->numofchild > 0) {
//          // not a leaf -> no remove
//          //std::cout << "error: try to remove an internal node" << endl;
//          return false;
//     }
//     else {
//          // remove from a leaf
//          if ((detx >= -(toremove->dx / 2)) && (detx < (toremove->dx / 2))) {
//               if ((dety >= -(toremove->dy / 2)) && (dety < (toremove->dy / 2))) {
//                    if ((detz >= -(toremove->dz / 2)) && (detz < (toremove->dz / 2))) {   
//                         // Bug found 2017/03/25 :
//                         // the content of the node should be updated ( its mass point position should be updated)
//                         // Following is the correction of the bug:.
//                         toremove->cmx = x;
//                         toremove->cmy = y;
//                         toremove->cmz = z;
//                         // correction end.
//
//                         return false; // the object is within the node,do not remove, but updated.
//
//                    }
//               }
//          }
//
//
//          //start removing
//          // if it is the root node
//          // clear the tree, but do not destroy it
//          if (toremove == root) {
//               root->cmx = 0;
//               root->cmy = 0;
//               root->cmz = 0;
//               root->tm = 0;
//               root->numofchild = -1;
//               root->numofallleaf = 0;
//               //if (root->whichstaristhisnode) {
//                    //*(root->whichstaristhisnode) = nullptr;
//               //}
//               //root->whichstaristhisnode = nullptr;
//               return true;
//          }
//
//          // if it is not the root, delete the node completely
//          auto tmpp = toremove->parent;
//          // IT IS HERE THAT GETS ERROR !!!!!!!!!!
//          deletenodeself(toremove);
//
//          // if the parent becomes empty, then remove it
//          while (tmpp->numofallleaf == 0) {
//               if (tmpp->parent) {
//                    auto tmpp2 = tmpp->parent;
//                    deletenodeself(tmpp);
//                    tmpp = tmpp2;
//               }
//               else {
//                    root->cmx = 0;
//                    root->cmy = 0;
//                    root->cmz = 0;
//                    root->tm = 0;
//                    root->numofchild = -1;
//                    root->numofallleaf = 0;
//                    //if (root->whichstaristhisnode) {
//                    //     *(root->whichstaristhisnode) = nullptr;
//                    //}
//                    //root->whichstaristhisnode = nullptr;
//               }
//          }
//          return true;
//     }
//}
//

std::vector<double> TreeOfStars::updatem(TreeCodeNode* & thisnode) {
     std::vector<double> m_cmxyz;
     // return the total mass and mass center's x/y/z as a vector
     // m_cmxyz [0] = tm;
     // m_cmxyz [1] = cmx; [2] = cmy; [3] = cmz

     if ((thisnode->numofchild == 0) && (thisnode->numofallleaf == 1) ) {
          //if this is a leaf, then return its tm and cmxyz
          m_cmxyz.push_back(thisnode->tm);
          m_cmxyz.push_back(thisnode->cmx);
          m_cmxyz.push_back(thisnode->cmy);
          m_cmxyz.push_back(thisnode->cmz);
     }
     else
     {
          // if this is a node, then return the sum of tm and cmxyz

          // initial the sum
          double tm = 0;
          double cmx = 0;
          double cmy = 0;
          double cmz = 0;

          //cm = sigma(tm*cm) / tm_total;
          if (thisnode->child_111 != nullptr) {
               auto tmp = updatem(thisnode->child_111);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };
          if (thisnode->child_112 != nullptr) {
               auto tmp = updatem(thisnode->child_112);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };
          if (thisnode->child_121 != nullptr) {
               auto tmp = updatem(thisnode->child_121);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };
          if (thisnode->child_122 != nullptr) {
               auto tmp = updatem(thisnode->child_122);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };
          if (thisnode->child_211 != nullptr) {
               auto tmp = updatem(thisnode->child_211);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };
          if (thisnode->child_212 != nullptr) {
               auto tmp = updatem(thisnode->child_212);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };
          if (thisnode->child_221 != nullptr) {
               auto tmp = updatem(thisnode->child_221);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };
          if (thisnode->child_222 != nullptr) {
               auto tmp = updatem(thisnode->child_222);
               tm += tmp[0];
               cmx += tmp[0] * tmp[1];
               cmy += tmp[0] * tmp[2];
               cmz += tmp[0] * tmp[3];
          };

          cmx = cmx / tm;
          cmy = cmy / tm;
          cmz = cmz / tm;

          thisnode->tm = tm;
          thisnode->cmx = cmx;
          thisnode->cmy = cmy;
          thisnode->cmz = cmz;

          m_cmxyz.push_back(tm);
          m_cmxyz.push_back(cmx);
          m_cmxyz.push_back(cmy);
          m_cmxyz.push_back(cmz);
     };


     return  m_cmxyz;
}

vector<double> TreeOfStars::getAfromnode(double x, double y, double z, double distcriterion, double soften, TreeCodeNode* fromthisnode) {
     // To a point at x/y/z, obtain the acceleration from "fromthisnode" and ALL its childrens 
     // Return the acceleration as a vector
     vector<double> a; // acceleration, a[0] = ax; a[1] = ay; a[2] = az
     a.push_back(0.0);
     a.push_back(0.0);
     a.push_back(0.0);


     double detx = x - fromthisnode->ox;
     double dety = y - fromthisnode->oy;
     double detz = z - fromthisnode->oz;


     // check if the object is within the range of a LEAF : if so, then it is itself. Return zero then
     if ((fromthisnode->numofchild == 0) || (fromthisnode->numofallleaf == 1)) {
          if ((detx >= -(fromthisnode->dx / 2)) && (detx < (fromthisnode->dx / 2))) {
               if ((dety >= -(fromthisnode->dy / 2)) && (dety < (fromthisnode->dy / 2))) {
                    if ((detz >= -(fromthisnode->dz / 2)) && (detz < (fromthisnode->dz / 2))) {
                         return a;
                    }
               }
          }
     }

     double r; // distance between (x,y,z) and center of the node
     double d; // dimension of the node, choose max dimension of the node
     d = fromthisnode->dx;
     if (fromthisnode->dy > d) {
          d = fromthisnode->dy;
     }
     if (fromthisnode->dz > d) {
          d = fromthisnode->dz;
     }
     r = sqrt(detx*detx + dety*dety + detz*detz);

     if ((r!=0) && (d / r > distcriterion) ) {
          //if the point at x/y/z is close enought to the node (not a leaf), then calculate a by each child
          if ( (fromthisnode->numofchild > 0) && (fromthisnode->numofallleaf > 1) ) {
               if (fromthisnode->child_111 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_111);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               if (fromthisnode->child_112 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_112);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               if (fromthisnode->child_121 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_121);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               if (fromthisnode->child_122 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_122);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               if (fromthisnode->child_211 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_211);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               if (fromthisnode->child_212 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_212);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               if (fromthisnode->child_221 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_221);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               if (fromthisnode->child_222 != nullptr) {
                    auto tmp = getAfromnode(x, y, z, distcriterion, soften, fromthisnode->child_222);
                    a[0] += tmp[0];
                    a[1] += tmp[1];
                    a[2] += tmp[2];
               }
               return a;
          }
     }

     // If the point is either faraway from the node, or close to a leaf, so calculate directly from Newtion's law
     // renew detx/y/z and r to the center of mass
     detx = x - (fromthisnode->cmx);
     dety = y - (fromthisnode->cmy);
     detz = z - (fromthisnode->cmz);
     r = sqrt(detx*detx + dety*dety + detz*detz + soften*soften);

     a[0] = -G * fromthisnode->tm * detx / (r*r*r);
     a[1] = -G * fromthisnode->tm * dety / (r*r*r);
     a[2] = -G * fromthisnode->tm * detz / (r*r*r);

     return a;
}



