using MassiveAttack.Common.Library.Enums;
using MassiveAttack.Common.Library.PlatformAbstractions;

namespace MassiveAttack.Common.Library.Objects.Common
{
    public class HandlerConstructorItem
    {
        public PLATFORMS CurrentPlatfrom { get; set; }

        public string WebAPIService { get; set; }

        public string Token { get; set; }

        public bool IsConnected { get; set; }

        public BaseFileIO FileIO { get; set; }
    }
}