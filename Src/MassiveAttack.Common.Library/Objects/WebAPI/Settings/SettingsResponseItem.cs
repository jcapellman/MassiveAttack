using System.Runtime.Serialization;

using MassiveAttack.Common.Library.Enums;

namespace MassiveAttack.Common.Library.Objects.WebAPI.Settings
{
    [DataContract]
    public class SettingsResponseItem
    {
        [DataMember]
        public int ResolutionX { get; set; }

        [DataMember]
        public int ResolutionY { get; set; }

        [DataMember]
        public int BPP { get; set; }

        [DataMember]
        public TEXTURE_DETAIL TextureDetail { get; set; }
    }
}