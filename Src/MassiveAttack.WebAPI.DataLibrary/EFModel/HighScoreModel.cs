using MassiveAttack.WebAPI.DataLibrary.EFModel.Objects;

using Microsoft.EntityFrameworkCore;

namespace MassiveAttack.WebAPI.DataLibrary.EFModel {
    public class HighScoreModel : EntityModel {
        public DbSet<HighScores> HighScore { get; set; }
         
        public HighScoreModel(string connectionString) : base(connectionString) { }
    }
}