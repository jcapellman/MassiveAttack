using System.Collections.ObjectModel;
using System.IO;
using System.Reflection;

using MassiveAttack.Windows.Objects;

namespace MassiveAttack.Windows.ViewModels {
    public class MainWindowViewModel : BaseViewModel
    {
        private ObservableCollection<MenuSelectionItem> _menuItems;

        public ObservableCollection<MenuSelectionItem> MenuItems
        {
            get { return _menuItems; }
            set { _menuItems = value; OnPropertyChanged(); }
        }
 
        private string _versionText;

        public string VersionText
        {
            get { return _versionText; }
            set { _versionText = value; OnPropertyChanged(); }
        }

        public MainWindowViewModel()
        {
            MenuItems = new ObservableCollection<MenuSelectionItem>
            {
                new MenuSelectionItem
                {
                    MenuText = "PLAY",
                    PageType = typeof (GameWindow)
                },
                new MenuSelectionItem
                {
                    MenuText = "SETTINGS",
                    PageType = typeof (GameWindow)
                },
                new MenuSelectionItem
                {
                    MenuText = "QUIT",
                    PageType = typeof (GameWindow)
                }
            };
            
            var assemblyVersion = Assembly.GetExecutingAssembly().GetName().Version;
            var assembly = System.Reflection.Assembly.GetExecutingAssembly();

            var fileInfo = new FileInfo(assembly.Location);

            var fileCreateDate = fileInfo.CreationTime.Date;

            VersionText =
                $"Version {assemblyVersion.Major}.{assemblyVersion.MinorRevision} (BUILD {assemblyVersion.Build}) - {fileCreateDate.Month}/{fileCreateDate.Day}/{fileCreateDate.Year}";
        }
    }
}