using System;
using MassiveAttack.Common.Library.Enums;
using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.PlatformAbstractions.Objects;
using MassiveAttack.Windows.PlatformImplementations;

using Vulkan;

namespace MassiveAttack.Windows
{
    public partial class App
    {
        public static Instance instance;

        public static NetworkCheck NetworkCheck { get; set; }

        public static HandlerConstructorItem HandlerWrapper { get; set; }

        public App()
        {
            InitWrapper();
        }
        
        private static void InitWrapper()
        {
            HandlerWrapper = new HandlerConstructorItem
            {
                Token = string.Empty,
                WebAPIService = MassiveAttack.Common.Library.Common.Constants.WEBSERVICE_URL,
                CurrentPlatfrom = PLATFORMS.WINDOWS,
                IsConnected = false
            };

            NetworkChanged += OnNetworkChanged;

            NetworkCheck = new NetworkCheck(HandlerWrapper);

            NetworkCheck.NetworkCheckEvent += NetworkCheckEvent;
            NetworkCheck.StartCheck();
        }

        private static void OnNetworkChanged(object sender, NetworkCheckEventArgs networkCheckEventArgs)
        {
            var handler = NetworkChanged;

            handler?.Invoke(null, networkCheckEventArgs);
        }

        public static event EventHandler<NetworkCheckEventArgs> NetworkChanged;

        private static void NetworkCheckEvent(object sender, NetworkCheckEventArgs networkCheckEventArgs)
        {
            HandlerWrapper.IsConnected = networkCheckEventArgs.HasConnection;

        //    OnNetworkChanged(sender, networkCheckEventArgs);
        }
    }
}