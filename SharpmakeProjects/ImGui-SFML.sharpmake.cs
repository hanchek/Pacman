using System.IO;

using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]
[module: Sharpmake.Include("ImGui.sharpmake.cs")]
[module: Sharpmake.Include("SFML.sharpmake.cs")]

[Generate]
public class ImGui_SFML : BaseProject
{
    public ImGui_SFML() : base()
    {
        SourceRootPath = LibRootPath;
        SourceFilesExcludeRegex.AddRange(new[]
        {
            @"[\\/]examples[\\/]",
        });

        AddTargets(MyOptions.GetCommonTarget());
    }

    public override void ConfigureAll(Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.Output = Configuration.OutputType.Lib;

        conf.AddPublicDependency<ImGui>(target);
        conf.AddPublicDependency<SFML>(target);

        conf.IncludePaths.Add(LibRootPath);

        conf.LibraryFiles.Add("opengl32");
    }

    public string LibRootPath
    {
        get { return Path.Combine(MyOptions.ExternPath, "imgui-sfml"); }
    }
}
