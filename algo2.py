INF = 999

graph = [
    [ 0, 0, 0, 0, 0],
    [ 0, 1, 0, 0, 0], 
    [ 1, 0, 0, 1, 0],
    [ 0, 0, 1,-1, 0],
    [ 0, 0, 0, 1, 0]
]

graph3 = [
    [ 0, 0, 0, 0, 0],
    [ 0, 0, 0, 0, 0], 
    [ 0, 0, 0, 1, 0],
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
    [ 0, 0, 0, 0, 0],
    [ 0, 1, 1, 0, 0],
    [ 1, 0, 0, 1, 0],
    [ 0, 0, 0,-1, 0],
    [ 0, 0, 0, 0, 0]
]

n_graph = [[0] * 5 for _ in range(5)]

# 시작점 -> 빨간점 -> 도착점 

# 하나씩 다 해보는 건데

# 시작점 + 빨간점 경로 잡고
# 빨간점까지 임시 경로 에서 들린 빨간색 체크하고
# 그거 그래프 바꾸고
# 다시 그 빨간점에서 도착점까지 다익스트라 돌리고
# 둘이 합쳐서 시작점에서 끝까지 다익스트라보다 작다면
# 경로를 갱신



visited = [False] * (25) 
distance = [INF] * (25)
parent = [-1] * (25)
red_origin_list = [0] * 25
red_visited = [False] * 25
dp = [[INF] * 25 for _ in range(25)]
# no red
NR = -1
# yes red no skip
YRNS = 0
# yes red yes skip
YRYS = 1
red_skip = [NR] * 25
path_start = 0
stack = [] * 25

def ctoi(x,y):
    return x * 5 + y

def itoc(i):
    return i // 5, i % 5

def red_scan(ga):
    for i in range(5):
        for j in range(5):
            if(ga[i][j] == 1):
                red_origin_list[ctoy(i,j)] = 1
                red_skip[ctoy(i,j)] = YRNS

def comparePath(gr):
    start = 0
    while(findShortestRed(gr,start) != -1 and start != 24):
        middle = findShortestRed(gr, start)

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
            if visited[i*5+j]:
                print("v(%2d) "%(distance[i*5+j]), end = "")
            else:
                print("%5d "%g[i][j], end = "")
        print("")

# 방문하지 않은 노드이면서 시작노드와 최단거리인 노드 반환
def get_smallest_node():
    min_value = INF
    index = 0
    for i in range(25):
        if not visited[i] and distance[i] < min_value:
            min_value = distance[i]
            index = i
    return index

# 다익스트라 알고리즘
def dijkstra(start):
    distance[start] = 0
    visited[start] = True
    dx = [1,-1,0,0]
    dy = [0,0,1,-1]
    now_x = start // 5
    now_y = start % 5
    for i in range(4):
        nx = now_x + dx[i]
        ny = now_y + dy[i]
        if (0 <= nx <= 4 and 0 <= ny <= 4):
            print("dijkstra near : [%d][%d]" % (nx,ny))
            distance[nx * 5 + ny] = n_graph[nx][ny]
            parent[nx * 5 + ny] = ctoi(now_x,now_y)
    # 시작노드 제외한 n-1개의 다른 노드들 처리
    for _ in range(24):
        now = get_smallest_node()  # 방문X 면서 시작노드와 최단거리인 노드 반환
        visited[now] = True        # 해당 노드 방문처리
        showGraph(n_graph)
        # 해당 노드의 인접한 노드들 간의 거리 계산
        now_x = now // 5
        now_y = now % 5
        for i in range(4):
            nx = now_x + dx[i]
            ny = now_y + dy[i]
            if (0 <= nx <= 4 and 0 <= ny <= 4):
                cost = distance[now] + n_graph[nx][ny]  # 시작->now 거리 + now->now의 인접노드 거리
                if cost < distance[nx * 5 + ny]:    # cost < 시작->now의 인접노드 다이렉트 거리
                    distance[nx * 5 + ny] = cost
                    if parent[ctoi(nx,ny)] == -1:
                        parent[nx * 5 + ny] = now
                    print("[%d][%d]"%(nx,ny) + "'s parent is [%d][%d]" % (itoc(now)))
        print("smallest node: [%d][%d]"%(now//5,now%5))
        print(parent)
        print()

def printPath(start):
    if parent[start] == -1:
        print("[%d][%d]"%(start//5,start%5))
        return
    else:
        print("[%d][%d]"%(start//5,start%5) + "<- ", end = " ")
        printPath(parent[start])

def findShortestRed(gr,start):
    dist = INF
    sx,sy = ctoi(start)
    rnode = -1
    isSameDist = False
    for x in range(5):
        for y in range(5):
            if abs(sx-x) + abs(sy-y) < dist:
                rnode = itoc(sx,sy)
                dist = abs(sx-x) + abs(sy-y)
            elif abs(sx-x) + abs(sy-y) == dist:
                isSameDist = True
    dist += 1
    if isSameDist:
        for x in range(5):
            for y in range(5):
                if abs(sx-x) + abs(sy-y):
                    rnode = itoc(sx,sy)
                    dist = abs(sx-x) + abs(sy-y)
                elif abs(sx-x) + abs(sy-y) == dist:
                    isSameDist = True
            
    return rnode

def initDP(g):
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


def bellmanford(start):
    dp[start][start] = 0;
    dx = [1,-1,0,0]
    dy = [0,0,1,-1]
    for next in range(24):
        sx = next // 5
        sy = next % 5
        for i in range(4):
            nx = sx + dx[i]
            ny = sy + dy[i]
            if (0 <= nx <= 4 and 0 <= ny <= 4):
                end = nx * 5 + ny
                dp[start][end] = g[nx][ny]


showGraph(graph2)
convert_graph(graph2)
print("\n")
showGraph(n_graph)
print("\n")
# initFloyd(n_graph)
# showGraph(dp)
# floyd()
print("\n")
# showGraph(dp)

dijkstra(0)

print(parent)

printPath(8)
# printPath(0)
