INF = 123456789
SIZE = 25
# graph = [
#     [ 0, 0, 0, 0, 0],
#     [ 0, 1, 0, 0, 0], 
#     [ 1, 0, 0, 1, 0],
#     [ 0, 0, 1,-1, 0],
#     [ 0, 0, 0, 1, 0]
# ]

# graph = [
#     [ 0,-1,-1,-1,-1],
#     [ 0,-1,-1,-1,-1], 
#     [ 1, 1, 1, 1, 1],
#     [ 1,-1,-1,-1,-1],
#     [ 1, 1, 1, 1, 1]
# ]

# graph = [
#     [ 0, 0, 0, 1, 1],
#     [ 0,-1,-1, 1, 1], 
#     [ 0,-1,-1,-1,-1],
#     [ 0, 0, 0, 0, 0],
#     [ 0, 0, 0, 0, 0]
# ]

graph = [
    [ 0,-1, 0, 1, 1],
    [ 0,-1,-1, 1, 1], 
    [ 0,-1,-1,-1,-1],
    [ 0,-1,-1,-1,-1],
    [ 0, 0, 0, 0, 0]
]

# graph = [
#     [ 0, 1, 1, 1, 1],
#     [ 0, 1, 1, 1, 1], 
#     [ 0, 1, 1, 1, 1],
#     [ 0, 1, 1, 1, 1],
#     [ 0, 0, 0, 0, 0]
# ]

# graph = [
#     [ 0, 0, 0, 1, 0],
#     [ 0, 1, 0, 0, 0], 
#     [ 1, 0, 0,-1, 0],
#     [ 1, 0,-1, 1, 0],
#     [ 1, 0, 0,-1, 0]
# ]

spMatrix = [[[-1] for _ in range(5)] for _ in range(5)]

red_list = [0] * 25

visited = [False] * 25

def ctoi(x,y):
    return x * 5 + y

def itoc(i):
    return i // 5, i % 5

def showGraph(g):
    for row in g:
        print(row)

def itocList(array):
    if array[0] == -1:
        return "[-1]"
    ret = "["
    for index in array:
        ret += str(itoc(index)) + "->"
    ret += "]"
    return ret


def red_scan(g):
    for i in range(5):
        for j in range(5):
            if(g[i][j] == 1):
                red_list[ctoi(i,j)] = 1

def evalStack(stack):
    if (stack[0] == -1):
        return -INF
    sx,sy = itoc(stack[0])
    score = 0
    visited_red = [0] * 25
    if graph[sx][sy] == 1:
        score += 5
        visited_red[stack[0]] = True
    elif graph[sx][sy] == -1:
        score -= 5
    for i in range(1,len(stack)):
        score -= 1
        x,y = itoc(stack[i])
        if graph[x][y] == 1:
            if (visited_red[stack[i]] == 1):
                score -= 5
            else:
                visited_red[stack[i]] = 1
                score += 5
        elif graph[x][y] == -1:
            score -= 5
    return score

def reroll(origin):
    dx = [1,-1,0,0]
    dy = [0,0,-1,1]
    origin_x, origin_y = itoc(origin)
    ret = False
    for i in range(4):
        near_x = origin_x + dx[i]
        near_y = origin_y + dy[i]
        if (0 <= near_x <= 4 and 0 <= near_y <= 4):
            # print("[%d][%d] -> [%d][%d]:"%(origin_x ,origin_y, near_x, near_y),
                #    itocList(spMatrix[near_x][near_y]), itocList(spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]))
            # print("\n")
            if evalStack(spMatrix[near_x][near_y]) <= evalStack(spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]):
                spMatrix[near_x][near_y] = spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]
                if (visited[ctoi(near_x,near_y)]):
                    # print("[%d][%d] has been changed. need to reroll [%d][%d]" % (near_x,near_y,near_x,near_y))
                    # ret = ctoi(near_x,near_y)
                    ret = True
                    visited[ctoi(near_x,near_y)] = False
            # elif evalStack(spMatrix[near_x][near_y]) == evalStack(spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]):
            #     spMatrix[near_x][near_y] = spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]
    visited[origin] = True
    return ret

def calSP(start, end):
    sx, sy = itoc(start)
    spMatrix[sx][sy][0] = start
    end_x,end_y = itoc(end)
    # showGraph(spMatrix)
    order = [
                (4,4),
                (4,3),(3,4),
                (4,2),(3,3),(2,4),
                (4,1),(3,2),(2,3),(1,4),
                (4,0),(3,1),(2,2),(1,3),(0,4),
                (3,0),(2,1),(1,2),(0,3),
                (2,0),(1,1),(0,2),
                (1,0),(0,1),
                (0,0)
            ]
    index = 0
    while index < SIZE:
        x,y = order[index]
        if (visited[ctoi(x,y)]):
            index += 1
        else:
            next_check = reroll(ctoi(x,y))
            if (next_check):
                index = 0
    print("End's score is :",evalStack(spMatrix[end_x][end_y]))
    print("End's route is ",spMatrix[end_x][end_y])

showGraph(graph)
calSP(24,0)
# showGraph(spMatrix)
