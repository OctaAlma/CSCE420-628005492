states = ["WA", "NT", "SA", "Q", "NSW", "V", "T"]
colors = ["R", "G", "B"]

allNeighbors = {
    "WA" : ["NT", "SA"], 
    "NT" : ["WA", "SA", "Q"], 
    "SA" : ["WA", "NT", "Q", "NSW", "V"], 
    "Q" : ["NT", "SA", "NSW"], 
    "NSW" : ["Q", "SA", "V"], 
    "V" : ["SA", "NSW"], 
    "T" : []
}

clauses = []

# Every state has to be some color
for s in states:
    curr = "(or "
    for c in colors:
        curr += s + c + " "
    curr += ")"
    clauses.append(curr)

# Each state cannot have the same color as its neighbors
for s in states:
    for c in colors:
        neighbors = allNeighbors[s]
        for n in neighbors:
            curr = "(-> " + s + c + " (not " + n + c + "))"
            clauses.append(curr)

# If a state is not two colors, then it must necessarily be the third color:
for s in states:
    for c in colors:
        noC = [otherc for otherc in colors if otherc != c]
        noC1 = noC[0]
        noC2 = noC[1]

        curr = "(<-> " + s + c + " (and (not " + s + noC1 + ") (not " + s + noC2 + ")))"
        clauses.append(curr)

for i in clauses:
    print(i)