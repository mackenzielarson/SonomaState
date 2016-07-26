__author__ = 'student'
total = 0
    for i in range (len(grid)):
        for j in range(len(grid[i])-1):
            if i == 0 and j == 0:
                if grid [i][j + 1] > 0:
                    total +=1
                if grid [i +1][j] > 0:
                    total +=1
                if grid [i + 1][j + 1] > 0:
                    total +=1
                grid[i][j] = total

            if i == 0 and j == len(grid)-1:
                if grid [i][j-1] > 0:
                    total += 1
                if grid [i+1][j-1] > 0:
                    total += 1
                if grid [i+1][j] > 0:
                    total +=1
                grid[i][j] = total

            if i == len(grid)-1 and j == 0:
                if grid [i-1][j] > 0:
                    total += 1
                if grid [i-1][j+1] > 0:
                    total +=1
                if grid [i][j+1] > 0:
                    total +=1
                grid[i][j] = total

            if i == len(grid-1) and j == len(grid)-1:
                if grid [i][j-1] > 0:
                    total+= 1
                if grid [i-1][j-1] > 0:
                    total +=1
                if grid [i-1][j] > 0:
                    total +=1
                grid[i][j] = total

            elif i == 0 and j != 0 and j != len(grid)-1:

            elif j == 0 and i != 0 and i != len(grid)-1:

            elif j == len(grid)-1 and i != 0 and i != len(grid)-1:

            elif i == len(grid)-1 and j != 0 and j != len(grid) - 1:

            else: