INF = 999

graph = [
    [ 0, 0, 0, 0, 0],
    [ 0, 1, 0, 0, 0],
    [ 1, 0, 0, 1, 0],
    [ 0, 0, 1,-1, 0],
    [ 0, 0, 0, 1, 0]
]

graph1 = [
    [ 0, 0,-1, 1, 1],
    [ 0,-1,-1, 1, 1],
    [ 0,-1,-1,-1,-1],
    [ 0, 0, 0, 0, 0],
    [ 0, 0, 0, 0, 0]
]

n_graph = [[0] * 5 for _ in range(5)]


dp = [[INF] * 25 for _ in range(25)]


def convert_graph():
    for i in range(5):
        for j in range(5):
            if graph[i][j] == 1:
                n_graph[i][j] = 0
            elif graph[i][j] == -1:
                n_graph[i][j] = 11
            else:
                n_graph[i][j] = 5

def showGraph(g):
    for i in range(len(g)):
        for j in range(len(g[0])):
            if g[i][j] == INF:
                print("INF ", end = "")
            else:
                print("%4d "%g[i][j], end = "")
        print("")
        
def floyd():
    for k in range(25):
        for i in range(25):
            for j in range(25):
                # print("i: ",i,"j: ",j, "dp: ",dp[i][j])
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])

def initFloyd(g):
    dx = [1,-1,0,0]
    dy = [0,0,1,-1]
    for start in range(25):
        dp[start][start] = 0
        sx = start // 5
        sy = start % 5
        for i in range(4):
            nx = sx + dx[i]
            ny = sy + dy[i]
            if (0 <= nx <= 4 and 0 <= ny <= 4):
                end = nx * 5 + ny
                dp[start][end] = g[nx][ny]

showGraph(graph)
convert_graph()
print("\n")
showGraph(n_graph)
print("\n")
initFloyd(n_graph)
showGraph(dp)
floyd()
print("\n")
showGraph(dp)