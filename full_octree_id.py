import argparse

NDIM = 3

def to_id(x, lev):
    id = 1
    for l in range(0, lev):
        for d in range(0, NDIM):
            id <<= 1
            id |= (x[d] >> l) & 1
    return id

def from_id(id):
    x = [0] * NDIM
    lev = 0
    
    while id != 1:
        print('{} {:o}'.format(lev, id))
        for d in range(NDIM - 1, -1, -1):
            x[d] <<= 1
            x[d] |= (id & 1)
            id >>= 1
        lev += 1
        
    return x, lev

def main():
    parser = argparse.ArgumentParser(
        description='Generate the Octree for sub-elements of a Octree')
    parser.add_argument('base', type=str)
    parser.add_argument('dlev', type=int)
    args = parser.parse_args()

    base_id = int(args.base, 8)
    dlev = args.dlev

    y = [0] * NDIM

    x, lev = from_id(base_id)

    print("base_level is", lev)

    for i in range(0, 1 << dlev):
        for j in range(0, 1 << dlev):
            for k in range(0, 1 << dlev):
                y[0] = (x[0] << dlev) + i
                y[1] = (x[1] << dlev) + j
                y[2] = (x[2] << dlev) + k
                new_id = to_id(y, lev + dlev)
                print('the ({},{},{}) cell in sub-grid {} has full octree id {:o}'.format(i, j, k, args.base, new_id))

if __name__ == '__main__':
    main()