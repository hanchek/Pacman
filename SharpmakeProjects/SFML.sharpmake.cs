using System.IO;

using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]

[Sharpmake.Export]
public class SFML : BaseProject
{
    public SFML()
    {
        AddTargets(MyOptions.GetCommonTarget());
    }
    
    public override void ConfigureAll(Project.Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.ProjectPath = @"[project.SharpmakeCsPath]/generated";

        conf.IncludePaths.Add(Path.Combine(LibRootPath, "include"));

        conf.LibraryPaths.Add(Path.Combine(LibRootPath, "lib"));

        if (target.Optimization == Optimization.Debug)
        {

            conf.LibraryFiles.Add("sfml-system-d");
            conf.LibraryFiles.Add("sfml-graphics-d");
            conf.LibraryFiles.Add("sfml-window-d");

            conf.TargetCopyFiles.Add(Path.Combine(LibBinPath, "sfml-system-d-2.dll"));
            conf.TargetCopyFiles.Add(Path.Combine(LibBinPath, "sfml-graphics-d-2.dll"));
            conf.TargetCopyFiles.Add(Path.Combine(LibBinPath, "sfml-window-d-2.dll"));
        }
        else
        {

            conf.LibraryFiles.Add("sfml-system");
            conf.LibraryFiles.Add("sfml-graphics");
            conf.LibraryFiles.Add("sfml-window");

            conf.TargetCopyFiles.Add(Path.Combine(LibBinPath, "sfml-system-2.dll"));
            conf.TargetCopyFiles.Add(Path.Combine(LibBinPath, "sfml-graphics-2.dll"));
            conf.TargetCopyFiles.Add(Path.Combine(LibBinPath, "sfml-window-2.dll"));
        }
    }

    private string LibRootPath
    {
        get { return Path.Combine(MyOptions.ExternPath, "SFML-2.5.1"); }
    }

    private string LibBinPath
    {
        get { return Path.Combine(LibRootPath, "bin"); }
    }
}
