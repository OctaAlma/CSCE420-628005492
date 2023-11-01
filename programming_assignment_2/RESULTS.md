##RESULTS

Below is the requested text file. All of this data was obtained from the transcripts.

| **Problem**      | **DPLL Calls (No UCH)** | **DPLL Calls with UCH** | **Model Output**                    | **Command Line Inputs**                             |
|------------------|-------------------------|-------------------------|-------------------------------------|-----------------------------------------------------|
| 3 Queens         | 83                      | 38                      | Unsatisfiable                       | ``./DPLL ./CNFs/3queens.cnf``                       |
| 4 Queens         | 113                     | 36                      | Q21 Q42 Q13 Q34                     | ``./DPLL ./CNFs/4queens.cnf``                       |
| 5 Queens         | 46                      | 26                      | Q11 Q32 Q53 Q24 Q45                 | ``./DPLL ./CNFs/5queens.cnf``                       |
| 6 Queens         | 2139                    | 274                     | Q21 Q42 Q63 Q14 Q35 Q56             | ``./DPLL ./CNFs/6queens.cnf``                       |
| Map Color 1      | 36                      | 22                      | WAR NTG SAB QR NSWG VR TR           | ``./DPLL ./CNFs/mapcolor.cnf``                      |
| Map Color 2      | 51                      | 26                      | WAG NTR SAB QG NSWR VG TR           | ``./DPLL ./CNFs/mapcolor.cnf QG``                   |
| Map Color 3      | 77                      | 16                      | Unsatisfiable                       | ``./DPLL ./CNFs/mapcolor.cnf QG VB``                |
| Sammy Scenario A | 68                      | 19                      | L1W C1B C2W L2Y C3Y L3B O1Y O2W O3Y | ``./DPLL ./CNFs/sammy.cnf O1Y O2W O3Y L1W L2Y L3B`` |
| Sammy Scenario B | 34                      | 19                      | L1W C1B C2Y L2B C3W L3B O1W O2Y O3W | ``./DPLL ./CNFs/sammy.cnf O1W O2Y O3W L1W L2B L3B`` |
