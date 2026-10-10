//
// Created by Divyanshu Gupta on 06/10/26.
//

#include <iostream>
extern "C" {
#include "bdduser.h"
}

using namespace std;

int main()
{
  bdd_manager m = bdd_init();
  auto var = [&] {return bdd_new_var_last(m);};
  auto NOT = [&](bdd a) {return bdd_not(m, a);};
  auto AND = [&](bdd a, bdd b) {return bdd_and(m, a, b);};
  auto OR  = [&](bdd a, bdd b) {return bdd_or(m, a, b);};

  bdd p  = var(), np  = var();
  bdd q0 = var(), nq0 = var();
  bdd q1 = var(), nq1 = var();
  bdd r0 = var(), r1  = var();

  bdd qv[] = { p, q0, q1, r0, r1, 0};
  bdd rn[] = { np, p, nq0, q0, nq1, q1, 0};
  int quant = bdd_new_assoc(m, qv, 0), ren = bdd_new_assoc(m, rn, 1);

  bdd g0 = bdd_ite(m, p, AND(q0, NOT(q1)), q0);
  bdd g1 = bdd_ite(m, p, q1, AND(q1, NOT(q0))); 

  bdd f_q0 = OR(AND(r0, NOT(q0)), AND(NOT(g0), q0));
  bdd f_q1 = OR(AND(r1, NOT(q1)), AND(NOT(g1), q1));

  bdd f_p = bdd_xor(m, p, OR(g0,g1));

  bdd T = AND(bdd_xnor(m, np, f_p),AND(bdd_xnor(m, nq0, f_q0),bdd_xnor(m, nq1, f_q1)));
  bdd R  = AND(NOT(p), AND(NOT(q0), NOT(q1)));

  for (int i = 1;; i++) 
  {
    bdd_assoc(m, quant);
    bdd img = bdd_rel_prod(m, R, T); // ∃x,r.R·T
    bdd_assoc(m, ren);
    img = bdd_substitute(m, img);// x'->x
    bdd Rn = OR(R, img);
    if (Rn == R)
    { 
      cout << "fixed point after " << i << " iterations\n"; 
      break; 
    }
    R = Rn;
  }

  for (int s=0; s< 8; s++) 
  {
    int a = s/4; 
    int b = (s/2)&1;
    int c = s & 1;
    bdd cube = AND(a ? p : NOT(p), AND(b ? q0 : NOT(q0), c ? q1 : NOT(q1)));
    if (AND(R, cube) != bdd_zero(m))
      cout << "(p,q0,q1) = (" << a << "," << b << "," << c << ")\n";
  }
  
  bdd_quit(m);

}
