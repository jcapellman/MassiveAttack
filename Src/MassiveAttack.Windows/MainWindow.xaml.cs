
using System.Windows;
using MassiveAttack.Windows.Common;
using Vulkan;

using Vulkan.Windows;

namespace MassiveAttack.Windows {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();

            var hWnd = new System.Windows.Interop.WindowInteropHelper(this).EnsureHandle();

            var hInstance = System.Runtime.InteropServices.Marshal.GetHINSTANCE(typeof(App).Module);

            var instance = new Instance(new InstanceCreateInfo { EnabledExtensionNames = new string[] { "VK_KHR_surface", "VK_KHR_win32_surface" } });

            var surface = instance.CreateWin32SurfaceKHR(new Win32SurfaceCreateInfoKhr { Hwnd = hWnd, Hinstance = hInstance });



//            var inspector = new Inspector { AppendText = (string s) => { textBox.Text += s; }, Surface = surface };



            //inspector.Inspect();
        }

        private void BtnExit_OnClick(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}
