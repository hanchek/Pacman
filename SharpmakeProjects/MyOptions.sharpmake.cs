using System.IO;

using Sharpmake;

public static class MyOptions
{
    public static string RootPath = Util.PathMakeStandard(Path.GetFullPath(
        Path.Combine(Util.GetCurrentSharpmakeFileInfo().DirectoryName, "..")));

    public static string ExternPath = Path.Combine(RootPath, "Extern");

    public static string DataPath = Path.Combine(RootPath, "Data");

    public static string BuildPath = Path.Combine(RootPath, ".build");

    public static Target GetCommonTarget(OutputType outputType = OutputType.Lib)
    {
        return new Target(Platform.win64, DevEnv.vs2019, Optimization.Debug | Optimization.Release, outputType);
    }

    public static string GetTargetPath(Target target)
    {
        return Path.Combine(BuildPath,
            string.Format("{0}_{1}", "[target.Platform]", "[target.Optimization]"));
    }

    public static string GetTargetDataPath(Target target)
    {
        return Path.Combine(GetTargetPath(target), "Data");
    }

    public static string GetIntermediatePath(Target target)
    {
        return Path.Combine(
            "obj",
            "[project.Name]",
            "[target.Optimization]");
    }
}

