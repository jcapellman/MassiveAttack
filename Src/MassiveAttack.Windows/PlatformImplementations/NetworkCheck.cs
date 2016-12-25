using System;

using MassiveAttack.Common.Library.PlatformAbstractions;
using MassiveAttack.Common.Library.PlatformAbstractions.Objects;

namespace MassiveAttack.Windows.PlatformImplementations
{
    public class NetworkCheck : INetworkCheck
    {
        public void OnNetworkChanged(NetworkCheckEventArgs e)
        {
            var handler = NetworkCheckEvent;

            handler?.Invoke(this, e);
        }

        public EventHandler<NetworkCheckEventArgs> NetworkCheckEvent { get; set; }

        EventHandler<NetworkCheckEventArgs> INetworkCheck.NetworkCheckEvent { get; set; }

        private bool _isConnected;

        public bool IsConnected() => _isConnected;
    
        public void StartCheck()
        {
            System.Net.NetworkInformation.NetworkChange.NetworkAvailabilityChanged += (sender, args) =>
            {
                OnNetworkChanged(new NetworkCheckEventArgs
                {
                    HasConnection = args.IsAvailable
                });

                _isConnected = args.IsAvailable;
            };

        }
    }
}