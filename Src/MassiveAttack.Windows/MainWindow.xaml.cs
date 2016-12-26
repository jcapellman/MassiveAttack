using System.Windows;
using System.Windows.Controls;

using MassiveAttack.Windows.Objects;

using Vulkan;

namespace MassiveAttack.Windows {
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();

            var hWnd = new System.Windows.Interop.WindowInteropHelper(this).EnsureHandle();

            var hInstance = System.Runtime.InteropServices.Marshal.GetHINSTANCE(typeof(App).Module);

            App.instance = new Instance(new InstanceCreateInfo { EnabledExtensionNames = new string[] { "VK_KHR_surface", "VK_KHR_win32_surface" } });
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