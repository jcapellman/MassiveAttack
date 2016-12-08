using System;

using MassiveAttack.Common.Library.Enums;

using Microsoft.EntityFrameworkCore;

namespace MassiveAttack.WebAPI.DataLibrary.EFModel {
    public class EntityModel : DbContext {
        private readonly string _connectionString;
        
        public EntityModel(string connectionString) {
            _connectionString = connectionString;
        }
        
        public override int SaveChanges() {
            foreach (var item in ChangeTracker.Entries()) {
                if (item.State == EntityState.Deleted || item.State == EntityState.Modified || item.State == EntityState.Added) { 
                    item.Property("ModifiedDate").CurrentValue = DateTimeOffset.Now;
                }
                
                switch (item.State) {
                    case EntityState.Deleted:
                        item.Property("StatusID").CurrentValue = (int)Statuses.Deleted;
                        break;
                    case EntityState.Added:
                        item.Property("CreatedDate").CurrentValue = DateTimeOffset.Now;
                        item.Property("StatusID").CurrentValue = (int)Statuses.Active;
                        break;
                    case EntityState.Detached:
                    case EntityState.Unchanged:
                    case EntityState.Modified:
                        break;
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }

            return base.SaveChanges();
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer(_connectionString);
        }
    }
}