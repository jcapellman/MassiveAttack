using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;

namespace MassiveAttack.WebAPI.Controllers {
    public class ProfileController : BaseController {
        public async Task<ReturnSet<string>> GET(Guid PlayerGUID)
            => await ProfileManager(ControllerHandlerItem).GetProfile(PlayerGUID);
    }
}