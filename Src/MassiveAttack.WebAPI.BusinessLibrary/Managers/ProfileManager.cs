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
                var rResult = await GetRedisObject<ProfileResponseItem>(PlayerGUID);

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

                await WriteRedisObject(PlayerGUID, response);

                return new ReturnSet<ProfileResponseItem>(response);                
            }
        }

        public override string GetRedisPrefix() => "PROFILE";
    }
}