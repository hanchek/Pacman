using System.IO;

using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]

[Generate]
public class ImGui : BaseProject
{
    public ImGui(): base()
    {
        SourceRootPath = LibRootPath;
        SourceFilesExcludeRegex.AddRange(new[]
        {
            @"[\\/]backends[\\/]",
            @"[\\/]examples[\\/]",
            @"[\\/]misc[\\/]",
        });

        AddTargets(MyOptions.GetCommonTarget());
    }

    public override void ConfigureAll(Project.Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.Output = Configuration.OutputType.Lib;

        conf.IncludePaths.Add(LibRootPath);
    }

    public string LibRootPath
    {
        get { return Path.Combine(MyOptions.ExternPath, "imgui-1.89.1"); }
    }
}
