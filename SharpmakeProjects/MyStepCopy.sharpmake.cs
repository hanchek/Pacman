using Sharpmake;

// New copy build step that support recursive copy

public class MyStepCopy : Project.Configuration.BuildStepCopy
{
    public MyStepCopy(Project.Configuration.BuildStepCopy copy) : base(copy) { }

    public override string GetCopyCommand(string workingPath, EnvironmentVariableResolver resolver)
    {
        string sourceRelativePath = Util.PathGetRelative(workingPath, resolver.Resolve(SourcePath));
        string destinationRelativePath = Util.PathGetRelative(workingPath, resolver.Resolve(DestinationPath));

        string commandParameters = string.Join(" ",
            "/xo",  // /XO :: eXclude Older files.

            // logging options
            "/ns",  // /NS :: No Size - don't log file sizes.
            "/nc",  // /NC :: No Class - don't log file classes.
            "/np",  // /NP :: No Progress - don't display percentage copied.
            "/njh", // /NJH :: No Job Header.
                    //"/njs", // /NJS :: No Job Summary.
            "/ndl", // /NDL :: No Directory List - don't log directory names.
            "/nfl" // /NFL :: No File List - don't log file names.
            );

        if (IsRecurse)
        {
            commandParameters += " /e"; // /E: Copies subdirectories (includes empty directories)
            //commandParameters += " /s"; // /S: Copies subdirectories (excludes empty directories)
        }

        return string.Join(" ",
            "robocopy.exe",
            commandParameters,

            "\"" + sourceRelativePath + "\"",
            "\"" + destinationRelativePath + "\"",
            "\"" + CopyPattern + "\"",

            "> nul", // direct all remaining stdout to nul

            // Error handling: any value greater than 7 indicates that there was at least one failure during the copy operation.
            // The type nul is used to clear the errorlevel to 0
            // see https://ss64.com/nt/robocopy-exit.html for more info
            "& if %ERRORLEVEL% GEQ 8 (echo Copy failed & exit 1) else (type nul>nul)"
        );
    }
}
