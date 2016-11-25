using MassiveAttack.Common.Library.Objects.WebAPI.Internal;

using Microsoft.AspNetCore.Mvc;

namespace MassiveAttack.WebAPI.Controllers {
    [Route("api/[controller]")]
    public class BaseController : Controller {
        public ControllerHandlerItem ControllerHandlerItem { get; set; }
    }
}