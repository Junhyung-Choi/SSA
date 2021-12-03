INF = 123456789
SIZE = 25
# graph = [
#     [ 0, 0, 0, 0, 0],
#     [ 0, 1, 0, 0, 0], 
#     [ 1, 0, 0, 1, 0],
#     [ 0, 0, 1,-1, 0],
#     [ 0, 0, 0, 1, 0]
# ]

graph = [
    [ 0, 0, 0, 1, 1],
    [ 0,-1,-1, 1, 1], 
    [ 0,-1,-1,-1,-1],
    [ 0,-1,-1,-1,-1],
    [ 0, 0, 0, 0, 0]
]

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
                red_list[ctoy(i,j)] = 1

def evalStack(stack):
    if (stack[0] == -1):
        return -INF
    sx,sy = itoc(stack[0])
    # if graph[sx][sy] == 1:
    #     score += 5
    #     visited_red
    visited_red = [0] * 25
    score = graph[sx][sy]
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
    ret = -1
    for i in range(4):
        near_x = origin_x + dx[i]
        near_y = origin_y + dy[i]
        if (0 <= near_x <= 4 and 0 <= near_y <= 4):
            print("[%d][%d] -> [%d][%d]:"%(origin_x ,origin_y, near_x, near_y),
                   itocList(spMatrix[near_x][near_y]), itocList(spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]))
            if evalStack(spMatrix[near_x][near_y]) <= evalStack(spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]):
                spMatrix[near_x][near_y] = spMatrix[origin_x][origin_y] + [ctoi(near_x,near_y)]
                if (visited[ctoi(near_x,near_y)]):
                    ret = ctoi(near_x,near_y)
                visited[ctoi(near_x,near_y)] = False
    visited[origin] = True
    return ret

def calSP(start, end):
    sx, sy = itoc(start)
    spMatrix[sx][sy][0] = start
    showGraph(spMatrix)
    i = 0
    while i < SIZE - 1:
        next_check = reroll(SIZE -1 - i)
        if (next_check == -1):
            i += 1
        else:
            i = SIZE - 1 - next_check
    end_x,end_y = itoc(end)
    print("End's score is :",evalStack(spMatrix[end_x][end_y]))
    print("End's route is ",spMatrix[end_x][end_y])


calSP(24,0)
showGraph(spMatrix)