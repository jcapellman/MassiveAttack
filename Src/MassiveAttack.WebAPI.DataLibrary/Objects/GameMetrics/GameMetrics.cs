using System;

namespace MassiveAttack.WebAPI.DataLibrary.Objects.GameMetrics {
    public class GameMetrics : BaseObject {
        public Guid LevelGUID { get; set; }

        public Guid PlayerGUID { get; set; }

        public int BulletsFired { get; set; }

        public int DamageInflicted { get; set; }

        public double DurationInSeconds { get; set; }

        public bool Victorious { get; set; }
    }
}