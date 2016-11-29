using System;

namespace MassiveAttack.WebAPI.DataLibrary.Objects.Profile {
    public class Profiles : BaseObject {
        public string Alias { get; set; }

        public Guid PlayerGUID { get; set; }

        public int Level { get; set; }
    }
}