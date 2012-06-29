#include <stdio.h>
#include <stdlib.h>

#include "Pattern.h"

#include <vector>
#include <yarp/sig/all.h>

using namespace yarp::sig;
using namespace std;

//#define VERBOSE 1

int indexify(int code, int factor, vector<int>& book, 
	     vector<int>& remaining, int omit) {
  for (int j=0; j<book.size()-omit; j++) {
    int x = book[j];
    int v = -1;
    for (int i=0; i<(int)remaining.size(); i++) {
      if (remaining[i] == x) {
	v = i;
	break;
      }
    }
    if (v==-1) {
      fprintf(stderr, "Failed to find code\n");
      exit(1);
    }
    int next_range = (int)remaining.size();
    remaining.erase(remaining.begin()+v);
    
    code += v*factor;
    factor *= next_range;
  }
  return code;
}

bool Patterns::load(const char *fname) {
  return file::read(ref,fname);
}

/*
  Order:
  2*7! + 2*8! = 90 720
  highest order code should be 90719

  Now, looking at inter-pixel timestamp behavior
    1 = big jump, 0 = small jump
  8 jump codes -> *256.
  Definition of big jump?  

  // suppose we care only about the 5 most recently touched cells.
  -->  2*(7 choose 3) + 2*(8 choose 4) = 420 + 1680

*/


//getTop: return 2*840 + 2*6720;

Pattern Patterns::evaluate1(yarp::sig::ImageOf<yarp::sig::PixelFloat>& stamp,
			   int cx, int cy) {
  cx--;
  cy--;

  Pattern p;

  int order[9] = {0,1,2,3,4,5,6,7,8};
  double vals[9];
  int at = 0;
  for (int y=0; y<3; y++) {
    for (int x=0; x<3; x++) {
      vals[at] = stamp(x+cx,y+cy);
      at++;
    }
  }
  bool more = true;
  for (int i=1; i<9;i++) {
    double item = vals[i];
    int oitem = order[i];
    int ihole = i;
    while (ihole>0 && vals[ihole-1]>item) {
      vals[ihole] = vals[ihole-1];
      order[ihole] = order[ihole-1];
      ihole--;
    }
    vals[ihole] = item;
    order[ihole] = oitem;
  }
  // 0 1 2
  // 3 4 5
  // 6 7 8

#ifdef VERBOSE
  printf("values:\n");
  double total = 0;
  for (int y=0; y<3; y++) {
    for (int x=0; x<3; x++) {
      printf("[%d]%g ", y*3+x, stamp(x,y));
      total += stamp(x,y);
    }
    printf("\n");
  }
  printf("order: ");
  for (int k=0; k<9; k++) {
    printf("%d ", order[k]);
  }
  printf("\n");
#endif

  int index = 0;
  int offset = 0;
  int base = -1;
  int factor = 1;
  int index_area = 0;
  if (order[0]==4) {
    offset++;
  } else {
    //// offset into 8! area
    //index_area = 10080; // 2*7!

    // offset into 6! area
    //index_area = 240; // 2*5!

    index_area = 2*840;

    base = order[0];
  }
  int v = order[offset];
  if (!(v==0 || v==2 || v==6 || v==8)) {
    index += 1*factor;
  }
  factor *= 2;
  if (base==-1) base = v;
  // base has certainly been set at this point, and
  // we've used up our rotational-normalization freedom.
  // we still have a mirror-symmetry, but not going to use it yet.
  // We have 8 or 7 (8 minus offset) cells remaining.

  // Should check what rotation we've made.
  //   1,2 -> 0
  //   5,8 -> 90
  //   7,6 -> 180
  //   0,3 -> 270
  // 0 1 2
  // 3 4 5
  // 6 7 8
  double rotation = 0;
  double crx = 1;
  double cry = 0;
  switch(base) {
  case 1:
  case 2:
    rotation = 0;
    crx = 1;
    cry = 0;
    break;
  case 5:
  case 8:
    rotation = M_PI/2;
    crx = 0;
    cry = -1;
    break;
  case 7:
  case 6:
    rotation = M_PI;
    crx = -1;
    cry = 0;
    break;
  case 0:
  case 3:
    rotation = -M_PI/2;
    crx = 0;
    cry = 1;
    break;
  }

  // code gets inefficient at this point.
  vector<int> book, remaining;
  if (offset==0) {
    remaining.push_back(-1);
  }
  for (int k=0; k<7; k++) {
    remaining.push_back(k);
  }
  int border_reverse[9] = {0,1,2,7,-1,3,6,5,4};
  int border_forward[8] = {0, 1, 2, 5, 8, 7, 6, 3};
  /*
  int k0 = border_reverse[base];
  for (int k=k0+1; k<k0+8; k++) {
    remaining.push_back(border_forward[k%8]);
  }
  */

  for (int k=offset+1; k<9; k++) {
    int v = order[k];
    if (v==4) { book.push_back(-1); continue; }
    int k0 = (border_reverse[v]-border_reverse[base]+8)%8 - 1;
    book.push_back(k0);
  }

  index = indexify(index, factor, book, remaining, 3);
  index += index_area;


#if 0
  index *= 8;
  factor = 1;
  double mdiff = 0;
  for (int i=0; i<8; i++) {
    mdiff += fabs(vals[i+1]-vals[i]);
  }
  mdiff /= 8;
  int jump = 0;
  for (int i=0; i<8; i++) {
    double diff = fabs(vals[i+1]-vals[i]);
    if (diff>mdiff*2) {
      jump = i;
      break;
    }
  }
  index += jump;
#endif

  p.code = index;
  p.pattern_rotation = rotation;
  p.pattern_rx = crx;
  p.pattern_ry = cry;

  if (index<ref.height()) {
    double xx = ref(1,index);
    double yy = ref(2,index);
    p.x =   crx*xx + cry*yy;
    p.y =  -cry*xx + crx*yy;
    p.mag = ref(3,index);
  }

  return p;
}




















