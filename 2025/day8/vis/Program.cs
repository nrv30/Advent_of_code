using Coroutine;
using Raylib_cs;
using System.Numerics;
using WeightedQuickUnionLib;

// what are the sets with >1 weights
// the set with the biggest weight will be colored yellow
// The other sets will have other sets weight > 1

// They should spawn in on-state
// Add a fade plus sound to off-state


// Pop sound
// Author DRAGON-STUDIO

// Electricity Sound
// freesound_community


internal static class Program
{
    static List<Vector3> boxes;

    static Color[] elementColors;
    static List<int>[] parentToChildren; 
    static PriorityQueue<ValueTuple<int, int>, int> pq;
    static WeightedQuickUnion<int> uf;

    static int ScreenWidth = 16*120;
    static int ScreenHeight = 9*120;

    static int Fps = 30;
    static float dt = 1.0f/60.0f;

    static float BoxDimension = 20;
    static float BoxDimensionHalf = BoxDimension/2;

    static Sound PopSound;
    static Sound ElecSound;

    static int leftWidth;
    static int leftHeight;
    static RenderTexture2D left;

    static RenderTexture2D bottomR;
    static RenderTexture2D topR;

    enum State
    {
        Init,
        Vis,
        End,
        Cleanup,
    }
    static State state;

    static bool InitCoroStarted;
    static int InitCount;
    static bool EndCoroStarted;

    static Vector3 end3D;
    static Vector2 end;

    static bool shouldAdvance;

    static List<ValueTuple<Vector3, Vector3>> connectedPairs;


    static PriorityQueue<ValueTuple<int, int>, int> BuildPairs(List<Vector3> boxes)
    {
        PriorityQueue<ValueTuple<int, int>, int> pqLocal = new PriorityQueue<ValueTuple<int, int>, int>();
        for (int i = 0; i < boxes.Count; ++i)
        {
            for (int j = i+1; j < boxes.Count; ++j)
            {
                pqLocal.Enqueue(ValueTuple.Create(i, j), (int)Vector3.DistanceSquared(boxes[i], boxes[j]));
            }
        }
        return pqLocal;
    }

    static List<Vector3> ParseInput(string filepath)
    {
        List<Vector3> boxes = new List<Vector3>();
        foreach (string line in File.ReadLines(filepath))
        {
            IEnumerable<int> components = line.Split(",").Select(comp =>
            {
                return int.Parse(comp);
            });

            Vector3 box = new Vector3(components.ElementAt(0),
                                      components.ElementAt(1),
                                      components.ElementAt(2));
            boxes.Add(box);
        }

        return boxes;
    }

    // initializes global fields
    static void Setup(String filepath)
    {
        boxes = ParseInput(filepath);
        pq = BuildPairs(boxes);

        int[] boxesIndices = new int[boxes.Count];
        for (int i = 0; i < boxes.Count; ++i) boxesIndices[i] = i;

        uf = new WeightedQuickUnion<int>(boxesIndices);

        parentToChildren = new List<int>[boxes.Count];
        UpdateParentToChildren();
        elementColors = new Color[boxes.Count];
        UpdateColors();

        connectedPairs = new List<(Vector3, Vector3)>();
        PopSound = Raylib.LoadSound("sounds/pop.wav");
        ElecSound = Raylib.LoadSound("sounds/electricity.wav");

        state = State.Init;
        //state = State.Vis;
        shouldAdvance = true;

        InitCoroStarted = false;
        InitCount = 0;
        EndCoroStarted = false;

        leftWidth = 510*2;
        leftHeight = ScreenHeight;

        left = Raylib.LoadRenderTexture(leftWidth, leftHeight);

        bottomR = Raylib.LoadRenderTexture(ScreenWidth-leftWidth+10, ScreenHeight/2);
        topR = Raylib.LoadRenderTexture(ScreenWidth-leftWidth+10, ScreenHeight/2);
    }

    static void DrawBoxes(int stopIndex)
    {
        if (stopIndex < 0)
        {
            stopIndex = boxes.Count;
        }
        for (int i = 0; i < stopIndex; ++i)
        {
            Raylib.DrawRectangle((int)boxes[i].X, (int)boxes[i].Y, 
                                 (int)BoxDimension, (int)BoxDimension, 
                                 elementColors[i]);
        }
    }

    static void DrawBoxes3D()
    {
        for  (int i = 0; i < boxes.Count; ++i)
        {
            Vector3 temp = new Vector3 (boxes[i].X, boxes[i].Y+250, boxes[i].Z);

            Raylib.DrawCube(temp, 100, 100, 100, elementColors[i]);
            Raylib.DrawCubeWires(temp, 100, 100, 100, Color.Black);
        }
    }

