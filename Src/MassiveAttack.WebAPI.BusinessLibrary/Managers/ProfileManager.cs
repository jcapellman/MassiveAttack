using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Internal;
using MassiveAttack.Common.Library.Objects.WebAPI.Profiles;
using MassiveAttack.WebAPI.DataLibrary.EFModel;

using Microsoft.EntityFrameworkCore;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class ProfileManager : BaseManager {
        public ProfileManager(ControllerHandlerItem controllerHandlerItem) : base(controllerHandlerItem) { }

        public async Task<ReturnSet<ProfileResponseItem>> GetProfile(Guid PlayerGUID) {
            using (var profileModel = new ProfileModel(SQLServerConnectionString)) {
                var result = await profileModel.Profiles.FirstOrDefaultAsync(a => a.PlayerGUID == PlayerGUID);

                if (result == null) {
                    throw new Exception($"PlayerGUID ({PlayerGUID} is null");
                }

                var response = new ProfileResponseItem {
                    Alias = result.Alias
                };

                return new ReturnSet<ProfileResponseItem>(response);
            }
        }
    }
}