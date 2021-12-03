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

graph2 = [
    [ 0, 0,-1, 1, 1],
    [ 0,-1,-1, 1, 1],
    [ 0,-1,-1,-1,-1],
    [ 0, 0, 0, 0, 0],
    [ 0, 0, 0, 0, 0]
]

n_graph = [[0] * 5 for _ in range(5)]


dp = [[INF] * 25 for _ in range(25)]

visited = [False] * (25) 
distance = [INF] * (25)

def convert_graph(ga):
    for i in range(5):
        for j in range(5):
            if ga[i][j] == 1:
                n_graph[i][j] = -4
            elif ga[i][j] == -1:
                n_graph[i][j] = 6
            else:
                n_graph[i][j] = 1

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

# 방문하지 않은 노드이면서 시작노드와 최단거리인 노드 반환
def get_smallest_node():
    min_value = INF
    index = 0
    for i in range(1, 25):
        if not visited[i] and distance[i] < min_value:
            min_value = distance[i]
            index = i
    return index

# 다익스트라 알고리즘
def dijkstra():
    distance[0] = 0
    visited[0] = True

    distance[1] = n_graph[0][1]
    distance[5] = n_graph[1][0]

    # 시작노드 제외한 n-1개의 다른 노드들 처리
    for _ in range(24):
        now = get_smallest_node()  # 방문X 면서 시작노드와 최단거리인 노드 반환
        visited[now] = True        # 해당 노드 방문처리
        # 해당 노드의 인접한 노드들 간의 거리 계산
        dx = [1,-1,0,0]
        dy = [0,0,1,-1]
        now_x = now // 5
        now_y = now % 5
        for i in range(4):
            nx = now_x + dx[i]
            ny = now_y + dy[i]
            if (0 <= nx <= 4 and 0 <= ny <= 4):
                cost = distance[now] + n_graph[nx][ny]  # 시작->now 거리 + now->now의 인접노드 거리
                if cost < distance[nx * 5 + ny]:    # cost < 시작->now의 인접노드 다이렉트 거리
                    distance[nx * 5 + ny] = cost
    print("Dijk: ",distance)

showGraph(graph)
convert_graph(graph1)
print("\n")
showGraph(n_graph)
print("\n")
initFloyd(n_graph)
showGraph(dp)
floyd()
print("\n")
showGraph(dp)

dijkstra()