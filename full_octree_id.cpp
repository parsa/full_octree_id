#include <array>
#include <cassert>
#include <utility>

constexpr auto NDIM = 3;

size_t to_id(std::array<int, NDIM> x, int lev)
{
    size_t id = 1;
    for (int l = 0; l < lev; l++)
    {
        for (int d = 0; d < NDIM; d++)
        {
            id <<= 1;
            id |= ((x[d] >> l) & 1);
        }
    }
    return id;
}

std::pair<std::array<int, NDIM>, int> from_id(size_t id)
{
    std::array<int, NDIM> x;
    int lev = 0;

    for (int d = 0; d < NDIM; d++)
    {
        x[d] = 0;
    }
    for (lev = 0; id != 1; lev++)
    {
        printf("%i %llo\n", lev, id);
        for (int d = NDIM - 1; d >= 0; d--)
        {
            x[d] <<= 1;
            x[d] |= (id & 1);
            id >>= 1;
        }
    }
    return std::make_pair(x, lev);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: full_octree <string subgrid id> <number of additional "
               "levels>\n");
    }

    const char* ptr = argv[1];
    int dlev = std::atoi(argv[2]);
    assert(*ptr == '1');
    size_t id = 1;
    ptr++;
    while (*ptr != '\0')
    {
        id <<= NDIM;
        id |= (*ptr - '0');
        ptr++;
    }
    std::array<int, NDIM> y;

    auto r  = from_id(id);
    std::array<int, NDIM> x = r.first;
    int lev = r.second;
    printf("base_level is %i\n", lev);
    for (int i = 0; i < (1 << dlev); i++)
    {
        for (int j = 0; j < (1 << dlev); j++)
        {
            for (int k = 0; k < (1 << dlev); k++)
            {
                y[0] = (x[0] << dlev) + i;
                y[1] = (x[1] << dlev) + j;
                y[2] = (x[2] << dlev) + k;
                size_t new_id = to_id(y, lev + dlev);
                printf("the (%i,%i,%i) cell in subgrid %s has full octree id "
                       "%o\n",
                    i, j, k, argv[1], new_id);
            }
        }
    }
}
