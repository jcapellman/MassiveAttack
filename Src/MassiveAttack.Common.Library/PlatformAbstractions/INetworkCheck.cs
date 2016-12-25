using System;
using System.Security.Cryptography.X509Certificates;
using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.PlatformAbstractions.Objects;

namespace MassiveAttack.Common.Library.PlatformAbstractions
{
    public interface INetworkCheck
    {
        EventHandler<NetworkCheckEventArgs> NetworkCheckEvent { get; set; }

        bool IsConnected();

        void StartCheck();
    }
}