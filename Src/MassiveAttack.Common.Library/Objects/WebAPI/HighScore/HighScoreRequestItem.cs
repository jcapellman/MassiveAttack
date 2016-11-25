using System;

namespace MassiveAttack.Common.Library.Objects.WebAPI.HighScore {
    public class HighScoreRequestItem {
        public Guid PlayerGUID { get; set; }

        public Guid LevelGUID { get; set; }

        public int Score { get; set; }
    }
}