    static ValueTuple<int, int> AdvanceAlgorithm()
    {
        if (connectedPairs.Count < boxes.Count-1){
            (int idx1, int idx2) = pq.Dequeue();
            if (uf.Union(idx1, idx2))
            {
                CoroutineHandler.Start(ConnectBoxes(idx1, idx2));
                return (idx1, idx2);
            } else
                return (-1, -1);
        } else {
            state = State.End;
            return (-1, -1);
        }
    }

    static IEnumerator<Wait> ConnectBoxes(int idx1, int idx2)
    {
        //float duration = 1 - (float)connectedPairs.Count / (float)boxes.Count;
        //duration = Raymath.Clamp(duration, .5f, 1);
        float duration = 1.0f;
        float timeElapsed = 0.0f;
        while (timeElapsed < duration)
        {
            float t = timeElapsed / duration;

            Vector2 start = new Vector2(boxes[idx1].X+BoxDimensionHalf, boxes[idx1].Y+BoxDimensionHalf);
            Vector2 endLocal = new Vector2(boxes[idx2].X+BoxDimensionHalf, boxes[idx2].Y+BoxDimensionHalf);

            end = Raymath.Vector2Lerp(start, endLocal, t);
            end3D = Raymath.Vector3Lerp(boxes[idx1], boxes[idx2], t);

            timeElapsed += dt;
            yield return new Wait(dt);
        }
        UpdateColors();
        UpdateParentToChildren();
        connectedPairs.Add((boxes[idx1], boxes[idx2]));
        Raylib.PlaySound(ElecSound);
        shouldAdvance = true;
    }

    static void DrawConnections(List<ValueTuple<Vector3, Vector3>> connectedPairs)
    {
        foreach (var pair in connectedPairs)
        {
            Raylib.DrawLineEx(new Vector2(pair.Item1.X + BoxDimensionHalf,
                              pair.Item1.Y + BoxDimensionHalf),
                              new Vector2(pair.Item2.X + BoxDimensionHalf,
                              pair.Item2.Y + BoxDimensionHalf),
                              4.0f, Color.Gold);
        }
    }

    // I need two methods like this because they're drawing to different render textures
    // Not combining with drawing boxes because I want these on top
    static void DrawConnections3D(List<ValueTuple<Vector3, Vector3>> connectedPairs)
    {
        foreach (var pair in connectedPairs)
        {
            Raylib.DrawCylinderEx(new Vector3(pair.Item1.X, pair.Item1.Y + 250, pair.Item1.Z),
                                  new Vector3(pair.Item2.X, pair.Item2.Y + 250, pair.Item2.Z), 10.0f, 10.0f, 10, Color.Gold);
        }
    }

    static IEnumerator<Wait> Init2DSpace()
    {
        if (Raylib.IsSoundPlaying(PopSound))
            Raylib.StopSound(PopSound);
        float duration = 5.0f;
        float timeElapsed = 5.0f;
        float delta = 1;
        for (int i = 0; i < boxes.Count; ++i)
        {
            float t = Raymath.Clamp(timeElapsed/duration, 0, 1);
            float speed = Raymath.Lerp(0.0f, 1.0f, t);
            speed = Raymath.Clamp(speed*speed, 0.2f, 1);
            timeElapsed -= delta;

            InitCount++;
            uf.elementColors[i] = Color.Blue;
            elementColors[i] = Color.Blue;
            Raylib.PlaySound(PopSound);
            yield return new Wait(speed);
        }
        state = State.Vis;
    }
    static IEnumerator<Wait> DoNothing()
    {
        float duration = 1.0f;
        float timeElapsed = 0.0f;
        while (timeElapsed < duration)
        {
            yield return new Wait(dt);
            timeElapsed+= dt;
        }
        state = State.Cleanup;
    }

    static void UpdateColors()
    {
        for (int i = 0; i < elementColors.Length; ++i)
        {
            elementColors[i] = uf.elementColors[i];
        }
        //elementColors = uf.elementColors.Select(color => color).ToArray();
    }

    static void UpdateParentToChildren()
    {
        for (int i = 0; i < parentToChildren.Length; ++i)
        {
            parentToChildren[i] = new List<int>(uf.parentToChildren[i]);
        }
    }

