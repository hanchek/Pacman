using Sharpmake;

[module: Sharpmake.Include("BomberManSolution.sharpmake.cs")]

public static class Main
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Arguments arguments)
    {
        arguments.Generate<BomberManSolution>();
    }
}
