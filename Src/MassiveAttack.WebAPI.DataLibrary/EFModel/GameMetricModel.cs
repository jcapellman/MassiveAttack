using MassiveAttack.WebAPI.DataLibrary.Objects.GameMetrics;

using Microsoft.EntityFrameworkCore;

namespace MassiveAttack.WebAPI.DataLibrary.EFModel {
    public class GameMetricModel : EntityModel {
        public GameMetricModel(string connectionString) : base(connectionString) { }

        public DbSet<GameMetrics> GameMetrics { get; set; }
    }
}