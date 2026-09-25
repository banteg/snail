import itertools, sys
sys.path.insert(0, sys.argv[1])
from qs import qsort
# name, weight, size
V = [("cursor",17,4),("crawl",8,4),("halfh",4,4),("height",4,4),("linew",4,4),("x",4,4),("file",4,4),
     ("width",3,4),("donor",3,4),("gr",3,4),("temp",2,4),("text_end",2,4),
     ("vectmp",6,12),("initpos",6,12),("velocity",6,12),("matrix",1,64),("a1",2,128),("a2",2,128)]
compat = {frozenset(p) for p in [("x","height"),("x","width"),("x","temp"),("x","halfh"),("gr","height"),("gr","width"),("gr","temp"),("gr","halfh"),
    ("temp","width"),("temp","halfh"),("donor","halfh"),("initpos","velocity")]}
def pipeline(vlist):
    # stable sort by size asc, weight desc
    vl = sorted(vlist, key=lambda v: (v[2], -v[1]))
    slots = []  # [members, weight, size]
    for name, w, sz in vl:
        for s in reversed(slots):
            if sz <= s[2]*2 and all(frozenset((name, m)) in compat for m in s[0]):
                s[0].append(name); s[1] += w; s[2] = max(s[2], sz); break
        else:
            slots.append([[name], w, sz])
    arr = [("/".join(s[0]), s[1], s[2]) for s in slots]
    return [a[0] for a in qsort(arr, 0, len(arr)-1)]
cur = pipeline(V)
print("current:", cur)
def layout_key(order):
    return order
target_sets = None
def is_target(order):
    # target: slot containing height (and x) right after cursor, then width slot, then crawl; vectmp before text_end
    names = [o.split("/") for o in order]
    idx = {n:i for i,ms in enumerate(names) for n in ms}
    return (idx["cursor"]==0 and idx["height"]==1 and idx["x"]==1 and idx["width"]==2 and idx["gr"]==2 and idx["temp"]==2
            and idx["crawl"]==3 and idx["halfh"]==4 and idx["donor"]==4 and idx["linew"]==5 and idx["initpos"]==6 and idx["file"]==7
            and idx["vectmp"]==8 and idx["text_end"]==9)
print("current is target:", is_target(cur))
if __name__ == "__main__":
    hits = []
    names = [v[0] for v in V]
    for k in (1, 2):
        for idxs in itertools.combinations(range(len(V)), k):
            for deltas in itertools.product((-2,-1,1,2), repeat=k):
                vv = list(V)
                bad = False
                for i, d in zip(idxs, deltas):
                    n, w, s = vv[i]
                    if w + d < 1: bad = True
                    vv[i] = (n, w + d, s)
                if bad: continue
                o = pipeline(vv)
                if is_target(o):
                    hits.append(([(names[i], d) for i, d in zip(idxs, deltas)], o))
    for h in hits: print(h[0])
    print(len(hits))
