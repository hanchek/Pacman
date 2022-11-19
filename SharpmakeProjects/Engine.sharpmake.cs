using System.IO;

using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]
[module: Sharpmake.Include("SFML.sharpmake.cs")]
[module: Sharpmake.Include("EnTT.sharpmake.cs")]

[Generate]
public class Engine : BaseProject
{
    public Engine() : base()
    {
        //The directory that contains the source code that we want include to the project
        SourceRootPath = Path.Combine(MyOptions.RootPath, "Engine");

        AddTargets(MyOptions.GetCommonTarget());
    }

    public override void ConfigureAll(Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.Output = Configuration.OutputType.Lib;

        conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);

        conf.IncludePaths.Add(SourceRootPath);

        // For inherited properties such as include paths and library paths,
        // Sharpmake provides the option to choose between public and private dependencies.
        // Private dependencies are not propagated to dependent projects
        conf.AddPublicDependency<SFML>(target);
        conf.AddPublicDependency<EnTT>(target);

        conf.PrecompHeader = "pch.h";
        conf.PrecompSource = "pch.cpp";
    }
}
