#!/bin/bash
# building the cnf genrator and them generating the 4 CNFs (a, b, c, p0) for K=8, and run CaDiCaL on each, saving the solver log and DRAT proof.
#   UNSAT (exit 20)
#   SAT   (exit 10)

set -e
cd "$(dirname "$0")"
g++ -std=c++23 -O2 -o cnf_generator cnf_generator.cpp
(cd cnfs && ../cnf_generator)
exec > >(tee prob2.log)
printf "%-8s %-6s %-8s %-8s %s\n" "Property" "Vars" "Clauses" "Lemmas" "Result"
printf "%-8s %-6s %-8s %-8s %s\n" "--------" "----" "-------" "------" "------"
for cnf in cnfs/*.cnf; do
  name=$(basename "$cnf" .cnf)
  set +e
  ./cadical --binary=false "$cnf" "proofs/$name.drat" > "logs/$name.log" 2>&1
  rc=$?
  set -e
  case $rc in
    10) res="SAT   (counterexample exists)" ;;
    20) res="UNSAT (property holds for K=8)" ;;
    *)  res="ERROR (exit $rc)" ;;
  esac
  read -r _ _ vars clauses < "$cnf"
  lemmas=$(grep -c -v '^d ' "proofs/$name.drat")
  printf "%-8s %-6s %-8s %-8s %s\n" "$name" "$vars" "$clauses" "$lemmas" "$res"
done
