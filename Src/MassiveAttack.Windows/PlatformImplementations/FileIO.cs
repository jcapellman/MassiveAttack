using System.Reflection;

using MassiveAttack.Common.Library.PlatformAbstractions;

namespace MassiveAttack.Windows.PlatformImplementations
{
    public class FileIO : BaseFileIO
    {
        protected override string GetRootDirectory() => System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
    }
}