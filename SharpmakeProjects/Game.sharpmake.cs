using System.IO;

using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]
[module: Sharpmake.Include("SFML.sharpmake.cs")]
[module: Sharpmake.Include("MyStepCopy.sharpmake.cs")]

[Generate]
public class Game : BaseProject
{
    public Game() : base()
    {
        //The directory that contains the source code that we want include to the project
        SourceRootPath = Path.Combine(MyOptions.RootPath, "Game");

        AddTargets(MyOptions.GetCommonTarget());
    }

    public override void ConfigureAll(Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        // Specify where the generated project will be. Here we generate the
        // vcxproj in a /generated directory.
        conf.ProjectPath = @"[project.SharpmakeCsPath]/generated";

        conf.IncludePrivatePaths.Add(MyOptions.RootPath);

        conf.VcxprojUserFile = new Configuration.VcxprojUserFileSettings();
        conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = MyOptions.RootPath;

        conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
        conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);

        conf.AddPublicDependency<SFML>(target);
    }
}
