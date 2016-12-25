using System.Windows;

using MassiveAttack.Windows.PlatformImplementations;

using Vulkan;

namespace MassiveAttack.Windows
{
    public partial class App
    {
        public static Instance instance;

        public static NetworkCheck NetworkCheck { get; set; }

        public App()
        {
            NetworkCheck.StartCheck();
        }
    }
}