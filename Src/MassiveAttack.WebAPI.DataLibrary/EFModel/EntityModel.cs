using System;

using MassiveAttack.Common.Library.Enums;
using MassiveAttack.WebAPI.DataLibrary.RModel;
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
                }
            }
            
            return base.SaveChanges();
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder) {
            optionsBuilder.UseSqlServer(_connectionString);
        }
    }
}