// getTop: 2
Pattern Patterns::evaluate2(yarp::sig::ImageOf<yarp::sig::PixelFloat>& stamp,
			    int cx, int cy) {
  cx--;
  cy--;

  Pattern p;

  int order[9] = {0,1,2,3,4,5,6,7,8};
  double vals[9];
  int at = 0;
  for (int y=0; y<3; y++) {
    for (int x=0; x<3; x++) {
      vals[at] = stamp(x+cx,y+cy);
      at++;
    }
  }
  bool more = true;
  for (int i=1; i<9;i++) {
    double item = vals[i];
    int oitem = order[i];
    int ihole = i;
    while (ihole>0 && vals[ihole-1]>item) {
      vals[ihole] = vals[ihole-1];
      order[ihole] = order[ihole-1];
      ihole--;
    }
    vals[ihole] = item;
    order[ihole] = oitem;
  }
  if (fabs(vals[0]-vals[1])<0.00001) {
    return p;
  }
  if (fabs(vals[0]-vals[8])<0.00001) {
    return p;
  }

  // FLIPPING Y:
  // 6 7 8
  // 3 4 5
  // 0 1 2

  int index = 0;
  int offset = 0;
  int base = -1;
  int factor = 1;
  int index_area = 0;
  if (order[0]==4) {
    offset++;
  } else {
    index_area = 2;
    base = order[0];
  }
  int v = order[offset];
  if ((v==0 || v==2 || v==6 || v==8)) {
    index += 1*factor;
  }
  factor *= 2;
  if (base==-1) base = v;
  // base has certainly been set at this point, and
  // we've used up our rotational-normalization freedom.
  // we still have a mirror-symmetry, but not going to use it yet.
  // We have 8 or 7 (8 minus offset) cells remaining.

  // Should check what rotation we've made.
  //   1,2 -> 90
  //   5,8 -> 0
  //   7,6 -> -90
  //   0,3 -> -180
  // 6 7 8
  // 3 4 5
  // 0 1 2
  double rotation = 0;
  double crx = 1;
  double cry = 0;
  switch(base) {
  case 1:
  case 2:
    rotation = -M_PI/2;
    crx = 0;
    cry = -1;
    break;
  case 5:
  case 8:
    rotation = 0;
    crx = 1;
    cry = 0;
    break;
  case 7:
  case 6:
    rotation = M_PI/2;
    crx = 0;
    cry = 1;
    break;
  case 0:
  case 3:
    rotation = M_PI;
    crx = -1;
    cry = 0;
    break;
  }

  //index += index_area;

  //if (base!=1 && base!=2) {
  //if (base!=7 && base!=6) {
  //if (base!=5 && base!=8) {
  //if (base!=3 && base!=0) {
  //  index = -1;
  //}

  p.code = index;
  p.pattern_rotation = rotation;
  p.pattern_rx = crx;
  p.pattern_ry = cry;

  if (index<ref.height() && index!=-1) {
    double xx = ref(1,index);
    double yy = ref(2,index);
    p.x =   crx*xx - cry*yy;
    p.y =   cry*xx + crx*yy;
    p.mag = ref(3,index);
  }

  return p;
}




