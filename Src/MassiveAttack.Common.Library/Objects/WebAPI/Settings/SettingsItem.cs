using System;
using System.Linq;
using System.Reflection;

using MassiveAttack.Common.Library.Enums;

namespace MassiveAttack.Common.Library.Objects.WebAPI.Settings
{
    public class SettingsItem
    {
        public int XRes { get; set; }

        public int YRes { get; set; }

        public int BPP { get; set; }

        public TEXTURE_DETAIL TextureDetail { get; set; }

        public uint DeviceID { get; set; }

        public string ToSettingFileFormat()
        {
            var fields = GetType().GetRuntimeProperties();

            return fields.Aggregate("", (current, field) => current + $"{field.Name.ToUpper()} {field.GetValue(this)}{System.Environment.NewLine}");
        }
    }
}