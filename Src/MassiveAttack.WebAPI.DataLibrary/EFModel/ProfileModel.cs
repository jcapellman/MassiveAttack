using MassiveAttack.WebAPI.DataLibrary.Objects.Profile;

using Microsoft.EntityFrameworkCore;

namespace MassiveAttack.WebAPI.DataLibrary.EFModel {
    public class ProfileModel : EntityModel {
        public ProfileModel(string connectionString) : base(connectionString) { }

        public DbSet<Profiles> Profiles { get; set; }
    }
}