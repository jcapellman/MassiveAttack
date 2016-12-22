using MassiveAttack.Common.Library.Enums;

namespace MassiveAttack.Common.Library.Objects.WebAPI.Settings
{
    public class SettingsResponseItem
    {
        public int ResolutionX { get; set; }

        public int ResolutionY { get; set; }

        public int BPP { get; set; }

        public TEXTURE_DETAIL TextureDetail { get; set; }
    }
}