    static void RenderCircuits(int width, int height, int TitleLabelHeight)
    {
        int counter = 0;
        List<int> validCircuits = new List<int>();
        for (int i = 0; i < parentToChildren.Length; ++i)
        {
            if (parentToChildren[i].Count > 0)
            {
                validCircuits.Add(i);
            }
        }

        validCircuits.Sort((a, b) => -parentToChildren[a].Count.CompareTo(parentToChildren[b].Count));

        int backHorzPad = (int)(width*0.05);
        int backVertPad = (int)(height * 0.05);
        int backWidth = width - backHorzPad * 2;
        int backHeight = height - backVertPad * 2 - TitleLabelHeight;
        int backY = TitleLabelHeight + backVertPad;
        int backX = backHorzPad;

        // int tableHeaderWidth = backWidth;
        int tableHeadeHeight = 45;

        int leftLabelWidth = (int)(0.66 * backWidth);
        int labelHeight = backY + 12;
        int fontsize = 24;

        int maxBoxCount = 5;
        int elemHorzPad = (int)(backWidth * 0.05);
        int colorBoxPad = 10;
        int elemVertPad = 20;
        int elemHeight = (backWidth - maxBoxCount * elemVertPad * 2) / maxBoxCount - 70;
        int elemWidth = backWidth - 2 * elemHorzPad;
        int colorBoxWidth = leftLabelWidth-2*colorBoxPad-elemHorzPad;

        Raylib.DrawRectangle(backHorzPad, backY, 
                             backWidth, backHeight, 
                             Color.DarkGray);
        Raylib.DrawRectangle(backHorzPad, backY, backWidth, tableHeadeHeight, Color.Black);

        
        Raylib.DrawRectangle(backX + leftLabelWidth, backY+5, 5, tableHeadeHeight-10, Color.LightGray);
        Raylib.DrawText("ID (color)", backX + leftLabelWidth/2-Raylib.MeasureText("ID (color)", fontsize)/2, 
                        labelHeight, fontsize, Color.LightGray);
        int rightLabelWidth = backWidth - leftLabelWidth;
        Raylib.DrawText("Size", backX + leftLabelWidth + rightLabelWidth / 2 - Raylib.MeasureText("Size", fontsize) / 2,
                        labelHeight, fontsize, Color.LightGray);

        for (int i = 0; i < validCircuits.Count; ++i)
        {
            // counter * elemHeight + counter* 2* elemVertPad + backY
            // counter(elemHeight+2*elemVertPad)+backY
            int elemY = backY + tableHeadeHeight + (counter + 1) * elemVertPad + counter * elemHeight;
            Raylib.DrawRectangleLinesEx(new Rectangle(backX+elemHorzPad, elemY, elemWidth, elemHeight), 
                                        4.0f, Color.Black);
            Raylib.DrawRectangleRounded(new Rectangle(backX+elemHorzPad+colorBoxPad, elemY+10, colorBoxWidth, 
                                        elemHeight-20), 0.5f, 10, elementColors[validCircuits[i]]);
            Raylib.DrawText($"{parentToChildren[validCircuits[i]].Count+1}", backX + elemHorzPad + colorBoxPad + colorBoxWidth + 150, elemY+15, fontsize, Color.LightGray);
            ++counter;
        }
    }

