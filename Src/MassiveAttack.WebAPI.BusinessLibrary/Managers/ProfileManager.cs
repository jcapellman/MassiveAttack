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

        public async Task<ReturnSet<bool>> UpdateProfile(ProfileUpdateRequestItem requestItem) {
            try {
                using (var profileModel = new ProfileModel(SQLServerConnectionString)) {
                    var existingModel = await profileModel.Profiles.FirstOrDefaultAsync(a => a.PlayerGUID == CurrentPlayerGUID);

                    if (existingModel == null) {
                        throw new Exception($"An existing Profile for {CurrentPlayerGUID} was not found");
                    }

                    existingModel.Alias = requestItem.Alias;

                    await profileModel.SaveChangesAsync();

                    var currentItem = await GetProfile(CurrentPlayerGUID);

                    currentItem.ObjectValue.Alias = requestItem.Alias;

                    await WriteRedisObject(CurrentPlayerGUID, currentItem);

                    return new ReturnSet<bool>(true);
                }
            } catch (Exception ex) {
                return new ReturnSet<bool>(ex);
            }
        }

        public override string GetRedisPrefix() => "PROFILE";
    }
}