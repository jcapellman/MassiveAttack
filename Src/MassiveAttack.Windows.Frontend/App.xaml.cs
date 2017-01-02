using MassiveAttack.Common.Library.Enums;
using MassiveAttack.Common.Library.Objects.Common;

using MassiveAttack.Windows.Frontend.PlatformImplementations;

namespace MassiveAttack.Windows.Frontend
{
    public partial class App
    {
        public static NetworkCheck NetworkCheck { get; set; }

        public static HandlerConstructorItem HandlerWrapper { get; set; }

        public delegate void NetworkCheckEventHandler(bool isConnected);
        public static event NetworkCheckEventHandler NetworkChanged;

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
                IsConnected = false,
                FileIO = new FileIO()
            };
            
            NetworkCheck = new NetworkCheck(HandlerWrapper);

            NetworkCheck.NetworkCheckEvent += NetworkCheck_NetworkCheckEvent; ;
            NetworkCheck.StartCheck();
        }
        
        private static void NetworkCheck_NetworkCheckEvent(bool isConnected)
        {
            HandlerWrapper.IsConnected = isConnected;

            NetworkChanged?.Invoke(isConnected);
        }
    }
}