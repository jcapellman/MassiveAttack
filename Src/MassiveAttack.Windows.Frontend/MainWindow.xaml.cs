using System.Windows;
using System.Windows.Controls;

using MassiveAttack.Windows.Frontend.Objects;

namespace MassiveAttack.Windows.Frontend {
    public partial class MainWindow : BaseWindow {
        public MainWindow() {
            InitializeComponent();
        }

        private void lvMain_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var selectedItem = ((sender as ListView).SelectedItem);

            if (selectedItem == null)
            {
                return;
            }

            var item = (MenuSelectionItem)selectedItem;

            if (!item.IsEnabled)
            {
                return;
            }

            if (item.WindowInstance == null)
            {
                Application.Current.Shutdown();

                return;
            }
            
            Visibility = Visibility.Hidden;

            item.WindowInstance.IsVisibleChanged += WindowInstance_IsVisibleChanged;
            item.WindowInstance.Show();

            (sender as ListView).SelectedItem = null;
        }

        private void WindowInstance_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            this.Visibility = ((bool)e.NewValue ? Visibility.Hidden : Visibility.Visible);
        }
    }
}