def dens(s): return s[1]*1000//s[2]
def qsort(a, lo, hi):
    while lo < hi:
        mid = (lo + hi) >> 1  # (lo+hi) signed >>1
        a[lo], a[mid] = a[mid], a[lo]
        last = lo
        for i in range(lo+1, hi+1):
            if dens(a[i]) > dens(a[lo]):
                last += 1
                a[last], a[i] = a[i], a[last]
        a[lo], a[last] = a[last], a[lo]
        qsort(a, lo, last-1)
        lo = last + 1
    return a
if __name__ == "__main__":
    slots = [("cursor",17,4),("crawl_y",8,4),("donor",7,4),("{h,x}",8,4),("linew",4,4),("file",4,4),("{w,gr,t}",8,4),("text_end",2,4),("vectmp",6,12),("initpos",12,12),("matrix",1,64),("a1",2,128),("a2",2,128)]
    print([s[0] for s in qsort(list(slots),0,len(slots)-1)])
