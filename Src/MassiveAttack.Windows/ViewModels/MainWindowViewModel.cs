using System.IO;
using System.Reflection;

namespace MassiveAttack.Windows.ViewModels {
    public class MainWindowViewModel : BaseViewModel
    {
        private string _versionText;

        public string VersionText
        {
            get { return _versionText; }
            set { _versionText = value; OnPropertyChanged(); }
        }

        public MainWindowViewModel()
        {
            var assemblyVersion = Assembly.GetExecutingAssembly().GetName().Version;
            var assembly = System.Reflection.Assembly.GetExecutingAssembly();

            var fileInfo = new FileInfo(assembly.Location);

            var fileCreateDate = fileInfo.CreationTime.Date;

            VersionText =
                $"Version {assemblyVersion.Major}.{assemblyVersion.MinorRevision} (BUILD {assemblyVersion.Build}) - {fileCreateDate.Month}/{fileCreateDate.Day}/{fileCreateDate.Year}";
        }
    }
}