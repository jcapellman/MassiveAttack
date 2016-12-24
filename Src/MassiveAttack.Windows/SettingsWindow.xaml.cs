using System.Windows;
using MassiveAttack.Windows.ViewModels;

namespace MassiveAttack.Windows
{
    public partial class SettingsWindow : Window
    {
        private SettingsViewModel viewModel => (SettingsViewModel) DataContext;

        public SettingsWindow()
        {
            InitializeComponent();

            DataContext = new SettingsViewModel();

            Loaded += SettingsWindow_Loaded;
        }

        private void SettingsWindow_Loaded(object sender, RoutedEventArgs e)
        {
            viewModel.InitializeSettings();
        }

        private void btnCancel_OnClick(object sender, RoutedEventArgs e)
        {
            Visibility = Visibility.Hidden;
        }
    }
}