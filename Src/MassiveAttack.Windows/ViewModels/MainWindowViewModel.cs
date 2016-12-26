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

        private bool _isConnected;

        public bool IsConnected
        {
            get { return _isConnected; }
            set { _isConnected = value; OnPropertyChanged(); }
        }

        private string _networkStatus;

        public string NetworkStatus
        {
            get { return _networkStatus; }
            set { _networkStatus = value; OnPropertyChanged(); }
        }

        public MainWindowViewModel()
        {
            App.NetworkChanged += App_NetworkChanged;

            MenuItems = new ObservableCollection<MenuSelectionItem>
            {
                new MenuSelectionItem
                {
                    MenuText = "PLAY",
                    WindowInstance = new GameWindow()
                },
                new MenuSelectionItem
                {
                    MenuText = "SETTINGS",
                    WindowInstance = new SettingsWindow()
                },
                new MenuSelectionItem
                {
                    MenuText = "QUIT",
                    WindowInstance = null
                }
            };
            
            var assemblyVersion = Assembly.GetExecutingAssembly().GetName().Version;
            var assembly = System.Reflection.Assembly.GetExecutingAssembly();

            var fileInfo = new FileInfo(assembly.Location);

            var fileCreateDate = fileInfo.CreationTime.Date;

            VersionText =
                $"Version {assemblyVersion.Major}.{assemblyVersion.MinorRevision} (BUILD {assemblyVersion.Build}) - {fileCreateDate.Month}/{fileCreateDate.Day}/{fileCreateDate.Year}";
        }

        private void App_NetworkChanged(object sender, MassiveAttack.Common.Library.PlatformAbstractions.Objects.NetworkCheckEventArgs e)
        {
            NetworkStatus = e.HasConnection ? "Service connected" : "Network or Service Unavailable";

            IsConnected = e.HasConnection;
        }
    }
}