echo "Creating all the necessary CNF files..."

# Create the knowledge base for the Australia map coloring problem
python3 ./mapcolor/mapcolor.py > ./mapcolor/mapcolor.kb
python3 convCNF.py ./mapcolor/mapcolor.kb -DIMACS > ../CNFs/mapcolor.cnf

# Create the knowledge base for Sammy's sport shop problem:
python3 ./sammy/sammy.py > ./sammy/sammy.kb
python3 convCNF.py ./sammy/sammy.kb -DIMACS > ../CNFs/sammy.cnf

# Create the knowledge bases for the n-Queens problem (3-6 queens):

minN=3
maxN=6

for i in $(seq $minN $maxN);
do
    python3 ./nQueens/nQueens.py $i > ./nQueens/${i}queens.kb
    python3 convCNF.py ./nQueens/${i}queens.kb -DIMACS > ../CNFs/${i}queens.cnf
done

echo "...done!"