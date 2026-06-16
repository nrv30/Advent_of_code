function SqDist {
    param (
        $b1,
        $b2
        )
        
        $dx = $b1[0] - $b2[0]
        $dy = $b1[1] - $b2[1]
        $dz = $b1[2] - $b2[2]
        
        return ($dx*$dx + $dy*$dy + $dz*$dz)
    }

[System.Reflection.Assembly]::load([System.IO.File]::ReadAllBytes("$PWD\WeightedQuickUnionLib\bin\Debug\net10.0\WeightedQuickUnionLib.dll"))
$boxes = [System.Collections.Generic.List[int[]]]::new()
$pq    = [System.Collections.Generic.PriorityQueue[[System.Tuple[int32, int32]], int64]]::new() 
    
# parse input
$lines = (get-content $($args[0]))
$lines | ForEach-Object {
   $point = $($_ -Split ',') | Foreach-Object {([int]::parse($_))}
   $boxes.Add($point)
}

$sw = [System.Diagnostics.Stopwatch]::StartNew()

# a parallel array of indices to boxes
$boxesIndices = 0..($boxes.Count-1) | ForEach-Object {$_}

# build the pairs
for ($i = 0; $i -lt $boxes.Count; $i++) {
    $b1 = $boxes[$i]

    for ($j = $i + 1; $j -lt $boxes.Count; $j++) {
        $b2 = $boxes[$j]
        $d = SqDist $b1 $b2
        $pair = [System.Tuple]::Create($i, $j)
        $pq.Enqueue($pair, $d)
    }
}

# UnionFind of indices into $boxes
$u = New-Object WeightedQuickUnionLib.WeightedQuickUnion[int](,$boxesIndices)

# Solution 1
if ($args[1] -eq 1) {
    $n = 1000
    for ($i = 0; $i -lt $n; $i++) {
        $pair = $pq.Dequeue()
        $null = $u.Union($pair.Item1, $pair.Item2)
    }
     
    $top3Weights = $u.Get3LargestSets();
    $answer = $top3Weights.Item1*$top3Weights.Item2*$top3Weights.Item3
    write-host($answer)
} else { # Solution 2
    $count = $boxes.Count
    $i, $j
    do {
        $pair = $pq.Dequeue()
        $i = $pair.Item1
        $j = $pair.Item2
        $success = $u.Union($pair.Item1, $pair.Item2)
        if ($success) {
            $count--
        }
    } while ($count -gt 1)
    write-host ($boxes[$i][0]*$boxes[$j][0])
}

$sw.Stop()
$sw.Elapsed
