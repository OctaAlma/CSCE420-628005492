clauses = []

# HAS TO BE GREATER THAN 3
n = 15

for col in range(1, n+1, 1):
    for row in range(1, n+1, 1):
        
        for otherCol in range(1, n+1, 1):
            if (otherCol == col):
                continue

            # If a queen is in column j, there cannot be a queen in column j
            clauses.append("(implies Q" + str(col) + str(row) + " (not Q" + str(otherCol) + str(row) + "))")

# if a queen is in row j, there cannot be another queen in row j
for col in range(1, n+1, 1):
    for row in range(1, n+1, 1):
        
        for otherRow in range(1, n+1, 1):
            if (otherRow == row):
                continue

            # If a queen is in column j, there cannot be a queen in column j
            clauses.append("(implies Q" + str(col) + "_"+ str(row) + " (not Q" + str(col) + str(otherRow) + "))")


# Queens should not be able to attack each other diagonally
for col in range(1, n+1, 1):
    for row in range(1, n+1, 1):

        # Check spaces going down and to the left        
        diagRow = row - 1
        diagCol = col - 1

        while(diagRow > 0 and diagCol > 0):
            clauses.append("(implies Q" + str(col) + str(row) + " (not Q" + str(diagCol) + str(diagRow) + "))")

            diagRow -= 1
            diagCol -= 1

        # Check spaces going up and to the right
        diagRow = row + 1
        diagCol = col + 1

        while (diagRow <= n and diagCol <= n):
            clauses.append("(implies Q" + str(col) + str(row) + " (not Q" + str(diagCol) + str(diagRow) + "))")

            diagRow += 1
            diagCol += 1
        
        # Check spaces going up and to the left
        diagRow = row + 1
        diagCol = col - 1

        while (diagRow <= n and diagCol > 0):
            clauses.append("(implies Q" + str(col) + str(row) + " (not Q" + str(diagCol) + str(diagRow) + "))")

            diagRow += 1
            diagCol -= 1
        
        # Check spaces going down and to the right
        diagRow = row - 1
        diagCol = col + 1
        while (diagRow > 0 and diagCol <= n):
            clauses.append("(implies Q" + str(col) + str(row) + " (not Q" + str(diagCol) + str(diagRow) + "))")

            diagRow -= 1
            diagCol += 1



# there has to be at least n queens in the chessboard
# You can verify this by ensuring there is at least one queen in every column
for col in range(1, n+1, 1):
    currClause = "(or "
    
    for row in range(1, n+1, 1):
        currClause += "Q" + str(col) + str(row)

        if (row != n):
            currClause += " "


    currClause += ")"
    clauses.append(currClause)

for i in clauses:
    print(i)