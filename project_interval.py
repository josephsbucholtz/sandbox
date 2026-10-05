
'''
projects[i] = [start, end, value] 
Can do any project you want so long as project is attended for duration
and you cannot do multi projects at once.
return maximum value you can get
'''

def max_value(projects: List[List[int]]) -> int:
    dp = [0] * len(projects)
    projects.sort()
    
    dp[0] = projects[0][2]

    for i in range(1, len(projects)):
        j = i 
        while (j >= 0 and projects[i][0] <= projects[j][1]):
            j -= 1

        if j >= 0:
            dp[i] = projects[i][2] + projects[j][2]
        else:
            dp[i] = projects[i][2]

    return max(dp)


projects = [[2, 4, 4], [3, 6, 6], [6, 8, 2], [5, 7, 3],]

print(max_value(projects)) # 7
