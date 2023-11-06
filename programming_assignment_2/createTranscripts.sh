echo "Creating all the required transcripts..."

# Create the transcript for the Australia map coloring problem
./DPLL ./CNFs/mapcolor.cnf > ./transcripts/results_mapcolor.txt
./DPLL ./CNFs/mapcolor.cnf +UCH > ./transcripts/results_mapcolor.UCH.txt

# second model: Add QG to the KB
./DPLL ./CNFs/mapcolor.cnf QG > ./transcripts/results_mapcolor2.txt
./DPLL ./CNFs/mapcolor.cnf QG +UCH > ./transcripts/results_mapcolor2.UCH.txt

# second model: Make an inconsistency by adding QG and VB as facts.
./DPLL ./CNFs/mapcolor.cnf QG VB > ./transcripts/results_mapcolor3.txt
./DPLL ./CNFs/mapcolor.cnf QG VB +UCH > ./transcripts/results_mapcolor3.UCH.txt


# Create the transcript for Sammy's sport shop

# Scenario A: O1Y O2W O3Y L1W L2Y L3B
./DPLL ./CNFs/sammy.cnf O1Y O2W O3Y L1W L2Y L3B > ./transcripts/results_sammy_scenarioA.txt
./DPLL ./CNFs/sammy.cnf O1Y O2W O3Y L1W L2Y L3B +UCH > ./transcripts/results_sammy_scenarioA.UCH.txt

# Scenario B: O1W O2Y O3W L1W L2B L3B
./DPLL ./CNFs/sammy.cnf O1W O2Y O3W L1W L2B L3B > ./transcripts/results_sammy_scenarioB.txt
./DPLL ./CNFs/sammy.cnf O1W O2Y O3W L1W L2B L3B +UCH > ./transcripts/results_sammy_scenarioB.UCH.txt


# Create the transcript for the n-Queens problem (3-6 queens):

minN=3
maxN=6

for i in $(seq $minN $maxN);
do
    ./DPLL ./CNFs/${i}queens.cnf > ./transcripts/results_${i}queens.txt
    ./DPLL ./CNFs/${i}queens.cnf +UCH > ./transcripts/results_${i}queens.UCH.txt
done

echo "...done!"