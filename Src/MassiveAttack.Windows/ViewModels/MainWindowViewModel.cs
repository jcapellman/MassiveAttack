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
            MenuItems = new ObservableCollection<MenuSelectionItem>();

            MenuItems.Add(new MenuSelectionItem
            {
                MenuText = "Play",
                PageType = typeof (GameWindow)
            });

            MenuItems.Add(new MenuSelectionItem
            {
                MenuText = "Settings",
                PageType = typeof(GameWindow)
            });

            MenuItems.Add(new MenuSelectionItem
            {
                MenuText = "Quit",
                PageType = typeof(GameWindow)
            });

            var assemblyVersion = Assembly.GetExecutingAssembly().GetName().Version;
            var assembly = System.Reflection.Assembly.GetExecutingAssembly();

            var fileInfo = new FileInfo(assembly.Location);

            var fileCreateDate = fileInfo.CreationTime.Date;

            VersionText =
                $"Version {assemblyVersion.Major}.{assemblyVersion.MinorRevision} (BUILD {assemblyVersion.Build}) - {fileCreateDate.Month}/{fileCreateDate.Day}/{fileCreateDate.Year}";
        }
    }
}