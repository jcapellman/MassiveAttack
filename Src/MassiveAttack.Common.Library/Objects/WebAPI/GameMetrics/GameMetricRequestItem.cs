using System;

namespace MassiveAttack.Common.Library.Objects.WebAPI.GameMetrics {
    public class GameMetricRequestItem {
        public Guid LevelGUID { get; set; }

        public int DamagedTaken { get; set; }

        public int BulletsFired { get; set; }

        public int DamageInflicted { get; set; }

        public double DurationInSeconds { get; set; }

        public bool Victorious { get; set; }
    }
}