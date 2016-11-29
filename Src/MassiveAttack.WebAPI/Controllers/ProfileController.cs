using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Profiles;

using MassiveAttack.WebAPI.BusinessLibrary.Managers;

namespace MassiveAttack.WebAPI.Controllers {
    public class ProfileController : BaseController {
        public async Task<ReturnSet<ProfileResponseItem>> GET(Guid PlayerGUID)
            => await new ProfileManager(ControllerHandlerItem).GetProfile(PlayerGUID);
    }
}