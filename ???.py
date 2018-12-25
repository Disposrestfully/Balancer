#!/usr/bin/python
def C(n, k):
    ret = 1
    for i in range(k):
    	ret *= n - i
    for i in range(1, k + 1):
    	ret //= i
    return ret

def calc(n, m):
    dp = [[0 for i in range(m + 1)] for i in range(n + 1)]
    dp[1][0] = 1
    for size in range(1, (n - 1) // 2 + 1):
    	s = sum(dp[size][:-1])
    	for i in range(n, size, -1):
    		for j in range(1, m + 1):
    			for k in range(1, j + 1):
    				if size * k < i:
    					dp[i][j] += dp[i - size * k][j - k] * C(s + k - 1, k)
    ret = sum(dp[n])
    if n % 2 == 0:
    	ret += C(sum(dp[n // 2][:-1]) + 1, 2)
    return ret
    
nn = int(input())
print(calc(nn, 4))
