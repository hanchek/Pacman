using Sharpmake;

[module: Sharpmake.Include("MyOptions.sharpmake.cs")]
[module: Sharpmake.Include("Game.sharpmake.cs")]

// Represents the solution that will be generated
[Generate]
public class BomberManSolution : Solution
{
    public BomberManSolution()
    {
        Name = "BomberMan";

        AddTargets(MyOptions.GetCommonTarget());
    }

    [Configure]
    public void ConfigureAll(Solution.Configuration conf, Target target)
    {
        // Puts the generated solution in the root folder
        conf.SolutionPath = MyOptions.RootPath;

        // Adds the project into the solution.
        // Note that this is done in the configuration, so you can generate
        // solutions that contain different projects based on their target.
        //
        // You could, for example, exclude a project that only supports 64-bit
        // from the 32-bit targets.
        conf.AddProject<Game>(target);
    }
}

