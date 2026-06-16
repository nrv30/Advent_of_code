namespace WeightedQuickUnionLib;

// A Weighted UnionFind implementation informed by the below video
// No path compression
// https://www.youtube.com/watch?v=xc9s9wdaSdU&t=95s
public class WeightedQuickUnion<T> {

    private Dictionary<T, int> elementsToIndex;
    private int[]              parent;

    public WeightedQuickUnion(T[] elements) 
    { 
        int size           = elements.Length;
        parent             = new int[size];
        elementsToIndex     = new Dictionary<T, int>();

        for (int i = 0; i < size; ++i)
        {
            parent[i] = -1;
            elementsToIndex.Add(elements[i], i);
        }
    }

    private int Find(T elem)
    {
        int idx = elementsToIndex[elem];
        int iParentIdx = parent[idx];
        if (iParentIdx < 0)
        {
            return idx;
        } 

        return Find(iParentIdx); 
    }

    private int Find(int idx)
    {
        int ParentIdx = parent[idx];
        if (ParentIdx < 0)
        {
            return idx;
        } 

        return Find(ParentIdx);
    }

    public bool Union(T a, T b)
    {

        int aParentIdx = Find(a);
        int bParentIdx = Find(b);
        if (aParentIdx == bParentIdx) return false;

        int aParentWeight = Math.Abs(parent[aParentIdx]);
        int bParentWeight = Math.Abs(parent[bParentIdx]);

        if (aParentWeight >= bParentWeight)
        {
            parent[aParentIdx] -= bParentWeight;
            parent[bParentIdx] = aParentIdx;
        } else
        {
            parent[bParentIdx] -= aParentWeight;
            parent[aParentIdx] = bParentIdx;
        }
        return true;
    }

    public bool IsConnected(T a, T b)
    {
        return Find(a) == Find(b);
    }

    public void Print()
    {
        Console.WriteLine(string.Join(" ", parent));
    }

    public Tuple<int, int, int> Get3LargestSets()
    {
        int m1, m2, m3;
        m1=m2=m3=0;

        for (int i = 0; i < parent.Length; ++i)
        {
            // we found a root note
            if (parent[i] < 0)
            {
                int weight = Math.Abs(parent[i]);
                if (weight > m1)
                {
                    m3 = m2;
                    m2 = m1;
                    m1 = weight;
                } else if (weight > m2)
                {
                    m3 = m2;
                    m2 = weight;
                } else if (weight > m3)
                {
                    m3 = weight;
                }
            }
        }

        return Tuple.Create(m1, m2, m3);
    }
}