using Sharpmake;

public abstract class BaseProject : Project
{
    protected BaseProject()
    {
        RootPath = MyOptions.RootPath;
    }

    [Configure]
    public virtual void ConfigureAll(Configuration conf, Target target)
    {
        /// Target path, where the output files will be compiled, ex: exe, dll, self, xex
        conf.TargetPath = MyOptions.GetTargetPath(target);

        // Specify where generated .vcxproj will be
        conf.ProjectPath = @"[project.SharpmakeCsPath]/generated";

        // Set the directory where the compiler will place the intermediate files.
        conf.IntermediatePath = MyOptions.GetIntermediatePath(target);

        conf.IncludePrivatePaths.Add(MyOptions.RootPath);

        conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
        //conf.Options.Add(Sharpmake.Options.Vc.Compiler.RTTI.Disable);
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
        conf.Options.Add(Sharpmake.Options.Vc.Linker.GenerateDebugInformation.Enable);
        conf.Options.Add(Sharpmake.Options.Vc.Linker.GenerateFullProgramDatabaseFile.Enable);

        if (target.Optimization == Optimization.Debug)
        {
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.Disable);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.StringPooling.Disable);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Both);
        }
        else
        {
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.MaximizeSpeed);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.StringPooling.Enable);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Default);
        }
    }
}
