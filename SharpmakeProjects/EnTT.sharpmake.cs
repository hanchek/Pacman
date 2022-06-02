using System.IO;

using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]

[Generate]
public class EnTT : BaseProject
{
    public EnTT() : base()
    {
        //The directory that contains the source code that we want include to the project
        SourceRootPath = Path.Combine(LibRootPath, "src");

        AddTargets(MyOptions.GetCommonTarget());
    }

    public override void ConfigureAll(Project.Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.Output = Configuration.OutputType.None;

        conf.IncludePaths.Add(Path.Combine(LibRootPath, "src"));
    }

    private string LibRootPath
    {
        get { return Path.Combine(MyOptions.ExternPath, "entt"); }
    }
}
