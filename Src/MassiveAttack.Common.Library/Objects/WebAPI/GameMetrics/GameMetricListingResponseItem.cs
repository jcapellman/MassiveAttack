using System;

namespace MassiveAttack.Common.Library.Objects.WebAPI.GameMetrics {
    public class GameMetricListingResponseItem : BaseListingResponseItem {
        public string LevelName { get; set; }

        public DateTime DatePlayed { get; set; }

        public int BulletsFired { get; set; }

        public int DamageInflicted { get; set; }

        public double DurationInSeconds { get; set; }

        public bool Victorious { get; set; }
    }
}