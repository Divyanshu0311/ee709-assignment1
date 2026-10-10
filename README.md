# EE 709 Assignment 1

## Contents

```
assignment_1.pdf        problem statement
bddlib.tar.gz           BDD library sources (course provided)
include/, lib/          BDD headers and prebuilt libbdd.a, libmem.a
compile.sh              builds a .cpp against the BDD library and runs it
problem_1/reach.cpp     Problem 1: reachable states using BDDs
problem_2/
  cnf_generator.cpp     Problem 2: writes CNFs for (a), (b), (c), p=0 (K = 8)
  cadical               CaDiCaL 3.0.1 SAT solver binary
  run.sh                builds the generator and solves all CNFs
  cnfs/  logs/  proofs/ outputs
```

## Licenses

- **CaDiCaL**: MIT License, (c) Armin Biere et al. See https://github.com/arminbiere/cadical
- **BDD library** (`bddlib.tar.gz`, `include/`, `lib/`): used in the course;

## Problem 1

```bash
./compile.sh problem_1/reach.cpp
```

This builds `problem_1/reach`, runs it, and prints the reachable states.
There is a saved log for this problem `problem_1/prob.log`
## Problem 2

```bash
./problem_2/run.sh
```

| Output | Location |
|---|---|
| CNF files | `problem_2/cnfs/<prop>_K8.cnf` |
| CaDiCaL logs | `problem_2/logs/<prop>_K8.log` |
| DRAT proofs (text) | `problem_2/proofs/<prop>_K8.drat` |

`<pro>` is `a`, `b`, `c` or `p0`. UNSAT means the property holds over 8 cycles; SAT means a counterexample exists (see the `v` lines in the log).
