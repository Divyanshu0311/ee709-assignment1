//
// Created by Divyanshu Gupta on 10/10/26.
//

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> cnf;
void add (vector<int> v) {
  cnf.push_back(v);
}

int V(int k, int i) {
  return 5*k + i;
}

void transition(int k, bool pzero) {

  int p = V(k,1), q0 = V(k,2), q1 = V(k,3), r0 = V(k,4), r1 = V(k,5);
  int P = V(k+1,1), Q0 = V(k+1,2), Q1 = V(k+1,3);

  if (!pzero) {
    add({ q0,-r0, Q0});
    add({-q0,-p,-q1, Q0});
    add({ q0, r0,-Q0});
    add({-q0, p,-Q0});
    add({-q0, q1,-Q0});
    //starting 5 equations shown in appendix 1, Q0 represents q_0(k+1)

    add({ q1,-r1, Q1});
    add({-q1, p,-q0, Q1});
    add({ q1, r1,-Q1});
    add({-q1,-p,-Q1});
    add({-q1, q0,-Q1});
    //starting 5 equations shown in appendix 1, Q1 represents q_1(k+1)

    add({ p,-q0, P});
    add({ p,-q1, P});
    add({-p, q0, q1, P});
    add({ p, q0, q1,-P});
    add({-p,-q0,-P});
    add({-p,-q1,-P});
    // last 6 equations, P represents p(k+1)
  }
  else {
    add({ q0,-r0, Q0});
    add({ r0,-Q0});
    add({-q0,-Q0});
    add({ q1,-r1, Q1});
    add({-q1,-q0, Q1});
    add({ q1, r1,-Q1});
    add({-q1, q0,-Q1});
  }
}

int main() {
  int K = 8; //8 cycles
  for (string pro : {"a", "b", "c", "p0"}) {
    cnf.clear();
    bool pz = (pro == "p0");

    for (int k = 0; k + 1 < K; k++)
      transition(k, pz);


    int nv = 5*K;

    if (pro == "a") {
      add({V(0,4)});
      for (int k = 0; k < K; k++) {
        add({-V(k,2), V(k,1)});
        add({-V(k,2), V(k,3)});
      }
    }
    if (pro == "b") {
      add({V(0,5)});
      for (int k = 0; k < K; k++) {
        add({-V(k,3), -V(k,1)});
        add({-V(k,3), V(k,2)});
      }
    }
    if (pro == "c") {
      vector<int> some;
      for (int i = 0; i< K; i++) {
        int m = 5*K + 1 +i;
        some.push_back(m);
        add({-m, V(i,2)});
        add({-m, -V(i,1), -V(i,3)});
        add({-m, V(i,3)});
        add({-m,  V(i,1), -V(i,2)});
      }
      add(some);
      nv = 6*K;
    }
    if (pro == "p0") {
      for (int k = 0; k < K; k++)
        add({-V(k,1)});

      add({V(0,5)});

      for (int k = 0; k < K; k++)
        add({-V(k,3), V(k,2)});
    }

    ofstream f(pro + "_K" + to_string(K) + ".cnf");
    f << "p cnf " << nv << " " << cnf.size() << "\n";
    for (auto &c : cnf) {
      for (int l : c)
        f << l << " "; f << "0\n";
    }
  }
}