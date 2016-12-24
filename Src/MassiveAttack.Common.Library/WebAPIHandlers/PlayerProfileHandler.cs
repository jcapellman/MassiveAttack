using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Profiles;

namespace MassiveAttack.Common.Library.WebAPIHandlers {
    public class PlayerProfileHandler : BaseWebAPIHandler {
        public PlayerProfileHandler(HandlerConstructorItem constructorItem) : base(constructorItem) { }

        public async Task<ReturnSet<ProfileResponseItem>> GetProfile(Guid playerGUID)
            => await GetAsync<ReturnSet<ProfileResponseItem>>($"Profile?PlayerGUID={playerGUID}");
    }
}