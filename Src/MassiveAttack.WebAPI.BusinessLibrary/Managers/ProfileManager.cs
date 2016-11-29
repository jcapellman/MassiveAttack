using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Internal;
using MassiveAttack.Common.Library.Objects.WebAPI.Profiles;

using MassiveAttack.WebAPI.DataLibrary.EFModel;
using MassiveAttack.WebAPI.DataLibrary.RModel;

using Microsoft.EntityFrameworkCore;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class ProfileManager : BaseManager {
        public ProfileManager(ControllerHandlerItem controllerHandlerItem) : base(controllerHandlerItem) { }

        private string R_KEY = "PROFILE_";

        public async Task<ReturnSet<ProfileResponseItem>> GetProfile(Guid PlayerGUID) {
            using (var profileModel = new ProfileModel(SQLServerConnectionString)) {
                using (var rModel = new RedisModel(RedisConnectionString)) {
                    var rResult = await rModel.Get<ProfileResponseItem>($"{R_KEY}{PlayerGUID}");

                    if (!rResult.HasError) {
                        return rResult;
                    }

                    var result = await profileModel.Profiles.FirstOrDefaultAsync(a => a.PlayerGUID == PlayerGUID);

                    if (result == null) {
                        throw new Exception($"PlayerGUID ({PlayerGUID} is null");
                    }

                    var response = new ProfileResponseItem {
                        Alias = result.Alias,
                        RegistrationDate = result.CreatedDate.DateTime
                    };

                    await rModel.Write($"{R_KEY}{PlayerGUID}", response);

                    return new ReturnSet<ProfileResponseItem>(response);
                }
            }
        }
    }
}