using System.Diagnostics;
using WeightedQuickUnionLib;


class Program
{

    static long SqDist(System.ValueTuple<long, long, long> a, System.ValueTuple<long, long, long> b)
    {
        long dx = a.Item1-b.Item1;
        long dy = a.Item2-b.Item2;
        long dz = a.Item3-b.Item3;

        return dx*dx+dy*dy+dz*dz;
    }
    static void Main(string[] args)
    {
        // parse input
        List<ValueTuple<long, long, long>> boxes = new List<System.ValueTuple<long, long, long>>();
        foreach (string line in File.ReadLines(@args[0]))
        {
            IEnumerable<long> components = line.Split(",").Select(comp =>
            {
                return long.Parse(comp);
            });

            (long x, long y, long z) box = (components.ElementAt(0),
                                            components.ElementAt(1),
                                            components.ElementAt(2));
            boxes.Add(box);
        }

        // I don't time parsing in any of my implementations 
        // there's no particular reason...
        Stopwatch sw = new Stopwatch();
        sw.Start();


        // parallel array of indices to boxes
        int[] boxesIndices = new int[boxes.Count];
        for (int i = 0; i < boxes.Count; ++i) boxesIndices[i] = i;

        // build pq of pairs
        PriorityQueue<ValueTuple<int, int>, long> pq = new PriorityQueue<ValueTuple<int, int>, long>();
        for (int i = 0; i < boxes.Count; ++i)
        {
            for (int j = i+1; j < boxes.Count; ++j)
            {  
                pq.Enqueue(ValueTuple.Create(i, j), SqDist(boxes[i], boxes[j]));
            }
        }

        WeightedQuickUnion<int> uf = new WeightedQuickUnion<int>(boxesIndices);
        
        // part 1
        if (int.Parse(args[1]) == 1) {
            int n = 1000;
            for (int i = 0; i < n; ++i)
            {
                (int idx1, int idx2) = pq.Dequeue();
                uf.Union(idx1, idx2);
            }

            var answer = uf.Get3LargestSets();
            Console.WriteLine(answer);
            Console.WriteLine(answer.Item1*answer.Item2*answer.Item3);
        } else // part 2 
        {
            long count = boxes.Count;
            int idx1, idx2;
            do {
                (idx1, idx2) = pq.Dequeue();
                if (uf.Union(idx1, idx2))
                {
                    count--;
                }
            } while (count > 1);
            Console.WriteLine(boxes[idx1].Item1*boxes[idx2].Item1);
        }
        
        sw.Stop();
        Console.Out.WriteLine(sw.ElapsedMilliseconds/(float)1000);
    }
}
