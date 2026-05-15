def reversed_adj(adj):
    radj=[[] for _ in adj]
    for i,e in enumerate(adj):
        for j in e:
            radj[j].append(i)
    return radj

def delweight(adj):
    return [[b for b,_ in e] for e in adj]