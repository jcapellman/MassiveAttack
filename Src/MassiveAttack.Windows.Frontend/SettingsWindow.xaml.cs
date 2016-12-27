using System.Windows;

using MassiveAttack.Windows.Frontend.ViewModels;

namespace MassiveAttack.Windows.Frontend
{
    public partial class SettingsWindow : BaseWindow
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

        private async void btnSave_OnClick(object sender, RoutedEventArgs e)
        {
            var result = await viewModel.SaveSettings();

            if (!result.HasError)
            {
                ShowMessagePopup(result.ExceptionThrown);

                return;
            }

            ShowMessagePopup("Settings saved successfully");
        }
    }
}