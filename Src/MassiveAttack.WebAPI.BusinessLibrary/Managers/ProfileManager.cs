using System;
using System.Threading.Tasks;

using MassiveAttack.Common.Library.Objects.Common;
using MassiveAttack.Common.Library.Objects.WebAPI.Internal;

namespace MassiveAttack.WebAPI.BusinessLibrary.Managers {
    public class ProfileManager : BaseManager {
        public ProfileManager(ControllerHandlerItem controllerHandlerItem) : base(controllerHandlerItem) { }

        public async Task<ReturnSet<string>> GetProfile(Guid PlayerGUID) {

        }
    }
}