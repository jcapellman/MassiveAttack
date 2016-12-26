using System;
using System.Net;
using System.Net.Http;
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

        public void OnNetworkChanged(NetworkCheckEventArgs e)
        {
            var handler = NetworkCheckEvent;

            handler?.Invoke(this, e);
        }
        
        public EventHandler<NetworkCheckEventArgs> NetworkCheckEvent { get; set; }
        
        private bool _isConnected;

        public bool IsConnected() => _isConnected;
    
        public void StartCheck()
        {
            System.Net.NetworkInformation.NetworkChange.NetworkAvailabilityChanged += NetworkChange_NetworkAvailabilityChanged;

            NetworkChange_NetworkAvailabilityChanged(null, null);
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

            OnNetworkChanged(new NetworkCheckEventArgs
            {
                HasConnection = hasConnection
            });

            _isConnected = hasConnection;
        }
    }
}