using Raylib_cs;
using System.Collections.Generic;

namespace WeightedQuickUnionLib;

// A Weighted UnionFind implementation informed by the below video
// No path compression
// https://www.youtube.com/watch?v=xc9s9wdaSdU&t=95s

public class WeightedQuickUnion<T> {

    static Color[] colors = {
        Color.Pink, Color.Green, Color.Violet, 
         Color.Red, Color.SkyBlue, Color.Purple,
    };

    private Dictionary<T, int> elementsToIndex;
    private int[]              parent;

    // for visualization

    // parallel array of colors
    public Color[]             elementColors;
    int colorPointer;

    // a parallel array of all the children to a parent index
    public List<int>[]         parentToChildren;

    public WeightedQuickUnion(T[] elements) 
    { 
        int size           = elements.Length;
        parent             = new int[size];
        elementsToIndex    = new Dictionary<T, int>();
        elementColors      = new Color[size];
        parentToChildren   = new List<int>[size];

        for (int i = 0; i < size; ++i)
        {
            parent[i] = -1;
            elementsToIndex.Add(elements[i], i);
            elementColors[i] = Color.Red;
            parentToChildren[i] = new List<int>();
        }
        int colorPointer = 0;
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
        // Console.Out.WriteLine($"Union({a}, {b})");
        int aParentIdx = Find(a);
        int bParentIdx = Find(b);
        if (aParentIdx == bParentIdx) return false;

        int aParentWeight = Math.Abs(parent[aParentIdx]);
        int bParentWeight = Math.Abs(parent[bParentIdx]);

        if (aParentWeight >= bParentWeight)
        {
            // they are both singletons and have default color
            // assign color to the new parent
            if (aParentWeight == 1 && bParentWeight == 1)
            {
                 elementColors[aParentIdx] = colors[colorPointer % colors.Length];
                 colorPointer++;
            }

            parent[aParentIdx] -= bParentWeight;
            parent[bParentIdx] = aParentIdx;

            elementColors[bParentIdx] = elementColors[aParentIdx];
            parentToChildren[aParentIdx].Add(bParentIdx);

            for (int i = 0; i < parentToChildren[bParentIdx].Count; ++i)
            {
                elementColors[parentToChildren[bParentIdx][i]] = elementColors[aParentIdx];
                parentToChildren[aParentIdx].Add(parentToChildren[bParentIdx][i]);
            }
            parentToChildren[bParentIdx].Clear();

            // elementColors[bParentIdx] = elementColors[aParentIdx];
            // ChangeSetColor(aParentIdx, elementColors[aParentIdx]);
        } else
        {
            parent[bParentIdx] -= aParentWeight;
            parent[aParentIdx] = bParentIdx;

            elementColors[aParentIdx] = elementColors[bParentIdx];
            parentToChildren[bParentIdx].Add(aParentIdx);

            for (int i = 0; i < parentToChildren[aParentIdx].Count; ++i)
            {
                elementColors[parentToChildren[aParentIdx][i]] = elementColors[bParentIdx];
                parentToChildren[bParentIdx].Add(parentToChildren[aParentIdx][i]);
            }
            parentToChildren[aParentIdx].Clear();

            //elementColors[aParentIdx] = elementColors[bParentIdx];
            //ChangeSetColor(bParentIdx, elementColors[bParentIdx]);
        }
        return true;
    }

    public bool IsConnected(T a, T b)
    {
        return Find(a) == Find(b);
    }

    // O(NlogN)
    // maybe memorize the ones part of the set in find to skip some
    //private void ChangeSetColor(int parentIdx, Color color)
    //{
    //    for (int i = 0; i < parent.Length; ++i)
    //    {
    //        if (Find(i) == parentIdx)
    //        {
    //            elementColors[i] = color;
    //        }
    //    }
    //}

    public void Print()
    {
        Console.WriteLine(string.Join(" ", parent));
    }

    // for aoc question part 1
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