    // STAThread is required if you deploy using NativeAOT on Windows
    // See https://github.com/raylib-cs/raylib-cs/issues/301
    [System.STAThread]
    static void Main(string[] args)
    {
        if (args.Length == 0)
        {
            Console.Out.WriteLine("You must provide text file in command-line arguments");
            return;
        }

        Camera3D camera;
        camera.Position = new Vector3(-100.0f, 1200.0f, 3200);
        camera.Target = new Vector3(1000.0f/3f, 1000.0f/1.5f, 1000.0f/1.5f);
        camera.Up = new Vector3(0.0f, 1.0f, 0.0f);
        camera.FovY = 45.0f;
        camera.Projection = CameraProjection.Perspective;

        Raylib.SetTraceLogLevel(TraceLogLevel.None);
        Raylib.SetTargetFPS(Fps);
        Raylib.InitWindow(ScreenWidth, ScreenHeight, "Day 8 Visualization");
        Raylib.InitAudioDevice();

        Setup(args[0]);

        int idx1, idx2;
        idx1 = idx2 = 0;

        int TitleLabelHeight = 200;
        int TitleLabelWidth = 50;
        string text;
        int fontsize;

        while (!Raylib.WindowShouldClose())
        {
            // update
            CoroutineHandler.Tick(dt);
            Raylib.UpdateCamera(ref camera, CameraMode.Orbital);
            if (state == State.Vis) 
            {
                if (shouldAdvance)
                {
                    (int t1, int t2) = AdvanceAlgorithm();
                    if (t1 >= 0 && t2 >= 0) 
                    {
                        idx1 = t1;
                        idx2 = t2;
                        shouldAdvance = false;
                    }
                }
            }

            if (state == State.Init && Raylib.IsKeyPressed(KeyboardKey.Space))
            {
                if (!InitCoroStarted)
                {
                    CoroutineHandler.Start(Init2DSpace());
                    InitCoroStarted = true;
                }
            }
            else if (state == State.End)
            {
                if (!EndCoroStarted)
                {
                    CoroutineHandler.Start(DoNothing());
                    EndCoroStarted = true;
                }
            }
            else if (state == State.Cleanup)
            {
                goto cleanup;
            }

            // Draw
            Raylib.BeginDrawing();

                Raylib.ClearBackground(Color.LightGray);

                Raylib.BeginTextureMode(left);
                    Raylib.ClearBackground(Color.LightGray);
                    Raylib.DrawRectangle(0, 0, TitleLabelHeight, TitleLabelWidth, Color.DarkGray);
                    text = "Top-Down";
                    fontsize = 24;
                    Raylib.DrawText(text, 15, 20, fontsize, Color.LightGray);
                    if (state == State.Vis) 
                    {
                        DrawBoxes(-1);
                        DrawConnections(connectedPairs);
                        Raylib.DrawLineEx(new Vector2(boxes[idx1].X + BoxDimensionHalf,
                                          boxes[idx1].Y + BoxDimensionHalf),
                                          new Vector2(end.X,
                                          end.Y),
                                          4.0f, Color.Yellow);

                    } else if (state == State.Init)
                    {
                        DrawBoxes(InitCount);
                    } else if (state == State.End)
                    {
                        DrawBoxes(-1);
                        DrawConnections(connectedPairs);
                    }
                Raylib.EndTextureMode();

                Raylib.BeginTextureMode(topR);
                    Raylib.ClearBackground(Color.LightGray);
                    Raylib.DrawRectangle(0, 0, TitleLabelHeight+150, TitleLabelWidth, Color.DarkGray);
                    text = "Circuits Ranked by size";
                    fontsize = 24;
                    Raylib.DrawText(text, 25, 20, fontsize, Color.LightGray);
                        RenderCircuits(bottomR.Texture.Width, bottomR.Texture.Height, TitleLabelWidth);
                Raylib.EndTextureMode();

                Raylib.BeginTextureMode(bottomR);
                    Raylib.ClearBackground(Color.LightGray);
                    Raylib.DrawRectangle(0, 0, TitleLabelHeight, TitleLabelWidth, Color.DarkGray);
                    text = "Perspective";
                    fontsize = 24;
                    Raylib.DrawText(text, 25, 20, fontsize, Color.LightGray);
                    Raylib.BeginMode3D(camera);
                        Raylib.DrawText(text, 15, 20, fontsize, Color.LightGray);
                        DrawBoxes3D();
                        DrawConnections3D(connectedPairs);
                        if (state == State.Vis)
                        {
                            Raylib.DrawCylinderEx(new Vector3(boxes[idx1].X, boxes[idx1].Y + 250, boxes[idx1].Z),
                                                  new Vector3(end3D.X, end3D.Y + 250, end3D.Z), 10.0f,
                                                  10.0f, 10, Color.Yellow);
                        }
                    Raylib.EndMode3D();
                Raylib.EndTextureMode();

                Raylib.DrawTextureRec(left.Texture, new Rectangle( 0, 0, left.Texture.Width,
                                    -left.Texture.Height), new Vector2( 0, 0 ), Color.White);

                Raylib.DrawTextureRec(topR.Texture, new Rectangle( 0, 0, topR.Texture.Width,
                                    -topR.Texture.Height), new Vector2( left.Texture.Width, 0 ), Color.White);

                Raylib.DrawTextureRec(bottomR.Texture, new Rectangle( 0, 0, bottomR.Texture.Width,
                                    -bottomR.Texture.Height), new Vector2( left.Texture.Width, topR.Texture.Height ), Color.White);

                // Draw UI padding in between panels
                Raylib.DrawRectangle(left.Texture.Width, 0, 10, ScreenHeight, Color.Black);
                Raylib.DrawRectangle(left.Texture.Width, topR.Texture.Height-5, topR.Texture.Width-10, 10, Color.Black);



            Raylib.EndDrawing();
        }

        cleanup:
            Raylib.UnloadSound(PopSound);
            Raylib.UnloadSound(ElecSound);

            Raylib.CloseWindow();
    }
}