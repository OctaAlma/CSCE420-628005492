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

# Every state can only be ONE color:
for s in states:
    for c in colors:
        for otherc in colors:
            if (c == otherc):
                continue
            
            curr = "(implies " + s + c + " (not " + s + otherc + "))"
            clauses.append(curr)

# Each state cannot have the same color as its neighbors
for s in states:
    for c in colors:
        neighbors = allNeighbors[s]
        for n in neighbors:
            curr = "(implies " + s + c + " (not " + n + c + "))"
            clauses.append(curr)


for i in clauses:
    print(i)