contents = ["W", "Y", "B"]
observations = ["W", "Y"]
boxes = ["1", "2", "3"]

clauses = []

# Labels tell us what the box does not have
# e.g: L1W -> -C1W
for b in boxes:
    for c in contents:
        curr = "(-> L" + b + c + " (not C" + b + c + "))"
        clauses.append(curr)

# Each box only has ONE label
# E.g: L1W <-> -L1Y ^ -L1B
for b in boxes:
    for c in contents:
        noC = [otherc for otherc in contents if otherc != c]
        
        c2 = noC[0]
        c3 = noC[1]

        curr = "(<-> L" + b + c + " (and (not L" + b + c2 + ") (not L" + b + c3 + ")))"
        clauses.append(curr)

# We can derive what a box contains based on what it does not contain
# e.g: C1W <-> -C1Y ^ -C1B
for b in boxes:
    for c in contents:
        noC = [otherc for otherc in contents if otherc != c]
        
        c2 = noC[0]
        c3 = noC[1]

        curr = "(<-> C" + b + c + " (and (not C" + b + c2 + ") (not C" + b + c3 + ")))"
        clauses.append(curr)

# Observing some color can let us know what their contents are:
# E.g: O1W -> C1W v C1B
for b in boxes:
    for o in observations:
    
        curr = "(-> O" + b + o + " (or C" + b + o + " C" + b + "B))"
        clauses.append(curr)

# Observing a color implies that the explicit color is not in the box
# e.g: O1W -> -C1Y
for b in boxes:
    for o in observations:
        noO = [othero for othero in observations if othero != o]
        
        noto = noO[0]

        curr = "(-> O" + b + o + " (not C" + b + noto + "))"
        clauses.append(curr)

# Each box can only contain one of the labels:
# E.g: C1W <-> -C1Y ^ -C1B
for b in boxes:
    for c in contents:
        noC = [otherc for otherc in contents if otherc != c]
    
        c2 = noC[0]
        c3 = noC[1]

        curr = "(<-> C" + b + c + " (and (not C" + b + c2 + ") (not C" + b + c3 + ")))"
        clauses.append(curr)

# Containing something implies that we will see something:
# E.g: C1W -> O1W ^ -O1Y
# E.g: C1B -> O1W v O1Y
for b in boxes:
    for c in contents:
        curr = "(-> C" + b + c + " "

        if (c == "B"):
            curr += "(or O" + b + observations[0] + " O" + b + observations[1] + "))"
        else:
            noO = [othero for othero in observations if othero != c]
            noto = noO[0]
            curr += "(and O" + b + c + " (not O" + b + noto + ")))"
            #curr += "O" + b + c + ")"

        clauses.append(curr)

# The box contents are unique!
# E.g: C1W -> -C2W ^ -C3W
for b in boxes:
    for c in contents:
        noB = [otherb for otherb in boxes if otherb != b]
        
        b2 = noB[0]
        b3 = noB[1]

        curr = "(<-> C" + b + c + " (and (not C" + b2 + c + ") (not C" + b3 + c + ")))"
        clauses.append(curr) 

# The observations are unique!
# E.g: O1W -> -O1Y
for b in boxes:
    curr = "(<-> O" + b + observations[0] + " (not O" + b + observations[1] + "))"
    clauses.append(curr)

for c in clauses:
    print(c)