Pattern Patterns::evaluate(yarp::sig::ImageOf<yarp::sig::PixelFloat>& stamp,
			   int cx, int cy) {
  cx--;
  cy--;

  Pattern p;

  int order[9] = {0,1,2,3,4,5,6,7,8};
  double vals[9];
  int at = 0;
  for (int y=0; y<3; y++) {
    for (int x=0; x<3; x++) {
      vals[at] = stamp(x+cx,y+cy);
      at++;
    }
  }
  bool more = true;
  for (int i=1; i<9;i++) {
    double item = vals[i];
    int oitem = order[i];
    int ihole = i;
    while (ihole>0 && vals[ihole-1]>item) {
      vals[ihole] = vals[ihole-1];
      order[ihole] = order[ihole-1];
      ihole--;
    }
    vals[ihole] = item;
    order[ihole] = oitem;
  }
  if (fabs(vals[0]-vals[1])<0.00001) {
    return p;
  }
  if (fabs(vals[0]-vals[8])<0.00001) {
    return p;
  }

  // FLIPPING Y:
  // 6 7 8
  // 3 4 5
  // 0 1 2

  int index = 0;
  int offset = 0;
  int base = -1;
  int factor = 1;
  int index_area = 0;
  if (order[0]==4) {
    offset++;
  } else {
    index_area = 2;
    base = order[0];
  }
  int v = order[offset];
  if ((v==0 || v==2 || v==6 || v==8)) {
    index += 1*factor;
  }
  factor *= 2;
  if (base==-1) base = v;
  // base has certainly been set at this point, and
  // we've used up our rotational-normalization freedom.
  // we still have a mirror-symmetry, but not going to use it yet.
  // We have 8 or 7 (8 minus offset) cells remaining.

  // Should check what rotation we've made.
  //   1,2 -> 90
  //   5,8 -> 0
  //   7,6 -> -90
  //   0,3 -> -180
  // 6 7 8
  // 3 4 5
  // 0 1 2
  double rotation = 0;
  double crx = 1;
  double cry = 0;
  switch(base) {
  case 1:
  case 2:
    rotation = -M_PI/2;
    crx = 0;
    cry = -1;
    break;
  case 5:
  case 8:
    rotation = 0;
    crx = 1;
    cry = 0;
    break;
  case 7:
  case 6:
    rotation = M_PI/2;
    crx = 0;
    cry = 1;
    break;
  case 0:
  case 3:
    rotation = M_PI;
    crx = -1;
    cry = 0;
    break;
  }

  index += index_area;

  //if (base!=1 && base!=2) {
  //if (base!=7 && base!=6) {
  //if (base!=5 && base!=8) {
  //if (base!=3 && base!=0) {
  //  index = -1;
  //}

  p.code = index;
  p.pattern_rotation = rotation;
  p.pattern_rx = crx;
  p.pattern_ry = cry;

  if (index<ref.height() && index!=-1) {
    double xx = ref(1,index);
    double yy = ref(2,index);
    p.x =   crx*xx - cry*yy;
    p.y =   cry*xx + crx*yy;
    p.mag = ref(3,index);
  }

  return p;
}



int Patterns::getTop() {
  return 4;
}
