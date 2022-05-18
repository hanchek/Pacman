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
        conf.TargetPath = MyOptions.GetTargetPath(target);
    }
}
