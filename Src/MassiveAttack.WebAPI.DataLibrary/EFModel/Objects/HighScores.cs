using System;
using System.ComponentModel.DataAnnotations;

namespace MassiveAttack.WebAPI.DataLibrary.EFModel.Objects {
    public class HighScores : BaseObject {
        [Required]
        public Guid PlayerGUID { get; set; }

        [Required]
        public Guid LevelGUID { get; set; }

        [Required]
        public int Score { get; set; }
    }
}