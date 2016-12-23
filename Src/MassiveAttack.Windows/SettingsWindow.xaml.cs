using System.Windows;

namespace MassiveAttack.Windows
{
    public partial class SettingsWindow : Window
    {
        public SettingsWindow()
        {
            InitializeComponent();
        }

        private void btnCancel_OnClick(object sender, RoutedEventArgs e)
        {
            Visibility = Visibility.Hidden;
        }
    }
}