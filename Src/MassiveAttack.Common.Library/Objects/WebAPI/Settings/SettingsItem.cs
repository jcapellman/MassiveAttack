using MassiveAttack.Common.Library.Enums;

namespace MassiveAttack.Common.Library.Objects.WebAPI.Settings
{
    public class SettingsItem
    {
        public int ResolutionX { get; set; }

        public int ResolutionY { get; set; }

        public int BPP { get; set; }

        public TEXTURE_DETAIL TextureDetail { get; set; }

        public uint DeviceID { get; set; }
    }
}