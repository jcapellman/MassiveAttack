using System;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.PlatformAbstractions;
using MassiveAttack.Common.Library.PlatformAbstractions.Objects;
using MassiveAttack.Common.Library.WebAPIHandlers;

namespace MassiveAttack.Windows.PlatformImplementations
{
    public class NetworkCheck : INetworkCheck
    {
        private HandlerConstructorItem _wrapper;

        public NetworkCheck(HandlerConstructorItem wrapper)
        {
            _wrapper = wrapper;
        }

        public event EventHandler<NetworkCheckEventArgs> NetworkCheckEvent;
        
        private bool _isConnected;

        public bool IsConnected() => _isConnected;
    
        public void StartCheck()
        {
            NetworkCheckEvent += NetworkCheck_NetworkCheckEvent;
            System.Net.NetworkInformation.NetworkChange.NetworkAvailabilityChanged += NetworkChange_NetworkAvailabilityChanged;

            NetworkChange_NetworkAvailabilityChanged(null, null);
        }

        private void NetworkCheck_NetworkCheckEvent(object sender, NetworkCheckEventArgs e)
        {
            
        }

        private async void NetworkChange_NetworkAvailabilityChanged(object sender, System.Net.NetworkInformation.NetworkAvailabilityEventArgs e)
        {
            bool hasConnection;

            try {
                var pingbackHandler = new PingBackHandler(_wrapper);

                var response = await pingbackHandler.CheckServiceStatus();

                hasConnection = response;
            }
            catch (Exception)
            {
                hasConnection = false;
            }

            NetworkCheck_NetworkCheckEvent(this, new NetworkCheckEventArgs
            {
                HasConnection = hasConnection
            });

            _isConnected = hasConnection;
        }
    }
}